#include "datacenter.h"
#include "ui_datacenter.h"

#include <QSqlQuery>
#include <QDebug>

dataCenter::dataCenter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dataCenter)
{
    ui->setupUi(this);

    openDatabase();
}

dataCenter::~dataCenter()
{
    delete ui;
}

void dataCenter::on_createDatabase_clicked()
{
    //根据输入的名字来创建数据库
    ui->toastLabel->setText("123");//test
    //qDebug()<<"create database success!";
    //showDatabase();//show all databases
}

void dataCenter::on_createTable_clicked()
{
    QSqlQuery query;
    QString createTableSql = QString("create table %1(number int unique)").arg(ui->tableEdit->text());
    query.exec(createTableSql);
}

void dataCenter::on_insertData_clicked()
{
    QSqlQuery query;
    QString insertTableSql = QString("insert into table %1 values(%2)").arg(ui->tableEdit->text()).arg(ui->insertEdit->text());
    query.exec(insertTableSql);
}

void dataCenter::on_queryData_clicked()
{
    ui->queryShow->clear();
    QString queryTableSql = QString("select * from table %1").arg(ui->tableEdit->text());
    QSqlQuery query(queryTableSql);
    while(query.next())
    {
        ui->queryShow->addItem(query.value(0).toString());
    }
}

bool dataCenter::openDatabase()
{
    mainDb = QSqlDatabase::addDatabase("QSQLITE", SQLDB_NAME);
    mainDb.setDatabaseName(SQLDB_NAME);
    //db.setHostName();
    if(mainDb.open())
    {
        qDebug()<<"open success!";
    }
}

bool dataCenter::closeDatabase()
{
    if(mainDb.open())
    {
        mainDb.close();
    }
}

void dataCenter::showDatabase()
{
    //ui->showAllDatabase  可选中某个进行操作
    //ui->toastLabel->setText(""); 选中数据库:   操作指示标签
}
