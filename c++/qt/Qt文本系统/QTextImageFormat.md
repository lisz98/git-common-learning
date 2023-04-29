# QTextImageFormat

## 函数

```cpp
qreal height() const; //返回图像占据的高度
qreal width() const; //返回图像占据的宽度
void setHeight(qreal height) ; //设置图像占据的高度
void setWidth(qreal width);//设置图像占据的宽度
QString name() const; //返回图像的名称，该名称是程序资源名称或文件路径字符串
void setName(const QString &name); //设置图像的名称(即图像的路径或资源名)
bool isValid() const; //若图像格式有效，则返回 true，否则返回 false
void QTextFormat::setObjectType(int atype) //父类函数，设置对象类型，在自定义文档对象中使用
```