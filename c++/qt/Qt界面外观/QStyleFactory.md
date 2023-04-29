# QStyleFactory

**QStyleFactory类是一个独立的类，该类主要用于创建一个QStyle对象**


## 函数

1. 创建并返回与键key匹配的QStyle对象，若没有匹配的QStyle，则返回0。来自样式插件的样式和内置样式都会被匹配。注意：key不区分大小写
   1. `static QStyle *create(const QString &key)`
2. 返回QStyleFactory类可以创建的QStyle的键
   1. `static QStringList keys()`