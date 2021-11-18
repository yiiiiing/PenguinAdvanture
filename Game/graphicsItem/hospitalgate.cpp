#include "hospitalgate.hh"

HospitalGate::HospitalGate():SceneItem(":/animation/animation/gate/gate", gateFrame)
{

    // define gate window (only 2 choices, yes or no)
    gateWindow = new TalkWindow();
    gateWindow->setDisplayText("Would you like to leave the hospital?");
    gateWindow->setButtonVisible("right", true);
    gateWindow->setButtonText("right", "Yes");
    gateWindow->setButtonVisible("left", true);
    gateWindow->setButtonText("left", "No");

    connect(gateWindow, &TalkWindow::windowReturnAnswer, this, &HospitalGate::windowQuestionResponse);
}


void HospitalGate::windowQuestionResponse(bool answer)
{
    if (answer){
        // emit signal leaveHospital to the hospitalScene
        emit leaveHospital();
    }
    else if (!answer){
        gateWindow->close();
    }
}
