# QStringListModel

> QStringListModel是一个字符串列表模型

## 基本原理

* 该类提供了一个由视图使用的字符串列表模型，可用于需要在视图部件中显示字符串的情况，比如用于QListView或QComboBox。QStringListModel模型将字符串列表中的数据表示为一列和等于列表中项目数行数的列表模型

## 成员变量

```cpp
class Q_CORE_EXPORT QStringListModel :public QAbstractListModel
{
private:
    /*存储字符串列表数据*/
    QStringList lst;
}
```

## 构造函数

```cpp
QStringListModel(QObject *parent = Q_NULLPTR);
QStringListModel(const QStringList &strings, QObject *parent = Q_NULLPTR);
```

## 其他函数

```cpp
/*设置内部字符串列表*/
void setStringList(const QStringList &strings);
/*返回存储数据的字符串列表*/
QStringList stringList() const;
```

## 重载函数

以下函数重新实现了QAbstractItemModel类中相应的函数

* `virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)`把索引index处指定角色role所关联的数据设置为value，若数据项被改变则发送dataChanged信号

```cpp
bool QStringListModel::setData(const QModelIndex &index,const QVariant &value,int role){
    if(index.row() >= 0 && index.row() < lst.size() //判断数据项长度和数据项角色
        && (role ==Qt::EditRole || role ==Qt::DisplayRole)){
            const QString valueString =value.toString();
            if(lst.at(index.row()) ==valueString){  //判断当前设置数据是否为index索引项数据相等
                return true;
            }

            lst.replace(index.row(),valueString); 
#if 0
            QVector<int> roles;
            roles.reserve(2);
            roles.append(Qt::DisplayRole);
            roles.append(Qt::EditRole);
            emit dataChanged(index,index,roles)
#else
            emit dataChanged(index,index,{Qt::DisplayRole,Qt::EditRole}); //使用列表初始化
#endif
            return ture;
    }
    return false;
}
```

* `virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const`返回索引index处指定角色role所关联的数据

``` cpp
QVariant QStringListModel::data(const QModelIndex &index,int role) const{
    if(index.row() <0 || index.row() >= lst.size()){
        return QVariant(); //无效索引，返回无效的QVariant
    }

    if(role ==Qt::DisplayRole || role ==Qt::EditRole){
        return lst.at(index.row());
    }

    return QVariant;
}
```

* `virtual Qt::ItemFlags flags(const QModelIndex &index) const` 返回索引Index处指定项目的标志，相当于调用了QAbstractListModel中的实现和QAbstractItemModel中的实现，并为有效索引添加Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemNeverHashChildren | Qt::ItemIsSelectable | Qt::ItemIsEnabled的标志
  
```cpp
/*QStringListModel的实现*/
Qt::ItemFlags QStringListModel::flags(const QModelIndex &index) const{
    if(!index.isValid()){
        return QAbstractListModel::flags(index) | Qt::ItemIsDropEnabled;
    }
    return QAbstractListModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

/*QAbstractListModel中的实现*/
Qt::ItemFlags QAbstractListModel::flags(const QModelIndex &index) const{
    Qt::ItemFlags f =QAbsrtactItemModel::flags(index);
    if(index.isValid()){
        f |= Qt::ItemNeverHashChildren; //如果idnex是有效的则添加此属性
    }
    return f;
}

/*QAbstractItemModel中的实现*/
Qt::ItemFlags QAbstractItemModel::flags(const QModelIndex &index) const{
    Q_D(QAbstractItemModel) //返回d指针，调用QAbstractItemModelPrivate
    if(!d->indexVaild(index)){
        return 0;
    }
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}
```

* `virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())`
  `virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex())`
  插入数据或删除数据，从row开始插入或删除count行，参数parent是可选的

```cpp
bool QStringListModel::insertRows(int row,int count, const QModelIndex &parent){
    if(count <1 || row <0 || row >rowCount(parent)){
        return false;
    }

    beginInsertRows(QModelIndex(),row,row+count -1);

    for(int r=0;r <count;++r){
        lst.insert(row,QString());
    }

    endInsertRows();

    return true;
}

bool QStringListModel::removeRows(int row,int count,const QModelIndex &parent){
    if (count <= 0 || row < 0 || (row + count) > rowCount(parent))
        return false;

    beginRemoveRows(QModelIndex(),row,row+count-1);

    const auto it =lst.begin() +row;
    lst.erase(it,it +count);

    endRemoveRows();

    return true;
}

```

* `virtual int rowCount(const QModelIndex &parent = QModelIndex()) const` 返回模型中的行数

```cpp
int QStringListModel::rowCount(const QModelIndex &parent) const{
    if(parent.isValid()){
        return 0;
    }
    return lst.count();
}
```

* `virtual QModelIndex sibling(int row, int column, const QModelIndex &idx) const`返回模型的姐妹

```cpp
QModelIndex QStringListModel::sibling(int row,int column,const QModelIndex &idx) const{
    if(!idx.isValid() || column != 0 || row >=lst.count() || row < 0){
        return QModelIndex();
    }
    return createIndex(row,0);
}
```

* `virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder)` 排序

```cpp
void QStringListModel::sort(int,Qt::SortOrder order){
    emit layoutAboutToBeChanged(QList<QPersistentModelIndex>(),VerticalSortHint);

    QVector<QPair<QString,int>> list;
    const int lstCount =lst.count();
    list.reserve(lstCount);
    for(int i=0;i <lstCount;++i>){
        list.append(QPair<QString,int>(lst.at(i),i)); //记录数据的列号和字符串
    }

    if(order ==Qt::AscendingOrder){ //根据字符串大小进行排序
        std::sort(list.begin(),list.end(),ascendingLessThan);   
    }else{
        std::sort(list.begin(),list.end(),decendingLessThan);
    }

    lst.clear();
    QVector<int> forwardinng(lstCount); //转发
    for(int i =0;i <lstCount;++i){
        lst.append(list.at(i).first);
        forwarding[list.at(i).second] =i;
    }

    QModelIndexList oldList = persistentIndexList();
    QModelIndexList newList;
    const int numOldIndexes =oldList.count();
    newList.reserve(numOldIndexes);
    for(int i=0;i <numOldIndex;++i>){
        newList.append(index(forwarding.at(oldList.at(i).row())),0);
    }
    changePersistentIndexList(oldList, newList);
    emit layoutChanged(QList<QPersistentModelIndex>(), VerticalSortHint);
}
```

* `virtual Qt::DropActions supportedDropActions() const` 是否支持拖拽动作,相当于返回了  Qt::MoveAction |Qt::CopyAction

```cpp
/*QStringListModel*/
Qt::DropActions QStringListModel::supportedDropActions() const
{
    return QAbstractItemModel::supportedDropActions() | Qt::MoveAction;
}

/*QAbstractItemModel*/
Qt::DropActions QAbstractItemModel::supportedDropActions() const
{
    return Qt::CopyAction;
}
```