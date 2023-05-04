# QTextTableCell

**这是个独立的类，该类用于描述表格中的单个单元格，其设置只作用于该单元格，`QTextTableCell`类需要使用`QTextTable::cellAt()`函数来获取**

## 函数

```cpp
/*返回/设置单元格的字符格式*/
QTextCharFormat format() const;
void setFormart(const QTextCharFormat &format);
/**/
int column() const; 
int row() const; 
int columnSpan() const; 
int rowSpan() const;
/*在文档的内部格式列表中返回表格单元格格式的索引*/
int tableCellFormatIndex() const;
/*返回此单元格中第一个/最后一个有效的光标位置*/
QTextCursor firstCursorPosition() const;
QTextCursor lastCursorPosition() const;
/*若有效返回true*/
bool isVaild() const;
/*返回指向单元格开始处的框架(frame)迭代器*/
QTextFrame::iterator begin() const;
QTextFrame::iterator end() const;
```
