# QAbstractItemView

## 基本原理

* QAbstractItemView类继承自QAbstractScrollArea,后者继承自QFrame
* 该类支持以下的键盘操作

> | 按键| 描述 |
> |  ---- | ----  |
> | 方向键 | 改变当前项目并选中该项目 |
> | Ctrl+方向键| 改变当前项目但不选择该项目|
> |Shift+方向键|改变当前项目并选中该项目|
> |Ctrl+Space|切换当前项目的选择|
> |Tab/Backtab|使后/前一个项目成为当前项目|
> |Home/End|选择第一个/最后一个项目|
> |Page up/Page down|向上/下滚动显示可见的行|
> |Ctrl+A|选择所有显目|

* 当前项目(或当前索引):
    * 当前项目用于键盘导航和焦点指示，若按下编辑键 F2，将会编辑当前项目
    * 当前项目不一定是当前已被选择的项目(高亮),当前项目可以处于被选中状态，也可以不处于被选择状态
    * 只能有一个当前项目，但可以同时有多个被选择的项目
    * 当前项目通常是具有焦点的项目

## 成员变量

```cpp

```

## 属性

```cpp
/*是否启用自动滚动*/
Q_PROPERTY(bool autoScroll READ hasAutoScroll WRITE setAutoScroll)
/*描述触发自动滚动时视口边缘区域的大小，当用户拖动至该区域时视图将自动滚动*/
Q_PROPERTY(int autoScrollMargin READ autoScrollMargin WRITE setAutoScrollMargin)
/*描述编辑项目的触发方式*/
Q_PROPERTY(EditTriggers editTriggers READ editTriggers WRITE setEditTriggers)
/*描述tab键是否用于项目导航，，若为 true，则按下 tab 键会选择(高亮) 下一个项目；若为false，则按下 tab 键没有任何反应，但是若 setEditTriggers()函数的设置包含QAbstractItemView::AnyKeyPressed，则按下 tab 键会直接编辑下一个项目*/
Q_PROPERTY(bool tabKeyNavigation READ tabKeyNavigation WRITE setTabKeyNavigation)
/*拖动项目在项目放下时，是否向用户显示设置指示符*/
Q_PROPERTY(bool showDropIndicator READ showDropIndicator WRITE setDropIndicatorShown)
/*是否启用拖放操作，默认视图未启动拖放*/
Q_PROPERTY(bool dragEnabled READ dragEnabled WRITE setDragEnabled)
/*描述拖放操作放置时的覆盖行为，若该值为 true，则选定的数据将在放置时覆盖现在的数据，若为 false，则在放置数据时，所选数据将作为新项目被插入。对于 QListView 和QTreeView 默认为 false，对于 QTableView 默认为 true。该属性对不同视图的行为并不一致*/
Q_PROPERTY(bool dragDropOverwriteMode READ dragDropOverwriteMode WRITE setDragDropOverwriteMode)
/*描述视图支持得拖放模式*/
Q_PROPERTY(DragDropMode dragDropMode READ dragRropMode WRITE setDragDropMode)
/*描述拖放时的默认动作*/
Q_PROPERTY(Qt::DropAction defaultDropAction READ defaultDropAction WRITE setDefaultDropAction)
/*是否使用交替的颜色绘制背景色，若为true，则使用QPalette::AlternateBase和QPalette::Base绘制背景色，否则使用 QPalette::Base 绘制背景色。默认为 false。*/
Q_PROPERTY(bool alternatingRowColors READ alternatingRowColors WRITE setAlternatingRowColors)
/*描述视图的选择模式(比如是否可以同时选择多个项目等)*/
Q_PROPERTY(SelectionMode selectionMode READ selectionMode WRITE setSelectionMode)
/*描述视图的选择行为(比如按行或列选择)*/
Q_PROPERTY(SelectionBehavior selectionBehavior READ selectionBehavior WRITE setSelectionBehavior)
/*描述视图项目图标的大小*/
Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize NOTIFY iconSizeChanged)
/*描述省略符的设置*/
Q_PROPERTY(Qt::TextElideMode textElideMode READ textElideMode WRITE setTextElideMode)
/*属性分别表示视图在水平或垂直方向上的滚动方式，即滚动一个像素还是一个项目的内容*/
Q_PROPERTY(ScrollMode verticalScrollMode READ verticalScrollMode WRITE setVerticalScrollMode RESET resetVerticalScrollMode)
Q_PROPERTY(ScrollMode horizontalScrollMode READ horizontalScrollMode WRITE setHorizontalScrollMode RESET resetHorizontalScrollMode)

```

