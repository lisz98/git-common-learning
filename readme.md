**git 学习项目**

> 简单的一个项目，勿喷 `QaQ`

-----------------------------------------------------------

# 介绍

一个开源的学习项目，旨在将自己和朋友学习的内容上传到`github`上，进行学习记录、学习交流。

好记性不如烂笔头，这也是一个`速查表(asesome-cheatsheets)`项目，将学习的语言和开发工具整理在一起，方便工作开发使用。

这个项目也会对一些`github`上的项目进行整理学习，并分享在文件夹中。


# 开发规范

# 配置git

配置好自己的`git`账号,配置方式如下:

```git
git config --global user.name 'xxx'
git config --global user.emial 'xxx'

# 如果数据推送不上的话，可能需要取消代理
# git config --global --unset http.proxy
# git config --global --unset https.proxy
```

# 开发分支

为了避免大量的合并冲突，每个人开发时应该使用自己创建自己独立的开发分支进行开发，最后上传到`github`上，进行合并,配置方式如下所示:

```git
# 创建一个git仓库中 feature文件夹下的分支
# feature 通常在工作中是一个开发分支 
git checkout -b feature/lsz
git push origin feature/lsz
# 将当前分支合并到 main 分支
git merge main
```

# 文件提交

为了避免生成大量的无用的数据，造成`git`仓库过大，需要自己过滤掉不需要上传的数数据,需要编写`.gitignore`文件,如下所示:

```git
# 会忽略git 目录下 满足build*扥文件夹，这里主要是因为cmake 构建时会生成build中间文件夹，这在我们代码开发中并不需要
/build*/

# 下面文件夹是 Visual Studio Code 的配置文件和存储文件，我们同样不需要，不加入到git 版本管理中
/.vscode/
/.cache/
```

如果出现其他的`python`解释器,`gcc`编译器生成的中间文件，例如`*.o`这种，请添加到`gitignore`中，避免生成大量的无关文件

# 注释内容

为了方便学习开发，如果可以，请写一些文档，可以使用任意格式书写，建议使用`markdown`,使用`markdown`的话`github`上可以直接看。

每添加一个项目，就应该在每个项目路径下生成一个`read.me`或者`history.log`文件夹，用于简单的注释当前项目的功能或作用，详情可参考`cheatsheets`文件夹

# 添加推荐项目

`gitmodules`文件记录添加的`git`项目，使用以下指令可以快速生成项目到git中:

```git
# 例如添加一个 cheatsheets 推荐项目
# 需要在cheatsheets文件夹中执行这个指令
git submodule add https://github.com/skywind3000/awesome-cheatsheets.git cheatsheets1
```