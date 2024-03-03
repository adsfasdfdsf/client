#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QContextMenuEvent>

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QString name, QWidget *parent = nullptr);
    ~user();
    void contextMenuEvent(QContextMenuEvent* event) override;
private:
    Ui::user *ui;
};

#endif // USER_H
