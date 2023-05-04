# QTextEdit

## 基本原理

* `QTextEdit`类继承自`QAbstractScrollArea`类，该类用于编辑和显示纯文本和富文本，该类可显示示表格、图像、列表等。对于富文本，则使用`HTML 4`进行描述。使用`QLabel` 可显示一小段富文本
* 若`QTextEdit`提供的富文本功能不能满足需求,可以使用`Qt WebKit`
* 使用`QTextCursor`类进行表格或列表等复杂对象插入到文档中，并进行处理
* `QTextEdit`默认支持的键盘操作与`QPlaintTextEdit`类相同

## QTextEdit类中的嵌套结构

```cpp
/*用于setExtraSelections()函数，以实现以指定的颜色临时标记文档中的某些区域*/
struct ExtraSelection{
    QTextCursor cursor;//标记的光标位置
    QTextCharFormat format;//标记的格式
}
```

## 成员变量

```cpp
class QTextEditPrivate :public QAbstractScrollAreaPrivate{
public:
    QWidgetTextControl *control; /*控制类，提供对文档的各种操作*/
    QTextEdit::AutoFormatting autoFormatting; /*自动格式方式*/
    bool tabChangesFocus;   /*是否开启tab按键焦点*/

    QBasicTimer autoScrollTimer;    /*自动滚动定时器*/
    QPoint autoScrollDragPos;       /*自动拖动的位置*/

    QTextEdit::LineWrapMode lineWrap;   /*换行方式*/
    int lineWrapColumnOrWidth;          /*根据换行方式表达不同意义*/
    QTextOption::WrapMode wordWrap;     /*单词换行方式*/

    uint ignoreAutomaticScrollbarAdjustment : 1;    /*忽略自动滚动条调整*/
    uint preferRichText : 1;                        /*更偏向富文本?*/
    uint showCursorOnInitialShow : 1;               /*显示光标在初始化位置*/
    uint inDrag : 1;                                /*在拖拽*/
    uint clickCausedFocus : 1;                      /*点击引起焦点*/

    // Qt3 COMPAT only, for setText
    Qt::TextFormat textFormat;                      /*字体格式*/

    QString anchorToScrollToWhenVisible;            /*当锚点可见时滚动到锚点*/

    QString placeholderText;                        /*占位符文本*/

#ifdef QT_KEYPAD_NAVIGATION
    QBasicTimer deleteAllTimer;
#endif
}
```

## 枚举

```cpp
/**/
enum LineWrapMode {
    NoWrap,/*不换行*/
    WidgetWidth,/*(默认),WidgetWidth 表示在右侧空白处换行，以保持整个单词是完整的*/
    FixedPixelWidth,/*在固定的宽度(像素)处换行*/
    FixedColumnWidth /*在固定的宽度(列数，即字符数)处换行*/
};
Q_ENUM(LineWrapMode)
/**/
enum AutoFormattingFlag {
    AutoNone = 0,/*不启动自动格式(默认)*/
    AutoBulletList = 0x00000001,/*自动创建项目符号列表*/
    AutoAll = 0xffffffff /*应用全自动格式*/
};
Q_DECLARE_FLAGS(AutoFormatting, AutoFormattingFlag)
Q_FLAG(AutoFormatting)
/**/

```

## 属性

```cpp
/*自动格式(即自动套用格式)*/
Q_PROPERTY(AutoFormatting autoFormatting READ autoFormatting WRITE setAutoFormatting)
/**/
Q_PROPERTY(bool tabChangesFocus READ tabChangesFocus WRITE setTabChangesFocus)
/**/
Q_PROPERTY(QString documentTitle READ documentTitle WRITE setDocumentTitle)
/**/
Q_PROPERTY(bool undoRedoEnabled READ isUndoRedoEnabled WRITE setUndoRedoEnabled)
/**/
Q_PROPERTY(LineWrapMode lineWrapMode READ lineWrapMode WRITE setLineWrapMode)
/**/
QDOC_PROPERTY(QTextOption::WrapMode wordWrapMode READ wordWrapMode WRITE setWordWrapMode)
/**/
Q_PROPERTY(int lineWrapColumnOrWidth READ lineWrapColumnOrWidth WRITE setLineWrapColumnOrWidth)
/**/
Q_PROPERTY(bool readOnly READ isReadOnly WRITE setReadOnly)
/*该属性为编辑器提供了一个 HTML 接口。读取函数 toHtml 以 HTML 的形式返回编辑器的文本*/
#ifndef QT_NO_TEXTHTMLPARSER
Q_PROPERTY(QString html READ toHtml WRITE setHtml NOTIFY textChanged USER true)
#endif
/**/
Q_PROPERTY(QString plainText READ toPlainText WRITE setPlainText DESIGNABLE false)
/**/
Q_PROPERTY(bool overwriteMode READ overwriteMode WRITE setOverwriteMode)
/**/
#if QT_DEPRECATED_SINCE(5, 10)
Q_PROPERTY(int tabStopWidth READ tabStopWidth WRITE setTabStopWidth)
#endif
/**/
Q_PROPERTY(qreal tabStopDistance READ tabStopDistance WRITE setTabStopDistance)
/*是否接受用户输入的富文本。默认为 true*/
Q_PROPERTY(bool acceptRichText READ acceptRichText WRITE setAcceptRichText)
/**/
Q_PROPERTY(int cursorWidth READ cursorWidth WRITE setCursorWidth)
/**/
Q_PROPERTY(Qt::TextInteractionFlags textInteractionFlags READ textInteractionFlags WRITE setTextInteractionFlags)
/**/
Q_PROPERTY(QTextDocument *document READ document WRITE setDocument DESIGNABLE false)
/**/
Q_PROPERTY(QString placeholderText READ placeholderText WRITE setPlaceholderText)
```

## 函数

### 设置字体

```cpp
/*获取/设置当前格式的字体*/
QFont currentFont() const;
void setCurrentFont();
/*获取/设置当前格式的字体族*/
QString fontFamily();
void setFontFamily(const QString &fontFamily);
/*获取/设置字体是否为斜*/
bool fontItalic() const; 
void setFontItalic(bool italic); 
/*返回/设置当前格式的字体大小(磅值，这是点大小)*/
qreal fontPointSize() const; 
void setFontPointSize(qreal s);
/*获取/设置字体是否带下划线，true(带下划线)*/
bool fontUnderline() const; 
void setFontUnderline(bool underline);
/*返回/设置当前格式的字体权重(即粗细程度)*/
int fontWeight() const; 
void setFontWeight(int weight);
```

### 其他函数

```cpp
/*滚动编辑器以使名称为name的锚点可见*/
void scrollToAnchor(const QString &name);
```