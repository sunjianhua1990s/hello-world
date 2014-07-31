###环境搭建：
1. 安装
2. 创建Github账号
3. 生成ssh key
4. Github添加SSH KEY
5. 测试SSH KEY
6. 配置本地Git文件

###利用git本地上传到GitHub
1. 进入要上传文件的目录输入git init
2. 创建一个本地仓库 git remote add origin xx
3. 添加文件到本地仓库 git add xxx
4. 把这个添加提交的到本地仓库，使用git commit -m进行说明
5. 将本地仓库提交的远程Github仓库 git push origin master

###从Github中克隆项目到本地
1. 到GitHub的某个仓库，复制右边的HTTPS clone url
2. 回到要存放的目录下，使用git clone urlxxx
3. 如果本地版本不是最新的，可使用git fetch origin
4. 把更新的内容合并到本地分支 git merge origin/master,或者使用git pull <本地仓库> master,去拉去最新的版本并自动合并

###GitHub分支管理
1. 创建一个本地分支 git branch
2. 将本地分支同步到GitHub上 git <本地仓库名><新分支名>
3. 切换到新建立的分支 git checkout <新分支名>
4. 为你的分支加一个远程端 git remote add <远程端名字><地址>
5. 查看当前有几个分支 git branch
6. 删除一个分支 branch -d <分支名>
7. 同步到github上删除这个分支 git push <本地仓库名>:<Github端分支>

###构建仓库
可以现在Github上建立仓库，然后在线下clone出一个，修改完全后，测试合格后（make html，./develop_server.sh start），push上去。
或者先在本地建立好后，通过远程 git remote add 添加一个仓库，然后push进去

###清空github某个仓库
git rm -r --cache . 
git add . 
git commit -m "gitignore working"

###初始化本地仓库，提交更新版本
git init
git add .
git remote add origin https://github.com/cowfighting/cowfighting.github.io
git pull origin master
git commit -m 'first blog'
git push origin master


###利用下面的命令来生成你的博客site：
$ make html
我比较喜欢下面的这个命令，它是实时生成你的站点，就是说你修改你的博客什么的它会实时的生成！很棒吧。
$ make regenerate
ok，生成之后，我们要看下显示的效果，用下面的命令吧
$ make serve
下面这个我比较喜欢，理由同上面的那个regerate，哈哈
$ make devserver


###文章开头
Title: 文章标题
Date: 2013-04-18
Category: 文章类别
Tag: 标签1, 标签2
slug:别名



