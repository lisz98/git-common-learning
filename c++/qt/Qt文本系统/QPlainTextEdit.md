# QPlainTextEdit

## 基本原理

* `QPlainTextEdit`类继承自`QAbstractScrollArea`类，该类用于编辑和显示纯文本，该类不支持表格和嵌入式框架，并且不适用高精度的像素滚动方式，而是使用逐行段滚动的方式，但该类具有很好的性能优势，并且能够处理更大的文档。
* 向QPlainTextEdit类中添加和获取内容的函数如下:
    * `setDocument()、ducument()`
    * `setPlainText()、insertPlainText()、appendPlainText()、toPlainText()\`
    * `appendHtml()`
* 要设置字符的格式，需使用以下函数:
    * `setCurrentCharFormat()`
    * `currentCharFormat()`
    * `mergeCurrentCharFormat()`
* 要实现自定义弹出菜单，需实现
    * `contextMenuEvent()`
    * `createStandardContextMenu()`
* 要实现拖放或粘贴自定义的MIME数据需重新实现以下函数
    * `canInsertFromMimeData()`
    * `createMimeFromSelection()`
    * `insertFromMimeData()`

## 默认支持键盘操作

|按键|说明|
|----|----|
|四个方向键|向指定方向移动一个字符|
|Ctrl+四个方向键|向指定方向移动一个单词|
|Shift+四个方向键|向指定方向选择文本|
|Home、End|移至行的开头或结尾|
|Ctrl+Home、Ctrl+End|移至文本开头或结尾|
|PageUp、PageDown|向上或向下移动一个页面(视口)|
|Ctrl + A、Ctrl+C、Ctrl+V、Ctrl+X|全选、复制、粘贴、剪切|
|Ctrl+K|删除到行尾|
|Ctrl+Z、Ctrl+Y|撤消、重做|
|Backspace、Delete|删除左侧或右侧字符|
|Shift+Delete、Shift+Insert|剪切、粘贴|
|Alt + 鼠标滚轮|水平滚动|
|Ctrl + 鼠标滚轮|放大文本|

## 枚举

```cpp
enum LineWrapMode{
    NoWrap,     /*不换行*/
    WidgetWidth /*在右侧空白处换行，以保持整个单词是完整的*/
}
Q_ENUM(LineWrapMode)
```

## 属性

```cpp
/*描述 tab 键是用于输入制表符，还是用于接受焦点。默认为 false(不接受焦点，输出制表符)。此属性若为 true，需在按下 tab 键有另一个部件接受焦点时才会起作用*/
Q_PROPERTY(bool tabChangesFocus READ tabChangesFocus WRITE setTabChangesFocus)
/*获取和设置文档的标题，注意：不是 QPlainTextEdit 的标题。默认为空字符串*/
Q_PROPERTY(QString documentTitle READ documentTitle WRITE setDocumentTitle)
/*是否启用撤消/重做*/
Q_PROPERTY(bool undoRedoEnabled READ isUndoRedoEnabled WRITE setUndoRedoEnabled)
/*设置文本的换行模式*/
Q_PROPERTY(LineWrapMode lineWrapMode READ lineWrapMode WRITE setLineWrapMode)
/*设置文本的换行模式。默认为 QTextOption::WrapAtWordBoundaryOrAnywhere*/
QDOC_PROPERTY(QTextOption::WrapMode wordWrapMode READ wordWrapMode WRITE setWordWrapMode)
/*编辑器是否为只读。默认为 false*/
Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
/*获取或设置编辑器的内容，设置此属性时，之前的内容将被删除，且撤消/重做历史会被重置。默认情况下对于没有内容的编辑器，此属性为空字符串*/
Q_PROPERTY(QString plainText READ toPlainText WRITE setPlainText NOTIFY textChanged USER true)
/*用户输入的文本是否覆盖现有文本，设置此属性类似于 office 中的插入功能*/
Q_PROPERTY(bool overwriteMode READ overwriteMode WRITE setOverwriteMode)
#if QT_DEPRECATED_SINCE(5,10)
Q_PROPERTY(int tabStopWidth READ tabStopWidth WRITE setTabStopWidth)
#endif
/*设置制表符的距离(以像素为单位)，默认为 80*/
Q_PROPERTY(qreal tabStopDistance READ tabStopDistance WRITE setTabStopDistance)
/*以像素为单位设置插入符的宽度，默认为 1*/
Q_PROPERTY(int cursorWidth READ cursorWidth WRITE setCursorWidth)
/*设置在显示文本时，应如何与用户输入交互。默认取决于编辑器是否是只读*/
Q_PROPERTY(Qt::TextInteractionFlags READ textInteractionFlags WRITE setTextInteractionFlags)
/*获取文档的块数，默认情况下，空文档为 1。对于纯文本，通常一个段落(使用换行符分隔)就相当于 1 块*/
Q_PROPERTY(int blockCount READ blockCount)
/*文档的最大块数。若文档中的块数多于设置的最大块数，则从文档的开头删除，此属性会立即作用于文档，且该属性还会禁用撤消/重做历史。若该属为负或 0，则表示有无限的块数，默认为 0*/
Q_PROPERTY(int maximumBlockCount READ maximumBlockCount WRITE setMaximumBlockCount)
/*是否设置调色板背景，该属性可用于在视觉上区分哪些区域是文档未覆盖的区域，哪些是文档覆盖的区域，默认为 false*/
Q_PROPERTY(bool backgroundVisible READ backgroundVisible WRITE setBackgroundVisible)
/*滚动时是否可以使插入符居中，设置该属性后，还允许编辑器滚动到文档的末尾之下*/
Q_PROPERTY(bool centerOnScroll READ centerOnScroll WRITE setCenterOnScroll)
/*设置占位符文本，只要 document()为空，便会使编辑器显示一个灰色的占位符文本*/
Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)

