# QTextFormat

## 基本原理

* QTextFormat类是所有格式类的父类，通常不需要使用该类设置各文档对象的格式，而应该使用该子类以设置特定文档元素的格式
* QTextFormat类定义了大量的属性，除了使用该类的子类来设置文档元素的格式外，还可设置该类的属性来间接设置文档元素的格式

## 枚举

```cpp
/*描述当前类是什么格式类型*/
enum FormatType{
    InvalidFormat = -1, /*默认构造器产生的无效格式*/
    BlockFormat = 1,    /*块格式*/
    CharFormat = 2,     /*字符串类型*/
    ListFormat = 3,     /*列表类型*/
#if QT_DEPRECATED_SINCE(5, 3)
    TableFormat = 4,    /*表格类型*/
#endif
    FrameFormat = 5,    /*框架类型*/

    UserFormat = 100    /*用户自定义需要在这之后*/
}
Q_ENUM(FormatType)
/*此枚举描述格式可以具有的不同属性，可以使用属性间接设置文档元素格式*/
enum Property {
    ObjectIndex = 0x0,/*格式化对象的索引*/

    //段落和字符属性
    CssFloat = 0x0800,//一个框架如何相对于周围的文本定位
    LayoutDirection = 0x0801,//文档中文本的布局方向

    OutlinePen = 0x810,
    BackgroundBrush = 0x820,
    ForegroundBrush = 0x821,
    // Internal to qtextlayout.cpp: ObjectSelectionBrush = 0x822
    BackgroundImageUrl = 0x823,

    //段落属性
    BlockAlignment = 0x1010,
    BlockTopMargin = 0x1030,
    BlockBottomMargin = 0x1031,
    BlockLeftMargin = 0x1032,
    BlockRightMargin = 0x1033,
    TextIndent = 0x1034,
    TabPositions = 0x1035,//指定制表符位置。标签位置是存储在QList中的QTextOption:: tab的结构体(在内部，在QList)
    BlockIndent = 0x1040,
    LineHeight = 0x1048,
    LineHeightType = 0x1049,
    BlockNonBreakableLines = 0x1050,
    BlockTrailingHorizontalRulerWidth = 0x1060,//水平标尺元素的宽度
    HeadingLevel = 0x1070,//标题的级别

    //字符属性
    FirstFontProperty = 0x1FE0,
    FontCapitalization = FirstFontProperty,
    FontLetterSpacingType = 0x2033,
    FontLetterSpacing = 0x1FE1,
    FontWordSpacing = 0x1FE2,
    FontStretch = 0x2034,
    FontStyleHint = 0x1FE3,
    FontStyleStrategy = 0x1FE4,
    FontKerning = 0x1FE5,
    FontHintingPreference = 0x1FE6,
    FontFamily = 0x2000,
    FontPointSize = 0x2001,
    FontSizeAdjustment = 0x2002,
    FontSizeIncrement = FontSizeAdjustment, // old name, compat
    FontWeight = 0x2003,
    FontItalic = 0x2004,
    FontUnderline = 0x2005, // deprecated, use TextUnderlineStyle instead
    FontOverline = 0x2006,
    FontStrikeOut = 0x2007,
    FontFixedPitch = 0x2008,
    FontPixelSize = 0x2009,
    LastFontProperty = FontPixelSize,

    TextUnderlineColor = 0x2010,
    TextVerticalAlignment = 0x2021,
    TextOutline = 0x2022,
    TextUnderlineStyle = 0x2023,
    TextToolTip = 0x2024,

    IsAnchor = 0x2030,
    AnchorHref = 0x2031,
    AnchorName = 0x2032,
    ObjectType = 0x2f00,

    //列表属性
    ListStyle = 0x3000,
    ListIndent = 0x3001,
    ListNumberPrefix = 0x3002,
    ListNumberSuffix = 0x3003,

    //表格和框架属性
    FrameBorder = 0x4000,
    FrameMargin = 0x4001,
    FramePadding = 0x4002,
    FrameWidth = 0x4003,
    FrameHeight = 0x4004,
    FrameTopMargin    = 0x4005,
    FrameBottomMargin = 0x4006,
    FrameLeftMargin   = 0x4007,
    FrameRightMargin  = 0x4008,
    FrameBorderBrush = 0x4009,
    FrameBorderStyle = 0x4010,

    TableColumns = 0x4100,
    TableColumnWidthConstraints = 0x4101,
    TableCellSpacing = 0x4102,
    TableCellPadding = 0x4103,
    TableHeaderRowCount = 0x4104,

    //单元格属性
    TableCellRowSpan = 0x4810,
    TableCellColumnSpan = 0x4811,

    TableCellTopPadding = 0x4812,
    TableCellBottomPadding = 0x4813,
    TableCellLeftPadding = 0x4814,
    TableCellRightPadding = 0x4815,

    //图片属性
    ImageName = 0x5000,
    ImageWidth = 0x5010,
    ImageHeight = 0x5011,
    ImageQuality = 0x5014,

    //内部
    /*
        SuppressText = 0x5012,
        SuppressBackground = 0x513
    */

    //选择属性
    FullWidthSelection = 0x06000,//当设置一个选择的字符格式时，文本的整个宽度将显示为选定的

    //分页符属性
    PageBreakPolicy = 0x7000,//指定如何打破页面。参见PageBreakFlag枚举。

    // --
    UserProperty = 0x100000
};
Q_ENUM(Property)

/*对象属性*/
enum ObjectTypes {
    NoObject,
    ImageObject,
    TableObject,
    TableCellObject,

    UserObject = 0x1000
};
Q_ENUM(ObjectTypes)

/*此枚举描述在打印时如何执行分页。它映射到相应的css属性。*/
enum PageBreakFlag {
    PageBreak_Auto = 0,//根据当前页上的可用空间自动确定分页符
    PageBreak_AlwaysBefore = 0x001,//页面总是在段落/表格前被打断
    PageBreak_AlwaysAfter  = 0x010//新页总是在段落/表之后开始
    // PageBreak_AlwaysInside = 0x100
};
Q_DECLARE_FLAGS(PageBreakFlags, PageBreakFlag)
```

## 示例

```cpp
void test(QTextEdit *edit) {
	QTextCursor cursor = edit->textCursor();
	cursor.movePosition(QTextCursor::Start);

	QTextBlockFormat blockFormat;
	blockFormat.setProperty(QTextFormat::BackgroundBrush, QBrush(QColor(111, 1, 1)));

	cursor.insertBlock(blockFormat);
}
```