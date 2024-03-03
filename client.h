#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>

#include <QMainWindow>
class Message;
QT_BEGIN_NAMESPACE
namespace Ui {
class client;
}
QT_END_NAMESPACE

class RegistrationModal;

class ipAdress;

class user;

class client : public QMainWindow
{
    Q_OBJECT
public:
    RegistrationModal* modal_ptr;
    ipAdress* ip_modal_ptr;
public:
    client(QWidget *parent = nullptr);
    ~client();
    void addMessage(Message* message);
    void addUser(user* user);
public slots:
    void onGetMessage();
    void onRegistered();
    void onSendMessage();
private:
    Ui::client *ui;
    QTcpSocket socket;
    QString name;
    QVector<QString> users;
private:
    QString toJsonMsg() const;
    QString toJsonName() const;
};
#endif // CLIENT_H
