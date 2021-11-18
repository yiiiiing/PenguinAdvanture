#include "buswindow.hh"
#include "ui_buswindow.h"

BusWindow::BusWindow(QString mapName, QWidget *parent) :
    QWidget(parent),
    MapOfBusStop(mapName),
    ui(new Ui::BusWindow)
{
    ui->setupUi(this);
    initWindow();
    connect(ui->rightButton, &QPushButton::clicked, [this](){
        this->close();
        emit selectedBus(ui->rightButton->text());
    });

    connect(ui->leftButton, &QPushButton::clicked, [this](){
        this->close();
        emit selectedBus(ui->leftButton->text());
    });
    connect(ui->endButton, &QPushButton::clicked, this, &QWidget::close);
}

BusWindow::~BusWindow()
{
    delete ui;
}

void BusWindow::initWindow()
{
    ui->textDisplay->setText("Which bus would you like to take?");
    if(MapOfBusStop.toLower() == "airport"){
        ui->rightButton->setVisible(true);
        ui->leftButton->setVisible(true);
        ui->rightButton->setText("6B");
        ui->leftButton->setText("1A");
        return;
    }
    ui->rightButton->setVisible(false);
    ui->leftButton->setVisible(true);
    ui->leftButton->setText("6B");
}
