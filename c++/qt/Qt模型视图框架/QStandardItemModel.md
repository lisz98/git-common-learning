# QStandardItemModel

## 基本原理

* `QStandardItemModel`继承自`QAbstractItemModel`，`QStandardItem`是一个独立的类
* `QStadnardItemModel`类是Qt实现的标准模型，该类的数据项(项目)由类`QStandardItem`类的描述
* `QStandardItemModel`类实现了三种结构的模型，即列表、树、表格。
* 创建表格模型的方法为：向构造函数传递表格的大小已创建一个表格模型，然后使用`setItem()`和`setData()`向模型中添加数据
* 创建列表或树形结构的方法为：创建一个空的`QStandardItemModel`，然后使用`appendRow()`函数将数据项添加到模型中

## 成员变量

```cpp
/*成员变量存储在QStandardItemModelPrivate中，使用d指针进行访问*/
class QStandardItemModelPrivate: public QAbstractItemModelPrivate
{
public:
    /*列表头*/
    QVector<QStandardItem*> columnHeaderItems; 
    /*行表头*/
    QVector<QStandardItem*> rowHeaderItems;
    /*跟节点*/
    QScopedPointer<QStandardItem> root;
    /*项目原型，用于clone*/
    const QStandardItem *itemPrototype;
    /*排序的角色*/
    int srotRole;
}
```

## 属性

```cpp
/*描述用于排序时使用的角色，比如可以设置为按照Qt::ToolTipRole角色的数据进行排序，默认为Qt::DisplayRole*/
Q_PROPERTY(int sortRole READ sortRole WRITE setSortRole)  
```

## 信号

```cpp
/*当数据项item的数据发生改变时，发送此信号*/
void itemChanged(QStandardItem *item)
```

## 构造函数

```cpp
/*若构造树形、列表结构使用默认构造器*/
explicit QStandardItemModel(QObject *parent = nullptr);
/*构造表格模型*/
QStandardItemModel(int rows, int columns, QObject *parent)
    : QAbstractItemModel(*new QStandardItemModelPrivate, parent)
{
    Q_D(QStandardItemModel);
    d->init(); /*连接dataChanged槽函数*/
    /*QScopedPointer<QStandardItem> root*/
    d->root->insertColumns(0, columns);
    d->columnHeaderItems.insert(0, columns, 0);
    d->root->insertRows(0, rows);
    d->rowHeaderItems.insert(0, rows, 0);
    d->root->d_func()->setModel(this);
}
```

## 追加、插入、添加、移除数据项函数

```cpp
/*把位于(row,column)处项目的数据项设置为item。若有必要会增加模型的行数和列数以适应数据项，若给定的位置已存在数据项，则以前的数据项被删除。设置数据项后，该模型获取该数据项的所有权*/
void setItem(int row,int column,QStandardItem *item)
void setItem(int row,QStandardItem *item)
/*向模型中的列或行追加数据项item*/
void appendColumn(const QList<QStandardItem*> &items)
void appendRow(const QList<QStandardItem*> &items)
/*用于向模型插入一行或一列*/
void insertColumn(int column,const QList<QStandardItem*> &items)
bool insertColumn(int column,const QModelIndex& parent =QModelIndex())
void insertRow(int row,const QList<QStandardItem*> &items)
bool insertRow(int row,const QModelIndex &parent =QModelIndex())
/*用于在只有一列的列表或树时，提供便捷的追加或插入单个数据项的方法*/
void appendRow(QStandardItem *item)
void insertRow(int row,QStandardItem *item)
/*移除(而不删除)列column或行row处的数据项，并返回指向已移除数据项的指针列表，若列或行中的数据项未设置，则对应的指针将为0*/
QList<QStandardItem*> takeColumn(int column)
QList<QStandarItem*> takeRow(int row)
/*移除(而不删除)位于(row,column)处的数据项，并返回指向该数据项的指针，调用该函数后，模型释放对该数据项的所有权*/
QStandardItem *takeItem(int row, int column = 0);
```

## 表头函数

```cpp
/*设置或获取表头数据项*/
void setHorizontalHeaderItem(int column,QStandardItem *item)
void setVerticalHeaderItem(int row,QStandardItem *item)
QStandardItem *horizontalHeaderItem(int column) const
QStandardItem *verticalHeaderItem(int row) const
/*用于设置水平/垂直表头的标签文本，若有必要会增加模型的数据项*/
void setHorizontalHeaderLabels(const QStringList &labels)
void setVerticalHeaderLabels(const QStringList &labels)
/*移除(而不删除)水平或垂直标头数据项，并返回指向该数据项的指针*/
QStandardItem *takeHorizontionHeaderItem(int column)
QStandardItem *takeVerticalHeaderItem(int row)
```

## 获取项目信息函数

```cpp
/*返回(row,column)处的数据项*/
QStandardItem* item(int row,int column=0) const
/*返回与数据项item相关联的模型索引,QStandardIten::index()函数相当于调用此函数*/
QModelIndex indexFromItem(const QStandardItem *item) const
/*返回指向与索引index相关联的QStandardItem搭的指针*/
QStandardItem* itemFromIndex(const QModelIndex &index) const
```

## 其他函数

```cpp
/*返回模型的不可见根数据项*/
QStandardItem *invisibleRootItem() const
/*删除模型中的所有数据项*/
void clear();
/*设置模型的行或列的数量*/
void setColumnCount(int columns)
void setRowCount(int rows)
/*查找模型中的数据项,text表示需要查找的文本,flags表示匹配的方式,column表示在该列中查找*/
QList<QStandardItem*> findItems(const QString &text,Qt::MatchFlags flags=Qt::MatchExactly,int column =0) const
/*设置项目角色的名称为roleNames，此函数与QAbstractItemModel::roleNames()函数相对应*/
void setItemRoleNames(const QHash<int,QByteArray> &roleNames)
/*获取和设置模型的项目原型。项目原型依靠QStandardItem::clone()函数充当QStandardItem工厂*/
const QStandardItem* itemPrototype() const
void setItemPrototype(const QStandardItem *item)
```