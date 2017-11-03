#ifndef DATACENTER_H
#define DATACENTER_H

#include <QWidget>
#include <QSqlDatabase>

//sql database
//file operation
//system

#define SQLDB_NAME "C:\\sqlite3\\family.db"  // data/smartHome

//平台编译  pro文件里判断以调用哪个
//#define UNIX_MODEL 1
#define WIN_MODEL  2

namespace Ui {
class dataCenter;
}

class dataCenter : public QWidget
{
    Q_OBJECT

public:
    explicit dataCenter(QWidget *parent = 0);
    ~dataCenter();

private slots:
    void on_createDatabase_clicked();
    void on_createTable_clicked();
    void on_insertData_clicked();
    void on_queryData_clicked();
    void on_pushButton_clicked();

private:
    Ui::dataCenter *ui;
    QSqlDatabase mainDb;
    bool isOpenDatabaseSuccess;

    bool openDatabase();
    bool closeDatabase();
    void showDatabase();//show directory database
    bool dropDatabase();//备份数据库
    void deleteDatabase();

    void showAllTables();
    bool deleteTables();

    void showAllColumn();
};

#endif // DATACENTER_H
