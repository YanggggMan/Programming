### placement new与内存池

关于placement new的一般表现形式如下：

~~~c++
char *p = malloc(sizeof(char));
Rua rua = new(p) Rua;
~~~

它与普通的new的区别主要有2点：

1. 需要预先分配好的内存。
2. new的使用需要传入这段内存的地址作为其参数

也就是说其实质就是在一个预先分配的空间上调用你指定的构造函数，这样可以使得不必去调用原始版本的new--malloc以至于有可能会触发系统的空间申请，造成比较大的开销；同时如果你的程序频繁申请空间的话，这个方法很适合实现内存池来帮助你管理碎片。

有个想法，应该可以用这个东西做个简单的生产者消费者内存模型。

> 先假设简单的应用场景：每次都只分配一小块固定值给消费者。所以生产者----内存池本身全身都是生产好了的。
>
> 1. malloc一大段内存。分配有个固定step len，有个已分配的界线 line，往后的都是未分配的
> 2. 如果一直分配没有回收，按照step len一段一段调用构造函数并返回即可，直到满为止
> 3. 如果提前回收，先看看能不能把line退回去，否则相当于内存碎片，那就挂到一个链表上，代表二手的。。。
> 4. 优先从二手的里面找，找不到再延伸line，否则返回满

延伸：

* 如果需求的大小不一样咧？
* 不够用有没有补救措施？