# QImage

## 基本原理

1. QImage图像的存储
   1. 存储为QImage的图像，每个像素使用一个整数来表示
   2. 单色图像的存储:
      1. 具有一位深度的图像被存储到最多拥有两种颜色的颜色表中，单色图像有两种类型:大端(MSB)或小端(LSB)位顺序
   3. 8位深度图像的存储：
      1. 使用一个8位的索引把8位图像存储到颜色表中，即8位图像的每个像素占据一个字节的存储空间，即每个像素的颜色与颜色表中某个索引号的颜色相对应。
      2. 颜色表使用QVector<QRgb>存储，QRgb类型是使用typedef定义的一个unsigned int类型，该类型包含一个0xAARRGGBB格式的四元组ARGB格式
   4. 32位图像没有颜色表，每个像素直接包含一个QRgb类型的值，共有3种类型的32位图像，分别是RGB(即0xffRRGGBB)，ARGB和预乘的ARGB，在预乘格式中，红、绿、蓝通道需乘以alpha分量除以255
2. 对alpha通道的处理
   1. 带alpha通道的图像有两种处理alpha通道的方法，一种是直接alpha，别一种是预乘alpha，使用预乘alpha通道的图像通常会更快
   2. 直接alpha图像的RGB数值是原始的数值，而预乘alpha图像的RGB数值是乘以alpha通道后得到的数值，比如ARGB = (a , r , g, b);则预乘alpha后的值为(a, a*r, a*g, a*b)
   3. Qt预乘alpha通道图像的算法是把红、绿、蓝通道的数值乘以alpha通道的数值再除以255，比如使用ARGB32格式表示的0x7F00004E，使用预乘ARGB32格式应表示为0x7F000027，算法为(0x4E*0x7F) / 0xFF ≈ 0x27，把(0x4E*0x7F) / 0xFF 变换一下为0x4E*(0x7F / 0xFF) 其中0x7F/0xFF是以小数表示的alpha值。再如对于透明度为80% (1-33/FF)的ARGB32格式表示的0x3337304B，使用预乘ARGB32格式应为0x330B170F，以0x37 为例计算0x37*(0x33/0xFF)，转换为10进制后为55*0.2 = 11=0xB

## 枚举

1. 该枚举描述QImage的图像格式

```cpp
enum Format {
  Format_Invalid,//图像无效
  Format_Mono,//MSB大端顺序的单色图像(每像素使用1位存储)
  Format_MonoLSB,//LSB小端顺序的单色图像(每像素使用1位存储)
  Format_Indexed8,//每像素使用8位索引存储图像
  Format_RGB32,//使用32位RGB格式(0xFFRRGGBB)存储图像
  Format_ARGB32,//使用32位ARGB格式(0xAARRGGBB)存储图像
  Format_ARGB32_Premultiplied,//使用预乘的32位ARGB格式(0xAARRGGBB)存储图像
  Format_RGB16,//使用16位RGB格式(5-6-5)存储图像
  Format_ARGB8565_Premultiplied,//使用预乘的24位RGB格式(8-5-6-5)存储图像
  Format_RGB666,//使用24位RGB格式(6-6-6)存储图像，未使用的最高位始终为0
  Format_ARGB6666_Premultiplied,//使用预乘的24位ARGB格式(6-6-6-6)存储图像
  Format_RGB555,//使用16位RGB格式(5-5-5)存储图像，未使用的最高位始终为0
  Format_ARGB8555_Premultiplied,//使用预乘的24位ARGB格式(8-5-5-5)存储图像
  Format_RGB888,//使用24位RGB格式(8-8-8)存储图像
  Format_RGB444,//使用16位RGB格式(4-4-4)存储图像，未使用的最高位始终为0。
  Format_ARGB4444_Premultiplied,//使用预乘的16位ARGB格式(4-4-4-4)存储图像
  Format_RGBX8888,//使用32位字节排序的RGB(x)格式(8-8-8-8)存储图像，这与Format_RGBA8888相同，但alpha必须始终为255
  Format_RGBA8888,//使用32位字节排序的RGBA格式(8-8-8-8)存储图像，与ARGB32不同的是，这是一种字节排序格式，这意味着32位编码在大端和小端之间会不相同。
  Format_RGBA8888_Premultiplied,//使用预乘的32位字节排序RGBA格式(8-8-8-8)存储图像
  Format_BGR30,//使用32位BGR格式(x-10-10-10)存储图像
  Format_A2BGR30_Premultiplied,//使用32位预乘的ABRG格式(2-10-10-10)存储图像
  Format_RGB30,//使用32位RGB格式(x-10-10-10)存储图像
  Format_A2RGB30_Premultiplied,//使用32位预乘的ARGB格式(2-10-10-10)存储图像
  Format_Alpha8,//图像仅使用8位alpha格式存储
  Format_Grayscale8,//使用8位灰度格式存储图像
  Format_RGBX64,//
  Format_RGBA64,//
  Format_RGBA64_Premultiplied,//
#if 0
  // reserved for future use
  Format_Grayscale16,
#endif
#ifndef Q_QDOC
  NImageFormats
#endif
};
```

