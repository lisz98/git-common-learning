# Qt输入/输出有关的类简介

1. `QTextStream`类(文本流)和`QDataStream`类(数据类)Qt输入输出的两个核心类，其作用如下:
   1. `QTextStream`类：用于对数据进行文本格式的读/写操作，可对`QString`、`QIODevice`或`QByteArray`上运行，比如把数据输出到`QString`、`QIODevice`或`QByteArray`对象上,或进行相反的操作
   2. `QDataStream`类：用于对数据进行二进制格式的读/写操作，`QDataStream`只可在`QIODevice`或`QByteArray`上运行，因为QString只存放字符数据
2. `QIODevice`类是Qt中所有I/O设备的基础接口类(这是一个抽象类)，也就是说`QIODevice`及其子类描述的是I/O设备，该类为支持读/写数据块的设备提供了通用实现和抽象接口，比如`QFile`、`QBuffer`、`QTcpSocket`等
3. QIODevice把设备分为两类：随机存储设备和顺序存储设备
   1. 随机存储设备：可定位到任意位置(使用seek()函数)，随机存储设备有`QFile`，`QTemporaryFile`，`QBuffer`
   2. 顺序存储设备：不支持任意的位置存储，顺序存储设备有`QProcess`、`QTcpSocket`、`QUdpSocket`和`QSslSocket`
4. `QTextCodec`类负责`Unicode`与各字符编码之间的转换
5. `QBuffer`类为`QByteArray`提供了一个`QIODevice`接口，以允许使用`QIODevice`接口来访问`QByteArray`。默认情况下，创建一个`QBuffer`时，会自动在内部创建一个`  