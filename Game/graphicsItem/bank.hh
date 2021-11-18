#ifndef BANK_HH
#define BANK_HH

#include "sceneitem.hh"
#include "Constants.hh"
#include "window/talkwindow.hh"

class Bank : public SceneItem
{
public:
    Bank();
    void processCollideWithPlayer() override;
    TalkWindow* bankWindow;

private:
    void windowFameResponse();
    void windowQuestionResponse(bool answer);
    QVector<QString> messages;
    int messageIndex = 0;
};

#endif // BANK_HH
