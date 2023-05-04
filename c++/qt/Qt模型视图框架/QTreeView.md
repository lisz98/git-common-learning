# QTreeView

> QTreeView 继承自 QAbstractItemView。该类是 Qt 实现的标准视图之一，实现了一个显示树形结构的视图

## 属性

```cpp
/*自动扩展延迟，在拖放操作时自动打开或关闭树节点之前的延迟时间(以毫秒为单位)，若小于 0，则禁用自动扩展，默认为-1*/
Q_PROPERTY(int autoExpandDelay READ autoExpandDelay WRITE setAutoExpandDelay)
/*描述节点的缩进量(以像素为单位)，顶级节点是指从视口边缘到第 1 列的水平距离，子节点的缩进量相对于父节点。默认取决于样式*/
Q_PROPERTY(int indentation READ indentation WRITE setIndentation RESET resetIndentation)
/*是否显示顶级项目用于展开和折叠顶级项目的控件，默认为 true(显示)*/
Q_PROPERTY(bool rootIsDecorated READ rootIsDecorated WRITE setRootIsDecorated)
/*确保所有数据项是否具有相同的高度，默认为 false(不确保具有相同高度)*/
Q_PROPERTY(bool uniformRowHeights READ uniformRowHeights WRITE setUniformRowHeights)
/*节点是否可由用户展开和折叠，默认为 true(允许展开和折叠)*/
Q_PROPERTY(bool itemsExpandable READ itemsExpandable WRITE setItemsExpandable)
/*是否启用排序，默认为 false(不启用)。为提高性能，建议在项目插入树中之后启用排序*/
Q_PROPERTY(bool sortingEnabled READ isSortingEnabled WRITE setSortingEnabled)
/*是否启用动画，若为 false(默认值)，则树视图会立即展开或折叠分支；若为 true，则会动画展开和折叠分支*/
Q_PROPERTY(bool animated READ isAnimated WRITE setAnimated)
/*设置键盘焦点是否显示至所有列，默认为 false(即只有一列显示焦点)*/
Q_PROPERTY(bool allColumnsShowFocus READ allColumnsShowFocus WRITE setAllColumnsShowFocus)\
/*设置数据项中的文字是否自动换行，默认为 false(不换行)*/
Q_PROPERTY(bool wordWrap READ wordWrap WRITE setWordWrap)
/*是否隐藏标头，默认为 false(不隐藏)。*/
Q_PROPERTY(bool headerHidden READ isHeaderHidden WRITE setHeaderHidden)
/*是否可使用双击展开和折叠节点*/
Q_PROPERTY(bool expandsOnDoubleClick READ expandsOnDoubleClick WRITE setExpandsOnDoubleClick)
```

## 函数

### 普通函数

```cpp
/*根据 expanded 的值，将索引 index 所指节点设置为展开或折叠*/
void setExpanded(const QModelIndex &index, bool expanded);
/*若索引 index 所指节点是展开的则返回 true，否则返回 false*/
bool isExpanded(const QModelIndex &index) const;
/*返回x坐标所在列*/
int columnAt(int x) const;
/*返回视口中列 column 的水平位置*/
int columnViewportPosition(int column) const;
/*返回或设置列 column 的宽度*/
int columnWidth(int column);
void setColumnWidth(int column,int width);
/*获取和设置视图的标头，设置标头后，该视图拥有该标头的所有权*/
QHeaderView *header() const;
void setHeader(QHeaderView *header);
/* hide 为 true，则隐藏行 row 或列 column，否则显示该行或列*/
void setRowHidden(int row, const QModelIndex &parent, bool hide);
void setColumnHidden(int column, bool hide);
/*若列 column 或父节点 parent 中的行 row 是隐藏的，则返回 true，否则返回 false*/
bool isRowHidden(int row, const QModelIndex &parent) const;
bool isColumnHidden(int column) const;
/*返回索引 index 上方或下方的模型索引。*/
QModelIndex indexAbove(const QModelIndex &index) const;
QModelIndex indexBelow(const QModelIndex &index) const;
/*若父级 parnet 的行 row 中第 1 列的节点跨越所有列，则返回 true，否则返回 false*/
bool isFirstColumnSpanned(int row,const QModelIndex &parent) const;
/*若 span 为 true，则把父级 parnet 的行 row 中第 1 列的节点设置为跨越所有列，否则显示在行 row 中的所有项*/
void setFirstColumnSpanned(int row,const QModelIndex &parent,bool span);
/*设置和返回树的逻辑索引,若为-1，则表示树放置在可视索引 0 上*/
void setTreePosition(int index);
int treePosition() const;
/*按列 column 进行排序(升序/降序)*/
void sortByColumn(int column, Qt::SortOrder order);
```

### 槽函数

#### 公有槽

```cpp
/*折叠或展开索引 index 所指节点或所有节点*/
void collapse(const QModelIndex &index);
void collapseAll();
void expand(const QModelIndex &index);
void expandAll();
/*将所有可展开的节点，展开至给定的深度 depth*/
void expandToDepth(int depth);
/*根据其内容调整列 column 的大小*/
void resizeColumnToContents(int column);
/*显示/隐藏列 column*/
void showColumn(int column);
void hideColumn(int column);
```

#### 受保护槽

```cpp
/*通知树视图列数已从 oldCount 更改为 newCoun*/
void columnCountChanged(int oldCount,int newCount);
/*当列被移除时，调用此槽函数*/
void columnMoved();
/*当表头的大小更改时，调用该槽函数*/
void columnResized(int column,int oldSize,int newSize);
/*通知视图，从 start 开始的行到 end 结束的行已从父索引 parent 中移除*/
void rowsRemoved(const QModelIndex &parent, int start, int end)；
```

### 受保护的函数

```cpp
/*使用绘制器painter在与索引index相同的行上，由rect指定的矩形中绘制树视图中的分支*/
virtual void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index);
/*使用绘制器 painter 在包含索引 index 的树视图中绘制行*/
virtual void drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
/*使用绘制器 painter 绘制树中与区域 region 相交的部分*/
void drawTree(QPainter *painter, const QRegion &region) const;
/*返回索引 index 所指的行的大小提示*/
int indexRowSizeHint(const QModelIndex &index) const;
/*返回索引 index 所指行的高度*/
int rowHeight(const QModelIndex &index) const;
```

### 信号

```cpp
/*当 index 所指节点折叠或展开时，发送以上信号*/
void collapsed(const QModelIndex &index);
void expanded(const QModelIndex &index);
```