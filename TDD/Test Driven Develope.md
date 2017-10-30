### Test Driven Develope



1. 安装GoogleTest

   1. cmake与makefile
   2. lib与头文件
   3. vs的GoogleTest插件

2. TDD基本方法

   1. 理想效果

      * 飘柔一样的重构
      * 测试即文档

   2. 三步

      * 只在让失败测试通过才编写产品代码
      * 测试发生失败时就停止编写测试
      * 只编写刚好能让一个失败测试通过的代码

   3. 相关联的产品代码

      * 以 **isEmpty()** 和 **size()** 为例

      * 推荐方法1：编写辅助方法or自定义断言

        ~~~c++
            MATCHER_P(HasSize, expected, ""){
              return
                arg.size() == expected &&
                arg.isEmpty() == (0 == expected);
            }
            TEST_F(```){
              ```
              ASSERT_THAT(object, HasSize(0u));
            }
        ~~~

      * 推荐方法2：为两个概念显式创建文档


        ~~~c++
        TEST_F(···){
          ASSERT_THAT(object.size(), Eq(0u));
          
          ASSERT_THAT(object.isEmpty());
        }
        TEST_F(```){
          object.add(xx);
          ASSERT_THAT(object.size(), Gt(0u));
          
          ASSERT_THAT(object.isEmpty());
        }
        ~~~

        ​

   3. 3a  Arrange-Act-Assert/Given-When-Then

4. GoogleTest的使用

   * TEST宏
   * Fixture[^1]
     * setup
   * MATCHER_P宏
   * ​

5. 重构策略

   * 单一责任原则

     * 例子：不要把高层策略与底层的实现细节糅合到一起。比如升级的打牌流程代码，一开始应该只定义相关的流程接口，再去实现相关接口	

       > ~~~c++
       > bool ret = m_GameLogic.CanOutCard();
       > if (ret){
       >   bool res = m_GameLogic.CompareOutCard();
       > }
       > ~~~
       >
       > ​


5. Other Tools

   * git:版本管理工具

6. 误区

   * 测试行为而非方法

     > TDD初学者常犯的一个错误就是会耗费精力去测试成员函数，为了完全覆盖（比如 **add()** )而写许多不同的情形，却失去了文档的价值。所以正确的做法是把注意力放在行为或描述行为的情形上。
     >
     > * 如果加入一个之前已经加入的object会怎样？
     > * 如果传入一个空的object会怎样？
     > * 如果object不在有效？







[^1]: fixture的加入以整理测试代码，而当你需要2个不同的fixture时，可能意味着违反了单一责任原则，需要拆分