# QColumnView

> QColumnView 继承自 QAbstractItemView。该类是 Qt 实现的标准视图之一，实现了一个列视图  
> 列视图是一个级联的视图，在其中的每一列都通过使用一个QListView来显示其数据

## 属性

```cpp
/*调整大小的夹点是否可见，若不可见，则列视图将不能调整位置。默认为 true(可见)*/
Q_PROPERTY(bool resizeGripsVisible READ resizeGripsVisible WRITE setResizeGripsVisible)
```

## 函数

```cpp
/*获取视图中列的宽度*/
QList<int> columnWidths() const;
/*设置列的宽度。列表中多余的值被保留，在创建新列时会使用*/
void setColumnWidths(const QList<int> &list);
/*返回预览部件，若没有则返回 0*/
QWidget *previewWidget() const;
/*设置预览部件，该部件成为列的子项，并在删除列区域或设置新的部件时被销毁*/
void setPreviewWidget(QWidget *widget);
/*当预览部件被更新时发送此信号*/
void updatePreviewWidget(const QModelIndex &index);
/*返回一个视图用于列视图中显示内容。QColumnView 自动获取返回的视图的所有权。index为分配给模型的根索引*/
virtual QAbstractItemView * createColumn(const QModelIndex &index);
/*主要用于设置列视图的内容，比如设置列视图的滚动条、拖放等*/
void initializeColumn(QAbstractItemView *column) const;
```

## 实列

### 直接使用
```cpp
int main(int argc, char **argv) {
	QApplication app(argc, argv);

	QStandardItemModel *model = new QStandardItemModel;
	QColumnView *view = new QColumnView;
	view->resize(600, 400);
	QStandardItem *root = model->invisibleRootItem();
	
	QStringList stringNames{
		"hello","world","this","is","a","QColumnView","demo"
	};

	for (int i =0;i <stringNames.length();++i)
	{
		QStandardItem *item = new QStandardItem(stringNames.at(i));
		if (i > 0) {
			root->child(0, 0)->appendRow(item);
		}
		else {
			root->appendRow(item);
		}
	}
	view->setSelectionMode(QAbstractItemView::ExtendedSelection);

	QPushButton *btn = new QPushButton("预览");
	btn->resize(22, 22);
	view->setPreviewWidget(btn);
	view->setModel(model);
	view->show();

	return app.exec();
}
```

### 自定义
```cpp
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QtWidgets>

class CustomColumnWidget : public QColumnView
{
	Q_OBJECT
public:
	QAbstractItemView *createColumn(const QModelIndex &index)override{
		QListView *v = new QListView(viewport()); //使用列表视图显示内容

		this->initializeColumn(v);

		v->setRootIndex(index);

		if (model()->canFetchMore(index)) {
			model()->fetchMore(index);
		}

		return v;

	}
	
	void initializeColumn(QAbstractItemView *column) const  {

		column->setFrameShape(QFrame::Shape::Panel); //设置列表视图的样式
		column->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		column->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		column->setMinimumWidth(100);

#if QT_CONFIG(draganddrop)	
		column->setDragDropMode(dragDropMode());
		/*描述覆盖行为*/
		column->setDragDropOverwriteMode(dragDropOverwriteMode());
		column->setDropIndicatorShown(showDropIndicator());
#endif
		column->setAlternatingRowColors(alternatingRowColors());
		column->setAutoScroll(hasAutoScroll());
		column->setEditTriggers(editTriggers());
		column->setHorizontalScrollMode(horizontalScrollMode());
		column->setIconSize(iconSize());
		column->setSelectionBehavior(selectionBehavior());
		column->setSelectionMode(selectionMode());
		column->setTabKeyNavigation(tabKeyNavigation());
		column->setTextElideMode(textElideMode());
		column->setVerticalScrollMode(verticalScrollMode());
		column->setModel(model());
	}
};
```