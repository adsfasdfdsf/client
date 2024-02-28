#ifndef IPADRESS_H
#define IPADRESS_H

#include <QWidget>

namespace Ui {
class ipAdress;
}

class ipAdress : public QWidget
{
    Q_OBJECT

public:
    explicit ipAdress(QWidget *parent = nullptr);
    ~ipAdress();

private:
    Ui::ipAdress *ui;
};

#endif // IPADRESS_H
