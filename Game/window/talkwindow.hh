#ifndef TALKWINDOW_HH
#define TALKWINDOW_HH

#include <QWidget>
#include <QGraphicsWidget>

namespace Ui {
class TalkWindow;
}

class TalkWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TalkWindow(QWidget *parent = nullptr);
    ~TalkWindow();

    void setDisplayText(QString text);
    void setButtonText(QString buttonName, QString text);
    void setButtonVisible(QString buttonName, bool ifVisible);

signals:
    void endTalkWindow();
    void PreviousTalkWindow();
    void NextTalkWindow();
    bool windowReturnAnswer(bool answer);

private:
    void processLeftButton();
    void processRightButton();

    Ui::TalkWindow *ui;

};

#endif // TALKWINDOW_HH
