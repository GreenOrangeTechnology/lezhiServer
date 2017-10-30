#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTcpServer>
#include <QTcpSocket>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include <QList>
#include <weatherlabel.h>

#define MAX_CONNECTION 20
#define HostPort 9875
#define HostPort2 9876
#define Server_Address "http://192.168.1.58/weather"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow //提供一个有菜单条、锚接窗口（例如工具条）和一个状态条的主应用程序窗口
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);//explicit阻止不应该允许的经过转换构造函数进行的隐式转换
    ~MainWindow();

private slots:
    //申请第三方数据
    void requestWeatherData();
    void requestNewsData();
    void connectToOtherServer();

    //与客户端进行交互
    void newConnect();//获取新连接
    void readMessage();//读取发来的信息
    void sendMessage();//有人来连接就发送一条信息给它
    void readControlOrder();//读取发来的控制命令
    void sendControlOrder();//读取发来的控制命令
    void displayError(QAbstractSocket::SocketError);

    //服务端私有槽
    void read_WertherData(QNetworkReply* reply);//读取天气数据
    void on_jinjiPush_clicked();
    void on_reqWeaButton_clicked();

private:
    quint16 blocksize;//占两个字节
    Ui::MainWindow *ui;
    QTcpServer *server;
    //int connect_num[MAX_CONNECTION];最大连接数
    QTcpSocket *socket[MAX_CONNECTION];//,*dmSocket;//socket数组怎么搞 普通socket接收终端连接信息等 弹幕socket专门用来发弹幕
    QNetworkAccessManager *manager;//http客户端管理对象,与终端通信
    QNetworkAccessManager *requestWeatherManager;//请求第三方天气数据
    weatherLabel *weaLabel[5];//[]或者数组 ,*weaLabel2
    QList<_Weather> weatherList;//用于存放天气数据
};

#endif // MAINWINDOW_H
