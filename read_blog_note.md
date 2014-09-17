##C语言结构体封装
1. 使用`#pragma packet`指定编译器对其
2. 声明位域
```C
struct foo5 {
    short s;       /* 2 bytes */
    char c;        /* 1 byte */
    int flip:1;    /* total 1 bit */
    int nybble:4;  /* total 5 bits */
    int septet:7;  /* total 12 bits */
    int pad1:4;    /* total 16 bits = 2 bytes */
    char pad2;     /* 1 byte */
};
```
3. 结构体排序
```C
struct foo7 {
    char c;         /* 1 byte */
    char pad1[7];   /* 7 bytes */
    struct foo7 *p; /* 8 bytes */
    short x;        /* 2 bytes */
    char pad2[6];   /* 6 bytes */
};
```
```C
struct foo8 {
    struct foo8 *p; /* 8 bytes */
    short x;        /* 2 bytes */
    char c;         /* 1 byte */
    char pad[5];    /* 5 bytes */
};
```
4. C语言编译器有个-Wpadded选项，能使它产生关于对齐空洞和填充的消息。
虽然我自己还没用过，但是一些反馈者称赞了一个叫pahole的程序。这个工具与编译器合作，产生关于你的结构体的报告，记述了填充、对齐及缓存行边界。

##C语言结构体中数组和指针
###柔性数组为何存在？
我们想给一个结构体内的数据分配一个连续的内存！这样做的意义有两个好处：

第一个意义是，**方便内存释放**。如果我们的代码是在一个给别人用的函数中，你在里面做了二次内存分配，并把整个结构体返回给用户。用户调用free可以释放结构体，但是用户并不知道这个结构体内的成员也需要free，所以你不能指望用户来发现这个事。所以，如果我们把结构体的内存以及其成员要的内存一次性分配好了，并返回给用户一个结构体指针，用户做一次free就可以把所有的内存也给释放掉。（读到这里，你一定会觉得C++的封闭中的析构函数会让这事容易和干净很多）

第二个原因是，这样**有利于访问速度**。连续的内存有益于提高访问速度，也有益于减少内存碎片。（其实，我个人觉得也没多高了，反正你跑不了要用做偏移量的加法来寻址）

###相对地址获取
offset 宏
```C
#define offsetof(TYPE, MEMBER) ( ( size_t ) & ( (TYPE *)0 )->MEMBER) 
```
理解：获取TYPE结构体重 MEMBER成员的偏移地址
通过 (TYPE *)0 将）地址强制转换为TYPE类型的指针；
通过 ( (TYPE *)0 )->MEMBER 访问TYPE结构中的MEMBER数据成员
通过 & ( (TYPE *)0 )->MEMBER 取出TYPE结构中数据成员MEMBER的地址
通过  ( size_t ) (& ( (TYPE *)0 )->MEMBER) 将结果转换为size_t类型

###Linux内核双向循环链表
如何取出宿主结构的指针？
```C
#define list_entry(ptr, type, member) \
( ( type * ) ( ( char *) ( ptr ) - ( unsigned long ) ( &( ( type * ) 0 )->member ) ) )
```
` ( unsigned long ) ( &( ( type * ) 0 )->member ) `为取出type类型中member成员的偏移量
 
ptr为指向member的指针，因为指针类型不同，所以要先进行(char *)转换在进行计算。

用ptr减去member的偏移量就得到了宿主结构体的指针。这是最精华的地方。

##C语言中的`#`和` ##`
1. 在C语言的宏中，#的功能是将其后面的宏参数进行字符串化操作

2. `##` 被称为连接符，用来将两个Token 连接为一个Token 。注意这里连接的对象是Token 就行。如

```C
#define LINK_MULTIPLE(a,b,c,d) a##_##b##_##c##_##d

typedef struct _record_type LINK_MULTIPLE(name,company,position,salary);
// 这里这个语句将展开为：
// 	typedef struct _record_type name_company_position_salary;
```

例题：
```C
#include <stdio.h>
#define f(a,b) a##b
#define g(a)  #a
#define h(a) g(a)
int main()
{
   printf("%s/n",h(f(1,2)));
   printf("%s/n",g(f(1,2)));
   return 0;
}
```
本题的输出是12和f(1,2)，为什么会这样呢？因为这是宏，宏的解开不象函数执行。
对于#的参数，即便是另一个宏，也不展开，仍然作为字符串字面信息输出。
所以，`g(f(1,2)) = f(1,2)`
对于`h(f(1,2))`，由于h(a)是非#或##的普通宏，需要先宏展开其参数a，即展开f(1,2)为12，则h(a) 宏替换为h(12)，进而宏替换为g(12), 进而宏替换为12。

3. `...`在C宏中称为Variadic Macro，也就是变参宏。比如：

```C
#define myprintf(templt,...) fprintf(stderr,templt,##__VA_ARGS__)
```

##C/C++的不安全性

```C
#include <stdio.h>
void foo(void)
{
    int a;
    printf("%d\n", a);
}
void bar(void)
{
    int a = 42;
}
int main(void)
{
    bar();
    foo();
}
```
你知道这段代码会输出什么吗？A) 一个随机值，B) 42。A 和 B都对（在“[在函数外存取局部变量的一个比喻](http://coolshell.cn/articles/4907.html)”文中的最后给过这个例子），不过，你知道为什么吗？

- 如果你使用一般的编译，会输出42，因为我们的编译器优化了函数的调用栈（重用了之前的栈），为的是更快，这没有什么副作用。反正你不初始化，他就是随机值，既然是随机值，什么都无所谓。
- 但是，如果你的编译打开了代码优化的开关，-O，这意味着，foo()函数的代码会被优化成main()里的一个inline函数，也就是说没有函数调用，就像宏定义一样。于是你会看到一个随机的垃圾数。


数学之美
罗塞塔
马尔科夫
条件概率估计 贝叶斯估计
二元模型 N元模型
古德图灵估计 `dr = (r+1)*N(r+1)/Nr`
Zipf定律：出现两次的概率比粗线三次的多
卡茨退避法
删除插值法
语料选取 网页 预处理

中文分词
字典法最少次数 缺陷 二义性分割无能为力
统计语言模型 计算分词后语句的概率 选最大可能
动态规划 维特比算法

隐含马尔科夫模型
马尔科夫假设
马尔科夫过程/链
隐含马尔科夫模型：状态序列是无法观测的，基于马尔科夫假设和独立输出假设，我们可以计算特定状态序列{A}产生输出符号{B}的概率。进而可应用于通信编码中，应用于语音识别，机器翻译中。
有监督的训练方法
无监督的训练方法
鲍姆-韦尔奇算法 期望最大化 凸函数

信息的度量
熵 `H(X) = -求和P(x)logP(x)`
条件熵 `H(X|Y) = -求和P(x,y)logP(x|y)`
互信息 `I(X;Y) = 求和P(x,y)log(P(x,y)/(P(x)P(y)))`
相对熵
















