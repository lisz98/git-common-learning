# QTextCursor

## 基本原理

* `QTextCursor`类主要用于管理插入符(光标)，还能够把表格或列表等复杂对象插入到`QTextDocument`中，并处理选择。
* 该类可以创建/删除选择、并检索文本的内容。
* `QTextCursor`用编程的方式创建和编辑`QTextDocument`
* 在`QPlainTextEdit`和`QTextEdit`类中使用`QTextCursor`的方法如下：
    * 在文档中使用`textCursor()`获取光标，然后编辑文档，然后把修改后的光标使用函数`setTextCursor()`设置为文档的光标以确保使设置生效。
* 如果光标有选择对象，则给定的格式用于当前选择的对象
* 当只选择块的一部分时，块格式将应用于整个块
* 当前字符和当前块：
    * 当前字符:指的文档中光标位置`position()`之前的字符。
    * 当前块:包含光标`position()`的块

## 枚举

1. MoveMode

    ```cpp
    /*描述光标移动模式*/
    enum MoveMode {
        MoveAnchor,//移动光标时移动锚点
        KeepAnchor//保持锚点位置(若此时移动光标，会选择光标移过的文本)
    };
    ```

2. MoveOperation 

    ```cpp
    /*描述光标移动行为*/
    enum MoveOperation {
        NoMove,//光标保持不动

        /*向前操作*/
        Start,//移动至文档开头
        Up,//向上一行
        StartOfLine,//移至当前行的开头
        StartOfBlock,//移至当前块的开头
        StartOfWord,//移至当前单词的开头
        PreviousBlock,//移至前一块的开头
        PreviousCharacter,//移至上一个字符
        PreviousWord,//移至前一个单词的开头
        Left,//向左移一个字符
        WordLeft,//向左移一个单词

        /*向后操作*/
        End,//移至文档的末尾
        Down,//向下移一行
        EndOfLine,//移至当前行的末尾
        EndOfWord,//移至当前单词的末尾
        EndOfBlock,//移至当前块的末尾
        NextBlock,//移至下一块的开头
        NextCharacter,//移至下一个字符
        NextWord,//移至下一个单词的开头
        Right,//向右移一个字符
        WordRight,//向右移一个单词

        NextCell,//移至当前表格的下一个单元格的开头，若单元格是该行中的最后一个单元格，则光标移至下一行中的第一个单元格
        PreviousCell,//移至当前表格的上一个单元格的开头，若单元格是该行中的第一个单元格，则光标移至上一行中的最后一个单元格
        NextRow,//移至当前表格中下一行的第一个单元格的开头
        PreviousRow//移至当前表格中上一行的第一个单元格的开头
    };
    ```
3. SelectionType

    ```cpp
    /*描述选择时的选择类型*/
    enum SelectionType {
        WordUnderCursor,//选择光标下的单词
        LineUnderCursor,//选择光标下的文本行
        BlockUnderCursor,//选择光标下的文本块
        Document//选择整个文档
    };
    ```

## 函数

### 插入文档对象

**其中插入块、HTML、Image、Text无返回值，需要使用`block()`、函数获取**

1. 光标关联的文档 `QTextDocument *document() const;` 
2. 创建和插入列表
   1. `QTextList *createList(const QTextListFormat &format)`
   2.  `QTextList *createList(QTextListFormat::Style style)`
   3.  `QTextList *insertList(const QTextListFormat &format)`
   4.  `QTextList *insertList(QTextListFormat::Style style)`
3. 插入块
    1. `void insertBlock(const QTextBlockFormat &format)`
    2. `void insertBlock(const QTextBlockFormat &format, const QTextCharFormat &charFormat)`
4. 插入文档片段 `void insertFragment(const QTextDocumentFragment &fragment)`
5. 插入框架 `QTextFrame *insertFrame(const QTextFrameFormat &format)`
6. 插入HTML `void insertHtml(const QString &html)`
7. 插入图像
    1. `void insertImage(const QTextImageFormat &format)`
    2. `void insertImage(const QTextImageFormat &format, QTextFrameFormat::Position alignment)`
    3. `void insertImage(const QString &name)`
    4. `void insertImage(const QImage &image, const QString &name = QString())`
8. 插入表格
    1. `QTextTable *insertTable(int rows, int columns, const QTextTableFormat &format)`
    2. `QTextTable *insertTable(int rows, int columns)`
