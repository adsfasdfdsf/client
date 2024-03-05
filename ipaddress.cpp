#include "ipaddress.h"
#include "ui_ipaddress.h"
#include <QtSql>

ipAdress::ipAdress(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ipAdress)
{
    ui->setupUi(this);
    connect(ui->accept, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->lastConnection, &QPushButton::clicked, this, &ipAdress::lastIp);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ipAddresses.db");
    db.open();
}

ipAdress::~ipAdress()
{
    delete ui;
}


void ipAdress::lastIp()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS addresses (id INTEGER PRIMARY KEY, ip STRING)");
    query.exec("SELECT * FROM addresses ORDER BY id DESC LIMIT 1");
    query.next();
    ui->ipInput->setText(query.value(1).toString());
    ui->accept->click();
}

QString ipAdress::getIp() const
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS addresses (id INTEGER PRIMARY KEY, ip STRING)");
    query.prepare("INSERT INTO addresses (ip) VALUES (:ip)");
    query.bindValue(":ip", ui->ipInput->text());
    query.exec();
    return ui->ipInput->text();
}



