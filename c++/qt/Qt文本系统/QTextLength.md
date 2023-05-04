# QTextLength

## 枚举

```cpp
/*指定宽度的类型*/
enum Type{
    VariableLength=0,   /*可变宽度*/
    FixedLength,        /*固定宽度*/
    PercentageLength    /*宽度为最大宽度的百分比,0-100*/
};
```

## 函数

### 构造函数

```cpp
/*必须使用该构造函数来指定长度，value 的意义依 type 而定*/
QTextLength()
QTextLength(Type type, qreal value);
```

### 普通函数

```cpp
/*返回设置的长度值，若Type为VariableLength 则返回 0*/
qreal rawValue() const;
/*返回设置的长度对象的类型*/
Type type() const;
/*返回有效长度，由 Type 和指定的参数 max 限制*/
qreal value(qreal max) const;
```