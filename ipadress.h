#ifndef IPADRESS_H
#define IPADRESS_H

#include <QDialog>

namespace Ui {
class ipAdress;
}

class ipAdress : public QDialog
{
    Q_OBJECT

public:
    explicit ipAdress(QWidget *parent = nullptr);
    ~ipAdress();

public:
    Ui::ipAdress *ui;
    void lastIp();
    QString getIp() const;
};

#endif // IPADRESS_H
