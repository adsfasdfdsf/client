#include "client.h"
#include "message.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    client w;
    w.addMessage(new Message("Иван", "Привет"));
    w.addMessage(new Message("Иван", "Пока"));

    w.show();
    return a.exec();
}