## 函数 

1. 使用格式format加载文件fileName
    1. `bool load(const QString &fileName, const char *format = Q_NULLPTR)`
2. 从设备device读取一个QImage
    1. `bool load(QIODevice *device, const char *format)`
3. 使用格式format从二进制数据data加载一个图像，若加载成功则返回true
   1. `bool loadFromData(const uchar *data, int len, const char *format = Q_NULLPTR)`
   2. `bool loadFromData(const QByteArray &data, const char *format = Q_NULLPTR)`
4. 根据二进制数据data构造一个QImage图像
   1. `static QImage fromData(const uchar *data, int size, const char *format = Q_NULLPTR)`
   2. `static QImage fromData(const QByteArray &data, const char *format = Q_NULLPTR)`
5. 使用给定的质量quality和文件格式format把像素图保存到文件fileName中,质量因子quality必须在0~100范围内，值0表示小型压缩文件，100表示未压缩文件，-1表示使用默认值,若format为0，则从fileName的后缀猜测图像格式
   1. `bool save(const QString &fileName, const char *format = Q_NULLPTR, int quality = -1) const`
6. 返回标识此QImage的编号，当改变图像时cacheKey()将发生改变
   1. `qint64 cacheKey() const`
7. 图像基本信息
   1. 返回图像的深度，支持的深度有1，8，16，24，32
      1. `int depth() const`
   2. 返回图像的格式/QPixelFormat的形式返回QImage::Forma
      1. `Format format() const`
      2. `QPixelFormat pixelFormat() const`
   3. 高度、宽度、大小、包围矩阵
      1. `int height() const`
      2. `int width() const`
      3. `QSize size() const`
      4. `QRect rect() const`
   4. 以字节为单位返回图像数据的大
      1. `qsizetype sizeInBytes() const`
   5. 返回图像的位平面数，当图像格式包含未使用的位时，位平面数与深度会不相同，此时位平面数小于深度
      1. `int bitPlaneCount() const`
   6. 若像素图具有alpha通道格式，则返回true
      1. `bool hasAlphaChannel() const`
   7. 若图像是灰色的(即红、蓝、绿通道的值相同)，则返回true，否则返回false，注意：对于没有颜色表的图像，此函数会比较慢
      1. `bool allGray() const`
      2. `bool isGrayscale() const`
   8. 设备像素比，默认为1.0
      1. `qreal devicePixelRatio() const`
      2. `void setDevicePixelRatio(qreal scaleFactor)`
   9. 若是一个空的图像，则返回true，空图像的所有参数都为0，且没有分配的数据
      1.  `bool isNull() const`
   10. 若pos或(x,y)是图像内的有效坐标，则返回true，否则返回false
      1. `bool valid(const QPoint &pos) const`
      2. `bool valid(int x, int y) const`
8. 填充和复制
   1. 使用值pixelValue填充整个图像。填充时使用数值的低位，比如对于1位深度的图像，若使用值0或2，则填充0，若使用1或3则填充1，若深度为8，16，则使用低8位、16位
      1. `void fill(uint pixelValue)`
   2. 使用颜色color填充整个图像，若图像深度为1，若颜色为Qt::color1，则填充1，否则填充0。若图像深度为8，若存在颜色表，则图像将被填充为对应的索引处的颜色，否则将填充0
      1. `void fill(const QColor &color)`
   3. 使用标准的全局颜色color填充图像
      1. `void fill(Qt::GlobalColor color)`
   4. 返回矩形范围内的像素图的深层副本，若rectangle为空，则复制整个图像，深层副本详见隐式数据共享
      1. `QImage copy(const QRect &rectangle = QRect()) const`
      2. `QImage copy(int x, int y, int width, int height) const`
9. 颜色表和操控像素
   1. 颜色表的大小，注意：对于32位深度的图像该函数返回0
       1. `void setColorCount(int colorCount)`
       2. `int colorCount() const`
   2. 颜色表
      1. `void setColorTable(const QVector<QRgb> colors)`
      2. `QVector<QRgb> colorTable() const`
   3. 返回位于索引i(从0计数)处的颜色表中的颜色，颜像表中的颜色使用ARGB四元组(QRgb)表示，可使用::qAlpha(QRgb)，::qRed(QRgb)，::qGreen(QRgb)，::qBlue(QRgb)获取这些元素
      1. `QRgb color(int i) const`
   4. 把颜色表中索引为index处的颜色设置为colorValue，颜色具有ARGB四元组，若index超出了颜色表的当前大小，则使用setColorCount()进行扩展
      1. `void setColor(int index, QRgb colorValue)`
   5. 返回坐标(x,y)处像素的颜色
      1. `QRgb pixel(int x, int y) const`
      2. `QRgb pixel(const QPoint &position) const`
   6. 把位置position或坐标(x,y)处像素的索引或颜色设置为index_or_rgb。若图像的格式是单色或调色板的，则index_or_rgb必须是颜色表的索引，否则必须是QRgb值。该函数很昂贵，若需要考虑性能，建议使用scanLine()或bits()直接访问像素数据
      1. `void setPixel(const QPoint &position, uint index_or_rgb)`
      2. `void setPixel(int x, int y, uint index_or_rgb)`
   7. 以QColor的形式返回位置position或坐标(x,y)处像素的颜色
      1. `QColor pixelColor(const QPoint &position) const`
      2. `QColor pixelColor(int x, int y) const`
   8. 返回位置position或坐标(x,y)处的像素索引，若position无效，或图像不是调色板(颜色表)图像(即位深大于8的图像)
      1. `int pixelIndex(int x, int y) const`
      2. `int pixelIndex(const QPoint &position) const`

