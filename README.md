longmaix3review
===============

longmai x3 ,x1,mtoken 测试代码，整个评估过程，可能会把文档也放进来

其实，x3就是一个 基于arm的，有内存和硬盘的小计算机。我很喜爱！

## chapter 1 跑案例

x3可以编写执行代码在锁内，有IDE，芯片也绝对算得上通用，是arm的。然后硬件和软件一起做加密。

光盘提供有案例。如何把第一个案例login-demo跑起来?

1. 执行 delphi应用程序

V:\Smart X3 SDK V2.1\samples\标准示例（通用）\login_demo\software\Delphi\Delphi_login_Demo\SmartX3_login_Demo.exe 

2. 执行 查找
找到

3. 执行 登录 按钮，结果应该是失败
9:24:51：执行失败　错误码：4

3.这是因为，锁内还没有写入配套程序bin

4. 这个bin位于

V:\Smart X3 SDK V2.1\samples\标准示例（通用）\login_demo\hardware\X3_user_login\X3_user_login.bin

5. 如何写入bin到锁内？

光盘 - 快速向导 内提及
     ...
     7. 通过Smart X3工程管理工具将编译后BIN可执行文件导入到工程的可执行文件系统中
     8. 完成工程设置后，在工程管理工具中下载工程到Smart X3设备中
     ...

6. 打开 “工程管理器”（从portal内打开）
 
选择打开  \login_demo\hardware\X3_user_login\ 目录，默认文件类型为*.proj,但是我们要把它改为*.x3proj。就可以看到 X3_Login_Demo.x3proj,打开

7. 喔，别有洞天。

可以看到数据文件，可执行文件之类的新东西。然后找到一个工具条按钮，叫做 下载全部 ，点击后，生成报告，说下载了一个执行文件之类的。然后，重复第一步，会发现结果不再是执行失败，而是

9:49:41：执行成功 可执行文件返回值：0
9:49:40：版本标识号:0.0.0.0
9:49:40：硬件序列号:faf986096626364bb86077ce70dabe8d
9:49:40：查找成功

----------------- DONE 

## chapter 2

术语

MDK ,羞羞答答的，其实就是keil ide。一般arm上比较通用的ide，某国外公司的 。

MDK 工程向导工具，就是更加软件狗的版本（标准，专业），以及出口入口参数，来生成不同的MDK 工程，然后调用keil 打开工程。

工程管理器，可以利用MDK工程（可以被KeilIDE打开），生成bin，数据文件定义，然后刷新硬件锁。

应用测试工具。从工程管理器哪里可以生成一个 应用测试工程（菜单-工具-生成应用测试工程），一个xml文件。这个文件，可以被应用测试工具 打开，然后可以看到数据文件，可执行文件，并且修改参数去运行可执行文件，查看结果。就是说，有了这个工具，可以写好并刷新了bin后，不必自己写应用程序文件，就可以通过这个工具，测试bin的输入输出。都对了之后，再去编写测试代码。这样对此测试 bin 很方便。

管理测试工具。和 应用测试工具的不同在于有一个管理员模式，在这个模式下，可以看到数据文件。

制作升级包工具。可以选择工程文件后，制定升级可执行文件，数据文件，改写b/s密码,改写版本等任务，生成结果是一个升级包。


目标

这次要完成的测试，是如何生成bin文件，并刷新硬件锁。为了方便，就把logindemo拿来改，把密码改为7654321，然后把软件的登录也改掉，看看是否可以软件硬件再次握手。

用keil ide 打开 

C:\龙脉加密锁研究\Smart X3 SDK V2.1\Samples\标准示例（通用）\login_demo\hardware\X3_user_login\X3_user_login.uvproj

注意keil ide 工程的扩展名为 *.uvproj

修改代码内校验密码 12345678 为 87654321

int main(void)
{
     if(g_user_password != 87654321)
     {
          smart_open_error();
          return (1);
     }
     else
     {
          smart_open();
     }
       return (0);
}

然后 project | build target ,就可以发现对应工程目录内的 X3_user_login.bin 日期变化，说明，编译成功。怎么可能不成功？可以的，只要你的代码在光盘这样的不可写介质内就会。解决方法是把它挪动到硬盘内。

刷新bin到软件狗，如tutial 1 说明那样。

再到delphi的工程

exe执行，点击登录，发现 

