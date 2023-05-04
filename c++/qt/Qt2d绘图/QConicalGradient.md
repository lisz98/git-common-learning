# QConicalGradient

## 函数

1. 构造函数
   1. `QConicalGradient()` 以(0,0)为中心，0为开始角度，构造一个圆锥渐变
   2. `QConicalGradient(const QPointF &center, qreal angle)`
   3. `QConicalGradient(qreal cx, qreal cy, qreal angle)`
2. 圆锥渐变的起始角度angle
   1. `qreal angle() const`
   2. `void setAngle(qreal angle)`
3. 圆锥渐变的中心
   1. `QPointF center() const`
   2. `void setCenter(const QPointF &center)`
   3. `void setCenter(qreal x, qreal y)`

## 示例

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
#include <QConicalGradient>
class DrawGradient :public QWidget
{
    Q_OBJECT
private:
    void init(){

    }
protected:
    void paintEvent(QPaintEvent *event) override{
        Q_UNUSED(event)

        QPainter painter;
        painter.begin(this);

        QPen pen =painter.pen();
        QConicalGradient gradient(QPointF(220,100),55);//设置中心点为(166,166)，角度为55
        /*两种设置渐变点的方式*/
#if 1
        gradient.setStops({
              QGradientStop(0,QColor(Qt::red)),
              QGradientStop(0.5,QColor(Qt::green)),
              QGradientStop(1.0,QColor(Qt::blue)),

        });
#else
        gradient.setColorAt(0,Qt::red);
        gradient.setColorAt(0.5,Qt::green);
        gradient.setColorAt(1.0,Qt::blue);
        gradient.setSpread(QGradient::RepeatSpread);//对锥形不起作用，失效
#endif


        QBrush brush(gradient);
        painter.setBrush(brush);
        /*设置连接点*/
#if 1
         //辐射颜色根据离QConicalGradient最近的颜色来
        QPainterPath path;
        path.addRect(50,50,100,100);

        pen.setJoinStyle(Qt::MiterJoin);
        painter.setPen(pen);
        painter.drawPath(path);

        pen.setJoinStyle(Qt::BevelJoin);
        painter.setPen(pen);
        path.translate(120,0);
        painter.drawPath(path);

        pen.setJoinStyle(Qt::RoundJoin);
        painter.setPen(pen);
        path.translate(120,120);
        painter.drawPath(path);

        pen.setJoinStyle(Qt::SvgMiterJoin);
        painter.setPen(pen);
        path.translate(0,120);
        painter.drawPath(path);

        pen.setJoinStyle(Qt::MPenJoinStyle);
        painter.setPen(pen);
        path.translate(240,0);
        painter.drawPath(path);
#endif
        painter.end();
    }

public:
    DrawGradient(QWidget *p =nullptr) :QWidget(p){ init(); }
};

#endif // WIDGET_H

```