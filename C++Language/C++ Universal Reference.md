### Universal Reference

总结至https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers

__问题__1：一个形如 T&& 的参数真的是右值吗？

__问题__2：const T& 和 T&& 两者作为参数能否有更好的办法统一起来，避免排列组合的爆炸重载？	//源自知乎



第一个问题当然是false，证据就是

~~~c++
int aa = 0; // a is a lvalue
int&& b = aa; // Oop! compile error! a rvalue cannot bind to a rReference.
int&& b = 10; // ok, 10 is a rvalue but but but but b is a lvalue though its type is rReference to 				 // inth. now just ignore wtf
auto&& bb = aa; // Oop! It's ok?! bb is a lvalue !
auto&& bb = 10; // also it's ok.
~~~

类似的效果还有

~~~c++
template<typename T>
void f(T&& _a)		
{}
//****************//
int a1 = 0;
f(a1);		// means f(int& a1), lvalue
f(10);		// means f(int&& _a), rvalue
~~~

也就是说，用&&有时候会有解决问题2的那种理想效果，当参数是左值它就传递左值，右值就move。可是为何不是总是生效呢？

它的成立条件在于：当一个变量**仅**被声明为 **可推导类型(deduce type)** 的时候，就可以智能传递左值or右值。Meyers称之为Universal Reference！

看到“仅”字强调了没有。任何修饰都会使之失效，比如 const，vector/<T/> 



1. 澄清左值(lvalue)与右值(rvalue)

   上述代码中b很奇怪的是左值，那是因为左值其实是种抽象概念，b是有具体变量名的，必然是左值。那如何判断一个expr到底是左值还是右值？（显然，表达式的声明类型并不可信，or完全无关）

   * 用&取的了地址（用c++有很多方法能取到右值的地址，但用&···应该取不到）
   * 表达式类型是左值(T& or T or const T&)
   * 除上述以外的是右值。显然右值经常是一些可以被编译器优化的立即数、临时变量

2. 原理：引用折叠(Reference Collapse)

   类似于const， 当你用n个const来修饰一样东西的时候，编译器是什么体验？

   ~~~c++
   const const const int a = 666;	// Equal to const int a = 666
   ~~~

   可以认为，当const大于等于1时，它会使其他全部失效。

   至于引用折叠，就是左值&对右值&&进行取缔的过程。大佬称之为感染性。

3. 弊端

   因为引用折叠的缘故，用Universal Reference的时候注意不要重载该template函数，显然因函数签名对左值右值区分的缘故，极其容易造成二义性。当无法避免重载这种函数的时候，可以用以下两种办法进行解决(Effective Morden C++ Item 27)：

   * 使用type tags
   * SFINAE机制

4. 延伸点

   * 重载决议
   * SFINAE
   * std::move与std::forward