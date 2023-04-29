# QTextFragment

## 基本原理

* `QTextFragment`类仅描述了文本片段的一些信息(长度、位置、文本等),因此不需要修改文本片段
* 文本片段需要通过`QTextBlock::iterator`类中的`fragment()`获取

## 函数

```cpp
QString text() const; //以纯文本形式返回文本片段包含的文本
int length() const; //返回文本片段中的字符数
int position() const; //返回文档中此文本片段的位置
bool isValid() const; //若文本片段有效，则返回 true，否则返回 false
bool contains(int position) const; //若在文当中的位置 position 处文本片段包含文本则返回 true
QTextCharFormat charFormat() const;//获取该文本片段的字符格式
int charFormatIndex() const;//返回该文本片段的字符格式在文档内部字符格式列表中的索引
QList<QGlyphRun> glyphRuns(int pos = -1, int len = -1) const;//返回文本片段的字形
```