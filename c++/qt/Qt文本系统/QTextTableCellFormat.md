# QTextTableCellFormat

* QTextTableCellFormat类设置的格式只能作用于该单元格，因此可用该类可把表格的每个单元格设置成各自不同的格式，单元格中的内容通常为字符
* 该类主要用于设置单元格的内部边距(padding)，其余格式需要使用从父类继承的函数设置

## 函数

```cpp
/*设置/获取单元格内边距*/
void setTopPadding(qreal padding);
void setBottomPadding(qreal padding);
void setLeftPadding(qreal padding);
void setRightPadding(qreal padding);
qreal topPadding() const; 
qreal bottomPadding() const;
qreal leftPadding() const;
qreal rightPadding() const;
void setPadding(qreal padding);
/*单元格是否有效*/
bool isValid() const;
```