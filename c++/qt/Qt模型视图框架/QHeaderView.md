# QHeaderView

> QHeaderView 继承自 QAbstractItemView。该类是 Qt 实现的表准视图之一，为项目视图提供了表头列和表头行

## 基本原理

* 并不是所有数据的角色(Qt::ItemDataRole枚举)都能应用于表头视图，表头只支持以下的角色：`Qt::DisplayRole`、`Qt::FontRole`、`Qt::DecorationRole(图表)`、`Qt::ForegroundRole`、`Qt::BackgroundRole`、`Qt::TextAlignmentRole`,若要使用自定义角色的数据，需要重写`paintEvent()`函数自行绘制
* 表头会渲染每个段自身的数据，并不依赖于委托，因此调用`setItemDelegate()`是无效的

## 信号

```cpp
/*当标头的几何形状发生变化时，发送此信号。改变段的大小并未改变标头的几何形状，在最小化时会发送此信号*/
void gemetriesChanged();
/*当点击标头的某个段时发送此信号，logicalIndex 表示被点击的段的逻辑索引。注意：还会发送 sectionPressed()信号*/
void sectionChanged(int logicalIndex);
/*当点击标头的某个段时发送此信号，logicalIndex 表示被点击的段的逻辑索引。*/
void sectionPressed(int logicalIndex);
/*当双击某个段时，发送此信号。logicalIndex 表示被双击的段的逻辑索引*/
void sectionDoubleClicked(int logicalIndex);
/*当双击某个段时，发送此信号。logicalIndex 表示被双击的段的逻辑索引*/
void sectionHandleDoubleClicked(int logicalIndex);
/*当某段上按下鼠标左键不放并将光标移至另一段时，发送此信号，logicalIndex 表示光标移动到的段的逻辑索引*/
void sectionEntered(int logicalIndex);
/*当移动某个段时，发送此信号，logicalIndex 表示被移动的段的逻辑索引，oldVisualIndex表示旧索引，newVisualIndex 表示新索引*/
void sectionMoved(int logicalIndex,int oldVisualIndex,int newVisualIndex);
/*当段数量发生变化时(比如添加或删除段)，发送此信号。oldCount 表示旧的数量，newCount 表示新的数量*/
void sectionCountChanged(int oldCount,int newCount);
/*当段被调整大小时，发送此信号，logicalIndex 为该段的逻辑索引，oldSize 为旧的大小，newSize 为调整后的大小*/
void sectionResized(int logicalIndex,int oldSize,int newSize);
/*当含有排序指示符的段或指示的顺序发生变化时，发送此信号，该段的逻辑索引由logicalIndex 指定，排序顺序由 order 指定*/
void sortIndicatorChanged(int logicalIndex,Qt::SortOrder ordere
;```

## 属性

```cpp
/*第一个段的是否可移动*/
Q_PROPERTY(bool firstSectionMovable READ isFirstSectionMovable WRITE setFirstSectionMovable)
/*是否显示排序指示符*/
Q_PROPERTY(bool showSortIndicator READ isSortIndicatorShown WRITE setSortIndicatorShown)
/*是否突出显示所选项目的段*/
Q_PROPERTY(bool highlightSections READ isSortIndicatorShown WRITE setSortIndicatorShown)
/*表头中最后一个可见段是否拉伸至所有可用空间*/
Q_PROPERTY(bool stretchLastSection READ stretchLastSection WRITE setStretchLastSection)
/*当用户调整大小的段达到最小大小后，是否关联到下一个段*/
Q_PROPERTY(bool cascadingSectionResizes READ cascadingSectionResizes WRITE setCascadingSectionResizes)
/*表头段的默认大小*/
Q_PROPERTY(int defaultSectionSize READ defaultSectionSize WRITE setDefaultSectionSize RESET resetDefaultSectionSize)
/*表头段的最小大小，若设置为 -1 ，将使用 QApplication::globalStrut 属性或QFontMetrics::fontMetrics()的最大大小*/
Q_PROPERTY(int minimumSectionSize READ minimumSectionSize WRITE setMinimumSectionSize)
/*表头段的最大大小，默认值为 1048575，若设置为-1，将重置为最大的段大小*/
Q_PROPERTY(int maxmumSectionSize READ maximumSectionSize WRITE setMaximumSectionSize)
/*表头段中文本的对齐方式。*/
Q_PROPERTY(Qt::Alignment defaultAlignment READ defaultAlignment WRITE setDefaultAlignment)

```

## 函数

### 隐藏/显示表头

* 若隐藏表头的某一段会同时隐藏该段所对应的模型数据，若只想隐藏表头而不是隐藏模型数据使用`QWidget::setHidden()`函数,不过该函数会隐藏整个表头

```cpp
/*hide 为 true，则隐藏由 logicalIndex 指定的段，否则显示该段*/
void hideSection(int logicalIndex);
void setSectionHidden(int logicalIndex,bool hide);
/*显示由由 logicalIndex 指定的段*/
void showSection(int logicalIndex);
/*返回表中已隐藏的段的数量*/
int hiddenSectionCount() const;
/*logicalIndex 所指的段对用户是隐藏的，则返回 true，否则返回 false*/
bool isSectionHidden(int logicalIndex) const;
/*若表头中的段被隐藏，则返回 true，否则返回 false*/
bool sectionsHidden() const;
```

