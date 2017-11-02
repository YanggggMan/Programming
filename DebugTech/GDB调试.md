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

2. 附加进程调试

   gdb		ProgramName		pid		//可先通过ps命令获得该进程的id

   接下来与断点调试相似

#####CORE文件调试

1. 基本操作

   gdb		ProgramName		CoreName	//例如   gdb	test		core.2333

   bt								//即可看到调用的盏	

