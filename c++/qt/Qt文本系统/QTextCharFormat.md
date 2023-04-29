# QTextCharFormat

## 基本原理

* `QTextCharFormat`类用于描述字符的格式信息(比如粗体、斜体等)，该类的绝大部分属性与`QFont`类是相同的

## 枚举

```cpp
/*描述字符的垂直对齐方式*/
enum VerticalAlignment {
    AlignNormal = 0,//标准方式对齐
    AlignSuperScript,//字符位于基线上标
    AlignSubScript,//字符位于基线下方
    AlignMiddle,//对象中心与基线垂直对齐(仅适用于嵌入对象)
    AlignTop,//对象的底部与底线垂直对齐
    AlignBottom,//对象的顶部与基线垂直对齐
    AlignBaseline//字符基线对齐
};
/*描述下划线样式*/
enum UnderlineStyle { //与Qt::PenStyle保持同步
    NoUnderline,//无下划线
    SingleUnderline,//实线
    DashUnderline,//虚线
    DotLine,//点线
    DashDotLine,//点划线
    DashDotDotLine,//双点划线
    WaveUnderline,//波浪线
    SpellCheckUnderline//取决于 QPlatformTheme 的 SpellCheckUnderlineStyle
};
/**/
enum FontPropertiesInheritanceBehavior {
    FontPropertiesSpecifiedOnly,
    FontPropertiesAll
};
```

## 函数

|获取方式|设置方式|描述|
|---|---|---|
|QString fontFamily() const| void setFontFamily(const QString &family)| 字体族|
|bool fontFixedPitch() const|void setFontFixedPitch(bool fixedPitch)|是否使用等宽字体|
|bool fontItalic() const|void setFontItalic(bool italic)|斜体|
|bool fontKerning() const|void setFontKerning(bool enable)|字距调整|
|qreal fontLetterSpacing() const|void setFontLetterSpacing(qreal spacing)|字母之间的间距|
|bool fontOverline() const|void setFontOverline(bool overline)|上划线|
|qreal fontPointSize() const|void setFontPointSize(qreal size)|字体大小|
|int fontStretch() const|void setFontStretch(int factor)|拉伸因子|
|bool fontStrikeOut() const|void setFontStrikeOut(bool strikeOut)|删除线|
|bool fontUnderline() const|void setFontUnderline(bool underline)|下划线|
|int fontWeight() const|void setFontWeight(int weight)|字体重量(即粗细)|
|qreal fontWordSpacing() const|void setFontWordSpacing(qreal spacing)|两单词间的间距|
|QString toolTip() const|void setToolTip(const QString &text)|文本片段的工具提示|
|QColor underlineColor() const|void setUnderlineColor(const QColor &col)|下划线颜色|
|bool isVaild() const||字符格式是否有效|
|QFont::SpacingType fontLetterSpacingType() const|void setFontLetterSpacingType(QFont::SpacingType letterSpacingType)|字母间距是以百分比设置还是以像素设置|
|QFont::Capitalization fontCapitalization() const|void setFontCapitalization(QFont::Capitalization capitalization)|设置文本字体的大写模式|
|QFont::StyleHint fontStyleHint() const|void setFontStyleHint(QFont::StyleHint hint, QFont::StyleStrategy strategy = QFont::PreferDefault)|字体样式提示(即优先匹配哪一个字体样式)|
|QFont::StyleStrategy fontStyleStrategy() const|void setFontStyleStrategy(QFont::StyleStrategy strategy)|样式策略提示，比如位图字体、轮廓字体等|
|QFont::HintingPreference fontHintingPreference() const|void setFontHintingPreference(QFont::HintingPreference hintingPreference)|字体提示首选项，主要用于选择优化字体方式|
|void setVerticalAlignment(VerticalAlignment alignment)|VerticalAlignment verticalAlignment() const|设置字符的垂直对齐方式|
|void setUnderlineStyle(UnderlineStyle style)|UnderlineStyle underlineStyle() const|下划线样式|
|QPen textOutline() const|void setTextOutline(const QPen &pen)|设置绘制字符轮廓线的画笔|
|QFont font() const|void setFont(const QFont &font) 、void setFont(const QFont &font, FontPropertiesInheritanceBehavior behavior)|设置文本格式字体|

**超级链接设置**

* 设置超级链接前应使用`setAnchor()`启用超级链接，然后使用`setAnchorHref()`设置超级链接的目标地址(通常为一个网址)，`setAnchorNames()`用于设置超链接显示的名称
* 我们通常见到的超链接是带下划线的蓝色文本，这些属性都需要我们进行设置，否则即使该文本是超链接，也不会是带下划线的蓝色文本，他看起来会像普通文本一样
* 要使设置的超链接在外观上有所区别，还需要设置`QTextEdit`的 `textInteractionFlags`属性包含`Qt::LinksAccessibleByMouse`(即超链接可使用鼠标激活)，否则超链接在`QTextEdit`中看起来与普通文本是一样的

```cpp
/*用于设置超级链接*/
bool isAnchor() const; 
void setAnchor(bool anchor); 
QString anchorHref() const
void setAnchorHref(const QString &value)
QStringList anchorNames() const
void setAnchorNames(const QStringList &names);
```

## 示例

```cpp
void test(QTextEdit *edit) {

	/*获取光标位置*/
	QTextCursor cursor = edit->textCursor();
	cursor.movePosition(QTextCursor::Start);

	/*设置编辑器超级链接可使用鼠标激活*/
	edit->setTextInteractionFlags(Qt::TextEditable | Qt::LinksAccessibleByMouse);


	QTextCharFormat charFormat;
	charFormat.setAnchor(true);//打开超级链接
	//charFormat.setAnchorNames({ "百度","百度一下" });//设置超级链接显示的名称
	charFormat.setAnchorHref("http://www.baidu.com");//设置超级链接目标地址
	charFormat.setForeground(Qt::blue);//设置前景色
	charFormat.setFontUnderline(true);//设置字体下划线
	charFormat.setFontPointSize(33);//设置字体大小
	charFormat.setTextOutline(QPen(Qt::red));//设置字符绘制轮廓的画笔

	cursor.insertText("百度一下", charFormat);

}
```
