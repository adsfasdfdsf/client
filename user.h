#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QContextMenuEvent>


class client;
namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QString name, client* mainwin, QWidget *parent = nullptr);
    ~user();
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    Ui::user *ui;
    client* mainwin;
};

#endif // USER_H
