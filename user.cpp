#include "user.h"
#include "ui_user.h"
#include <QMenu>
#include "client.h"

user::user(QString name, client* mainwin, QWidget *parent)
    : QWidget(parent),
    mainwin(mainwin),
    ui(new Ui::user)
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

    menu.QWidget::addAction("Написать лично", [this](){
        mainwin->message_to(ui->label->text());
    });
    menu.exec(event->globalPos());
 }
