# QModelIndex

## 基本原理

* `QModelIndex`类是一个独立的类，无继承关系，用于管理项目的模型索引，主要有以下几点：
    * 模型索引需要使用`QAbstractItemModel::createIndex()`函数来创建
    * 无效模型索引通常是模型中顶级项目的索引
    * 无效模型索引使用`QModelIndex`的默认构造函数来创建
    * 模型索引应立即生效，然后丢弃，因为在改变模型结构或删除项目后，模型索引很有可能会不再有效
    * `QModelIndex`提供的索引是一个临时索引，若需要对数据项进行长时间的引用，应使用`QPersistentModelIndex`创建一个持久模型索引

## 成员变量

```cpp
class QPersistentModelIndexData //持续型模型索引
{
public:
    QPersistentModelIndexData() :model(0){}
    QPersistentModelIndexData(const QModelIndex &idx) :index(idx),model(idx.model()){}
    QModelIndex index;  
    QAtomicInt ref; //原子操作
    const QAbstractItemModel *model;
    static QPersistentModelIndexData *create(const QModelIndex &index);
    static void destory(QPersistentModelIndexData *data);
}

class Q_CORE_EXPORT QAbstractItemModelPrivate : public QObjectPrivate
{
public:   
    struct Change{  //数据发生改变时使用这个结构体,beginInserstRows函数会调用这个结构体
        Q_DECL_CONSTEXPR Change() : parent(), first(-1), last(-1), needsAdjust(false) {}
        Q_DECL_CONSTEXPR Change(const QModelIndex &p, int f, int l) : parent(p), first(f), last(l),
        needsAdjust(false) {}

        QModelIndex parent;
        int first,last;
        bool needsAdjust;
    };
    QStack<Change> changes;

    struct Persistent{  //rowsAboutToBeRemoved会调用这个结构体
        Persistent(){}
        QHash<QModelIndex,QPersistentModelIndexData *> indexes;
        QStack<Qvector<QPersistentModelIndexData *>> moved;
        QStack<QVector<QPersistentModelIndexData *>> invalidated;

    }persistent;

    Qt::DropActions supportedDragActions;   //是否支持拖拽动作

    QHash<int,QByteArray> roleNames;    //角色数据
    
}

```

## 函数

```cpp
/*构造函数*/
QModelIndex()
/*返回索引的行号或列号*/
int column() const
int row() const
/*返回由该索引所指定项目的角色role的数据*/
QVariant data(int role =Qt::DisplayRole) const
/*获取索引所指项目的项目标志*/
Qt::ItemFlags flags() const
/*返回该索引所指项目与内部数据结构所关联的void*指针或qunintptr*/
quniptr internalId() const;
void* internalPointer() const;
/*若模型索引有效则返回true*/
bool isValid() const
/*返回索引所指项目的模型的指针*/
const QAbstractItemModel *model() const
/*返回模型的父索引，若没有则返回QModelIndex()*/
QModelIndex parent() const
/*返回位于row和列column处的兄弟索引*/
QModelIndex sibling(int row,int column) const
```