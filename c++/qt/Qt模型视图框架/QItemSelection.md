# QItemSelection

## ***基本原理***

1. QItemSelectionModel 类继承自 QObject，该类主要用于跟踪视图中所选择的项目。
2. 使用选择模型的步骤：
要使选择模型的设置显示在视图上，需要使选择模型关联与视图相同的项目模型(QAbstractItemModel)，并且应使用视图的 setSelectionModel()函数把该选择模型作为视图的选择模型。具体代码类似如下：

```
QStandardItemModel *pd…. //模型
QTableView *pv…. //视图
QItemSelectionModel *ps …. //选择模型
…. //其他代码
pv->setModel(pd); //设置与视图关联的项目模型，注意：视图的 setModel()函数会删除之前
//设置的选择模型，所以此步骤应位于 setSelectionModel()之前。
ps->setModel(pd); //设置与选择模型关联的项目模型
pv->setSelectionModel(ps); //设置与视图关联的选择模型，注意：此步必须在 pv->setModel(pd);之后
```

## ***QItemSelection类***

1. QItemSelection 类继承自 QList 类，该类的原型如下：
```cpp
class Q_CORE_EXPORT QItemSelection: public QList<QItemSelectionRange>{

};
```  
可见该类存储的是 QItemSelectionRange 类型的列表。QItemSelectionRange 类用于管理模型中选定项目范围的信息，该类通常通过 QItemSelection 进行使用，很少被直接使用

2. QItemSelection 类用于描述一个选择范围，其方法为指定左上角和右下角项目的索引,注意：指定了一个选择范围，不代表该范围内的项目会被选择(高亮显示)，项
目是否被选择需由选择模型 QItemSelectionModel 进行设置。

3. QItemSelection类的函数
   *  **```QItemSelection()```** 默认构造函数
   *  **```QItemSelection(const QModelIndex &topLeft,const QModelIndex &bottomRight)```** 构造一个从左上角到右下角的选择范围。通常使用这个构造函数
   *  void **```select(const QModelIndex &topLeft,const QModelIndex &bottomRight)```** 该函数通常用于普通构造函数结合使用，如下:  
   *  
    ```cpp
    QItemSelection *s =new QItemSelection;
    s->slect(topLeft,bottomRight);
     ```

    *  **```bool constains(const QModelIndex &) const```**
    *  **```QModelIndex indexes() const```** 返回选择范围的索引列表
    *  **```void merge(const QItemSelection &other,QItemSelectionModel::SelectionFlags command)```** 使用选择标志command将选择other与当前选择范围合并。注意：选择标志只支持一下:
    ```cpp
    enum{
        QItemSelectionModel::Select,
        QItemSelectionModel::Deselect,
        QItemSelectionModel::Toggle
    };
    ```
    * **```static void split(const QItemSelectionRange &range,const QItemSelectionRange &other,QItemSelection *result)```** 静态的拆分范围，使用选择范围 other 拆分选择范围 range,从 range 中移除所有 other，并将结果存入 result 之中。
  
##  ***QItemSelectionModel类中的函数和属性***

1. 属性、枚举及构造函数
   * 构造函数
     ```cpp
     QItemSelectionModel(QAbstractItemModel *model =Q_NULLPTR)
     QItemSelectionModel(QAbstractItemModel *model,QObject *parent)
     ```
   * 属性 
   ```cpp
    Q_PROPERTY(QAbstractItemModel *model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(bool hasSelection READ hasSelection NOTIFY selectionChanged STORED false DESIGNABLE false)
    Q_PROPERTY(QModelIndex currentIndex READ currentIndex NOTIFY currentChanged STORED false DESIGNABLE false)
    Q_PROPERTY(QItemSelection selection READ selection NOTIFY selectionChanged STORED false DESIGNABLE false)
    Q_PROPERTY(QModelIndexList selectedIndexes READ selectedIndexes NOTIFY selectionChanged STORED false DESIGNABLE false)
   ```
   * 枚举
    ```cpp
    enum SelectionFlag {
        NoUpdate       = 0x0000, /*不做出选择*/
        Clear          = 0x0001, /*清除已选择索引*/
        Select         = 0x0002, /*选择指定的索引，该选项不会清除之前的选择*/
        Deselect       = 0x0004, /*取消选择指定的索引*/
        Toggle         = 0x0008, /*切换选择/取消选择*/
        Current        = 0x0010, /*更新当前选择(注意：当前选择不是当前索引和当前项目)*/
        Rows           = 0x0020, /*将索引扩展至整行*/
        Columns        = 0x0040, /*将索引扩展至整列*/
        SelectCurrent  = Select | Current, 
        ToggleCurrent  = Toggle | Current, 
        ClearAndSelect = Clear | Select 
    };
    Q_DECLARE_FLAGS(SelectionFlags, SelectionFlag)
    Q_FLAG(SelectionFlags)
    ```
