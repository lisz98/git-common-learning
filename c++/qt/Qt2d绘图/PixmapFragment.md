# PixmapFragment 

## 基本原理

1. `QPainter`中使用到的函数
   1. `void drawPixmapFragments(const PixmapFragment *fragments, int fragmentCount,const QPixmap &pixmap, PixmapFragmentHints hints = PixmapFragmentHints())`
        > 把像素图Pixmap拆分为fragmentCount个像素图片段fragments，并以不同比例、旋转和透明度等在多个位置绘制这些像素图片段
        > 该函数比多次调用drawPixmap()更快
        > 枚举QPainter::PixmapFragmentHint就只有一个值，即QPainter::OpaqueHint，表示需要绘制的像素图片段是不透明的，不透明的片段会更快绘制
        > ixmapFragment是QPainter类中的嵌套类
2. 该嵌套类需配合`QPainter::drawPixmapFragments()`函数使用
3. sourceLeft、sourceTop、width、height四个变量被传入QPainter::drawPixmapFragments()函数的像素图中的源矩形
4. x、y、width、height四个变量被用于计算绘制的目标矩形。x和y表示目标矩形的中心
5. 目标矩形的width和height由变量scaleX和scaleY进行缩放，然后把得到的目标矩形以x, y为中心点旋转rotation度

## 函数

1. 用于创建一个QPainter::PixmapFragment，注意pos指的是目标矩形的中心点而不是左上角的坐标
   1. `static PixmapFragment create(const QPointF &pos,const QRectF &sourceRect, qreal scaleX = 1,qreal scaleY = 1, qreal rotation = 0, qreal opacity = 1)`
2. 保存目标矩形的不透明度(0透明，1不透明)
   1. `qreal opacity`
3. 保存目标矩形的旋转角度(以度为单位)。目标矩形在缩放后被旋
   1. `qreal rotation`
4. 保存目标矩形的水平/垂直缩放比。
   1. `qreal scaleX`
   2. `qreal scaleY`
5. 保存源矩形左侧或顶部的坐标
   1. `qreal sourceLeft`
   2. `qreal sourceTop`
6. 保存源矩形的宽/高度，并用于计算目标矩形的宽/高度
   1. `qreal height`
   2. `qreal width`
7. 保存目标矩形中心点的x和y坐标
   1. `qreal x`
   2. `qreal y`

## 示例

### 使用drawPixmapFragments()函数以不同形式显示原始图像的不同部分

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QRectF>
class aDrawImage :public QWidget
{
    Q_OBJECT
private:
    QPixmap pixmap;//像素图，用于在屏幕上显示
    QString fileNmae ="C:/Users/lsz/Desktop/mygit/qt-learning/Qt2d绘图/images/2d绘图系统.png";

    void init(){

    }
protected:
    void paintEvent(QPaintEvent *event) override{
        Q_UNUSED(event)

        QPainter painter;
        painter.begin(this);
         QRectF rect(11,11,55,55);
        pixmap.load(fileNmae);
        pixmap =pixmap.scaled(QSize(111,111));//调整大小

       //创建PixmapFragment，第一个参数表示的是目标矩形的中心点,第二个参数表示源矩形的大小信息
       QPainter::PixmapFragment fg1 =QPainter::PixmapFragment::create(QPointF(111,111),rect);
       fg1.rotation =60;//使fg1旋转60度
       QPainter::PixmapFragment fg2=QPainter::PixmapFragment::create(QPointF(222,111),rect,2);
       QPainter::PixmapFragment fg3=QPainter::PixmapFragment::create(QPointF(411,111),rect,1,2);
       QPainter::PixmapFragment fg4=QPainter::PixmapFragment::create(QPointF(333,111),rect,1,2,60);
       QPainter::PixmapFragment pixmapFragments[] ={fg1,fg2,fg3,fg4};
       int fragmentsCount = sizeof (pixmapFragments) /sizeof (pixmapFragments[0]);

       painter.drawPixmapFragments(pixmapFragments,fragmentsCount,pixmap,QPainter::OpaqueHint);

       //绘制目标矩形的中心点
       painter.drawLine(0,111,444,111);
       painter.drawLine(111,0,111,444);
       painter.drawLine(222,0,222,444);
    }

public:
    aDrawImage(QWidget *p =nullptr) :QWidget(p){ init(); }
};

#endif // WIDGET_H
```