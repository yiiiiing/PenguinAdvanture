#ifndef HOSPITALGATE_HH
#define HOSPITALGATE_HH

#include "sceneitem.hh"
#include "Constants.hh"
#include "window/talkwindow.hh"

class HospitalGate : public SceneItem
{
    Q_OBJECT

public:
    HospitalGate();
    TalkWindow* gateWindow;
signals:
    void leaveHospital();

private:
    void windowQuestionResponse(bool answer);
};

#endif // HOSPITALGATE_HH
