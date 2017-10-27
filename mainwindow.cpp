#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    manger = new QNetworkAccessManager();
    //当服务器处理完毕返回应答包的时候manger会发生finished信号
    connect(manger,SIGNAL(finished(QNetworkReply*)),this,SLOT(read_data(QNetworkReply*)));

    /*服务器数据区域*/
    //终端每(是否需要最新并且为第一)次请求之后的内容保存进服务器
    //设置为text文件地址关联QUrl url("http://wthrcdn.etouch.cn/weather_mini?city=广州");
    //设置触发条件QNetworkRequest request(url);
    //manger->get(request);

    server = new QTcpServer();
    connect(server,SIGNAL(newConnection()),this,SLOT(accept_client()));
    server->listen(QHostAddress::Any,9876);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::read_data(QNetworkReply* reply)
{
    QString msg = reply->readAll();
    //这里作为终端数据提供区
    //ui->textBrowser->append(msg);
}

void MainWindow::accept_client()
{
    qDebug()<<"新客户端连接";
    socket = server->nextPendingConnection();
    //关联读取数据的信号
    connect(socket, SIGNAL(readyRead()),this,SLOT(read_data()));
}

void MainWindow::read_data()
{
    //这里改为客户端是否已成功接收数据 判断在线情况 调试信息等
    QString msg = socket->readAll();
    ui->listWidget->addItem(msg);
}


void MainWindow::on_pushButton_clicked()
{
    socket->write(ui->textEdit->toPlainText().toUtf8());
}
