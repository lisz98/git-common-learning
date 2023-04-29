
## 实列

```cpp
#pragma once

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QtWidgets>
#include <QPainter>

#ifndef QT_NO_PRINTER
#include <QPrinter>
#endif 


class TextEdit :public QWidget
{
	Q_OBJECT
private:
	QPushButton *outputPdf, *outputOdt;
	QTextEdit *edit;
	void init() {
		/*设置布局*/
		edit = new QTextEdit();
		outputPdf = new QPushButton("输出PDF");
		outputOdt = new QPushButton("输出Odt");

		QHBoxLayout *h = new QHBoxLayout;
		h->addStretch();
		h->addWidget(outputOdt);
		h->addWidget(outputPdf);

		QVBoxLayout *v = new QVBoxLayout(this);
		v->addWidget(edit,8);
		v->addLayout(h, 2);

		/*获取光标并创建自定义文档对象*/
		QTextCursor cursor = edit->textCursor(); //获取光标
		cursor.movePosition(QTextCursor::Start); //设置光标位置

		/*设置字体样式并插入文本*/
		if(true){
			
			QTextCharFormat charFormat;
			charFormat.setForeground(Qt::red);//设置前景色
			charFormat.setFontFamily("宋体");//设置字体族
			//charFormat.setFontFixedPitch(true);//设置等宽字体
			charFormat.setFontItalic(false);//设置斜体
			charFormat.setFontKerning(true);//设置字距调整
			//charFormat.setFontLetterSpacing(100);//设置字母间距
			charFormat.setFontOverline(false);//设置上划线
			charFormat.setFontPointSize(80);//设置字体大小
			//charFormat.setFontStretch(4);//设置拉伸因子
			charFormat.setFontStrikeOut(false);//设置删除线
			charFormat.setFontUnderline(true);//设置下划线
			charFormat.setFontWeight(5);//设置字体粗细
			//charFormat.setFontWordSpacing(2);//设置单词间距
			charFormat.setToolTip("自定义字符串格式");//设置文本片段的工具提示
			charFormat.setUnderlineColor(Qt::red);//设置下划线颜色
			charFormat.setFontLetterSpacingType(QFont::SpacingType::PercentageSpacing);//设置百分比字母间距
			charFormat.setFontCapitalization(QFont::Capitalization::Capitalize);//设置首字母大小
			charFormat.setFontStyleHint(QFont::System);//设置字体样式提示跟随系统
			charFormat.setFontStyleStrategy(QFont::PreferDefault);//设置字体策略提示
			charFormat.setFontHintingPreference(QFont::PreferDefaultHinting);//设置字体提示首选项
			charFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);//设置字符垂直对齐的方式
			charFormat.setUnderlineStyle(QTextCharFormat::DashDotLine);//设置下划线样式
			charFormat.setTextOutline(QPen(Qt::red));//设置绘制字符轮廓画笔
			//charFormat.setFont()
			cursor.insertText("自定义字体样式片段", charFormat);
		}

		/*获取当前文档并打印文档信息*/
		if (true) {
			QTextDocument *document = cursor.document();//获取当前文档

			document->setPageSize(QSize(666, 666));//设置页面大小

			QTextFrame *rootFrame = document->rootFrame();//获取根框架
			qDebug() << "文档字符总数,页数的总数:" << document->characterCount() << "," << document->pageCount();
			
			for (QTextBlock block = document->begin(); block != document->end(); block = block.next())
			{
				qDebug()<<"当前块的位置，文本:" << block.position()<<"," << block.text();
				QTextBlock::iterator itr = block.begin();
				while (!itr.atEnd())
				{
					qDebug() << "片段:" << itr.fragment().text();
					++itr;
				}
			}

		}
		
#if 0
		QMetaObject::connectSlotsByName(this);	//按照on_按键名称_clicked()连接槽

#else
		connect(outputPdf, &QPushButton::clicked, this, &TextEdit::on_outputPdf_clicked);
		connect(outputOdt, &QPushButton::clicked, this, &TextEdit::on_outputOdt_clicked);
#endif
	}

private slots:
	void on_outputPdf_clicked(){
		QTextDocument *doc = edit->document();//获取当前文档
#ifndef QT_NO_PRINTER
		QPrinter pr; //创建打印机
		pr.setOutputFileName("C:/Users/Administrator/Desktop/Qt-learning/Qt文本系统/output.pdf"); //设置输出文件的路径和名称
		pr.setOutputFormat(QPrinter::PdfFormat); //设置输出文件的格式
		pr.setPageSize(QPrinter::A4); //设置打印页面大小(此处为 A7 纸大小)
		doc->print(&pr); //调用 print()函数打印文档
#endif

	}

	void  on_outputOdt_clicked() {
		QTextDocument *doc = edit->document();//获取当前文档
#ifndef QT_NO_PRINTER
		//使用 QTextDocumentWriter 类把文档保存为.odt 文件，该类详见后文
		QTextDocumentWriter wr(R"(C:\Users\Administrator\Desktop\Qt-learning\Qt文本系统\output.odt)"); //输出文件的路径和名称
		wr.write(doc);//把文档 pd 的内容输出到 1.odt 文件
#endif
	}

public:
	TextEdit(QWidget *p = nullptr) :QWidget(p) { init(); }
};
```