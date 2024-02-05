#include "client.h"
#include "./ui_client.h"
#include "message.h"

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
