#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H


#include <QWidget>

namespace Ui {
class registrationWindow;
}

class registrationWindow : public QWidget
{
    Q_OBJECT

public:
    explicit registrationWindow(QWidget *parent = nullptr);
    ~registrationWindow();

private slots:
    void onCheckIPclicked();

public:
    Ui::registrationWindow *ui;
};

#endif // REGISTRATIONWINDOW_H
