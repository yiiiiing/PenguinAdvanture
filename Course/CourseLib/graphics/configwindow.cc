#include "configwindow.hh"
#include "ui_konffiikkuna.h"


namespace CourseSide
{

ConfigWindow::ConfigWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KonffiIkkuna)
{
    ui->setupUi(this);
    connect(ui->btnAja, SIGNAL(clicked(bool)), this, SLOT(accept()) );
    connect(ui->btnPeruuta, SIGNAL(clicked(bool)), this, SLOT(reject()) );

    ui->timeEdit->setTime(QTime::fromString("10:00", "hh:mm"));
}

ConfigWindow::~ConfigWindow()
{
    delete ui;
}


int ConfigWindow::exec()
{
    int rv = QDialog::exec();
    if (rv == QDialog::Accepted){
        emit configChanged(ui->timeEdit->time(), ui->cbDebug->isChecked());
    }
    return rv;
}

}
