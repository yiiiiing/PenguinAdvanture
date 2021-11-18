#include "login.hh"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    //initDialog();
    ui->graphicsView->setStyleSheet("background-image: url(:/otherImage/images/tampere.png)");
    connect(ui->cancelButton, &QPushButton::clicked, this, &Login::rejected);
    connect(ui->startButton, &QPushButton::clicked, this, &Login::accepted);

}
