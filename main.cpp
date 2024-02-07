#include "client.h"
#include "message.h"
#include "registrationwindow.h"
#include "registrationwindow.cpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client w;
    w.addMessage(new Message("Иван", "Привет"));
    w.addMessage(new Message("Иван", "Пока"));
    registrationWindow win;
    QObject::connect(win.ui->CheckIP, &QPushButton::clicked, &w, &client::onRegistered);
    w.rwui = win.ui;
    win.show();
    w.show();
    return a.exec();
}
