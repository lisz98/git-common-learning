# QStyleOptionViewIte🇲

## 基本原理

* QStyleOptionViewItem继承自QStyleOption
* Qt绘制控件的基本原理：Qt内置的部件的外观几乎都是由QStyle类的成员函数进行绘制的，使用这些函数绘制部件时需要向函数提供一些所需绘制图形元素的信息，而这些信息都是由QStyleOption类进行描述的，QStyleOption类的不同子类描述了不同圆形元素所需的信息，比如QStyleOptionButton描述了绘制按钮所需的有关新信息等。因此模型/视图结构中的QStyleOptionViewItem类描述了绘制数据项所需的有关信息
* 只是储存了与样式相关的成员变量，并没有直接使用的函数

## 构造函数

```cpp
QStyleOptionViewItem()
   :QStyleOption(Version,SO_ViewItem),
    displayAlignment(Qt::AlignLeft),decorationAlignment
    (Qt::AlignLeft),textElideMode(Qt::ElideMiddle),
    decorationPosition(Left),showDecorationSelected(false),
    features(None),widget(0),checkState(Qt::Unchecked),
    viewItemPosition(QStyleOptionViewItem::Invalid)
{        
}
QStyleOptionViewItem(int version)
    : QStyleOption(version, SO_ViewItem),
      displayAlignment(Qt::AlignLeft), decorationAlignment(Qt::AlignLeft),
      textElideMode(Qt::ElideMiddle), decorationPosition(Left),
      showDecorationSelected(false), features(None), widget(0),
      checkState(Qt::Unchecked), viewItemPosition(QStyleOptionViewItem::Invalid)
{
}

```

## 枚举

```cpp
/*描述样式类型*/
enum StyleOptionType { Type = SO_ViewItem };
/*描述版本信息*/
enum StyleOptionVersion { version =4 }
/*描述项目装饰的位置*/
enum Position { Left, Right, Top, Bottom }
/*描述项目的特征*/
enum ViewItemFeature{
    None = 0x00,    /*正常项目*/
    WrapText =0x01, /*项目的文本可以自行换行*/
    Alternate =0x02, /*项目使用 alternateBase 渲染背景*/
    HasCheckIndicator =0x04, /*项目具有可选中指示符*/
    HasDisplay =0x08, /*项目具有 Qt::DisplayRole*/
    HasDecoration =0x10 /*项目具有 Qt::DecorationRole*/
}
/*描述项目在一行中的位置，可根据项目的位置不同而绘制项目的不同外形，比如为开始和结束处的项目绘制圆形边缘等*/
enum ViewItemPosition{ 
    Invaild, /*未知的，应忽略*/
    Beginning, /*项目位于行的开头*/
    Middle, /*项目位于行的中间*/
    End, /*项目位于行的末尾*/
    OnlyOne /*项目是唯一的(即该行只有一项)*/
}
```

## 成员变量

* `QBrush backgrounBrush` 用于绘制项目背景的画刷
* `Qt::CheckState checkState` 描述项目选中状态
* `Qt::Alignment decorationAlignment` 项目装饰的对齐方式
* `Posistion decorationPosition` 项目装饰的位置
* `QSize decorationSize` 项目装饰的大小，默认为 QSize(-1,-1)，即无效大小。若要在项目上绘制图标需设置此变量的大小
* `Qt::Alignment displayAlignment` 项目显示值的对齐方式，默认值为Qt::AlignLeft。通常用于设置与角色Qt::DisplayRole对应的值的对齐方式
* `ViewItemFeatures features` 描述项目的特征，即该项目可以包含哪些类型的数据
* `QFont font` 项目的字体
* `QIcon icon` 绘制项目中的图标
* `QModelIndex index` 需要绘制的模型的索引
* `bool showDecorationSelected` 当项目被选中时，是否突出显示装饰，默认为false
* `QString text` 在项目中绘制的文本
* `Qt::TextElideMode textElideMode` 当项目文本太长时，省略号应出现的位置，默认为 Qt::ElideMiddle，即省略号位于文本中间。
* `ViewItemPosition viewItemPosition` 该项目相对于其他项目的位置
* `QRect QStyleOption::rect` 表示绘制的项目的区域
* `QStyle::State QStyleOption::state` 绘制控件时的样式标志