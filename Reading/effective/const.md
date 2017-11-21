### C++ Tech

#### const

> * __bitwise constness__
>
>   令函数为const函数，禁止修改成员的值，并不能保证不会把地址传出去导致const失效
>
>
> * __logical constness__
>
>   而逻辑上保持const的操作可能会需要赋值操作。可以通过mutable的声明来达到。
>
> * __const重载__
>
>   一个值得注意的点是，const成员函数只能由const对象来调用，同时，const是函数签名的一部分，可以重载函数。所以当你有两个相似的函数的const与non-const版本的时候，应该使用后者调用前者的技巧来避免重复代码。
>
>   这个技巧是通过给 this 添加const: static<const T>(*this) 来调用const版本的函数，如果返回的是const对象，再进行const_cast。这个技巧是安全的，因为它是将 non-const 的对象转换成 const对象来得到结果的，这意味着不会违背const承诺。