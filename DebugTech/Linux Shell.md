### 记录一些常用且重要的shell cmd

1. ps:获取进程信息

2. grep：搜索，结合管道极其常用

3. tail：跟踪文件

   * -f : 跟踪当前的
   * -F:更新了也跟踪

4. cp：复制

5. kill/pkill：杀进程

6. mkdir/rmdir：建立/删除文件

7. rm -rf *：全删

8. rz/sz：需要安装，远程传送文件

9. 查看端口号

   > lsof -i：port
   >
   > 用以显示某一端口的占用情况
   >
   > netstat -tunlp
   >
   > 用以显示tcp,udp的端口和进程等相关情况，可以加grep来查看特定端口号
   >
   > ​

10. ​