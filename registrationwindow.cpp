#include "registrationwindow.h"
#include "ui_registrationwindow.h"

registrationWindow::registrationWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::registrationWindow)
{
    ui->setupUi(this);
}

registrationWindow::~registrationWindow()
{
    delete ui;
}

