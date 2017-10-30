#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

//服务端功能:获取第三方服务器数据(天气 新闻等) 保存数据到本地服务器(写入文件) 调试终端 传数据到终端(发弹幕 天气 新闻 紧急通知)
//网络模块独立开来,不能等着过来连接(服务器开启按钮 数组或链表维护连接客服端)
int gConnectNum=0;//连接进来的数量

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*tcp与终端通信 listen是阻塞的吗 为什么跑飞 后期考虑移到其它函数*/
    server = new QTcpServer();
    //connect(server,SIGNAL(newConnection()),this,SLOT(accept_client()));
    if(!server->listen(QHostAddress::Any,HostPort)){//监听会一直进行。一旦有新的连接的时候，就会发出newConnection()信号
        qDebug()<<server->errorString();
        close();
    }
    connect(server,SIGNAL(newConnection()),this,SLOT(sendMessage()));
    //server2 = new QTcpServer();
    //connect(server2,SIGNAL(newConnection()),this,SLOT(accept_client2()));
    //server2->listen(QHostAddress::Any,HostPort2);

    /*http与第三方服务器进行通信 获取(天气 新闻等)数据
    requestWeatherManager = new QNetworkAccessManager();
    connect(requestWeatherManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_WertherData(QNetworkReply*)));
    QUrl url(Server_Address);//这里应该请求json网络数据并写入文件,提供接口给终端调用
    //xml-"http://wthrcdn.etouch.cn/WeatherApi?citykey=101280101"
    QNetworkRequest request(url);
    requestWeatherManager->get(request);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newConnect()//返回一个读写套接字，这里，可以用一个容器来放读写套接字，这样就不会覆盖
{
    blocksize = 0;//数据块大小清0
    ++gConnectNum;
    connect_num[gConnectNum]->abort();
    connect_num[gConnectNum] = server->nextPendingConnection();
    qDebug()<<"新客户端连接";//可以考虑做一个小toast
    //socket = server->nextPendingConnection();
    connect(connect_num[gConnectNum], SIGNAL(readyRead()),this,SLOT(read_data()));//关联读取数据的信号
    connect(connect_num[gConnectNum],signal(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError));
}

//void MainWindow::accept_client2()
//{
//    qDebug()<<"弹幕就绪";
//    dmSocket = server2->nextPendingConnection();
//    connect(dmSocket, SIGNAL(readyRead()),this,SLOT(read_dmData()));
//}

void MainWindow::read_data()
{
    //判断客户端是否在线 接收数据成功情况 调试信息等
    QString msg = socket->readAll();
    qDebug()<<msg;
}

void MainWindow::sendMessage()
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    out<<(quint16)0;//用0占位
    out<<tr("hello!");

    QTcpSocket *clientConnection = server->nextPendingConnection();
    connect(clientConnection,SIGNAL(disconnected()),clientConnection,SLOT(deleteLater()));//防止内存泄露

}

void MainWindow::readMessage()
{

}

void MainWindow::displayError(QAbstractSocket::SocketError)
{

}

void MainWindow::requestWeatherData(QNetworkReply *reply)
{

}

//void MainWindow::read_dmData()
//{
//    //弹幕是否回东西过来了
//    QString msg = dmSocket->readAll();
//    qDebug()<<msg;
//}

void MainWindow::read_WertherData(QNetworkReply* reply)//获取第三方天气(新闻等)数据
{
    qDebug()<<"成功读取天气数据";
    QString msg = reply->readAll();
    //解析json数据 封装成自己的工作类
    weatherList.clear();
    QJsonDocument doc = QJsonDocument::fromJson(msg.toUtf8());
    QJsonObject obj = doc.object();
    obj = obj.value("data").toObject();
    //ui->label->setText(obj.value("wendu").toString());
    //ui->label_2->setText(obj.value("ganmao").toString());
    QJsonArray array = obj.value("forecast").toArray();//需要的天气数据
    for(int i=0; i<array.count(); i++)
    {
        QJsonValue value = array.at(i);
        QJsonObject tmp = value.toObject();

        _Weather w;//天气类对象
        w.riqi = tmp.value("date").toString();
        w.fengli = tmp.value("fengli").toString();
        w.fx = tmp.value("fengxiang").toString();
        w.gaowen = tmp.value("high").toString();
        w.diwen = tmp.value("low").toString();
        w.tianqi = tmp.value("type").toString();
        weatherList.append(w);
    }
    //weaLabel[i]->setWeather(weatherList.at(i));
}

void MainWindow::on_zpPush_clicked()
{

}

void MainWindow::on_jinjiPush_clicked()//紧急信息
{
//    socket->write(ui->jinjiNews->toPlainText().toUtf8());
//    qDebug()<<"发送了紧急信息:"<<ui->jinjiNews->toPlainText().toUtf8();
}

void MainWindow::on_reqWeaButton_clicked()
{

}

//void MainWindow::on_danmuPush_clicked()//发弹幕
//{
//    dmSocket->write(ui->danmuArea->toPlainText().toUtf8());
//    qDebug()<<"发送了弹幕:"<<ui->danmuArea->toPlainText().toUtf8();
//}
