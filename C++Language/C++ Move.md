##### 问题：如何写一个安全的函数支持 **foo( type()) **调用？

* 不安全的用法：

  ~~~c++
  class Type;
  Type(){
    member = new otherType;
    //print this here can be more obviously
  }
  void Type::Action(){
    //do sth with member
  }
  ~Type(){
    //print mark here
    
    delete member;
    member = nullptr;
  }

  Type* foo(const Type& son){
    son.Action();		//unsafe place 1
    return &son;		//unsafe place 2?
  }

  //main function
  foo(Type());		//in a test, I hope I can call a func like this safely
   
  //oher vertion
  Type* foo(Type& son);//without const 

  foo(Type());		//in msvc is ok, in GCC will occur compile error:an 					 // rvalue cant bind to a lvalue

  ~~~



* **讨论** 

  且不论foo的返回值，里面参数的声明是很常见的。但是面对临时对象，依然会在传参后马上被销毁。这样foo里面这个对象就会出问题。更不用说有可能这个foo是跟string差不多的声明，返回一个对象的引用。。。

* **引入move语义(semantic)** 

  将**foo**的参数声明为右值引用后就能避免崩溃了。