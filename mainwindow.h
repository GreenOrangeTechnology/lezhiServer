#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

#include <QNetworkAccessManager> //客户端管理
#include <QNetworkRequest>//客户端请求对象
#include <QNetworkReply>//应答对象

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void accept_client();
    void read_data();
    void on_pushButton_clicked();
    void read_data(QNetworkReply* reply);
private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *socket;
    QNetworkAccessManager *manger;
};

#endif // MAINWINDOW_H