### 扫描线

**是指把图像按水平方向分割成很多条线，每条线就是一条扫描线，说简单点就是一条扫描线就是图像中的一行，比如对于300*200的图像，共有200条扫描线(即，有200行)**

1. 返回指向第一个像素数据的指针，相当于scanLine(0)
   1. `uchar *bits()`
   2. `const uchar *bits() const`
2. 返回指向第一个像素数据的指针
   1. `const uchar *constBits() const`
3. 返回指向具有索引为I (从0计数)的扫描线上的像素数据的指针，扫描线数据是在32位边界上对齐的。若要访问32位深度的图像数据，可把返回的指针强制转换为QRbg*格式，然后再进行读/写像素值
   1. `uchar *scanLine(int i)`
   2. `const uchar *scanLine(int i) const`
4. 返回指向扫描线上具有索引为i(从0计数)的像素数据的指针，扫描线数据是在32位边界上对齐的
   1. `const uchar *constScanLine(int i) const`
5. 返回每个图像扫描线的字节数，若height()不为零，则相当于sizeInBytes()/height()
   1. `int bytesPerLine() const`


## 示例

### 颜色表以及像素操控

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
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
        QImage image(200,200,QImage::Format_Mono);//大端格式单色格式



        painter.begin(this);
        painter.drawImage(11,11,image);
        painter.end();

        qDebug() <<"未使用rgb进行添加的单色图的颜色表:" <<image.colorTable();


        image.fill(Qt::color1);//使用单色图的颜色表中的索引1填充图像

        image.setColorCount(2);//设置颜色表中的颜色数量
        QRgb red =qRgb(111,1,1);//红色
        QRgb green =qRgb(1,111,1);//绿色
        QRgb yellow=qRgb(111,111,1);//黄色
        image.setColorTable({red,green,yellow});//设置一个新的颜色表

        painter.begin(&image);//使用单色图的新颜色表逐像素绘制一个矩形(22,22,128,100)
        for(int i=22;i <150;i++){
            for(int j=22;j<122;j++){
                image.setPixel(i,j,0);//使用新颜色表中索引为0的颜色填充位于(i,j)处的像素
            }
        }
        painter.end();

        painter.begin(this);
        painter.drawImage(222,11,image);

        qDebug() << "新的颜色表：" << image.colorTable();

        image.setColor(1,yellow);//将颜色表中索引为1的颜色更改为黄色
        painter.drawImage(444,11,image);
        qDebug() <<"新的颜色表:" << image.colorTable();

        painter.end();

    }

public:
    aDrawImage(QWidget *p =nullptr) :QWidget(p){ init(); }
};

#endif // WIDGET_H
```

### 扫描线的使用

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>
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
        QImage image(200,200,QImage::Format_ARGB32);
        QImage image2(200,200,QImage::Format_ARGB32);

        image.fill(qRgb(1,111,1));
        image2.fill(qRgb(1,111,1));//填充绿色作为背景色

        painter.begin(&image);

        //获取指向第一行第一个像素的指针，并将其强制转换为QRgb*以方便修改
        QRgb *bit =reinterpret_cast<QRgb* >(image.bits());//扫描线中指向第一个像素的指针

        for(int i=0;i<(200 *100);i++){ //每行有200个像素，扫描100行
            *bit =qRgb(QRandomGenerator::global()->bounded(255),
                       QRandomGenerator::global()->bounded(255),
                       QRandomGenerator::global()->bounded(255));
            ++bit;
        }

        QRgb *bit2 = reinterpret_cast<QRgb* >(image2.scanLine(19));//获取第二十行第一个元素的指针
        for (int i=0;i< (200 *100);i++) {
            *bit2 =qRgb(QRandomGenerator::global()->bounded(255),
                       QRandomGenerator::global()->bounded(255),
                       QRandomGenerator::global()->bounded(255));
            ++bit2;
        }
        painter.end();

        painter.begin(this);

        painter.drawImage(11,11,image);
        painter.drawImage(222,11,image2);

        qDebug() << image.bytesPerLine();

        painter.end();
    }

public:
    aDrawImage(QWidget *p =nullptr) :QWidget(p){ init(); }
};

#endif // WIDGET_H
```