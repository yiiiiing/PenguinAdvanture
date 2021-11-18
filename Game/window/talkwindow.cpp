#include "talkwindow.hh"
#include "ui_talkwindow.h"

TalkWindow::TalkWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TalkWindow)
{
    ui->setupUi(this);
    //ui->textDisplay->setText();
    ui->leftButton->setVisible(false);
    ui->rightButton->setText("End");
    connect(ui->rightButton, &QPushButton::clicked, this, &TalkWindow::processRightButton);
    connect(ui->leftButton, &QPushButton::clicked, this, &TalkWindow::processLeftButton);
}

TalkWindow::~TalkWindow()
{
    delete ui;
}

void TalkWindow::setDisplayText(QString text)
{
    ui->textDisplay->setText(text);

}

void TalkWindow::setButtonText(QString buttonName, QString text)
{
    if (buttonName == "left"){
        ui->leftButton->setText(text);
        return;
    }

    else if (buttonName == "right"){
        ui->rightButton->setText(text);
        return;
    }
    ui->leftButton->setText("");
    ui->rightButton->setText("");
}

void TalkWindow::setButtonVisible(QString buttonName, bool ifVisible)
{
    if (buttonName == "left"){
        ui->leftButton->setVisible(ifVisible);
        return;
    }

    else if (buttonName == "right"){
        ui->rightButton->setVisible(ifVisible);
        return;
    }
    ui->leftButton->setVisible(false);
    ui->rightButton->setVisible(false);

}

void TalkWindow::processLeftButton()
{
    QString text = ui->leftButton->text().toLower();
    if (text == "previous"){
        emit PreviousTalkWindow();
        return;
    }

    if (text == "no"){
        emit windowReturnAnswer(false);
        return;
    }
    if (text == "yes"){
        emit windowReturnAnswer(true);
        return;
    }

}

void TalkWindow::processRightButton()
{
    QString text = ui->rightButton->text().toLower();
    if (text == "end"){
        emit endTalkWindow();
        return;
    }

    if (text == "next"){
        emit NextTalkWindow();
        return;
    }

    if (text == "no"){
        emit windowReturnAnswer(false);
        return;
    }
    if (text == "yes"){
        emit windowReturnAnswer(true);
        return;
    }

}
