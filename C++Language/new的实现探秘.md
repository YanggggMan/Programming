### new的实现探秘

在知乎上看到一个问题，把一个new出来的double指针扔给一个int类型，会发生内存泄漏吗？

蓝色大大于是乎拿出了new的源码：

~~~c++
作者：蓝色
链接：https://www.zhihu.com/question/61295343/answer/186166407
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

_LIBCPP_WEAK
void *
operator new(std::size_t size) _THROW_BAD_ALLOC
{
    if (size == 0)
        size = 1;
    void* p;
    while ((p = ::malloc(size)) == 0)
    {
        // If malloc fails and there is a new_handler,
        // call it to try free up memory.
        std::new_handler nh = std::get_new_handler();
        if (nh)
            nh();
        else
#ifndef _LIBCPP_NO_EXCEPTIONS
            throw std::bad_alloc();
#else
            break;
#endif
    }
    return p;
}

_LIBCPP_WEAK
void
operator delete(void* ptr) _NOEXCEPT
{
    if (ptr)
        ::free(ptr);
}
~~~

这里可以看到new和delete是基于malloc和free的。

首先它会令至少要分配的内存size为1（也就是有时你定义了一个空的类型）；接着在while处会调用malloc试图分配内存，我们知道当malloc分配内存时有2种行为，一种是分配成功，则返回内存；其次是分配失败，就会返回null，而null在C里面其实是个0。

当malloc分配成功时，显然不会进入while，直接返回p，也就是说new成功了。当malloc得到的size是0时，也就是分配内存失败后它会干嘛呢？

它会优先调用new_handler！除非new_handler为空才会抛出bad_alloc()的异常！

这里就要解说一下new_handler是啥了。首先它作为概念上的handler，顾名思义，是在new行为的基础上才会触发的一种callback(cb)，看源码得知，准确来说是在分配内存失败的时候才会调用。

其次，这个cb非空并且进行调用后，会不断触发malloc，试图再次分配内存并且得到内存为止！我们可以想象这个cb的行为有可能是到外面坑蒙拐骗掳掠后让计算机让出了一丝丝资源让malloc得以偿愿后才能回去休息，不然就要不停地干活！！一个不注意可能会导致死循环。。。

往下看可以看到当nh这个cb为空时，会跑到人尽皆知的bad_alloc()异常，说明其实这个cb是我们手工定义代替系统默认的内存分配失败cb。那么我们应该怎么设定这个自定义bad_alloc()呢？

答案就在effective C++ 49处：set_new_handler()。其实看到get_new_handler就应该有这个预感了，毕竟这是常见的命名规范~。



回到原问题，会内存泄露吗？我们看delete的时候发现它是基于free的，也就是这个问题转移到了malloc/free会不会分辨类型。

那么free释放内存需要知道指针p的确切大小吗？

答案是不需要。因为这个属于C库的memory management范畴，你只需要给到free(void* p)正确的地址即可，地址长度已经在在里面记录了下来，传递的时候是不需要的。

或者也可以更深一步研究：free的空间一定被os回收了吗？

如果一个管理几G的系统整体分配回收几byte的内存会非常低效。这时就应该有碎片的管理，都是属于memory  management方面的内容，交由系统管理~

在Linux下可以通过查看proc文件来见证其行为（一般用的malloc似乎是glib的）

![glib的malloc](E:\learning\Programming\C++Language\glib的malloc.jpg)

glib的malloc有个特征就是初次malloc会申请33页的内存，即图中090f2000 - 09113000    heap处，差等于33。又因为程序停在了while(1)处，该程序已经释放了指针p，而proc中的heap还在，验证了glib的行为。