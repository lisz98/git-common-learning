# QTextTable

* QTextTable类用于描述QTextDocument中的表格元素，表格是按行和列按序的一组单元格，一个表格至少有一行和一列。每个单元格包含一个块，并被框架包围。
* 通常通过`QTextCursor::insertTable()`来创建
* 对表格的进行格式设置需要使用辅助类:`QTextTableFormat、QTextTableCell、QTextTableCellFormat、QTextLength`
* 该类的主要作用是拆分和合并单元格
  
## 函数

### 获取单元格的接口函数

```cpp
/*获取单元格*/
QTextTableCell cellAt(int row,int column) const;
QTextTableCell cellAt(int position) const;
QTextTableCell cellAt(const QTextCursor &cursor);
```

### 格式、光标函数

```cpp
/*获取/设置格式*/
QTextTableFormat format() const;
void setFormat(const QTextTableFormat &format);
/*返回光标 cursor 所在行的行尾/开头的光标*/
QTextCursor rowEnd(const QTextCursor $cursor) const;
QTextCursor rowStart(const QTextCursor &cursor) const;
```
  
### 追加、删除、插入单列/行数

```cpp
int columns() const;
int rows() const;
void appendColumns(int count);
void appendRows(int count);
void insertColumns(int index, int columns);
void insertRows(int index, int rows);
void removeRows(int index, int rows);
void removeColumns(int index, int columns);
/*重新设置表格的行数和列数*/
void resize(int rows, int columns);
```

### 合并、拆分单元格

类似于word中合并表格和拆分表格的操作

```cpp
/*从(row，column)处的单元格向右合并 numRows 行，向下合并 numCols 列*/
void mergeCells(int row,int column,int numRows,int numCols);
/*合并由光标选中的单元格*/
void mergeCells(const QTextCursor &cursor);
/*拆分单元格，只能拆分跨越多行或多列的单元格*/
void splitCell(int row, int column, int numRows, int numCols);
```

## 示例

```cpp
void insertTableToTextEdit(QTextEdit* edit) {

	QTextCursor cursor(edit->textCursor());	//必不可少，插入表格列表需要使用QTextCursor类来辅助完成
	cursor.movePosition(QTextCursor::Start);

	//需要使用QTextTableFormat、QTextTableCell、QTextTableCellFormat、QTextLength来设置表格

	QVector< QTextLength> textLength{
		QTextLength(QTextLength::FixedLength,33), //第一列
		QTextLength(QTextLength::FixedLength,88), //第二列
		QTextLength(QTextLength::FixedLength,88), //第三列
	};
	QTextTable *table = cursor.insertTable(3, 3);	//插入三行四列的表格
	QTextTableFormat tableFormat = table->format();
	tableFormat.setAlignment(Qt::AlignmentFlag::AlignCenter);
	tableFormat.setCellSpacing(10);
	tableFormat.setColumnWidthConstraints(textLength);
	tableFormat.setWidth(33 + 88 + 88);
	tableFormat.setBackground(Qt::red);
	table->setFormat(tableFormat);
	
}
```