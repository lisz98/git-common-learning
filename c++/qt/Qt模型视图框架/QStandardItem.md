# QStandardItem

## 基本原理

* QStandardItem数据项是一个二维的子项目表(即n行m列的表)，这使得数据项可以以层次结构构建，典型的层次结构是树形结构。
* 数据项不是一个单独的元素，而是有多个子项目组成的
* 因为数据项具有层次结构，模型的项目也具有层次结构，因此在使用时应设计好模型、视图和数据项三者之间的结构。若设计不合理，可能会无法正确显示。若数据项QStandardItem组织为树形结构，则QStandItemModel和树形视图默认只会使用1列来显示数据项，，因此若数据项的某个节点有多余 1 列的数据需要显示，则需要增加模型QStandItemModel 的列数，否则数据将不会被显示。

## 成员变量

```cpp
/*成员变量存储在QStandardItemPrivate中，使用d指针进行访问*/
class QStandardItemData{
public:
    /*数据角色*/
    int role;
    /*数据*/
    QVariant value;
}
class QStandardItemPrivate 
{
public:
    /*所属于的模型*/
    QStandardItemModel *model;
    /*父节点*/
    QStandardItem *parent;
    /*存储数据元素*/
    QVector<QStandardItemData> values;
    /*子节点*/
    QVector<QStandarItem*> children;
    /*所属模型行和列*/
    int row,column;
    /*QStandardItem指针*/
    QStandardItem *q_ptr;
    /*缓存值，最后一个被知晓的项目的索引*/
    mutable int lastKnownIndex;
}
```

## 构造函数

```cpp
QStandardItem();
explicit QStandardItem(const QString &text);
/*使用图标和文本构造一个数据项*/
QStandardItem(const QIcon &icon, const QString &text);
/*构造一个有 rows 行，columns 列的子项目的数据项*/
explicit QStandardItem(int rows, int columns = 1);
```

## 外观函数

* 通过设置role的角色来进行设置

```cpp
/*文本*/
void setText(const QString &text);
Qstring text() const;
/*文本对齐*/
void setTextAlignment(Qt::Alignmnet alignmnet);
Qt::Alignmnet textAlignment() const;
/*图标*/
void setIcon(const QIcon &icon);
QIcon icon() const;
/*字体*/
void setFont(const QFont &font);
QFont font() const;
/*背景色*/
void setBackground(const QBrush &brush);
QBrush background() const;
/*前景色(如文字颜色)*/
void setForeground(const QBrush &brush);
QBrush foreground() const;
/*工具提示*/
void setToolTip(const QString &toolTip);
QString toolTip() const;
/*状态提示*/
void setStatusTip(const QString &statusTip);
QString statusTip() const;
/*what's this 帮助*/
void setWhatsThis(const QString &whatsThis);
QString whatsThis() const;
```

## 状态函数

* 通过QFlags来获取和设置
* 注：要启用三态(tristate)需要启用项目的可选中状态，若三态是由 setAutoTristate()启用的，则会由
QTreeWidget 自动控制(注意：QTreeView 视图不会自动控制)，即当用户在部分选中其子项时，父项呈
现部分选中状态，若子项全都选中，则父项选中，若子项都未选中，则父项未选中

```cpp
/*是否启用可选中状态*/
void setCheckable(bool checkable); 
bool isCheckable() const;
/*选中状态*/
void setCheckState(Qt::CheckState state);
Qt::CheckState() const;
/*是否启动三态并由QTreeWidget自动控制*/
void setAutoTristate(bool tristate);
bool isAutoTristate() const;
/*是否启动三态并由用户控制*/
void setUserTristate(bool tristate);
bool isUserTristate() const;
/*是否可被选中*/
void setEditable(bool editable)
bool isEditable() const;
/*是否启用该项目*/
void setEnabled(bool enabled);
bool isEnabled() const;
/*大小提示*/
void setSizeHint(const QSize &size);
QSize sizeHint() const;
/*设置标志*/
void setFlags(Qt::ItemFlags flags);
Qt::ItemFlags flags() const;
/*是否可被拖动*/
void setDragEnabled(bool dragEnabled);
bool isDrageEnabled() const 
/*是否可接收放置*/
void setDropEnabled(bool dropEnabled);
bool isDropEnabled() const;
```

## 设置数据项函数

* 以行为列，`insertRow()`只会插入一行，因此插入的数据项只会位于该项，而`insertRows()`函数用于插入多行，因此插入的数据项会分别填充这些新行

```cpp
void appendColumn(const QList<QStandardItem*> &items);
void appendRow(const QList<QStandardItem *> &items);
void appendRows(const QList<QStandardItem *> &items);
void appendRow(QStandardItem *item);
void insertColumn(int column,const QList<QStandardItem*> &items);
/*插入count列空间*/
void insertColumns(int column,int count);
void insertRow(int row, QStandardItem *item);
void insertRows(int row,const QList<QStandardItem*> &items);
void insertRows(int row, int count);
/*把(row,column)处子项目的数据项设置为item.该数据项获得item的所有权,该函数会增加列数和行数，若item为空指针，将删除该位置处的数据项*/
void setChild(int row,int column,QStandardItem *item);
void setChild(int row,QStandardItem *item);
/*设置行或列数量*/
void setColumnCount(int columns);
void setRowCount(int rows);
/*删除指定数据项*/
void removeColumn(int column);
void removeColumns(int column,int count);
void removeRow(int row);
void removeRows(int row,int count);
/*移除而不删除数据项*/
QList<QStandarItem*> takeColumn(int column);
QList<QStandarItem*> takeRow(int row);
QStandardItem *takeChild(int row,int column =0);
```

## 获取项目信息函数

```cpp
int column() const;
int row() const;
int columnCount() const;
int rowCount() const;
QStandardItem *child(int row,int column =0) const;
bool hasChildren() const;
QStandardItem *parent() const;
QModelIndex index() const;
QStandardItemModel *model() const;
```

## 排序规则

* 在进行排序时，数据项的比较规则由`operator<()`函数定义,该函数默认实现使用QStandardItemModel::sortRole属性设置的角色数据项进行比较，否则使用Qt::DisplayRole角色数据项进行比较。若要实现自定义的排序规则，可以重新实现`operator <()`函数

```cpp
/*操作符小于函数的实现*/
bool operator< (const QStandardItem &other) const{
    /*先获取role*/
    const int role = model() ? model()->sorlRole() : Qt::DisplayRole;
    /*获取角色数据*/
    const QVariant l =data(role);
    const QVariant r =other.data(role);
    return QAbstractItemModelPrivate::isVariantLessThan(l,r);
}
/*使用给定顺序对列column进行排序，该函数递归执行，会对所有子项进行排序*/
void srotChildren(int column,Qt::SortOrder order =Qt::AscendingOrder);
```

## 其他函数

```cpp
/*返回该数据项的类型*/
virtual int type() const;
/*将数据项读取或写入流，不含子项，且只读取或写入数据项的数据和标志*/
virtual void read(QDataStream &in)
virtual void write(QDataStream &out) const
/*返回该数据项的副本(不包含子项),若希望能够按需自定义数据项类型的示例，可以重新实现此函数向QStandardItemModel提供一个工厂*/
virtual QStandardItem *clone() const
```