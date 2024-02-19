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

class client : public QMainWindow
{
    Q_OBJECT
public:
    RegistrationModal* modal_ptr;
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
private:
    QString toJson() const;
};
#endif // CLIENT_H