```

## 函数

### 字符格式

```cpp
/*返回插入新文本时使用的字符格式*/
QTextCharFormat currentCharFormat() const;
/*设置字符格式，若有选择的文本，则格式应用于该文本，否则格式应用于插入符处(若在该处接着输入文本，该文本会以以设置的格式显示)*/
void setCurrentCharFormat(const QTextCharFormat &format);
/*把字符格式 modifier 合并到文本。若有选择的文本，则格式应用于该文本，否则格式应用于插入符处(若在该处接着输入文本，该文本会以以设置的格式显示)*/
void mergeCurrentCharFormat(const QTextCharFormat &modifier);
```

### 插入符

```cpp
/*滚动文本，以确保插入符可见*/
void ensureCursorVisible();
/*设置或返回当前可见光标的 QTextCursor 副本，注意：返回的光标不会影响编辑器当前的光标*/
void setTextCursorr(Const QTextCursor &cursor);
QTextCursor textCursor() const;
/*在pos位置(视口坐标)返回一个QTextCursor*/
QTextCursor cursorForPosition(const QPoint &pos) const;
/*返回包含cursor的矩形*/
QRect cursorRect(const QTextCursor &cursor) const;
/*返回文本编辑器插入符的矩形(视口坐标)*/
QRect cursorRect() const;
/*使用由 selections 指定的颜色临时标记文档中的某些区域*/
QList<QTextEdit::ExtraSelection> extraSelection() const;
void setExtraSelection(const QList<QTextEdit::ExtraSelection> &selections);
/*通过 operation 移动插入符，此函数可用于以编程的方式操作插入符*/
void moveCursor(QTextCursor::MoveOperation operation,QTextCursor::MoveMode mode =QTextCursor::MoveAnchor);
moveCursor(QTextCursor::Left, QTextCursor::MoveAnchor);//向左移动一个字符
moveCursor(QTextCursor::Left, QTextCursor::KeepAnchor);//向左移动一个字符并选择该字符，相当于移动的同时按住了 Shift 键
/*把 document 设置为编辑器的新文档，编辑器不会获取 document 所有权，document 必须具有继承 QPlainTextDocumentLayout 的文档布局*/
void setDocument(QTextDocument *document);
QTextDocument *ducument() const;
```

### 查找、锚点、打印、资源及判断是否可粘贴

```cpp
/*使用给定的规则options(即向前、向后查找、是否区分大小写)查找下一个与exp匹配的字符串*/
bool find(const QString &exp,QTextDocument::FindFlags options =QTextDocument::FinFlags());
bool find(const QRegExp &exp, QTextDocument::FindFlags options = QTextDocument::FindFlags());
/*返回点 pos 处锚点的引用，若 pos 处不存在锚点，则返回一个空字符串*/
QString anchorAt(const QPoint &pos) const;
/*返回文本是否可以从剪贴板粘贴到编辑器中。比如若剪贴板中是从屏幕上剪切的图片时，便不能被粘贴到编辑器中。注意，若复制的是文件，则会粘贴该文件的路径，因此是可粘贴的*/
bool canPaste() const;
/*使用 printer 打印编辑器的文档。该函数还支持 QPrinter::Selection 作为打印范围*/
void print(QPagedPaintDevice *printer) const;
/*加载由 type 和 name 指定的资源，该函数是 QTextDocument::loadResource()的扩展*/
virtual QVariant loadResource(int type,const QUrl &name);
```

### 槽

```cpp
/*复制、剪切、粘贴、撤消、重做、选择所有文本*/
void copy();
void cut();
void paste();
void undo();
void redo();
void selectAll();
/*删除编辑器中的所有文本，注意：还会清除撤消/重做历史记录*/
void clear();
/*插入文本*/
void appendHtml(const QString &html);
void appendPlainText(const QString &text);
void insertPlainText(const QString &text);
/*放大缩小*/
void zoomOut(int range =1);
void zoomIn(int range =1);
/*滚动文档并使插入符垂直居中*/
void centerCursor();
```

### 受保护的函数

```cpp
/*以内容坐标的形式返回文本块 block 的边界矩形，使用 contentOffset()函数转换矩形以获得视口上的坐标*/
QRectF blockBoundingGeometry(const QTextBlock &block) const;
/*返回文本块 block 在块自身坐标中的边界矩形*/
QRectF blockBoundingRect(const QTextBlock &block) const;
/*返回第一个可见的块*/
QTextBlock firstVisibleBlock() const;
/*返回在视口坐标中内容的原点*/
QPointF contentOffset() const;
/*返回视口的 PaintContext(绘图上下文)，仅在重新实现 paintEvent()时有用*/
QAbstractTextDocumentLayout::PaintContext getPaintContext() const;
```

### 信号

```cpp
/*当块数发生变化时，发送此信号，newBlockCount 为新的块数*/
void blockCountChanged(int newBlockCount);
/*每当选择改变时，都会发送此信号*/
void selectionChanged();
/*在编辑器中的文本被选择或取消所有选择时发送此信号，若有文本被选择，则 yes 为
true，若没有文本被选择则 yes 为 false*/
void copyAvailable();
/*当插入符的位置改变时，发送此信号*/
void cursorPositionChanged();
/*只要文档被修改，就发送此信号，若 changed 为 true，则表示文档已修改*/
void modificationChanged(bool changed);
/*只要文档内容发生变化就发送此信号，该信号与 modificationChanged 的区别是，比如我们在同一个字符上重复使用同一个格式，此时会连续发送该信号*/
void textChanged();
/*只要重做操作变为可用或不可用，就会发送此信号*/
void redoAvialable();
/*只要撤消操作变为可用或不可用，就会发送此信号*/
void undoAvialable();
/*当文本文档需要更新矩形 rect 时，发送此信号*/
void updateRequest(const QRect &rect,int dy);
```

### 菜单处理

```cpp
/*若需要自定义或扩展标准上下文菜单需要重新实现此函数。若要禁用弹出菜单，可设置 QWidget::contextMenuPolicy 属性为值 Qt::NoContextMenu*/
virtual void contextMenuEvent(QContextMenuEvent* e);
/*创建标准上下文菜单*/
QMenu *createStandardContextMenu();
QMenu *createStandardContextMenu(const QPoint &position);
```

## 实列

```cpp
#pragma once

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QtWidgets>

