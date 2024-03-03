#include "user.h"
#include "ui_user.h"
#include <QMenu>
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

void user::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    menu.addAction("Написать лично");
}
