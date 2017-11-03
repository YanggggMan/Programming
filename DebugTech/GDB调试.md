##GDB调试

#### 进程调试

1. 基本的断点调试

   gdb		ProgramName

   b		function_name		//b 代表断点，如:	b	Rua::foo	程序运行就会断在Rua这个类的foo函数位置

   r							//r  run即运行

   c							//continue

   ref							//在程序断点成功后，输入ref可以看到相关代码

   n							//n  next，即下一步

   s							//进入函数

   p							//print命令，可加入  /d  /x等控制输出格式，数组后加入@index来打印数组

   ​

2. 附加进程调试

   gdb		ProgramName		pid		//可先通过ps命令获得该进程的id

   接下来与断点调试相似

   >例如：我要用附加进程在测试服调试一个test程序
   >
   >ps -e | grep test
   >
   >得到：23333(pid)     xxx     test
   >
   >gdb		test		23333
   >
   >c
   >
   >b		Rua::GetMember()
   >
   >这时你在外部让程序调用到GetMember这个Rua类的函数的话，它就会停下来
   >
   >ref
   >
   >这时你就能在xshell上看到代码，通过n一步一步往下走，碰到函数可以用s进入
   >
   >比如这时想要查看某些变量的信息，一个int数组  arr
   >
   >p/d	arr@1
   >
   >如果是一维数组，就会全部以10进制的方式打印出来

#####CORE文件调试

1. 基本操作

   gdb		ProgramName		CoreName	//例如   gdb	test		core.2333

   bt								//即可看到调用的盏	

