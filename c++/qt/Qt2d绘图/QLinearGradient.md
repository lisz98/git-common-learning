# QLinearGradient

## 函数

1. 构造函数
   1. `QLinearGradient()`
   2. `QLinearGradient(const QPointF &start, const QPointF &finalStop)`
   3. `QLinearGradient(qreal x1, qreal y1, qreal x2, qreal y2)`
2. 渐变的最终停止点(逻辑坐标)
   1. `QPointF finalStop() const`
   2. `void setFinalStop(const QPointF &stop)`
   3. `void setFinalStop(qreal x, qreal y)`
3. 线性渐变的起点
   1. `QPointF start() const`
   2. `void setStart(const QPointF &start)`
   3. `void setStart(qreal x, qreal y)`