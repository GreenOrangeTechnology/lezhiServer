# lezhiServer
## 使用方法
1.服务器未检测到连接只可以使用单机功能
2.点击开启服务器才能连接到服务器
3.接收显示区域放置历史数据信息(天气 传感器)
4.客户端连接后发送信息按钮才能使用

## 数据库设计
数据来源
0.第三方数据源
1.底层传感器传回
2.软件运行/系统调试等信息
3.客户端(安卓 非开发板)发给服务器
4.服务器发给客户端

存储方式
1.写入本地文件(缓存到文件)
2.sqlite3数据库

## 项目规划
目标
智能家居后端服务提供(数据模型 接口,这个项目既是大项目一部分,又可以单独立项)
客户端:终端(带触控屏的控制台-可能与另外一台服务器通信的服务器)用

需求
0.使用列表说明
1.模块化(网络开关-按了从其他服务器获取数据就开始获取数据 开启服务器-供客户端进行使用)
2.存储数据 并提供给下面(只是硬件模块需要的),作为手机客户端数据源 获取传感器数据
3.客服端(非手机客户端):界面显示(传感器数据 操作 菜单) 基础的控制(串口通信) 
4.与本地服务器进行交互 弹幕发送/接收
5.FTP (手机下载log文件)  

设计
UI->拖动式(但要明确如何转换为代码)
网络接口

bug及风险控制(工具 API http://www.kuqin.com/qtdocument/index.html)
1.点击按钮会退出
2.网络连接没加判断 (之前:需要开虚拟机和先打开服务端)

模块划分
1.网络通信(bearer management是什么?)步骤 概念关系(理清server socket 端口 进程 之间关系 分析需求:发送弹幕是一个socket还是一个server) 坑 http://blog.csdn.net/chenlong12580/article/details/7431864
http://blog.csdn.net/chenlong12580/article/details/7434114  -udp & hostinfo
[拆包黏包 http://blog.csdn.net/sweettool/article/details/77018506]
2.串口模块测试单独模块加入
3.单元测试

数据结构

通信协议

------------------------------- 
参考设计说明
开发系统：Windows10 64位 
		    Ubuntu 14.04 32 位
软件版本：Qt 4.8.6
		    IAR .0
          Altium Designer 13.0
工具链:arm-linux-gcc 4.4.3

系统实现的主要功能如下所示：
1.	STM32下位机
(1)	应用了小型的嵌入式操作系统μC/OS-II；
(2)	各个传感器的数据以多任务的形式
获取，实时性很好；
(3)	数据调试使用STM32串口1；
(4)	数据的发送使用STM32的串口3，并以任务的形式进行打包发送，具体数据帧格式请看代码；
(5)	STM32接收数据采用终端方式，当有数据到来时会触发终端，进入数据接收解析过程，在此过程中会对数据的帧头等信息进行判断；
2.	Zigbee无线通信
Zigbee部分其实没有太多功能，一句话概括就是一个串口透传功能！本来当初计划直接使用zigbee驱动各个传感器，然后组网后发送给协调器，考虑到既然学习了STM32，就利用上吧！其实这里完全可以直接使用zigbee，不使用STM32的。
两套方案的编码工作其实早就已经完成了，思考了好久才决定采用STM32+zigbee方式，这样下来可以学到很多，尤其是μC/OS-II系统的移植，还是很深奥的，很值的以后继续深入的去学习。
3.	ARM上位机
ARM上位机采用友善支臂的SMART210开发板，自己后续移植了Qt4.8。上位机主要实现了一下几个功能：
(1)	模拟室内三个场景：卧室、客厅、厨房
(2)	分别对这个三个场景下的温度，湿度以及烟雾浓度进行一个测量并显示；
(3)	使用LED灯模拟室内照明灯；
(4)	使用人体红外传感器进行检测是否有人(这个传感器有点不靠谱，最后取消了)
(5)	当初计划添加视频监控，到了后期发现工作量太大，没有时间做了，所以就没有完成，这点以后会添加上去的。
(6)	代码中使用了“liudianwu”分享的一些api，由于时间紧，所以直接拿来用了，在此感谢！
(7)	代码重复率有点高，好几处的button样式是相同的，完全可以提取出来，在此请大家海涵。