## 枚举

```cpp
/*描述视图的选中模式*/
enum SelectionMode{
    NoSelection,            /*项目不能被选择*/
    SingleSelection,        /*只能同时选中一个项目*/
    MutiSelection,          /*可以选中多个项目*/
    ExtendedSelection,      /*选择该项目时，会取消其他已选中项目，但是若在单击某个项目时按住了 Ctrl 键，则该项目的选择状态会在选择或取消选择之间切换，若在单击某个项目时按住了Shift 键，则会选择或取消选择当前项目和单击项目之间的所有项*/
    ContiguousSelection     /*选择该项目时，会取消其他已选中项目，但是若在单击某个项目时按住了 Shift 键，则会选择或取消选择当前项目和单击项目之间的所有项*/
};
Q_ENUM(SelectionMode)
/*描述视图的选择行为*/
enum SelectionBehavior{
    SelectItems,    /*一次选择一个项目*/
    SelectRows,     /*按行选择，即选择某个项目时，会同时选中该项目所在行的所有项目*/
    SelectColumns   /*按列选择，即选择某个项目时，会同时选中该项目所在列的所有项目*/
};
Q_ENUM(SelectionBehavior)
enum ScrollHint{
    EnsureVisible,      /*滚动以确保项目可见*/
    PositionAtTop,      /*滚动，以将项目定位于视口顶部*/
    PositionAtBottom,   /*滚动，以将项目定位于视口底部*/
    PositionAtCenter    /*滚动，以将项目定位于视口中心*/
};
Q_ENUM(ScrollHint)
/*描述编辑项目的触发方式*/
enum EditTrigger{
    NoEditTriggers =0,  /*无法编辑*/
    CurrentChanged =1,  /*只要当前项目发生变化，即开始编辑*/
    DoubleClicked =2,   /*双击项目时开始编辑*/
    SelectedClicked =4, /*单击已选定的项目时开始编辑*/
    EditKeyPressed =8,  /*按下编辑兼(通常为F2)开始编辑*/
    AnyKeyPressed =16,  /*按下任意键开始编辑*/
    AllEditTriggers =31 /*以上所有方式的组合*/
};
Q_DECLARE_FLAGS(EditTriggers, EditTrigger) //Q_DECLARE_FLAGS(Flags, Enum) typedef QFlags<Enum> Flags;
Q_FLAG(EditTriggers)
/*描述视图的滚动模式*/
enum ScrollMode{
    ScrollPerItem,  /*一次滚动一个项目内容*/
    ScrollPerPixel  /*一次滚动一个像素内容，此滚动模式的滚动距离还与滚动时的单步大小有关*/
};
Q_ENUM(ScrollMode)
/*描述视图的拖放模式*/
enum DragDropMode{
    NoDragDrop,     /*不支持拖放*/
    DragOnly.       /*仅支持拖放*/
    DropOnly,       /*仅支持放置操作*/
    DragDrop,       /*支持拖放和放置*/
    InternalMove    /*仅接收来自其自身的操作*/
}
Q_ENUM(DragDropMode)
enum CursorAction{
    MoveUp,         /*移至当前项目上方的项目*/
    MoveDown,       /*移至当前项目下方的项目*/
    MoveLeft,       /*移至当前项目左侧的项目*/
    MoveRight,      /*移至当前项目右侧的项目*/
    MoveHome,       /*移至左上角的项目*/
    MoveEnd,        /*移至右下角的项目*/
    MovePageUp,     /*在当前项目上方移动一页*/
    MovePageDown,   /*在当前项目下方移动一页*/
    MoveNext,       /*移至当前项目之后的项目*/
    MovePrevious    /*移至当前项目之前的项目*/
}
/*描述视图的状态*/
enum State{
    NoState,                /*默认状态*/
    DraggingState,          /*用户正在拖动项目*/
    DragSelectingState,     /*用户正在选择项目*/
    EditingState,           /*用户正在编辑项目*/
    ExpandingState,         /*用户正在打开一个项目分支*/
    CollapsingState,        /*用户正在关闭一个项目分支*/
    AnimatingState          /*视图正在执行动画*/
}
enum DropIndicatorPosition{
    OnItem,         /*项目将放置在索引处*/
    AboveItem,      /*项目将放置在索引的上方*/
    BelowItem,      /*项目将放置在索引的下方*/
    OnViewport,     /*该项目将被放置到没有项目的视口区域中。每个视图处理放置在视口上的项目的方式取决于所使用的模型的行为*/
}
```

