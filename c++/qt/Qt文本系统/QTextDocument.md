# QTextDocument

## 基本原理

* QTextDocument是一个独立的类，该类用于处理格式化文本
* QTextDocument是结构化富文本文档的容器，支持样式化文本和各种类型的文档元素素(比如列表、表格、框架和图像)

## 枚举

1. 元对象信息
   ```cpp
   /*此枚举描述可以添加到文档的不同类型的元信息*/
    enum MetaInformation {
        DocumentTitle,//文档的标题
        DocumentUrl//文档的url。loadResource()函数在加载相对资源时使用这个url作为基础
    };   
   ```
2. 查找方式
    ```cpp
    /*这个enum描述QTextDocument的find函数可用的选项*/
    enum FindFlag
    {
        FindBackward        = 0x00001,//向后搜索而不是向前搜索
        FindCaseSensitively = 0x00002,//默认情况下，find工作不区分大小写。指定此选项会将行为更改为区分大小写的查找操作
        FindWholeWords      = 0x00004//使查找匹配只有完整的单词
    };
    Q_DECLARE_FLAGS(FindFlags, FindFlag)
    ```
3. 资源类型
    ```cpp
    /*这个enum描述了QTextDocument的loadResource()函数可以加载的资源类型*/
    enum ResourceType {
        HtmlResource  = 1,//资源包含HTML
        ImageResource = 2,//资源包含图像数据。目前不支持 QVariant::Icon
        StyleSheetResource = 3,//资源包含CSS

        UserResource  = 100
    };
    ```
4. 栈操作
   ```cpp
    enum Stacks {
        UndoStack = 0x01,//撤销堆栈
        RedoStack = 0x02,//重做堆栈
        UndoAndRedoStacks = UndoStack | RedoStack
    };
   ```
## 属性

1. 是否启用撤消/重做
   1. `undoRedoEnabled`
   2. `Q_PROPERTY(bool undoRedoEnabled READ isUndoRedoEnabled WRITE setUndoRedoEnabled)`
2. 获取和设置文档是否已被用户修改
    1. `modified`
    2. `Q_PROPERTY(bool modified READ isModified WRITE setModified DESIGNABLE false)`
3. 描述文档的页面大小
    1. `pageSize`
    2. `Q_PROPERTY(QSizeF pageSize READ pageSize WRITE setPageSize)`
4. 文档中文本使用的默认字体
    1. `defaultFont`
    2. `Q_PROPERTY(QFont defaultFont READ defaultFont WRITE setDefaultFont)`
5. 是否启用设计度量来提高文本布局的准确性，若不使用设计度量，将使`QAbstractTextDocumentLayout::setPaintDevice()`上设置的绘制设备的度量标准。若使用设计度量，则布局的宽度将不再依赖于提示和像素舍入。默认为false(不启用)
    1. `useDesignMetrics`
    2. `Q_PROPERTY(bool useDesignMetrics READ useDesignMetrics WRITE setUseDesignMetrics)`
6. 返回文档的实际大小
    1. `size`
    2. `Q_PROPERTY(QSizeF size READ size)`
7. 设置文本的宽度
    1. `textWidth`
    2. `Q_PROPERTY(qreal textWidth READ textWidth WRITE setTextWidth)`
8. 文本块数量
    1. `blockCount`
    2. `Q_PROPERTY(int blockCount READ blockCount)`
9.  获取和设置列表和文本块缩进的宽度，默认为 40
    1. `indentWidth`
    2. `Q_PROPERTY(qreal indentWidth READ indentWidth WRITE setIndentWidth)`
