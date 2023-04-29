# QRegion

**主要用于创建裁剪区域，该类与QRectF类似，只是使用此类创建的区域没有轮廓线**

## 函数

1. 构造函数
   1. `QRegion()`
   2. `QRegion(int x,int y,int w,int h,RegionType t =Rectangle)`
   3. `QRegion(const QRect &r,RegionType t=Rectangle)`
   4. `QRegion(const QPolygon &a,Qt::FillRule fillRule=Qt::OddEvenFill)`
   5. `QRegion(const QBitmap &bm)`
   6. `QRegion(const QRegion &r)`
   7. `QRegion(QRegion &&other)`
2. 对区域的判断
   1. 返回此区域的边界矩形
      1. `QRect boundingRect() const`
   2. 判断是否包含点p或矩形r是否重叠
      1. `bool contains(const QPoint &p) const`
      2. `bool contains(const QRect &r) const`
   3. 判断区域是否为空
      1. `bool isEmpty() const`
      2. `bool isNull() const`
3. 组合多个区域
   1. 组成区域的非重叠矩形的数
      1. `int rectCount() const`
      2. `QVector<QRect> rects() const`
      3. `void setRects(const QRect *rects, int number)`
        * 使用矩形数组rects和数量number设置区域，这些矩形必须按照Y-X排序，且准守以下原则
          * 矩形不能相交
          * 所有具有给定顶点坐标的矩形，必须具有相同高度
          * 两个矩形不能水平邻接
          * 矩形必须按升序排序，其中Y为主排序键，X为次
4. 区域的集合运算
   1. 交集
      1. `QRegion intersected(const QRegion &r) const`
      2. `QRegion intersected(const QRect &rect) const` 
      3. `bool intersects(const QRegion &region) const`
      4. `bool intersects(const QRect &rect) const`
   2. 相减
      1. `QRegion subtracted(const QRegion &r) const`
   3. 平移
      1. `void translate(int dx,int dy)`
      2. `void translate(const QPoint &point)`
      3. `QRegion translated(int dx, int dy) const`
      4. `QRegion translated(const QPoint &p) const`
   4. 并集
      1. `QRegion united(const QRegion &r) const`
      2. `QRegion united(const QRect &rect) const`
   5. 返回该区域与区域r的异或运算
      1. `QRegion xored(const QRegion &r) const`
   6. 交换
      1. `void swap(QRegion &other)`