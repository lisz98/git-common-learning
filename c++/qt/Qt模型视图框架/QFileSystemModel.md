# QFileSystemModel

> 目录模型或文件系统模型

## 基本原理

* `QFileSystemModel`类继承自`QAbstractItemModel`,该类代替`QDirModel`类，是该类称为目录模型的原因
* `QFileSystemModel`类提供了一个本地文件系统的数据模型，该类提供了对本地文件系统的访问，比如可以重命名、删除文件或目录等，该类可以与合适的显示部件一起使用，通常与`QTreeView`一起使用，当然也可与其他视图使用
* `QFileSystemModel`类的数据来自于本地文件系统
* 在调用`setRootPath()`之前，`QFileSystemModel`不会获取任何文件或目录，这样可以避免在文件系统上的不必要查询。
* `QFileSystemModel`使用单独的线程来填充自己，因此在查询文件系统时不会导致主线程挂起

## 成员变量

```cpp
class Q_AUTOTEST_EXPORT QFileSystemModelPrivate : public QAbstractItemModelPrivate
{
public:
    enum { NumColumns =4 };

    class QFileSystemNode{  //文件系统节点
        QString fileName; //文件名称
#if defined(Q_OS_WIN)
        QString volumeName; //储存卷名称
#endif
        bool populatedChildren; //是否填充孩子
        bool isVisible; //是否有效
        QHash<QFileSystemModelNodePathKey,QFileSystemNode *> children; //孩子
        QList<QString> visibleChildren; //记录孩子是否有效
        int dirtyChildrenIndex; //Dirty Bit错误状态位索引
        QFileSystemNode *parent;   
        QExtendedInformation *info; //扩展信息
    };
            QDir rootDir;
#if QT_CONFIG(filesystemwatcher)        
    QFileInfoGatherer fileInfoGatherer; //信息采集者
#endif
    QTimer delayedSortTimer; //延时排序定时器
    bool forceSort; 
    int sortColum;
    Qt::SortOrder sortOrder;
    bool readOnly;
    bool setRootPath;
    QDir::Filters filters;
    QHash<const QFileSystemNode*, bool> bypassFilters; //是否开启节点的过滤器
    bool nameFilterDisables;
    bool disableRecursiveSort; //是否递归排序
#if QT_CONFIG(regularexpression)
    QStringList nameFilters;
#endif  
    QHash<QString, QString> resolvedSymLinks;
    QFileSystemNode root;
    QBasicTimer fetchingTimer; //抓取信息的定时器
    struct Fetching{
        QString dir;
        QString file;
        const QFileSystemNode *node;
    };
    QVector<Fetching> toFetch;
}

class QEXtenedInformation{
public:
    enum Type { Dir,File,System };
    QString displayRole;
    QIcon icon;
private:
    QFileInfo mFileInfo;
}

/*通过线程采集文件系统信息*/
class Q_AUTOTEST_EXPORT QFileInfoGatherer : public QThread{
private:
    mutable QMutex mutex;
    QWaitCondition condition;
    QStack<QString> path;
    QStack<QStringList> files;
    QAtomicInt abort;
#if QT_CONFIG(filesystemwatcher)
    QFileSystemWatcher *watcher;
#endif
    bool m_resolveSymlinks;
    QFileIconProvider *m_iconProvider;
    QFileIconProvider defaultProvider;
}
```

## 属性

```cpp
/*是否解析符号链接*/
Q_PROPERTY(bool resolveSymlinks READ resolveSymlinks WRITE setResolveSymlinks)
/*描述了是否为只读模式，即是否允许目录模型写入文件系统，若为false则支持重姓名、复制、删除文件和目录等操作*/
Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
/*描述是否隐藏由名称过滤器过滤掉的文件，默认为true,若文件未隐藏，将被显示未被禁用的状态(通常未灰色)*/
Q_PROPERTY(bool nameFilterDisables READ nameFilterDisables WRITE setNameFilterDisables)
```

