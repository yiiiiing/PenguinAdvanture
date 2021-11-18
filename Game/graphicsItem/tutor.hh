#ifndef TUTOR_HH
#define TUTOR_HH

#include "sceneitem.hh"
#include "Constants.hh"
#include "window/talkwindow.hh"

class Tutor : public SceneItem
{
public:
    Tutor();
    void processCollideWithPlayer() override;
    void setMessage(QVector<QString> newMessages);
    TalkWindow* tutorWindow;

private:
    void windowFameResponse();
    QVector<QString> messages;
    int messageIndex;

};

#endif // TUTOR_HH