## 信号

```cpp
/*当按下鼠标时，发送此信号*/
void pressed(const QModelIndex &index) ;
/*当单击鼠标左键时发出此信号*/
void clicked(const QModelIndex &index);
/*当用户激活索引 index 指定的项目时，发送此信号*/
void activated(const QModelIndex &index);
/*当鼠标进入视口时，发送此信号，需启用鼠标跟踪功能才能使用此信号*/
void viewportEntered();
/*当鼠标进入索引index指定的项目时，发送此信号，需启用鼠标跟踪功能才能使用此信号*/
void entered(const QModelIndex &index);
/*双击鼠标时，发送此信号*/
void doubleClicked(const QModelIndex &index);
```

## 函数

### 纯虚函数

```cpp
/*将选择标志flags应用于矩形rect中的项目，或rect所触及的项目*/
virtual void setSelection(const QRect &rect,QItemSelectionModel::SelectionFlags flags) =0;
/*返回索引index所指项目占用的视口上的矩形*/
virtual QRect visualRect(const QModelIndex &index) const =0;
/*从selection选择的项目的视口返回区域*/
virtual QRegion visualRegionForSelection(Const QItemSelection &selection) const =0;
/*返回视图的水平/垂直偏移量，必须返回视口在窗口部件中x和y坐标的偏移量量(通常滚动条的值(value())就是需要的偏移量)*/
virtual int horizontalOffset() const = 0;
virtual int verticalOffset() const = 0;
/*返回视口坐标点 point 处的模型索引*/
virtual QModelIndex indexAt(const QPoint &point) const = 0;
/*索引 index 所引用的项目隐藏在视图中，则返回 true，否则返回 false，隐藏是视图特定的特性*/
virtual bool isIndexHidden(const QModelIndex &index) const = 0 ;
/*根据cursorAction和键盘修饰符modifiers，返回指向视图中的下一个对象的模型索引*/
virtual QModelIndex moveCursor(CursorAction cursorAction ,Qt::KeyboardModifiers modifiers) = 0;
/*必要时滚动视图，以确保 index 处的项目是可见的*/
virtual void scrollTo(const QModelIndex &index, ScrollHint hint = EnsureVisible) = 0;
```

### 模型有关的函数

```cpp
/*返回/设置视图使用的模型*/
QAbstractItemModel *model() const;
virtual void setModel(QAbstractItemModel *model);
```

### 与拖放有关的函数

```cpp
/*返回放置指示符(见属性 showDropIndicator)相对于最近项目的位置*/
DropIndicatorPosition dropIndicatorPosition() const;
/*通过使用参数 supportedActions 调用 drag->exec()来启用拖动。*/
virtual void startDrag(Qt::DropActions supportedActions);
```

### 与委托有关的函数

