#include "client.h"
#include "./ui_client.h"
#include "message.h"
//#include "ui_registrationwindow.h"
#include "registrationmodal.h"
#include <QScrollBar>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonParseError>

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
 //   auto bar = ui->scrollArea->verticalScrollBar();
 //   bar->setValue(bar->maximumHeight());  TODO : this thing
}

void client::onGetMessage()
{
    while(socket.bytesAvailable() > 0){
        auto msg = socket.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(msg);
        QJsonObject json = doc.object();
        QJsonArray arr = json["messages"].toArray();
        for(const auto& i: arr){
            QJsonObject msg = i.toObject();
            addMessage(new Message(msg["name"].toString(), msg["message"].toString()));
        }
        auto bar = ui->scrollArea->verticalScrollBar();
        bar->setValue(bar->maximumHeight());
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
    socket.write(name.toLatin1());
}


void client::onSendMessage()
{
    if (ui->inputText->toPlainText() == ""){
        return;
    }
    socket.write(toJson().toLatin1());
    ui->inputText->clear();
}

QString client::toJson() const
{
    QJsonArray arr;
    QJsonObject arrobj;
    arrobj.insert("name", name);
    arrobj.insert("message", ui->inputText->toPlainText());
    arr.push_back(arrobj);
    QJsonObject message;
    message.insert("messages", arr);
    QJsonDocument doc(message);
    QString json = doc.toJson(QJsonDocument::Compact);
    return json;
}
