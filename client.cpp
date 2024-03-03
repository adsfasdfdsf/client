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
#include "ipaddress.h"
#include "user.h"

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
    modal_ptr = new RegistrationModal(this);
    ip_modal_ptr = new ipAdress(this);
    connect(modal_ptr, &QDialog::accepted, this, [this](){ip_modal_ptr->exec();});
    connect(ip_modal_ptr, &QDialog::accepted, this, &client::onRegistered);
    connect(ui->buttonSend, &QPushButton::clicked, this, &client::onSendMessage);
    modal_ptr->exec();
}

client::~client()
{
    delete ui;
}

void client::addMessage(Message *message)
{
    auto bar = ui->scrollArea->verticalScrollBar();
    if (bar->value() == bar->maximum()){
        ui->chat->layout()->addWidget(message);
        ui->chat->adjustSize();
        qApp->processEvents();
        bar->setValue(bar->maximum());
    }else{
        ui->chat->layout()->addWidget(message);
    }
}

void client::addUser(user* user)
{
    ui->users->layout()->addWidget(user);
}

void client::onGetMessage()
{
    while(socket.bytesAvailable() > 0){
        auto msg = socket.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(msg);
        QJsonObject json = doc.object();
        if (json["mode"].toString() == "message"){
            QJsonArray arr = json["messages"].toArray();
            for(const auto& i: arr){
                QJsonObject msg = i.toObject();
                addMessage(new Message(msg["name"].toString(), msg["message"].toString()));
            }
            return;
        }
        if (json["mode"].toString() == "add_user")
        {
            users.push_back(json["name"].toString());
            ui->users->layout()->addWidget(new ipAdress);
            return;
        }
    }
}

void client::onRegistered()
{
    socket.connectToHost(ip_modal_ptr->getIp(), 1234);
    name = modal_ptr->getName();
    connect(&socket, &QTcpSocket::readyRead, this, &client::onGetMessage);
    qDebug() << "connected";
    socket.write(toJsonName().toUtf8());
}


void client::onSendMessage()
{
    if (ui->inputText->toPlainText() == ""){
        return;
    }
    socket.write(toJsonMsg().toUtf8());
    ui->inputText->clear();
}


QString client::toJsonMsg() const
{
    QJsonArray arr;
    QJsonObject arrobj;
    if (!ui->anonymus->isChecked())
        arrobj.insert("name", name);
    else
        arrobj.insert("name", "");
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
    QJsonObject json;
    json.insert("mode", "setName");
    json.insert("name", name);
    QJsonDocument doc(json);
    QString str = doc.toJson(QJsonDocument::Compact);
    return str;
}