```cpp
/*把该视图和模型的委托设置为 delegate，现有的委托将被移除，但不会被删除*/
void setItemDelegate(QAbstractItemDelegate *delegate);
/*把该视图和模型所在列 column 或行 row 的委托设置为 delegate，设置委托后，列或行上的所有项目都将由delegate 进行绘制和管理，而不再使用默认委托(即itemDelegate())，现有的委托将被移除，但不会被删除*/
void setItemDelegateForColumn(int column, QAbstractItemDelegate *delegate);
void setItemDelegateForRow(int row, QAbstractItemDelegate *delegate);
/*示获取视图和模型在索引 index 或列 column 或行 row 处使用的项目委托*/
QAbstractItemDelegate* itemDelegate() const;
QAbstractItemDelegate* itemDelegate(const QModelIndex &index) const;
QAbstractItemDelegate* itemDelegateForColumn(int column) const;
QAbstractItemDelegate* itemDelegateForRow(int row) const;
```

### 与编辑有关的函数

```cpp
/*若索引 index 指定的项目是可编辑的，则编辑该项目*/
void edit(const QModelIndex &index);
/*在索引index处开始编辑项目，必要时创建编辑器，若视图的State(状态)为EditingState，则返回 true，否则返回 false。参数 trigger 指定引起编辑的方式，相关的事件由 event描述。若把 trigger 指定为 QAbstractItemView::AllEditTriggers，则可以强制编辑*/
virtual bool edit(const QModelIndex &index, EditTrigger trigger, QEvent *event);
/*将编辑器 editor 中的数据提交给模型*/
virtual void commitData(QWidget *editor);
/*关闭编辑器 editor，然后释放它，参数 hint 用于指示视图应如何响应编辑操作结束时的行为，比如 hint 可以表示当编辑操作结束时，打开视图中的下一个项目进行编辑*/
virtual closeEditor(QWidget *editor,QAbstractItemDelegate::EndEditHint hint);
/*销毁编辑器 editor*/
virtual void editorDestroyed(QObject *editor);
/*在索引 index 处打开持久编辑器，若没有编辑器，则委托将创建一个新的编辑器。普通编辑器当离开该项目时会自动关闭，而持久编辑器则会一直存在，直到调用colsePersistentEditor()关闭*/
void openPersistentEditor(const QModelIndex &index);
/*返回索引 index 处项目的持久编辑器是否已打开。*/
bool isPersistentEditorOpen(const QModelIndex &index) const;
/*关闭索引 index 处的持久编辑器*/
void closePersistentEditor( const QModelIndex &index);
```

### 与选择有关的函数

```cpp
/*返回当前的选择模型*/
QItemSelectionModel *selectionModel() const;
/*把当前的选择模型设置为 selectionModel*/
virtual void setSelectionModel(QItemSelectionModel *selectionModel);
/*取消所有选择的项目，当前索引不会被改变*/
void clearSelection();
/*选择视图中的所有项目*/
virtual void selectAll();
/*返回视图中所有可被选择项目和非隐藏项目的索引列表，该列表不包含重复项目，且未排序*/
virtual QModelIndexList selectedIndexes() const;
/*返回在更新包含索引 index 的选择时，使用的 SelectionFlags(选择标志)，事件 event 是用户输入事件，比如鼠标或键盘事件*/
virtual QItemSelectionModel::SelectionFlags selectionCommand(const QModelIndex &index,const QEvent *event =Q_NULLPTR) const;
/*当选择改变时，调用此槽函数，deselected 表示之前的选择(可能为空)，selected 表示新的选择*/
virtual void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) const;
```

### 与索引有关的函数

```cpp
/*返回当前项目的模型索引*/
QModelIndex currentIndex() const;
/*索引 index 处的项目设置为当前项目*/
void setCurrentIndex(const QModelIndex &index);
/*返回模型根项目的模型索引，根项目是视图的顶级项目的父项目，根目录的索引可能是无效索引*/
QModelIndex rootIndex() const;
/*把索引 index 所指项目设置为根项目*/
virtual void setRootIndex(const QModelIndex &index);
```

### 与滚动有关的函数

