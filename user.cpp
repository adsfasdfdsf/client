#include "user.h"
#include "ui_user.h"

user::user(QString name, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::user)
{
    ui->setupUi(this);
    ui->label->setText(name);
}

user::~user()
{
    delete ui;
}
