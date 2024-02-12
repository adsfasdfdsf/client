#include "client.h"
#include "./ui_client.h"
#include "message.h"
//#include "ui_registrationwindow.h"
#include "registrationmodal.h"

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
    modal_ptr = new RegistrationModal(this);
    connect(modal_ptr, &QDialog::accepted, this, &client::onRegistered);
    connect(ui->buttonSend, &QPushButton::clicked, this, &client::onSendMessage);
    modal_ptr->exec();
}

client::~client()
{
    delete ui;
}

void client::addMessage(Message *message)
{
    ui->chat->layout()->addWidget(message);
    qDebug() << ui->chat->layout()->count();
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
    //quint16 port = rw_ptr->ui->port->toPlainText().toUInt();
    //socket.connectToHost(rw_ptr->ui->ip->toPlainText(), port);
    //name = rw_ptr->ui->setName->toPlainText();
    socket.connectToHost(modal_ptr->getIp(), 1234);
    name = modal_ptr->getName();
    connect(&socket, &QTcpSocket::readyRead, this, &client::onGetMessage);
    qDebug() << "connected";
}

void client::onSendMessage()
{
    if (ui->inputText->toPlainText() == ""){
        return;
    }
    socket.write(name.toLocal8Bit());
    socket.write("#");
    socket.write(ui->inputText->toPlainText().toLocal8Bit());
    ui->inputText->clear();
}
