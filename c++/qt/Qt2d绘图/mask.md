# 蒙版(mask)

## 蒙版基本概念

1. 在绘图软件中，蒙版类似于蒙在原始图片上的一块玻璃(即蒙版)，然后我们再在这块玻璃上使用其他工具对图片进行修改，这样就不会破坏原始图片，而又能看到图片修改后的效果
2. 蒙版通常是黑白色的，通常通过改变蒙版(玻璃)的灰度可以改变蒙版的透明度，从而可以使原始照片变为可见、不可见、透明三种效果，也就是说蒙版本身只能改变透明度，并不能改变原始图像的色彩或其他性质(这些性质的改变需借助其他工具)
3. 蒙版(即玻璃)很少有彩色蒙版，几乎都是黑白色的(即只能通过灰度改变透明度)，虽然可以使用蒙版蒙住原始图的某个通道，但蒙版本身仍然是黑白色的。比如使用蒙版蒙住红色通道，则通过改变蒙版本身的透明度，可使原始图的红色变为可见、不可见或透明，但蒙版本身并不是彩色的
4. Qt通常使用`QBitmap`来保存蒙版，`QBitmap`类是一个只有1位深度的图像，因此Qt的蒙版只能在可见和不可见之间变换，不能实现透明度的效果

## QPixmap函数

1. 设置蒙版位图。此函数把蒙版与像素图的alpha通道合并，蒙版(即一个QBitmap图像)上的像素值为1(黑色)，则像素图的像素不变(即仍被显示)，若蒙版的值为0，则表示像素图的像素是透明的(即隐藏而不被显示)。蒙版必须与此像素图具有相同的大小。在绘制像素图时，此函数的效果是未定义的。该函数可能是一项昂贵的操作
   1. `void setMask(const QBitmap &mask)`
2. 从像素图的alpha通道创建一个蒙版，该函数是遗留函数(因为操作可能会很昂贵)，不应被使用
   1. `QBitmap mask() const`
3. 为此像素图创建并返回一个启发式蒙版，该函数的工作原理是从一个角中选择一种颜色，然后从所有边缘开始切掉该颜色的像素，若clipTight为true，则蒙版的大小足以覆盖像素，否则蒙版大于数据像素。该函数可能会很慢
   1. QBitmap createHeuristicMask(bool clipTight = true) const
4. 使用颜色maskColor为此像素图创建一个蒙版，若mode是Qt::MaskInColor，则与maskColor匹配的所有像素都是透明的，即隐藏像素，不显示该像素，若model是Qt::MaskOutColor，则与maskColor匹配的所有像素都是不透明的，即显示该像素。注意：被蒙板黑色部分遮挡的像素会被显示，被白色部分遮档的像素不会被显示。白色：显示、不透明。黑色：隐藏、透明
   1. `QBitmap createMaskFromColor(const QColor &maskColor,Qt::MaskMode mode = Qt::MaskInColor) const`

## 示例

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QRectF>
class aDrawImage :public QWidget
{
    Q_OBJECT
private:

    void init(){

    }
protected:
    void paintEvent(QPaintEvent *event) override{
        Q_UNUSED(event)

        QPainter painter;

        QPixmap pixmap1("C:/Users/lsz/Desktop/mygit/qt-learning/Qt2d绘图/images/原始图像.png")
                ,pixmap2("C:/Users/lsz/Desktop/mygit/qt-learning/Qt2d绘图/images/原始图像.png");


        painter.begin(this);

        QBitmap bitmap1 = pixmap1.createMaskFromColor(QColor(255,0,0),Qt::MaskInColor);
        QBitmap bitmap2 = pixmap1.createMaskFromColor(QColor(255,0,0),Qt::MaskOutColor);

        painter.drawPixmap(11,11,pixmap1);

        //蒙版1
        pixmap1.setMask(bitmap1);
        painter.drawPixmap(222,11,pixmap1);
        painter.drawPixmap(222,222,bitmap1);

        //蒙版2
        pixmap2.setMask(bitmap2);
        painter.drawPixmap(444,11,pixmap2);
        painter.drawPixmap(444,222,bitmap2);

        painter.end();
    }

public:
    aDrawImage(QWidget *p =nullptr) :QWidget(p){ init(); }
};

#endif // WIDGET_H
```