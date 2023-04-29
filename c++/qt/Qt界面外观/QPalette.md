# QPalette(调色板)

## 基本原理

1. `QWidegt`类中的属性
   1. `palette`属性描述了部件的调色板。在渲染标准部件时，窗口部件的样式使用调色板，而且不同的平台或不同的样式通常具有不同的调色板
   2. 该属性的默认值取决于系统环境，QApplication维护着一个系统/主题调色板，它是所有部件的默认调色板
   3. 注意：不要把此属性与Qt样式表联合使用
   4. 访问函数
      1. `const QPalette &palette() const`
      2. `void setPalette(const QPalette&)`
2. Qt的所有部件都含有一个调色板，并且使用各自的调色板来绘制自身
3. QWidget会把调色板角色从父级传播到子级，除非启用了`Qt::WA_WindowPropagation`属性(使用`QWidget::setAttribute()`函数设置) ，否则默认情况下调色板不会传播到窗口
4. 因某些样式依赖于第三方API(比如Mac样式、windows vista样式等)，而这些样式并不一定遵循调色板，因此不能保证部件的调色板分配角色会改变部件的外观
5. 另外还可以使用QApplication::setPalette();静态函数设置整个应用程序的默认调色板
6. 调色板设置的内容通常比较多，因此更改调色板时，通常是使用函数QWidget::palette()或静态函数QApplication()::palette()获取调色板，然后再对其需要修改的部分进行修改，最后使用相应的setPalette()函数设置修改后的调色板
7. QPalette类(调色板)包含了每个部件状态的颜色组，调色板由3个颜色组组成：
   1. 活动(active):即具有键盘焦点的窗口
   2. 禁用(disabled):即被禁用的部件(而不是窗口)
   3. 非活动(inactive):其他窗口

## 枚举

1. 描述颜色角色

```cpp
enum ColorGroup {
    Active, //活动
    Disabled,//禁用
    Inactive, //非活动
    NColorGroups, 
    Current, 
    All, 
    Normal = Active //同Active
};
Q_ENUM(ColorGroup)
```

2. 描述颜色角色

```cpp
enum ColorRole { 
    WindowText,//前景色
    Button,//普通按钮背景色 
    /*以下枚举用于3D效果，比如使按钮看更有立体感等，以下枚举依赖于Window*/
    Light,//比Button的颜色更亮
    Midlight,//在Button和Light之间
    Dark,//在Button的颜色更暗
    Mid,//在Button和Drak之间
    Shadow,//阴影颜色，这是一个很深的颜色，默认使用Qt::black(黑色)
    /**************************************/

    Text,// 与Base一起使用的前景色，通常与WindowText相同，Text通常用于文本，但也可用于线条、图标等
    BrightText,// 
    ButtonText,//与Button一起使用的前景色
    Base,//主要用于文本输入部件的背景色，也可用于组合框下拉列表、工具栏的背景，通常是白色或其他浅色
    Window,//背景色

    /*以下枚举用于选择项目时的颜色*/       
    Highlight,//突出显示所选内容，默认颜色为Qt::darkBlue(深蓝)
    HighlightedText,//突出显示时的文本颜色，默认颜色为Qt::white(白色)
    /****************************/

    Link,//未访问的超链接的颜色，默认为Qt::blue(蓝色) 
    LinkVisited,//已访问过的超链接的颜色，默认为Qt::magenta(洋红)
    AlternateBase,//用于视图中带有交替行颜色的备用背景色
    NoRole,//无角色
    ToolTipBase,//QToolTip和QWhatsThis的背景色，QToolTip使用QPalette的非活动颜色组，因为工具提示不是活动窗口 
    ToolTipText,//QToolTip和QWhatsThis的前景色
    PlaceholderText,//
    NColorRoles = PlaceholderText + 1,//
    Foreground = WindowText,//已过时，同windowText
    Background = Window//已过时，同window
};
Q_ENUM(ColorRole)
```

## 函数

1. 构造函数
   1. `QPalette()`
   2. `QPalette(const QColor &button)`
   3. `QPalette(Qt::GlobalColor button)`
   4. `QPalette(const QColor &button, const QColor &window)`
   5. `QPalette(const QBrush &windowText, const QBrush &button, const QBrush &light,const QBrush &dark, const QBrush &mid, const QBrush &text,const QBrush &bright_text, const QBrush &base, const QBrush &window)`
   6. `QPalette(const QPalette &p)`
   7. `QPalette(QPalette &&other)`
2. 获取角色的函数
   1. `const QBrush& window() const`
   2. `const QBrush& windowText() const`
   3. `const QBrush& base() const`
   4. `const QBrush& alternateBase() const`
   5. `const QBrush& toolTipBase() const`
   6. `const QBrush& toolTipText() const`
   7. `const QBrush& text() const`
   8. `const QBrush& button() const`
   9. `const QBrush& buttonText() const`
   10. `const QBrush& brightText() const`
   11. `const QBrush& light() const`
   12. `const QBrush& midlight() const`
   13. `const QBrush& dark() const`
   14. `const QBrush& mid() const`
   15. `const QBrush& shadow() const`
   16. `const QBrush& highlight() const`
   17. `const QBrush& highlightedText() const`
   18. `const QBrush& link() const`
   19. `const QBrush& linkVisited() const`

## 示例

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
class aStyle :public QWidget
{
    Q_OBJECT
private:

    void init(){
        //看不懂就别看，我写完可能也就看不懂了,风格全靠随机
        typedef QPair<int,int> pos;
        typedef QPair<QWidget *,pos> group;
        QVector<group> childs ={   //妖魔鬼怪代码法
            group(new QPushButton("按钮1"),pos(22,22)),
            group(new QPushButton("按钮2"),pos(111,22)),
            group(new QLabel("标签1"),pos(22,55)),
            group(new QLineEdit("编辑器1"),pos(99,55)),
            group([=]()->QComboBox *{
                QComboBox * comboBox =new QComboBox;
                comboBox->addItems({"H","L","W"});
                return comboBox;
            }(),pos(266,55)),
            group(new QPlainTextEdit("编辑器2"),pos(22,88)),
        };
        for (int i = 0; i < childs.count(); ++i) {
            auto child = childs.at(i);
            QWidget* widget = child.first;
            pos p =child.second;
            widget->setParent(this);
            widget->move(p.first,p.second);
        }

        QPalette palette;

        for (int i =(int)QPalette::WindowText;i <QPalette::NColorRoles; i++) {
            palette.setColor((QPalette::ColorRole)i
                             ,QColor(QRandomGenerator::global()->bounded(255),
                                     QRandomGenerator::global()->bounded(255),
                                     QRandomGenerator::global()->bounded(255)));
        }
        this->setPalette(palette);


        qApp->setStyle(QStyleFactory::create(QStyleFactory::keys()
                                             .at(QRandomGenerator::global()->bounded(QStyleFactory::keys()
                                                                                     .count()))));

      }




public:
    aStyle(QWidget *p =nullptr) :QWidget(p){ init(); }
};

#endif // WIDGET_H
```