class myPlainTextEdit :public QWidget {
	Q_OBJECT
private:
	QPushButton *btn;
	QPlainTextEdit *edit;
	void init() {
		edit = new QPlainTextEdit(this);
		edit->resize(333, 333);
		btn = new QPushButton("", this);
		btn->setGeometry(22, 355, 22, 22);
		btn->setShortcut(QKeySequence("Ctrl+F"));
		connect(btn, &QPushButton::clicked, this, &myPlainTextEdit::on_edit_click);
	}
public:
	myPlainTextEdit(QWidget *parent =nullptr) : QWidget(parent) { init(); }

private slots:
	void on_edit_click() {
		QTextCursor cursor = edit->textCursor();//获取编辑器内部文档的光标
		cursor.movePosition(QTextCursor::Start);//回到开头
		cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 1);
		cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, 4);//选择右边四个字符

		QTextCharFormat format;
		format.setBackground(QBrush(Qt::red));
		format.setForeground(Qt::yellow);


		//实现选中开头第一个字符到第四个字符并设置背景色红色，前景色黄色
		QTextEdit::ExtraSelection extraSelection;
		extraSelection.cursor = cursor;
		extraSelection.format = format;

		QList< QTextEdit::ExtraSelection> extras;
		extras.append(extraSelection);
		edit->setExtraSelections(extras); //使用 setExtraSelections 函数设置字符的格式
	}

};
```

```cpp
#pragma once

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QtWidgets>
#include <QMimeData>
class CustomPlainTextEdit :public QPlainTextEdit
{
	Q_OBJECT
protected:
	/*自定义弹出菜单*/
	void contextMenuEvent(QContextMenuEvent *e) override{
#if 0
		QMenu *menu = createStandardContextMenu();//创建一个与qt弹出菜单一样的
		menu->addAction("是否退出", [=]() { menu->close(); });
		menu->exec(QCursor::pos());
#else
		QMenu *menu = new QMenu("自定义菜单啊");
		menu->addActions({
		new QAction("自定义动作1"),
		new QAction("自定义动作2"),
		new QAction("自定义动作3")
			});
		menu->exec(QCursor::pos());
#endif

	}

	bool canInsertFromMimeData(const QMimeData *source) const override{
		qDebug() << source->text();
		return true;
	}

	/*剪切复制会调用这个函数*/
	QMimeData *createMimeDataFromSelection() const override{
		QMimeData *mimeData = new QMimeData;
		mimeData->setText("自定义数据");
		return mimeData;

	}
public:
	CustomPlainTextEdit(QWidget *parent =nullptr) :QPlainTextEdit(parent){}
};

class widget :public QWidget
{
	Q_OBJECT
private:
	CustomPlainTextEdit *edit;
	void init() {
		edit = new CustomPlainTextEdit(this);
		edit->resize(600, 400);
		QMenuBar *menuBar = new QMenuBar(this);
		QMenu *menu = edit->createStandardContextMenu(QPoint(111, 111));
		menuBar->addMenu(menu);
		menu->addAction("自定义菜单");
		menu->menuAction()->setText("dasd");
	}
public:
	widget(QWidget *parent =nullptr) :QWidget(parent) { init(); }

};
```