## 信号

```cpp
/*当线程完成路径 path 的加载时，发送此信号。*/
void directoryLoaded(const QString &path);
/*当文件 oldName 被成功重命名为 newName 时，发送此信号*/
void fileRenamed(const QString &path,const QString &oldName,const QString &newName)
/*当根路径更改为 newPath 时，发送此信号*/
void rootPathChanged(const QString &newPath)
```

## 构造函数

```cpp
QFileSystemModel(QObject *parent =Q_NULLPTR)
   :QAbstractItemModel(*new QFileSystemModelPrivate,parent)
{
    Q_D(QFileSystemModel);
    d->init();
}

void QFileSystemModelPrivate::init(){
    Q_Q(QFileSystemModel);
    qRegisterMetaType<QVector<QPair<QString,QFileInfo>>>(); //注册元素
#if QT_CONFIG(filesystemwatcher)    //使用文件系统观察者来获取新的文件
    q->connect(&fileInfoGatherer, SIGNAL(newListOfFiles(QString,QStringList)),
               q, SLOT(_q_directoryChanged(QString,QStringList)));
    q->connect(&fileInfoGatherer, SIGNAL(updates(QString,QVector<QPair<QString,QFileInfo> >)),
            q, SLOT(_q_fileSystemChanged(QString,QVector<QPair<QString,QFileInfo> >)));
    q->connect(&fileInfoGatherer, SIGNAL(nameResolved(QString,QString)),
            q, SLOT(_q_resolvedName(QString,QString)));
    q->connect(&fileInfoGatherer, SIGNAL(directoryLoaded(QString)),
               q, SIGNAL(directoryLoaded(QString)));
#endif // filesystemwatcher
    q->connect(&delayedSortTimer, SIGNAL(timeout()), q, SLOT(_q_performDelayedSort()), Qt::QueuedConnection);

    roleNames.insertMulti(QFileSystemModel::FileIconRole, QByteArrayLiteral("fileIcon")); // == Qt::decoration
    roleNames.insert(QFileSystemModel::FilePathRole, QByteArrayLiteral("filePath"));
    roleNames.insert(QFileSystemModel::FileNameRole, QByteArrayLiteral("fileName"));
    roleNames.insert(QFileSystemModel::FilePermissions, QByteArrayLiteral("filePermissions"));
}
```

## 根目录函数

* 通过在模型上安装文件系统监视程序(QFileSystemWatcher)，将模型正在监视的目录
设置为 newPath，该目录中的任何文件和目录的更改都会反映到模型中，若路径被更
改，则发送 rootPathChanged()信号。
* 注意：该函数不会更改模型的结构或修改视图的数据，也就是说，模型的“根”不
会更改为仅包含文件系统中由 newPath 指定的目录内的文件和目录。
* 以上规则说明，无论该函数设置为何种目录，模型的根不会被更改(也没有可以更改
的函数)，对于 Windows 而言，模型的根是“我的电脑”(即直接显示电脑下的硬盘
分区)。另外，该函数的设置也不会影响视图的显示。
* setRootPath()函数的最终结果是，对文件系统模型的设置将只作用于由该函数指定的
目录及其子目录

```cpp
/*获取当前根目录*/
QDir rootDirectory() const;
QString rootPath() const;
/*设置当前根目录*/
QModelIndex setRootPath(const QString &newPath)
```

## 过滤器

```cpp
/*设置过滤器,默认为QDir::AllEntries|QDir::NoDotAndDotDot | QDir::AllDirs*/
void setFilter(QDir::Filters filters);
QDir::Filters filter() const;
/*用于设置和返回模型的名称过滤器列表,例如{"*.jpg","*.txt"}*/
void setNmaeFilters(const QStringList &filters);
QStringList nameFilters() const;
```

## 删除、创建

