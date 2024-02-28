#include "ipadress.h"
#include "ui_ipadress.h"
#include <QtSql>

ipAdress::ipAdress(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ipAdress)
{
    ui->setupUi(this);
    connect(ui->accept, &QPushButton::clicked, this, &QDialog::accept);
    connect(ui->lastConnection, &QPushButton::clicked, this, &ipAdress::lastIp);
    connect(ui->lastConnection, &QPushButton::clicked, this, &QDialog::accept);
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("ipAdresses.db");
    db.open();
}

ipAdress::~ipAdress()
{
    delete ui;
}


void ipAdress::lastIp()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS adresses (id INTEGER PRIMARY KEY, ip STRING)");
    if (!query.exec("SELECT * FROM adresses ORDER BY id DESC LIMIT 1")){
        ui->ipInput->setText("");
    }
    else{
        ui->ipInput->setText(query.value(1).toString());
    }
}

QString ipAdress::getIp() const
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS adresses (id INTEGER PRIMARY KEY, ip STRING)");
    query.prepare("INSERT INTO adresses (ip) VALUES (:ip)");
    query.bindValue(":ip", ui->ipInput->text());
    query.exec();
    return ui->ipInput->text();
}



