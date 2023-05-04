# QSyntaxHighlighter

## 基本原理

* 语法高亮是用于使编辑的文本以各种不同的格式(比如颜色)呈现在用户面前
* 实现:使用一个类来专门设置文档中显示的文本的格式，通常使用`QTextCharFormat`类来设置文本的格式
* 实现语法高亮的步骤:
    * 子类化`QSyntaxHighlighter`
    * 重新实现现`QSyntaxHighlighter::highlightBlock()`函数，根据需求来实现语法高亮的文本
    * 创建子类化对象，并为其指定一个需要语法高亮的文档
* 语法高亮只能同时作用于一个文档

## 函数

1. 获取/设置高亮的文档
    1. `QTextDocument *document() const`
    2. `void setDocument(QTextDocument *doc)`
2. 把高亮显示重新应用于整个文档 `void rehighlight()`
3. 把高亮显示重新应用于块block `void rehighlightBlock(const QTextBlock &block)`


## 示例

### 最小的语法高亮

```cpp
#pragma once

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QtWidgets>
#include <QSyntaxHighlighter>

class CustomSyntaxHighlighter : public QSyntaxHighlighter
{
protected:
	/*高亮提示块*/
	void highlightBlock(const QString &text) override{
#if 0
		enum Token {//标志
			alnum,//[:alnum:]
			lbrace,//{
			rbrace,//}
			colon,//:
			semicolon,//;
			comma,//,
			slash,// /
			star// *
	};
#endif
		qDebug() << text;

#if 0
		QString::const_iterator itr = text.begin();


		while (itr != text.end())
		{
			qDebug() << *itr;

			switch ()
			{
			default:
				break;
			}

			itr++;
		}
#endif
		for (int i =0;i <text.length();i++)
		{
			const char c = text.at(i).toLatin1(); //获取每个字符
			qDebug() << c;

			QTextCharFormat charFormat;
			switch (c)
			{
			case '{': 
			case '}': {
				charFormat.setFontPointSize(44);//设置字体大小
				charFormat.setBackground(Qt::red);//设置背景色
			}break;
			case ':': {
				charFormat.setFontPointSize(22);//设置字体大小
				charFormat.setForeground(Qt::blue);//设置前景色
			}break;
			case ',': {
				charFormat.setFontPointSize(22);//设置字体大小
				charFormat.setForeground(Qt::black);//设置前景色
			}break;
			case '\"': {
				charFormat.setFontPointSize(44);//设置字体大小
				charFormat.setForeground(Qt::red);//设置前景色
			}break;
			case '/':
			case '*':
			case '\\': {
				charFormat.setFontPointSize(44);//设置字体大小
				charFormat.setForeground(Qt::green);//设置前景色
			}break;
			default: {
				charFormat.setFontPointSize(16);//设置字体大小
				charFormat.setForeground(Qt::black);//设置前景色
			}break;
			}
			setFormat(i, 1, charFormat); //设置格式

		}




	}

public:
	CustomSyntaxHighlighter(QTextDocument *parent) :QSyntaxHighlighter(parent) {}
};

class TextEdit :public QWidget
{
	Q_OBJECT
private:
	QTextEdit *edit;
	void init() {
		/*设置布局*/
		QTextEdit *edit = new QTextEdit();
		QVBoxLayout *v = new QVBoxLayout(this);
		v->addWidget(edit);

		/*获取光标并创建自定义文档对象*/
		QTextCursor cursor = edit->textCursor(); //获取光标
		cursor.movePosition(QTextCursor::Start); //设置光标位置

		QTextDocument *editDocument = edit->document();//获取编辑器的文档对象

		new CustomSyntaxHighlighter(editDocument);
	}
public:
	TextEdit(QWidget *p =nullptr) :QWidget(p) { init(); }
};
```

### 格式存储

```cpp
#pragma once

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#ifndef StorageFormat
#define StorageFormat
#endif

#include <QtWidgets>
#include <QSyntaxHighlighter>

class CustomSyntaxHighlighter : public QSyntaxHighlighter
{
private:
#ifdef  StorageFormat
	QTextCursor cursor;
	QTextDocument *doc;
#else
	int i;//存储一个值
#endif 
protected:
	/*高亮提示块*/
	void highlightBlock(const QString &text) override{
		QTextCharFormat charFormat;
		charFormat.setFontPointSize(33);
#ifdef  StorageFormat
		if (cursor.atEnd()) {
			cursor.movePosition(QTextCursor::Start);
		}
		cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);//选中并向右移动一个光标
		cursor.setCharFormat(charFormat);//设置格式
		cursor.clearSelection();//清除选中
#else
		setFormat(i++, 1, charFormat);
#endif 
	}

public:
	CustomSyntaxHighlighter(QTextDocument *parent) :QSyntaxHighlighter(parent){
#ifdef  StorageFormat
		doc = document();//获取当前文档
		cursor = QTextCursor(doc);//获取文档光标
		cursor.movePosition(QTextCursor::Start); //移动光标至文档开头
#else
		i = 0;
#endif

	}
};

class TextEdit :public QWidget
{
	Q_OBJECT
private:
	QTextEdit *edit;
	void init() {
		/*设置布局*/
		QTextEdit *edit = new QTextEdit();
		QVBoxLayout *v = new QVBoxLayout(this);
		v->addWidget(edit);
		edit->setText("12345");
		/*获取光标并创建自定义文档对象*/
		QTextCursor cursor = edit->textCursor(); //获取光标
		cursor.movePosition(QTextCursor::Start); //设置光标位置

		QTextDocument *editDocument = edit->document();//获取编辑器的文档对象

		new CustomSyntaxHighlighter(editDocument);
	}
public:
	TextEdit(QWidget *p =nullptr) :QWidget(p) { init(); }
};
```
