# QAbstractItemDelegate

## 基本原理

* QAbstractItemDelegate类继承自QObject
* 委托用于显示视图中的单个项目，并处理模型数据的编辑
* 若需要以自定义方式渲染项目，则必须重新实现 ``paint()``和 ``sizeHint()``函数
* 可使用如下两种方法实现自定义的编辑：

  * 创建一个编辑器部件，并将其设置为项目的编辑器，此方法必须重新实现 `createEditor(QWidget *parent,const QStyleOptionViewItem &option, const QModelIndex &index)`函数，并使用 `setEditorData(QWidget *editor, const QModelIndex &index)`函数从模型中获取数据用于编辑器，使用 `setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)`函数把编辑器的内容写入到模型中
  * 重新实现 `editorEvent(QEvent *event,QAbstractItemModel *model,const QStyleOptionViewItem &option,const QModelIndex &index)`函数，直接处理用户事件
* QAbstractDelegate的子类QItemDelegate和QStyleItemDelegate是Qt提供的对QAbstractDelegate类的默认实现
* QAbstractItemDelegate 类中的函数  
  
## 枚举

```cpp
enum EndEditHint{
  NoHint, /*无推荐可执行*/
  EditNextItem, /*应在下一个项目上打开编辑器*/
  EditPreviousItem, /*应在上一个项目上打开编辑器*/
  SubmitModeCache,  /*若模型缓存数据，则应把缓存的数据写入底层的数据存储*/
  RevertModelCache  /*若模型缓存数据，则应放弃缓存的数据并将其替换为底层数据存储中的数据*/
};
```

## 信号

```cpp
/*当用户使用编辑器editor完成对项目的编辑时，发送此信号。hint为委托提供了编辑完成后影响模型和视图行为的方式，可以指示组件接下来执行什么操作*/
void closeEditor(QWidget *editor,QAbstractItemDelegate::EndEditHint hint =NoHint)
/*当编辑器editor编辑完数据并且要将其写回模型中时，必须徐发送此信号，也就是说当数据写回模型时，会发送此信号*/
void commitData(QWidget* editor)
/*当索引index的sizeHint()变化时，必须发送此信号，视图自动连接到此信号，并根据需要重新布局项目*/
void sizeHintChanged(const QModelIndex &index)
```
## 函数

> 注意：QAbstractItemDelegate类中的函数都是虚函数，这些函数的参数都附带有必要的信息，如对于`paint()`函数的index参数，就表示需要绘制的模型的索引，且`idnex.data()`函数包含有来自模型的数据。重新实现这些虚函数时，应合理使用这些参数所附带的信息

* 构造函数

```cpp
  QAbstractItemDelegate(QObject* parne = Q_NULLPTR) 
```

* 纯虚函数
  
```cpp
/*若要提供自定义渲染，则必须实现此函数，使用painter和外观选项option来渲染索引index所指的项目。若重新实现该函数,则必须实现sizeHint()函数*/
virtual void paint(QPainter *painter,const QStyleOptionViewItem &option,const QModelIndex &index) const =0;
/*若要提供自定义渲染，则必须重新实现此函数*/
virtual QSize sizeHint(const QStyleOptionViewItem &option,const QModelIndex &index) const =0;
```

* 编辑器

```cpp
/*返回用于编辑索引index所指数据项的编辑器,index包含正在使用的模型的信息，parent表示编辑器的父部件，项目选项由OPTION指定*/
virtual QWidget* createEditor(QWidget* parent,const QStyleOptionViewItem &option,const QModelIndex &index) const;

/*将编辑器editor的内容设置为索引index所指项目的数据*/
virtual void setEditorData(QWidget *editor,const QModelIndex &index) const

/*将模型model中由索引idnex所指项目的数据设置为编辑器editor的内容*/
virtual void setModelData(QWidget* editor,QAbstractItemModel *model,const QModelIndex &index) const;

/*根据option中的矩形，更新索引index所指项目的编辑器的几何尺寸，该函数决定编辑器在视图的位置和大小，因此是比较重要的，默认实现什么也不做，若要使用自定义的编辑器，则需要重新实现此函数*/
virtual void updateEditorGeometry(QWidget* editor,const QStyleOptionViewItem &option,const QModelIndex &index) const

/*当编辑器editor不再需要编辑索引index所指的数据项且应该被销毁时调用，也就是说，该函数用于销毁编辑器editor。默认行为时调用编辑器editor的QObject::deleteLater函数*/
virtual void destroyEditor(QWidget *editor,const QModelIndex &index) const

```

* 事件
  
```cpp
/*在开始编辑项目时，会调用这个函数，event为触发该编辑的事件,model、index分别为被编辑项目的模型和索引，option为渲染项目的选项。即使鼠标事件没有开始编辑该项目，也会发送给editorEvent()，比如当在2项目上按下鼠标右键视图打开一个上下文菜单时*/
virtual bool editorEvent(QEvent *event,QAbstractItemModel,const QStyleOptionViewItem &option,const QModelIndex &index)

/*当发生帮助事件时，会调用这个函数，若委托处理该事件返回true，否则返回false。对于成功处理的QEvent::ToolTip和QEvent::WhatsThis事件，根据系统的配置可能会显示相关的弹出窗口*/
virtual bool helpEvent(QHelpEvent *event,QAbstractItemView *view,const QStyleOptionViewItem &option,const QModexIndex &index)
```