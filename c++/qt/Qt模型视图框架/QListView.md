# QListView

> Qt实现的标准视图之一，实现了一个显示列表的视图

## 基本原理

* QListView继承自QAbstractItemView
* 列表视图没有水平和垂直的表头
* 列表视图可以按水平或垂直方向显示(由flow属性设置)
* 列表视图可以ListMode模式和IconMode模式显示(由viewMode属性设置)
* 列表视图中的项目还可以自由移动和捕捉(由movement属性设置)，自由移动是指数据项可以移至视图中的任何位置，而捕捉则只能将数据项移至属视图的概念网格中

## 属性

```cpp
/*移动方式(静态、自由、捕捉)*/
Q_PROPERTY(Movement movement READ movement WRITE setMovement)
/*项目排列方向*/
Q_PROPERTY(Flow flow READ flow WRITE setFlow)
/*项目是否自动换行*/
Q_PROPERTY(bool isWrapping READ isWrapping WRITE setWrapping)
/*是否自动布局*/
Q_PROPERTY(ResizeMode resizeMode READ resizeMode WRITE setResizeMode)
/*布局模式*/
Q_PROPERTY(LayoutMode layoutMode READ layoutMode WRITE setLayoutMode)
/*项目周围的空白空间大小*/
Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
/*网格的大小*/
Q_PROPERTY(QSize gridSize READ gridSize WRITE setGridSize)
/*视图模式(图标或列表)*/
Q_PROPERTY(ViewMode viewMode READ viewMode WRITE setViewMode)
/*显示模型中的哪一列*/
Q_PROPERTY(int modelColumn READ modelColumn WRITE setModelColumn)
/*项目是否具有相同的大小*/
Q_PROPERTY(bool uniformItemSizes READ uniformItemSizes WRITE setUniformItemSizes)
/*批处理数量*/
Q_PROPERTY(int batchSize READ batchSize WRITE setBatchSize)
/*是否换行*/
Q_PROPERTY(bool wordWrap READ wordWrap WRITE setWordWrap)
/*选中矩形是否可见*/
Q_PROPERTY(bool selectionRectVisible READ isSelectionRectVisible WRITE setSelectionRectVisible)
/*项目对齐的方式*/
Q_PROPERTY(Qt::Alignment itemAlignment READ itemAlignment WRITE setItemAlignment)
```

## 枚举

```cpp
/*描述项目的移动方式*/
enum Movement{ 
    Static, /*静态移动，表示项目不能被用户移动*/
    Free,   /*自由移动，显目可移动至视图任意位置*/
    Snap    /*捕捉，项目移动时会被捕捉到指定的网格*/
};
Q_ENUM(Movement)
/*描述项目的方向*/
enum Flow{
     LeftToRight, /*项目从左到右*/
     TopToBottom  /*项目从上到下*/
};
Q_ENUM(Flow)
/*描述项目改变大小时的布局方式*/
enum ResizeMode{
     Fixed, /*项目仅在第一次显示时布局，在视图调整大小时，项目将固定不动*/
     Adjust /*每次调整视图大小时都对项目进行布局*/
};
Q_ENUM(ResizeMode)
enum LayoutMode{ 
    SinglePass, /*项目一次性排序*/
    Batched     /*项目分批批量进行排序*/
};
Q_ENUM(LayoutMode)
/*描述列表视图的视图模式*/
enum ViewMode{
     ListMode,  /*列表模式，项目默认使用 TopToBottom 布局，且具有静态移动。*/
     IconMode   /*图标模式，项目默认使用 LeftToRight 排列，具有自由移动*/
};
Q_ENUM(ViewMode)
```

## 信号

```cpp
/*当索引indexes在视图中移动，发送此信号*/
void indexesMoved(const QModelIndexList &indexes);
```

## 函数

```cpp
/*清除QListView的特定属性标志*/
void clearPropertyFlags();
/*获取和设置行 row 的隐藏状态*/
bool isRowHidden(int row) const;
void setRowHidden(int row,bool hide);
/*返回模型中索引index所指项目的矩形(使用内容坐标)*/
QRect rectForIndex(const QModelIndex &index) const;
/*将索引index所指项目的位置设置为position，若列表视图为静态移动模式，则此函数将
不起作用*/
void setPositionForIndex(const QPoint &position,const QModelIndex &index);
```

