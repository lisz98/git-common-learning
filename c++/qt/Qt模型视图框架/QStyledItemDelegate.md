# QStyledItemDelegate

> 注：QItemDelegate和QStyledItemDelegate类似
> QStyledItemDelegate是所有Qt标准项目视图的默认委托


## 基本原理

* `QStyledItemDelegate`绘制委托的方法是根据每个数据元素的角色为数据项进行不同绘制，以使项目再视图中显示不同的外观，下表是该委托可以处理的角色和数据类型，自定义绘制与子类化`QAbstractItemDelegate` 的方法相同

|角色|接受的类型|
|----|----|
|Qt::DisplayRole|QString|
|Qt::EditRole||
|Qt::FontRole|QFont|
|Qt::QSizeHintRole|QSize|
|Qt::DecorationRole|QIcon、QPixmap、QImage、QColor|
|Qt::TextAlignmentRole|Qt::Alignment|
|Qt::CheckStateRole|Qt::CheckState|
|Qt::FiregroundRole|QBrush|
|Qt::BackgroundRole|QBrush|

* `QStyledItemDelegate`使用`QItemEditorFactory`类(编辑器工厂)创建编辑器，当然也可子类化该类并重新实现`createEditor()`等函数创建自定义的编辑器,这样就不需要使用`QItemEditorFactory`了

* 使用编辑器工厂指定自定义的编辑器
    * 编辑器的最终创建者是睡？
        > QStyledItemDelegate使用QItemEditorFactory 创建编辑器，QItemEditorFactory 又通过抽象类 QItemEditorCreatorBase(该类被称为编辑器创建者)创建编辑器