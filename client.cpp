#include "client.h"
#include "./ui_client.h"
#include "message.h"
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
}

void client::onGetMessage()
{
    setlocale(LC_ALL, "Russian");
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
    setlocale(LC_ALL, "Russian");
    socket.connectToHost(modal_ptr->getIp(), 1234);
    name = modal_ptr->getName();
    connect(&socket, &QTcpSocket::readyRead, this, &client::onGetMessage);
    qDebug() << "connected";
    socket.write(toJsonName().toUtf8());
}


void client::onSendMessage()
{
    setlocale(LC_ALL, "Russian");
    if (ui->inputText->toPlainText() == ""){
        return;
    }
    socket.write(toJsonMsg().toLatin1());
    ui->inputText->clear();
}

QString client::toJsonMsg() const
{
    setlocale(LC_ALL, "Russian");
    QJsonArray arr;
    QJsonObject arrobj;
    arrobj.insert("name", name);
    arrobj.insert("message", ui->inputText->toPlainText());
    arr.push_back(arrobj);
    QJsonObject message;
    message.insert("mode", "message");
    message.insert("messages", arr);
    QJsonDocument doc(message);
    QString json = doc.toJson(QJsonDocument::Compact);
    return json;
}


QString client::toJsonName() const{
    setlocale(LC_ALL, "Russian");
    QJsonObject json;
    json.insert("mode", "setName");
    json.insert("name", name);
    QJsonDocument doc(json);
    QString str = doc.toJson(QJsonDocument::Compact);
    return str;
}


