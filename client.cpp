#include "client.h"
#include "./ui_client.h"
#include "message.h"
#include "registrationwindow.cpp"

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
}

client::~client()
{
    delete ui;
}

void client::addMessage(Message *message)
{
    ui->chat->layout()->addWidget(message);
}

void client::onGetMessage()
{
    while(socket.bytesAvailable() > 0){
        QString msg = socket.readAll();
        auto list = msg.split("#");
        addMessage(new Message(list[0], list[1]));
    }
}

void client::onRegistered()
{
    quint16 port = rw_ptr->ui->port->toPlainText().toUInt();
    socket.connectToHost(rw_ptr->ui->ip->toPlainText(), port);
    name = rw_ptr->ui->setName->toPlainText();
}

void client::onSendMessage()
{
    socket.write(name.toLocal8Bit());
    socket.write("#");
    socket.write(ui->inputText->toPlainText().toLocal8Bit());

}
