# QTextList

## 函数

```cpp
QTextListFormat format() const;
void setFormat(const QTextListFormat &format);
/*把块 block 添加到列表*/
void add(const QTextBlock &block);
int count() const;
/*返回列表中第 i 个文本块*/
QTextBlock item(int i) const;
/*返回与块 block 对应的列表项的编号文本*/
QString itemText(const QTextBlock &block) const;
/*把块 block 从列表中删除*/
void remove(const QTextBlock &block);
/*返回与块 block 对应的列表项的索引(从 0 开始)，若块不在列表中，则返回-1*/
int itemNumber(const QTextBlock &block) const;
/*删除列表中位置为 i 的项目，当列表中的最后一项被删除时，该列表会被拥有它的QTextDocument 自动删除*/
void removeItem(int i);
```