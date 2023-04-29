#  QTextListFormat

## 枚举

```cpp
/*描述项目编号的样式*/
enum Style{
    ListDisc = -1,              /*实心圆*/
    ListCircle = -2,            /*空心圆圈*/ 
    ListSquare = -3,            /*正方形*/
    ListDecimal = -4,           /*十进制数值*/
    ListLowerAlpha = -5,        /*小写字母*/
    ListUpperAlpha = -6,        /*大写字母*/
    ListLowerRoman = -7,        /*小写罗马数字*/
    ListUpperRoman = -8,        /*大写罗马数字*/
    ListStyleUndefined = 0      /*未使用*/
}
```

## 函数

```cpp
/*设置列表的缩进量。缩进量为 in 乘以 QTextDocument::indentWidth 属性的值*/
int indent();
void setIndent(int in);
/*是否有效*/
bool isVaild() const;
/*设置列表项目编号的前缀/后缀(对不能排序的编号无影响)*/
void setNumberPrefix(const QString &numPrefix); 
void setNumberSuffix(const QString &numSuffix);
QString numberPrefix() const; 
QString numberSuffix() const;
/*返回列表编号的样式*/
Style style() const; 
void setStyle(Style style);
```