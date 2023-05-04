# QTextObjectInterface

**QTextObjectInterface类允许在QTextDocuments中绘制自定义文本对象**

## 函数

```cpp
class Q_GUI_EXPORT QTextObjectInterface
{
public:
    virtual ~QTextObjectInterface();
    /*该函数的返回值决定了绘制图像的大小*/
    virtual QSizeF intrinsicSize(QTextDocument *doc, int posInDocument, const QTextFormat &format) = 0;

    /*绘制自定义的文档对象，painter 表示绘制器，rect 表示把图形绘制于该矩形内，该参数是由以下的函数 intrinsicSize()返回的值，doc 表示在该文档上绘制，poInDocument表示文档中的位置(以字符数表示)format 表示绘制时的格式。若不需要在文档中指定位置以指定格式绘制对象，则后面三个参数可以不使用*/
    virtual void drawObject(QPainter *painter, const QRectF &rect, QTextDocument *doc, int posInDocument, const QTextFormat &format) = 0;
};
```