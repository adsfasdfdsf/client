#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include "ui_registrationwindow.h"

#include <QMainWindow>
class Message;
QT_BEGIN_NAMESPACE
namespace Ui {
class client;
}
QT_END_NAMESPACE

class client : public QMainWindow
{
    Q_OBJECT
public:
    Ui::registrationWindow *rwui;
public:
    client(QWidget *parent = nullptr);
    ~client();
    void addMessage(Message* message);
public slots:
    void onGetMessage();
    void onRegistered();
    void onSendMessage();
private:
    Ui::client *ui;
    QTcpSocket socket;
    QString name;
};
#endif // CLIENT_H
