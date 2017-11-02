#ifndef DATACENTER_H
#define DATACENTER_H

#include <QWidget>
#include <QSqlDatabase>

#define SQLDB_NAME "data/smartHome2.db"

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

private:
    Ui::dataCenter *ui;
    QSqlDatabase mainDb;

    bool openDatabase();
    bool closeDatabase();
    void showDatabase();//show directory database
};

#endif // DATACENTER_H
