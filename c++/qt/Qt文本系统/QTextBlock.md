# QTextBlock

## 函数

### 块的文本、方向、列表、文档
```cpp
/*以纯文本形式返回块的内容*/
QString text() const;
/*返回块的文字方向(Qt::LeftToRight 或 Qt::RightToLeft)*/
Qt::LayoutDirection textDirection() const; 
/*若块表示一个列表项，则返回该项所属的列表，否则返回 0*/
QTextList *textList() const; 
/*返回该块所属的文档，若块不属于任何文档，则返回 0*/
const QTextDocument *document() const; 
```

## 块的格式

```cpp
/*返回块的块格式*/
QTextBlockFormat blockFormat() const;
/*返回该块的字符格式*/
QTextCharFormat charFormat() const;
/*返回文档内部块格式列表的索引*/
int blockFormatIndex() const;
/*返回文档内部字符格式列表的索引*/
int charFormatIndex() const;
/*返回块的文本格式选项*/
QVector<QTextLayout::FormatRange> textFormats() const;
```

### 块的位置

```cpp
/*若位置 position 位于文本块内，则返回 true*/
bool contains(int position) const;
/*返回文档中此块的下一个块，若最后一个块，则返回空块*/
QTextBlock next() const;
/*返回文档中此块的前一个块，若是第一个块，则返回空块*/
QTextBlock previous() const;
/*返回文档中该块的第一个字符的索引*/
int position() const;
/*返回块的编号，若无效则返回-1*/
int blockNumber() const;
```

### 块的行数、长度

```cpp
/*以字符形式返回块的长度，返回的长度包含所有的格式化字符，比如换行符*/
int length() const;
/*返回/设置行数，注：并非所有布局都支持此功能*/
int lineCount() const; 
void setLineCount(int count);
/*返回块的行号，若块无效，则返回-1，通常行号与块编号相同*/
int firstLineNumber() const;
```

### 块的可见性、有效性、版本

```cpp
/*若块有效，则返回 true，否则返回 false*/
bool isValid() const;
/*若块可见，则返回 true，否则返回 false*/
bool isVisible() const;
void setVisible(bool visible);
/*设置块的修订次数，设置后修订次数不会再增加*/
int revision() const;
void setRevision(int rev);
```

## 布局及其他

```cpp
/*返回该块的布局，布局用于显示和布局块的内容*/
QTextLayout *layout() const;
void clearLayout();
/*把数据 data 附加到文本块(可用于自定义数据)*/
void setUserData(QTextBlockUserData *data);
QTextBlockUserData *userData() const;
/*在文本块中存储整数值 state，在语法高亮(QSyntaxHighlighter)中有用*/
void setUserState(int state);
int userState() const;
```
