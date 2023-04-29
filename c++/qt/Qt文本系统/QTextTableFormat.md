# QTextTableFormat

**该类描述表格的格式信息，比如相邻单元格之间的间距、表格的背景色，单元格的长度等**

## 函数

```cpp
/*返回/设置表格的对齐方式*/
Qt::Alignment alignment() const;
void setAlignment(Qt::Alignment alignment);
/*返回/设置表格单元格的内部边距*/
qreal cellPadding();
void setCellPadding(qreal padding);
/*返回和设置表格单元格的列宽度约束*/
QVector<QTextLength> columnWidthConstraints() const;
void setColumnWidthConstraints(const QVector<QTextLength> &constraints);
/*清除单元格的列宽度约束*/
void clearColumnWidthConstraints();
/*返回表格格式约束的表格的列数*/
int columns() const;
/*返回标头行。表格标头在跨页时，会在页边距重复*/
int headerRowCount() const;
void setHeaderRowCount(int count);
/*若表格格式有效,返回true*/
bool isValid() const;
```

