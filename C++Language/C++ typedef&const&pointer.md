### 狗血面试题引发的血案

想必大家都见过形如：

~~~c++
const int * a;		//case1
int* const a;		//case2
typedef char *pchar;
const pchar b;		//case3
const int *** const a;
typedef int (*p)();
​```
~~~

不知道什么鬼的鬼畜声明。看了忘忘了看，顶层底层const傻傻分不清。这次要彻底解决后患了！

经过一番百度鏖战，主要总结出一个分析的方法：

case 1 写成如下形式：

> ptr< const  \< int \> \> a	指向const int的普通指针

​	也就是从左往右进行解析，**类型名称** 放在第一个尖括号里面，外面依次嵌套const或者\*\(即ptr\) 即可

case 2 

> const< ptr \< int \> \> a	指向int的const指针

看到我强调的**类型名称**了吗，typedef可不是#define这种简单的文本替换，而是定义了一种新的类型，所以一样：

> const\<pchar\> a	\-\-\>		const\< ptr \<int \>\> a		指向int的const指针，指针本身不可变

case 3 同理：

> const\<int\>  \-\-\> const\< ptr\*n \< const \< int \> \> \> a		不想念

最后一个则不然，那是一个函数了。介绍一种神奇的用法：

~~~c++
class hehe{
  public:
  	p(haha);		//实际定义了一个函数，等价于  int p();
};
~~~

现在c++ 0x时代，用using或许更好：

> using p = \(\*\)  void (int, const std::string&);			是不是清晰了很多？