```cpp
/*表示将视图滚动到底/顶部*/
void scrollToBottom();
void scrollToTop();
/*将区域 region 标记为脏区域(Dirty Region),，并安排更新，只有在自定义视图子类时，才需调用此函数*/
void setDirtyRegion(const QRegion &region);
/*返回视图中 Dirty Region(脏区域)的偏移量。若使用 ScrollDirtyRegion()并在该类的子类中实现了paintEvent()，则应使用从该函数返回的偏移量来转换paint事件给出的区域。*/
QPoint dirtyRegionOffset() const;
/*通过在相反方向移动脏区域，以使视图滚动(dx,dy)像素。只有在自定义视图子类实现滚动视口时，才需调用此函数。若在该类的子类中重新实现*/
void scrollDirtyRegion(int dx, int dy);
/*QAbstractScrollArea::viewportSizeHint()的重新实现。返回视口的大小提示*/
virtual QSize viewportSizeHint() const;
/*则此函数用于处理工具提示、What's this 模式，对于其他事件，则传递给父类的 viewportEvent()函数处理*/
virtual bool viewportEvent(QEvent *event);
```

### 与外观有关的函数

```cpp
/*返回由视图的调色板(palette)、字体(font)、状态、对齐等填充的 QStyleOptionViewItem结构*/
virtual QStyleOptionViewItem viewOptions() const;
/*返回索引 index 所指项目的大小提示或无效索引的无效大小*/
QSize sizeHintForIndex(const QModelIndex &index) const;
/*返回列 column 的宽度大小提示，若没有模型，则返回-1，此函数用于具有水平标头的视图，以根据列 column 查找标头部分的大小提示*/
virtual int sizeHintForColumn(int column) const;
/*返回行 row 的高度大小提示，若没有模型，则返回-1，此函数用于具有垂直标头的视图，以根据列 row 查找标头部分的大小提示*/
virtual int sizeHintForRow(int row) const;
/*更新索引 index 占用的区域*/
void update(const QModelIndex &index) ;
/*更新视图的子部件的几何形状*/
virtual void updateGeometries();
```

### 其他函数

```cpp
/*返回索引 index 处的 QWidget 部件*/
QWidget* indexWidget(const QModelIndex &index) const;
/*把部件 widget 设置到索引 index 所指项目上，并把部件 widget 的所有权传递给视口*/
void setIndexWidget(const QModelIndex &index, QWidget *widget);
/*返回或设置项目视图的状态，通常只在重新实现自已的视图时才有意义*/
State state() const;
void setState(State state);
/*重置视图的内部状态。此函数将重置编辑器、滚动条位置、选择等，并且现在的更改不会被提交*/
virtual void reset();
/*移动并选择与字符串 search 最匹配的项，若没有该项目，则什么都不会发生*/
virtual void keyboardSearch(const QString &search);
/*当在模型中更改具有角色 roles 的项目时，会调用此槽函数，更改的项目范围为 topLeft到 bottomRight，若只有一个项目被改变，则 topLeft == bottomRight。若 roles 为空，则意味着所有项目都已更改*/
virtual void dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, 
const QVector<int> &roles = QVector<int>());
/*当新项目成为当前项目时，会调用此槽函数，previous 表示上一个当前项目，current表示新项目。*/
virtual currentChanged(const QModelIndex &current, const QModelIndex &previous);
/*当行即将被移除时，调用此槽函数，移除的行是父级 parent 下从 start 开始到 end 结束的行。*/
virtual void rowsAboutToBeRemoved(const QModelIndex &parent, int start, int end);
/*在插入行时调用此槽函数，新行是父级 parent 下从 start 开始到 end 结束的行*/
virtual void rowsInserted(const QModelIndex &parent, int start, int end);
/*执行预定的布局(Scheduled Layout)，而无需等待事件处理开始*/
void executeDelayedItemsLayout();
/*计划视图中项目的布局，以便在事件处理开始时执行。即使在事件处理之前多次调用该函数，视图也只会执行一次布局*/
void scheduleDelayedItemsLayout()
```