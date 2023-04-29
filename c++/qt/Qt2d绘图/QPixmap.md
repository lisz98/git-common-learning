# QPixmap

# 基本原理

1. QPixmap默认支持的文件格式如下
   
   |文件格式|说明|文件格式|说明|文件格式|说明|
   |---|---|---|---|---|---|
   |BMP|读/写|PBM|读|XBM|读/写|
   |JPG|读/写|PGM|读|XPM|读/写|
   |JPEG|读/写|PPM|读/写|GIF|读|
   |PNG|读/写|

## 枚举

1. 描述缩放时是否保持高宽比(纵横比)

```cpp
enum AspectRatioMode {
  IgnoreAspectRatio,//不保留纵横比，即，尺寸可自由缩放
  KeepAspectRatio,//保持纵横比，，在给定矩形内图像尺寸尽可能保持大的矩形
  KeepAspectRatioByExpanding//保持纵横比，在给定矩形外，像素图缩放为外部尺寸尽可能小的矩形
};
```

2. 描述图像变换时(比如缩放)是否平滑图像

```cpp
enum TransformationMode {
  FastTransformation,//快速转换，没有平滑
  SmoothTransformation//使用双线性滤波变换图像
};
```

## 函数

1. 构造函数
   1. `QPixmap()`
   2. `QPixmap(int width, int height)`
   3. `QPixmap(const QSize &size)`
   4. `QPixmap(const QPixmap &pixmap)`
   5. 使用格式format加载文件fileName，若文件不存在或格式未知，则创建一个空像素图，若加载图像时未指定格式，则加载程序会尝试猜测文件格式。参数flags用于指示图像怎样从高分辨率转换为低分辨率
      1. `QPixmap(const QString &fileName, const char *format = Q_NULLPTR,Qt::ImageConversionFlags flags = Qt::AutoColor)`
   6. 使用xpm数据构造一个像素图，注：XPM是一种X11上使用的图像格式，是一种基于ASCII编码的图像格式
      1. `QPixmap(const char * const[] xpm)`
2. 像素图的加载和存储
   1. `bool load(const QString &fileName, const char *format = Q_NULLPTR,Qt::ImageConversionFlags flags = Qt::AutoColor)`
   2. 使用格式format从二进制数据data加载一个像素图，若加载成功则返回true
      1. `bool loadFromData(const uchar *data, uint len, const char *format = Q_NULLPTR,Qt::ImageConversionFlags flags = Qt::AutoColor)`
      2. `bool loadFromData(const QByteArray &data, const char *format = Q_NULLPTR,Qt::ImageConversionFlags flags = Qt::AutoColor)`
   3. 直接从imageReader读取的图像创建一个像素图。在某此系统上，把图像读入到QPixmap比读取QImage再将其转换为QPixmap使用更少的内存
      1. `static QPixmap fromImageReader(QImageReader *imageReader,Qt::ImageConversionFlags flags = Qt::AutoColor)`
   4. 使用给定的质量quality和文件格式format把像素图保存到文件fileName中
      1. `bool save(const QString &fileName, const char *format = Q_NULLPTR, int quality = -1) const`
   5. 此函数表示把文件写入设备device中，比如可把文件写入QByteArray中
      1. `bool save(QIODevice *device, const char *format = Q_NULLPTR, int quality = -1) const`
   6. 返回标识此QPixmap的编号，当改变像素图时cacheKey()将发生改变
      1. `qint64 cacheKey() const`
   7. 从共享像素图中分离像素图。当像素图的内容即将发生改变时(比如调用fill()、fromImage()、load()等)，Qt就会自动分离它
      1. `void detach()`
3. 像素图的基本信息
   1. 返回像素图的深度
      1. `int depth() const`
   2. 返回该程序使用的默认像素图深度，通常返回主屏幕的深度
      1. `static int defaultDepth()`
   3. 高度、宽度、大小、包围矩形
      1. `int height() const`
      2. `int width() const`
      3. `QSize size() const`
      4. `QRect rect() const`
   4. 若像素图是空的，则返回true。空像素具有零宽度、零高度和零内容
      1. `bool isNull() const`
   5. 若像素图是一个QBitmap则返回true
      1. `bool isQBitmap() const`
   6. 设备像素比例，默认为1，若把其设置为其他值，将使像素图被缩放，比如像素图为200*200，若设置设备像素比为2，则像素图会被缩小为100*100，因为这相当于提高了当前绘制设备的分辨率
      1. `qreal devicePixelRatio() const`
      2. `void setDevicePixelRatio(qreal scaleFactor)`