### 表头的索引和位置

* 可视索引`visualIndex`,逻辑索引`logicalIndex`,位置`position`
* 索引从0开始，位置以像素为单位
* 逻辑索引:为表头的段所拥有，也就是说无论表头移动到何处，逻辑索引都不会发生变化
* 可视索引:即视图上所看到的段的索引，即使该段隐藏，也不会隐藏可视索引
* 位置:是从单元格的左侧或顶部开始计算

```cpp
/**/
int logicalIndex(int visualIndex) const;
/*返回位置position或坐表(x,y)或点pos处段的逻辑索引。水平表头使用x坐表，垂直表头使用y坐表*/
int logicalIndexAt(int position);
int logicalIndexAt(int x,int y) const;
int logicalIndexAt(const QPoint &pos) const;
/*返回逻辑索引 logicalIndex 所指段的可视索引，隐藏的段的可视索引仍然有效*/
int visualIndex(int logicalIndex) const;
/*返回位置 position 处段的可视索引*/
int visualIndex(int position) const;
/*返回逻辑索引 logicalIndex 的位置。若该段被隐藏了，则返回-1*/
int sectionPosition(int logicalIndex) const;
/*返回逻辑索引 logicalIndex 的视口位置。若该段被隐藏了，则返回的值未定义*/
int sectionViewportPosition(int logicalIndex) const
```

### 获取表头的基本信息

```cpp
/*返回表头的段数*/
int count() const;
/*返回表头的长度*/
int length() const;
/*返回逻辑索引所指段的长度*/
int sectionSize(int logicalIndex) const;
/*返回表头的方向*/
Qt::Orientation orientation() const;
/*返回逻辑索引所指段的大小提示*/
int sectionSizeHint(int logicalIndex) const;
```

### 移动表头

```cpp
/*若 movable 为 true，则用户可以拖动表头，否则不能拖动，但可使用编程方式移动*/
bool sectionsMovable() const;
void setSectionsMovable(bool movable);
/*若表头中的段已被移动，则返回 true，否则返回 false*/
bool sectionsMoved() const;
/*获取/设置表头的偏移量*/
int offset() const ;
void setOffset(int offset);
/*交换可视索引 first 指定的段与可视索引 second 指定的段*/
void swapSections(int first, int second);
```

### 修改表头大小

```cpp
/*返回大小调整模式*/
ResizeMode sectionResizeMode(int logicalIndex) const;
void setSectionResizeMode(ResizeMode mode);
void setSectionResizeMode(int logicalIndex, ResizeMode mode);
/*根据大小调整模式 mode 调整各段的大小*/
void resizeSections(QHeaderView::ResizeMode mode);
/*返回大小调整模式被设置为 Stretch(拉伸)的段的数量*/
int stretchSectionCount() const;
/*调整由逻辑索引 logicalIndex 所指段的大小为 size(以像素为单位)，参数 size 必须大于或等于 0，不建议使用 0(此时应隐藏该段)*/
void resizeSection(int logicalIndex, int size);
/*设置表头视图在使用大小调整模式 ResizeToContents 调整大小时的精确度。默认值为1000*/
int resizeContentsPrecision() const;
void setResizeContentsPrecision(int precision);
```

### 排序及保存/恢复表头

```cpp
/*为由逻辑索引 logicalIndex 所指的段按照 order 指定的顺序设置排序指示符，并移除其他段中的排序指示符。该函数只负责设置排序指示符的位置，不一定具有排序功能。*/
void setSortIndicator(int logicalIndex, Qt::SortOrder order);
/*返回排序指示符的顺序，若该段没有排序指示符，则返回值是未定义的*/
Qt::SortOrder sortIndicatorOrder() const;
/*返回具有排序指示符的段的逻辑索引，默认为 0*/
int sortIndicatorSection() const;
/*保存/恢复表头视图的状态*/
QByteArray saveState() const,
bool restoreState(const QByteArray &state);
```

### 表头是否可被点击

```cpp
/*若表头是可点击的，则返回 true，否则返回 false*/
bool sectionsClickable() const;
/*若 clickable 为 true，则表头将响应单击*/
void setSectionsClickable(bool clickable);
```

### 槽

#### 公有槽函数

```cpp
/*使用方向 orientation 更新已更改的标头段，从 logicalFirst 更新到 logicalLast*/
void headerDataChanged(Qt::Orientation orientation,int logicalFirst,int logicalLast);
/*设置偏移量以使最后一段可见*/
void setOffsetToLastSection();
/*把偏移量设置为 visualSectionNumber 处的段的起始位置*/
void setOffsetToSectionPosition(int visualSectionNumber);
```

#### 保护槽函数

```cpp
/*根据段的大小提示调整段的大小，通常不需要调用此槽函数*/
void resizeSections();
/*从父级 parent 删除段时，调用此槽函数，logicalFirst 和 logicalLast 表示被删除的段的位置，若只有一个节点，他们是相等的*/
void sectionsAboutToBeRemoved(const QModelIndex &parent,int logicalFirst,int logicalLast);
/*当段插入到父级 parent 时，调用此槽函数，logicalFirst 和 logicalLast 表示被插入的段的位置，若只有一个节点，他们是相等的*/
void sectionsInserted(const QModelIndex &parent,int logicalFirst,int logicalLast);
```

