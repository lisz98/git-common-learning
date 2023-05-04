# QDataStream

# QDataStream类读/写对象原理

1. `QDataStream`类负责以二进制方式读/写程序中的对象，输入源和输出目样标可以是`QIODevice`、`QByteArray`对象
2. 字节序：即多字节数据(即大于一个字节的数据)在内存中的存储顺序，有如下两种方式
   1. Little-Endian(LE，小端)：即低位字节存储在低地址端，高位字节存储在高地址端
   2. Big-Endian(BE，大端)：即高位字节存储在低地址端，低位字节储倣在高地址端。这是QDataStream的默认字节序
3. 对象的存储和传输：`若直接把一个对象保存在文件(或其他地方)上是没有意义的，因为对象中通常包含指向其他对象的指针，指针所指对象在下次运行时其内存地址很可能并不相同，因此在保存对象时，保存本次运行时指针的值就毫无意义，对此，需要采取必要的手段来解决保存对象的问题。对象的传输同样会遇到这种问题(比如在客户端和服务端传递对象时，在进程间传递对象时)，解决这一问题的方法就是序列化(serializable)或称为串行化`
4. 序列化(serializable)：是把对象状态转换为可保存或可传输的形式的过程，与其对应的是反序列化，序列化和反序列化保证了数据易于存储和传输。数据通常以二进制序列的形式进行传输，因此序列化通常是把对象转换为字节序列的过程，其相反过程称为反序列化
5. QDataStream实现了基本的C++数据类型的序列化，比如char，short，int，char *等。更复杂的数据类型的序列化是通过分解原始单元来完成的
6. 数据流与QIODevice紧密合作，QIODevice表示一个能读/写数据的I/O设备，其中QFile是常见的I/O设备
7. QDataStream支持的Qt类型有QBrush、QColor、QDateTime、QFont、QPixmap、QString、QVariant等类型，还包括容器类型，比如QList、QVector、QSet、QMap等，支持的Qt类型的完整列表可参阅帮助文档`Serializing Qt Data Types`
8. 自定义类型的输入/输出：使用QDataStream输入自定义类型时，需要重载<<和>>运算符，以使QDataStream支持新的数据类型，下面以示例进行说明。对于Qt类型是否支持类似的运算符，可查看该类帮助文档中的Related Non-Members(相关的非成员)部分的函数

## 函数

1. 构造函数:
   1. QDataStream(QIODevice *d)
   2. QDataStream(QByteArray *a, QIODevice::OpenMode mode)
   3. QDataStream(const QByteArray &a)
2. 当前的字节序
   1. ByteOrder byteOrder() const
   2. void setByteOrder(ByteOrder bo)
3. I/O设备
   1. void setDevice(QIODevice *d)
   2. QIODevice *device() const
4. 数据流的状态
   1. Status status() const
   2. void resetStatus()
   3. void setStatus(Status status)
5. 若I/O设备已到达结束位置，流或文件的末尾，或没有I/O设备集
   1. bool atEnd() const
6. 序列化格式的版本号
   1. int version() const
   2. void setVersion(int v)
7. 事务相关
   1. void startTransaction()
   2. void abortTransaction()
   3. bool commitTransaction()
   4. void rollbackTransaction()
8. 读取和写入原始二进制数据
   1. int readRawData(char *s, int len)
   2. int writeRawData(const char *s, int len)
   3. QDataStream &readBytes(char *&s, uint &u)
   4. QDataStream & writeBytes(const char *s, uint len)
   5. int skipRawData(int len)

## 示例

## 使用QDataStream输入/输出自定义类型对象

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QtWidgets>


#include <QDataStream>


class CustomData
{

public:
    QIcon icon;
    QString str;
    QPoint point;

    void init(){

    }


public:
    CustomData(){ init(); }
    ~CustomData(){}

};

//!告诉QDataStream如何去存取数据
//!需要重载全局函数
QDataStream &operator<<(QDataStream &out, const CustomData &data){
    out << data.icon <<data.str <<data.point;
    return out;
}
QDataStream &operator>>(QDataStream &in,CustomData &data){
    in >> data.icon >> data.str >>data.point;
    return in;
}
#endif // WIDGET_H
```