2. ***模型***
   * **```void setMdoel(QABstractItemModel *model)```** 设置与该选择模型相关的项目为model，并发送modelChange()信号
   * **```const QAbstractItemModel *model const```** 函数返回与该选择模型相关联的模型
3. ***以编程的方式选择项目***
   * 以下函数表示，使用给定的选择标志command选择模型项目索引index或选择项目selection，并发送selectionChanged()信号。
   * 使用第一个函数一次只能选择一个项目，若想同时选择多个项目，需要使用第二个函数，并由QItemSelection对象指定一个选择范围
    ```cpp
    public slots:
    virtual void select(const QModelIndex &index, QItemSelctionModel::SelectionFlag command);
    virtual void select(const QItemSelection &slection, QItemSelectionModel::SelectionFlags command);
    ```
  
4. ***当前项目(或当前索引)***
   * **```QModelindex currentIndex() const```** 返回当前项目的模型索引，若没有当前项目，则返回无效索引
   * **```virtual void setCurrentIndex(const QModelIndex &index,QItemSelectionModel::SeletionFlags command```** 把index所指项目设置为当前项目，并发送currentChanged()信号。根据指定的command，index也可以成为当前选择的一部分
  
5. ***清除内容***
   * **```virtual void reset()```** 清除选择模型(该函数会同时清除已选择的索引和当前索引)，不发送任何信号
   * **```virtual void clear()```** 清除选择模型(该函数会同时清除已选择的索引和当前索引),并发送selectionChanged()信号和currentChange()信号
   * **```virutal void clearCurrentIndex()```** 清除当前索引(该函数不会清除已选择的索引),发送currentChanged()信号
   * **```void clearSelection()```** 清除选择模型中的选择(该函数不会清除当前索引),发送selectionChanged()信号

6. ***获取所选择项目的信息***
   * **```const QItemSelection selection() const```** 返回存储在选择模型中的选择范围
   * **```bool isSelected(const QModelIndex &index) const```** 若索引index被选择，则返回true
   * **```bool hasSelection() const```** 若选择模型包括任意的选择范围，则返回true，否则返回false
   * **```QModelIndexList selectedColumns(int row =0) const```** 返回"行row所在列中"的所有行被选中的索引
   * **```QModelIndexList selectedRows(int column = 0) const```** 返回“列 column 所在行中”的所有列被选中的行的索引
   * 函数表示如果在列column/行row 中选择了父项parent 中的任意项目，则返回true
      ```cpp
      bool columnIntersetsSelection(int column,const QModelIndex &parent) const

      bool rowIntersetsSelection(int row,const QModelIndex &parent) const
      ```
   * 函数表示如果在列column/行row 中选择了父项parent 中的所有项目，则返回true。以上函数比在同一列或行的所有项目上依次调用 isSelected()进行判断更快，且忽略不可选项目
      ```cpp
      bool isColumnSelection(int column,const QModelIndex &parent) const

      bool isRowSelection(int row,const QModelIndex &parent) const
      ```
7. ***信号***
   * **```void selectionChanged(const QItemSelection &seleted,const QItemSelection &deselected)```** 当选择变化时，发送此信号。选择的变化是指项目在取消选择和被选择之间的变化，注意：当前索引的改变不会发送此信号，另外，重置项目模型时也不会发送此信号
   * **```void currentChanged(const QModelIndex &current,const QModelIndex &previous)```** 当项目改变时，发送此信号。之前项目索引previous被替换为选择的当前项目索引current。重置项目模型时不会发送此信号
   * 若当前项目 current 发生变化，且与前一个当前项目 previous 的行/列不相同时，发送此信号。重置项目模型时不会发送此信号
    ```cpp
    void currentRowChanged(const QModelIndex &current,const  QModelIndex &previous)

    void currentColumnChanged(const QModelIndex &current,const QModelIndex &previous)
    ```
   * **```void modelChanged(QAbstractItemModel *model)```** 使用setModel()成功设置模型时，发送此信号