4. 像素图的复制、填充、替换
   1. 使用颜色color填充像素图
      1. `void fill(const QColor &color = Qt::white)`
   2. 返回矩形范围内的像素图的深层副本，若rectangle为空，则复制整个图像
      1. `QPixmap copy(const QRect &rectangle = QRect()) const`
      2. `QPixmap copy(int x, int y, int width, int height) const`
   3. 像素图与other交换
      1. `void swap(QPixmap &other)`
5. 像素图的缩放与滚动
   1. 把像素图缩放到给定的大小，并返回缩放后的副本(注意：不会修改原始像素图)。若size为空或width、height为0 或负，则函数返回空像素图。其中参数aspectRatioMode用于指定缩放时是否保持高宽比，transformMode用于指定缩放时是否平滑图像
      1. `QPixmap scaled(const QSize &size, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio,Qt::TransformationMode transformMode = Qt::FastTransformation) const`
      2. `QPixmap scaled(int width, int height, Qt::AspectRatioMode aspectRatioMode = Qt::IgnoreAspectRatio,Qt::TransformationMode transformMode = Qt::FastTransformation) const`
   2. 返回缩放后的像素图的副本，像素图被保持纵横比缩放到给定的高度height或宽度width，未指定的宽度或高度由纵横比自动计算。若width、height为0或负，则返回空像素图
      1. `QPixmap scaledToHeight(int height, Qt::TransformationMode mode = Qt::FastTransformation) const`
      2. `QPixmap scaledToWidth(int width, Qt::TransformationMode mode = Qt::FastTransformation) const`
   3. 把像素图的矩形部分rect滚动(dx, dy)距离，区域exposed可用于保存未被改变的区域部分，当像素图上有一个活动的QPainter时，无法进行滚动
      1. `void scroll(int dx, int dy, int x, int y, int width, int height, QRegion *exposed = Q_NULLPTR)`
      2. `void scroll(int dx, int dy, const QRect &rect, QRegion *exposed = Q_NULLPTR)`
6. 像素图变换
   1. 返回使用transform变换后的像素图的副本，原始像素图不会改变。转换时会在内部调整变换矩阵，以补偿不必要的转换，使用trueMatrix()函数可获得实际的变换矩阵
      1. `QPixmap transformed(const QTransform &transform,Qt::TransformationMode mode = Qt::FastTransformation) const`
      2. `QPixmap transformed(const QMatrix &matrix,Qt::TransformationMode mode = Qt::FastTransformation) const`
      3. `static QTransform trueMatrix(const QTransform &matrix, int width, int height)`
      4. `static QMatrix trueMatrix(const QMatrix &m, int w, int h)`
7. QPixmap与QImage之间的转换
   1. `QImage toImage() const`
   2. s`tatic QPixmap fromImage(const QImage &image,Qt::ImageConversionFlags flags = Qt::AutoColor)`
   3. `static QPixmap fromImage(QImage &&image,Qt::ImageConversionFlags flags = Qt::AutoColor)`
   4. 使用图像image替换此像素图的数据
      1. `bool convertFromImage(const QImage &image, Qt::ImageConversionFlags flags = Qt::AutoColor)`

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
    QPixmap pixmap;//像素图，用于在屏幕上显示
    QString fileNmae ="C:/Users/lsz/Desktop/mygit/qt-learning/Qt2d绘图/images/2d绘图系统.png";

    void init(){

    }
protected:
    void paintEvent(QPaintEvent *event) override{
        Q_UNUSED(event)

        QPainter painter;

        pixmap.load(fileNmae);
        pixmap =pixmap.scaled(QSize(111,111));//调整大小

        //当改变像素图时，会发生改变
        qDebug() <<"绘制前QPixmap的编号:" << pixmap.cacheKey();

        painter.begin(&pixmap);

        painter.drawText(44,44,"绘制");
        painter.end();

        qDebug() <<"绘制后QPixmap的编号:" << pixmap.cacheKey();

        painter.begin(this);
        painter.drawPixmap(11,11,333,222,pixmap);
        pixmap.save("C:/Users/lsz/Desktop/mygit/qt-learning/Qt2d绘图/images/自定义保存的图像.png");


        painter.end();
    }

public:
    aDrawImage(QWidget *p =nullptr) :QWidget(p){ init(); }
};

#endif // WIDGET_H
```

### 图像滚动原理

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

        pixmap.load(fileNmae);
        pixmap =pixmap.scaled(QSize(111,111));//调整大小

        QRegion region;//裁剪区域

        QRect rect(33,33,111,111);

        pixmap.scroll(33,33,rect,&region);

        painter.drawPixmap(11,11,pixmap);

        qDebug() << region;


        painter.end();
    }

public:
    aDrawImage(QWidget *p =nullptr) :QWidget(p){ init(); }
};

#endif // WIDGET_H

```