10:17:23：执行成功 可执行文件返回值：1

修改密码 87654321

10:17:23：执行成功 可执行文件返回值：0

这说明修改生效了

----DONE 

把所有光盘的案例都看了一遍，都是比较基本的锁内api调用案例，非常基本，几乎就是直接使用api，毫无变通。这对于初学者来说，是很不错的，来的简单！接下来看 api 说明文档

## chapter 3

很本质的一句话

”
Smart X3智能型编程锁更适合的是“逻辑算法块搬移”，用户就
可以把大量算法在Smart X3中实现，并把它看成是完整程序的一个充满算法逻
辑的动态链接库，所以它可以抽象成硬件级“算法DLL
”


技术指标

1. 锁用户内存分配

8KB：6KB（普通）+2KB（共享）
6KB普通：1KB数据交互区+1KB栈+4KB全局变量
共享内存，支持可执行文件之间的数据交换

2. 芯片

32bit arm （具体型号未知，芯片已经打磨）

3. 有硬件唯一序列号

4.文件

数据文件，共4K，最多48个
执行文件，共8k，最多48个

通过ide生成多个bin，和数据文件，可以在bin内通过api访问数据文件，在多个bin之间通过共享内存交换数据。这就是x3加密的基本原理。

5. howto

---- 如何更改 气泡信息？

a. 建立工程
b. 第一页内，修改气泡信息
c. 下载全部（输入超级密码验证）
d. 通过菜单： 工具 - 加密锁信息 ，可以看到气泡信息已经更改 （此信息在高级标签页）

## chapter 4 

目标：

编写一个bin，输入参数 src，输出为
src++, return src+1。

步骤

1. 创建keil 工程

点击 portal - mdk 工程向导工具
指定路径
加入参数 src ，类型int，长度1
生成并且打开keil

2. keil 修改 代码

extern int                src;
int main(void)
{
    src++;
       return (src+1);
}

3. build 

4. 工程管理器

创建工程，反正就是一个 *.x3proj 文件，放到一个地方

创建 可执行文件 ，选择刚刚生成的 bin

5. 写入 X3 （我的小计算机：）
报告：写入 1 个可执行文件 就对了

6. 应用测试工具

生成应用测试工程（在 工程管理器内 ，点击 工具-生成应用测试工程）
打开应用测试工具，选择刚刚生成的工程文件
点击 开始测试
默认src = 0 
点击测试，发现src=1，return 等于 2

-------DONE

## chapter 5

目标：在 x3 内完成一个bubble sort算法，可以把传入参数数组做一个排序


要点：

1. 创建MDK 工程时，传入参数为src，类型int，长度 5 ，只要不是1 ，就是数组！

2. main 代码

extern int                src[5];
int main(void)
{
    int j,i,n,temp;
     n = 5;
     for(i=0 ; i<n ; i++)
     {
       for(j=0 ; j<n-i-1 ; j++)
       {
        if(src[j]>src[j+1]) 
        {
              temp=src[j];
              src[j]=src[j+1];
              src[j+1]=temp;
        }
       }
     }
       return (0);
}

其他步骤类似 tutorial 4

----DONE 

## chapter 6 

目标：

访问数据文件，排序后写回，然后用 管理测试工具 查看数据文件。

步骤：

1. 就是代码了

读入file 0的头5个字符，排序后，把结果写回file 0 的头五个字符内

int main(void)
{
     HANDLE l_hfile;
     int l_ret = 0;    
     unsigned long       g_positon=0;
     unsigned long       g_len = 5 ;    
     unsigned char      src[5];
     int j,i,n,temp;
    l_hfile = smart_open_file(0);
     smart_read_file(l_hfile, g_positon, g_len, src);
     n = 5;
     for(i=0 ; i<n ; i++)
     {
       for(j=0 ; j<n-i-1 ; j++)
       {
        if(src[j]>src[j+1])
        {
              temp=src[j];
              src[j]=src[j+1];
              src[j+1]=temp;
        }
       }
     }
    l_ret = smart_write_file(l_hfile, g_positon, g_len, src);
       return (l_ret);               // 写入字符数 ，5
}

2. 要用 工程管理器 加入一个数据文件
就是file0了。分配一个8字节的文件给它。

3. 下载
4. 管理测试工具，查看被排序后的数据文件

确实排序了


----DONE
















