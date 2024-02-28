#include "ipadress.h"
#include "ui_ipadress.h"

ipAdress::ipAdress(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ipAdress)
{
    ui->setupUi(this);
}

ipAdress::~ipAdress()
{
    delete ui;
}
