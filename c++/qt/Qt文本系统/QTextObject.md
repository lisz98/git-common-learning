# QTextObject

## 基本原理

* 该类用于描述文档对象，是`QTextFrame`和`QTextBlockGroup`类的父类

## 函数

```cpp
void setFormat(const QTextFormat &format);//设置文本对象的格式
QTextFormat format() const;//返回该文本对象的格式
int formatIndex() const;//返回文档内部格式列表中对象格式的索引
QTextDocument *document() const;//返回该文本对象所关联的文档
int objectIndex() const;//返回该文本对象的对象索引
```