```cpp
/*使用QDir::mkdir创建*/
QModelIndex mkdir(const QModelIndex &parent,const QString &name)
/*该函数并不会把目录放置于可以恢复的位置(比如回收站)，而是直接删除*/
bool rmdir(const QModelIndex &index);
bool remove(const QModelIndex &index);
```

## 获取信息

```cpp
/*获取索引 index 所指项目的图标、QFileInfo(文件信息)、文件名、路径*/
QIcon fileIcon(const QModelIndex &index) const
QFileInfo fileInfo(const QModelIndex &index) const
QString fileName(const QModelIndex &index) const
QString filePath(const QModelIndex &index) const
/*返回给定路径 path 和列 column 的项目的模型索引*/
QModelIndex index(const QString &path, int column = 0) const
/*若索引 index 所指的项目表示目录则返回 true，否则返回 false。*/
bool isDir(const QModelIndex &index) const
/*最后编辑时间*/
QDateTime lsatModified(const QModelIndex &index) const
/*返回index项目的文件权限*/
QFile::Permissions permissions(const QModelIndex &index) const;
/*返回索引 index 所指项目的大小*/
qint64 size(const QModelIndex &index) const;
/*返回索引 index 所指项目的类型，比如"jpeg"、"txt"、"Directory"*/
QString type(const QModelIndex &index) const;
/*返回项目“我的电脑”中与角色 role 关联的数据*/
QVariant myComputer(int role=Qt::DisplayRole) const;
```

## 图标

```cpp
/*表示设置和返回此目录模型的文件图标提供程序，QFileIconProvider 类为
QFIleSystemModel 提供文件图标*/
void setIconProvider(QFileIconProvider *provider)
QFileProvider *iconProvider() const;
```

## 示例

```cpp
#include <QtWidgets>

class myFileSystemView : public QWidget {
private:
	QFileSystemModel *m_model; //公用的文件系统数据模型
	QTreeView *m_treeView; //树视图
	QListView *m_ListView; //列表视图
	QComboBox *m_filtersListBox; //过滤器选择器
	void initView() { //初始化各组件
		m_model = new QFileSystemModel(this);
		m_treeView = new QTreeView(this);
		m_treeView->hideColumn(1);
		m_treeView->hideColumn(2);
		m_treeView->hideColumn(3);
		m_treeView->setHeaderHidden(1);
		m_treeView->setTextElideMode(Qt::ElideNone);
		m_ListView = new QListView(this);
		m_filtersListBox = new QComboBox(this);
		m_filtersListBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		m_filtersListBox->addItems({ "*","*.jpg;*.bmp","*.txt;*.text" });
		QSplitter *splitter = new QSplitter(Qt::Horizontal);
		splitter->addWidget(m_treeView);
		splitter->addWidget(m_ListView);
		QVBoxLayout *totalLayout = new QVBoxLayout(this);
		totalLayout->addWidget(splitter);
		totalLayout->addWidget(m_filtersListBox);

		connect(m_treeView, &QTreeView::clicked, this, &myFileSystemView::on_treeView_clicked);
		connect(m_treeView, &QTreeView::doubleClicked, this, &myFileSystemView::on_treeView_clicked);
		connect(m_filtersListBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::activated), this, &myFileSystemView::on_filtersListBox_activated);
	}
	void initFileSystemModel() {
		m_model->sort(0);
		m_model->setRootPath("");
		m_model->setReadOnly(false);
		m_model->setNameFilterDisables(false);
		m_treeView->setModel(m_model);
		m_ListView->setModel(m_model);
		m_ListView->setRootIndex(m_model->index("C:"));

		
	}
	void init() {
		initView();
		initFileSystemModel();
	}
public:
	myFileSystemView(QWidget *parent = nullptr) : QWidget(parent) { init(); }


private slots:
	void on_treeView_clicked(const QModelIndex &index) {
		m_ListView->setRootIndex(index);
	}

	void on_filtersListBox_activated(const QString &filters) {
		m_model->setNameFilters(filters.split(";"));
	}

};
```


