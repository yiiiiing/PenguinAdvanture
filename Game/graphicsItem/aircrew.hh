#ifndef AIRCREW_HH
#define AIRCREW_HH

#include "sceneitem.hh"
#include "Constants.hh"
#include "window/talkwindow.hh"

class AirCrew : public SceneItem
{
public:
    AirCrew();
    void processCollideWithPlayer() override;
    TalkWindow* airCrewWindow;

private:
    void windowQuestionResponse(bool answer);
    void windowFameResponse();
    QVector<QString> messages;
    int messageIndex = 0;

};

#endif // AIRCREW_HH
