#include <QApplication>
//#include "../../Course/CourseLib/graphics/simplemainwindow.hh"
#include "window/login.hh"
#include "gameview.hh"
#include <QGraphicsView>
#include<iostream>
#include<QSplashScreen>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Add Splash Screen
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/otherImage/images/splash.png"));
    splash->show();

    GameView myGame;
    myGame.close();

    Login loginWindow;
    loginWindow.close();


    QTimer::singleShot(5*1000,splash, &QSplashScreen::close);
    QTimer::singleShot(5*1000,&loginWindow, &QDialog::show);

    loginWindow.connect(&loginWindow, &QDialog::accepted, &myGame, &GameView::startView);
    loginWindow.connect(&loginWindow, &QDialog::accepted, &loginWindow, &QDialog::close);
    loginWindow.connect(&loginWindow, &QDialog::rejected, &loginWindow, &QDialog::close);

    return a.exec();
}