10. 默认样式表，默认样式表应用于插入到文档中的最近的 HTML 格式文本。更改默认样式表不会对文档的现有内容产生影响
    1. `defaultStyleSheet`
    2. ```cpp
        #ifndef QT_NO_CSSPARSER
        Q_PROPERTY(QString defaultStyleSheet READ defaultStyleSheet WRITE setDefaultStyleSheet)
        #endif
        ````
11. 文档最大块数，若文档中的块数大于该属性的值，则从文档的开头删除内容。负值和零表示文档有无限的块。默认为 0
    1. `maximumBlockCount`
    2. `Q_PROPERTY(int maximumBlockCount READ maximumBlockCount WRITE setMaximumBlockCount)`
12. 文档的边距
    1. `documentMargin`
    2. `Q_PROPERTY(qreal documentMargin READ documentMargin WRITE setDocumentMargin)`
13. 在创建`QTextBlock`时将该在其`QTextLayout`上设置该属性，这允许设置文档的全局属性。`QTextOption`类封装了富文本的一些属性，包括文本对齐、布局方向、文字换行等
    1. `defaultTextOption`
    2. `QDOC_PROPERTY(QTextOption defaultTextOption READ defaultTextOption WRITE setDefaultTextOption)`
14. 
    1. `baseUrl`
    2. `Q_PROPERTY(QUrl baseUrl READ baseUrl WRITE setBaseUrl NOTIFY baseUrlChanged)`

## 函数

### 信号

1. 文档中文本块的总数变化时，发送此信号 `void blockCountChanged(int newBlockCount)`
2. 只要文档内容变化，就发送此信号(注意：应用格式(比如加粗字体)也会发送此信号) `void contentsChange(int position, int charsRemoved, int charsAdded)`
3. 只要文档内容变化，就发送此信号 `void contentsChanged()`
4. 只要光标位置变化，就发送此信号 `void cursorPositionChanged(const QTextCursor &cursor)`
5. 设置新文档布局时，发送此信号 `void documentLayoutChanged()`
6. 当修改文档时，发送此信号 `void modificationChanged(bool changed)`
7. 只要重做操作变为可用或不可用，就会发送此信号 `void redoAvailable(bool available)`
8. 只要撤消操作变为可用或不可用，就会发送此信号 `void undoAvailable(bool available)`
9. 每次增加新的撤消时，发送此信号 `void undoCommandAdded()`

### 基本信息

1. 返回文档的根框架 `QTextFrame *rootFrame() cons`
2. 返回与格式 f 相关联的文本对象 `QTextObject *objectForFormat(const QTextFormat &f) const`
3. 返回与 objectIndex 相关联的文本对象 `QTextObject *object(int objectIndex) const`
4. 返回文档中的页数 `int pageCount() const`
5. 返回位置 pos 处的字符(相对于文档从 0 开始计数光标后的字符) `QChar characterAt(int pos) const`
6. 返回此文档的字符数 `int characterCount() const`
7. 以向量的形式返回列表中所使用的所有格式 `QVector<QTextFormat> allFormats() const`


### 迭代器操作

**`for(QTextBlock t = doc->begin(); t = !doc->end(); t = t.next()) qDebug()<< t . text();`**

1. 返回文档的第一个文本块 `QTextBlock begin() const`
2. 返回文档的第一个文本块 `QTextBlock firstBlock() const`
3. 返回文档的最后有效文本块 `QTextBlock end() const`
4. 返回文档的最后有效文本块 `QTextBlock lastBlock() const`

### 基本操作(插入/获取 HTML、纯文本、打印、资源等)

1. 根据文档页面的内容自动调整文档的大小 `void adjustSize()`
2. 清除文档 `virtual void clear()`
3. 创建一个该文档的副本 `QTextDocument *clone(QObject *parent = Q_NULLPTR) const`
4. 将文档打印到打印机 `void print(QPagedPaintDevice *printer) const`
5. 使用给定的 HTML 格式文本 html 替换文档的全部内容(即，会清除文档之前的内容)。此函数还会重置撤消/重做历史`void setHtml(const QString &html)`
6. 返回以 HTML 形式表示的字符串形式，注意，返回的文本会比较多，包含了 html 头等生成 HTML 文件所需的信息 `QString toHtml(const QByteArray &encoding = QByteArray()) const`
7. 使用文本 text 替换文档的全部内容 `void setPlainText(const QString &text)`
8. 返回文档中包含的纯文本(包含文档中的所有文本)
    1. `QString toPlainText() const`
    2. `QString toRawText() const`
9. 把资源 resource 使用名称 name 添加到资源缓存，其中 type 是资源的类型
    1.  `QVariant resource(int type, const QUrl &name) const`
    2.  `void addResource(int type, const QUrl &name, const QVariant &resource)`
10. 光标的默认移动样式，默认为 Qt::LogicalMoveStyle
    1.  `Qt::CursorMoveStyle defaultCursorMoveStyle() const;`
    2. ` void setDefaultCursorMoveStyle(Qt::CursorMoveStyle style)`

### 查找

1. 在文档中根据参数cursor、position、options查找字符串
    1. `QTextCursor find(const QString &subString, const QTextCursor &cursor, FindFlags options=FindFlags()) const`
    2. `QTextCursor find(const QString &subString, int position = 0, FindFlags options = FindFlags()) const`
    3. `QTextCursor find(const QRegExp &expr, int from = 0, FindFlags options = FindFlags()) const;`
    4. `QTextCursor find(const QRegExp &expr, const QTextCursor &cursor, FindFlags options = FindFlags()) const;`
    5. `QTextCursor find(const QRegularExpression &expr, int from = 0,FindFlags options = FindFlags()) const;`
    6. `QTextCursor find(const QRegularExpression &expr, const QTextCursor &cursor, FindFlags options = FindFlags()) const`

### 文档布局

1. 文档的文档布局
    1. `QAbstractTextDocumentLayout *documentLayout() const`
    2. `void setDocumentLayout(QAbstractTextDocumentLayout *layout)`
2. 若布局支持，则返回文档的行数，否则与块的数量相同 `int lineCount() const`
3. 把由位置 position 和长度 length 指定的内容标记为"dirty(脏)"，通知文档需要重新布局 `void markContentsDirty(int position, int length)`
4. 使用绘制器 p 绘制文档内容 `void drawContents(QPainter *p, const QRectF &rect = QRectF())`
5. 返回或设置由 info 指定的类型的文档的元信息
    1. `QString metaInformation(MetaInformation info) const`
    2. `void setMetaInformation(MetaInformation info, const QString &string)`

### 受保护的函数

1. 根据格式 format 创建并返回一个新的 QTextObject 对象 `virtual QTextObject *createObject(const QTextFormat &format)`
2. 使用给定的名称 name 从资源加载指定类型的数据。该函数由富文本引擎调用 `virtual QVariant loadResource(int type, const QUrl &name)`



## 示例

```cpp
void test(QTextEdit *edit) {

	/*获取光标位置*/
	QTextCursor cursor = edit->textCursor();
	cursor.movePosition(QTextCursor::Start);
	QTextDocument *document = cursor.document();//获取文档都西昂

	const QString imageNmae("图片");
	const QImage image(R"(C:\Users\Administrator\Desktop\Qt-learning\Qt文本系统\images\Qt_ducument_frame_block.png)");

	document->addResource(QTextDocument::ImageResource, imageNmae,
		QVariant(image));	//添加QImage对象到资源缓存
	

	cursor.insertImage(imageNmae); //使用资源缓存插入图像

	/*使用imageFormat来添加图片*/
	QTextImageFormat imageFormat;
	imageFormat.setName(imageNmae);

	cursor.insertImage(imageFormat);

	/*使用html方式添加图片*/
	QString html(QString(R"(<img src="%1">)").arg(imageNmae));

	edit->append(html);
	edit->insertHtml(html);

	edit->resize(image.size() * 4);
}
```