9. 插入文本 
    1.  `void insertText(const QString &text)`
    2.  `void insertText(const QString &text, const QTextCharFormat &format)`

### 文档元素

1. 设置和合并格式，其中`set`函数将替换当前格式，而素格式`merge`函数将格式添加到当前格式。
    1. `void setBlockCharFormat(const QTextCharFormat &format)`
    2. `void setBlockFormat(const QTextBlockFormat &format)`
    3. `void setCharFormat(const QTextCharFormat &format)`
    4. `void mergeBlockCharFormat(const QTextCharFormat &modifier)`
    5. `void mergeBlockFormat(const QTextBlockFormat &modifier)`
    6. `void mergeCharFormat(const QTextCharFormat &modifier)`

### 获取文档对象信息

1. 获取块字符格式 `QTextCharFormat blockCharFormat() const`
2. 获取块格式 `QTextBlockFormat blockFormat() const`
3. 获取字符格式 `QTextCharFormat charFormat() const`
4. 获取框架 `QTextFrame *currentFrame() const`
5. 获取列表 `QTextList *currentList() const`
6. 获取表格 `QTextTable *currentTable() const`
7. 获取块 `QTextBlock block() const`
8. 获取块的编号,仅适用于无复杂对象(如表格或框架)的文档 `int blockNumber() const`

### 构造函数

1. `QTextCursor();` 构造函数
2. `QTextCursor(QTextDocument *document);`构造一个指向文档开头的光标
3. `QTextCursor(QTextFrame *frame);` 构造一个指向框架开头的光标
4. `QTextCursor(const QTextBlock &block)`
5. `QTextCursor(const QTextCursor &cursor)`

### 光标位置

1. 判断光标位置是否位于块/文档在开头/末尾
    1. `bool atBlockEnd() const`
    2. `bool atBlockStart() const`
    3. `bool atEnd() const`
    4. `bool atStart() const`
2. 返回锚点位置 `int anchor() const`
3. 返回光标信息
    1. 返回光标所在的列号 `int columnNumber() const`
    2. 返回光标相对于块内的位置 `int positionInBlock() const`
    3. 返回文档中光标的绝对位置(即相对于整个文档的位置) `int position() const`
4. 设置/移动光标位置
    1. 使用模式 m，把光标移至文档中的绝对位置 pos 处(即相对于整个文档的位置 pos 处) `void setPosition(int pos, MoveMode m = MoveAnchor)`
    2. 根据模式mode和选项operation移动光标 `bool movePosition(MoveOperation operation, MoveMode mode = MoveAnchor, int n = 1)`
   
### 选择

1. 清除选择 `void clearSelection()`
2. 删除所选的内容 `void removeSelectedText()`
3. 根据选择类型selection选择文档中的文本 `void select(SelectionType selection)`
4. 返回当前选择的纯文本 `QString selectedText() const`
5. 返回所选择的内容，包含其格式信息 `QTextDocumentFragment selection() const`
6. 返回光标的开始或结束位置
    1. `int selectionEnd() const`
    2. `int selectionStart() const`
7. 返回光标选中状态 `bool hasSelection() const`
8. 获取所选择单元格的信息 `void selectedTableCells(int *firstRow, int *numRows, int *firstColumn, int *numColumns) const`
9. 若是复杂选择则返回 true `bool hasComplexSelection() const`

### 分组操作

1. 操作分组，即从撤消/重做角度看，位于这两个函数之间的动作被视为单个动作处理
    1. `void beginEditBlock()`
    2. `void endEditBlock()`
2. 在该函数之后的操作加入到之前的操作分组中 `void joinPreviousEditBlock()`

## 删除、保持光标不动插入、垂直移动 x 位置

1. 删除光标位置之后、之前或所选择的字符
    1. 删除光标位置之后 `void deleteChar()`
    2. 删除光标位置之前或 `void deletePreviousChar()`
2. 在光标当前位置处插入文本时，光标是否应保持当前位置
    1. `bool keepPositionOnInsert() const`
    2. `void setKeepPositionOnInsert(bool b)`
3. 垂直移动时的 x 位置(注意：该位置不是按字符数计算的)，即当使用上下箭移动光标时，光标会移动至上一行或下一行的 x 位置
    1. `int verticalMovementX() const`
    2. `void setVerticalMovementX(int x)`