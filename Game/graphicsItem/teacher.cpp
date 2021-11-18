#include "teacher.hh"

Teacher::Teacher():SceneItem(":/animation/animation/teacher/stand/stand", npcStandFrame)
{
    // store all messages in the vector
    messages.append("Hello! Little Penguin, Welcome to study at Tampere University!");
    messages.append("Please show me your passport.");
    messages.append("Also, you need to pay student fee, we only support bank card.");
    messages.append("I'm sorry that you don't have bank card, you should open a card at bank in city center.");
    messages.append("Thanks, you have finished your registration, would you like to end game now?");
    messageIndex = 0;

    teacherWindow = new TalkWindow();
    teacherWindow->setDisplayText(messages.at(messageIndex));
    teacherWindow->setButtonText("right", "Next");
    connect(teacherWindow, &TalkWindow::endTalkWindow, [this](){
        teacherWindow->close();
        messageIndex = 0;
        setTeacherState(TeacherState::Stand);
    });

    connect(teacherWindow, &TalkWindow::NextTalkWindow, [this](){
        // if message = we only support bank card
        // check if player has bank card
        if (ifPlayerHasBankCard){
            // if player has bank card, directly display the last sentence
            messageIndex = messages.length()-1;
        }else{
            messageIndex += 1;
        }
        windowFameResponse();
    });
    connect(teacherWindow, &TalkWindow::PreviousTalkWindow, [this](){
        messageIndex -= 1;
        windowFameResponse();
    });

    connect(teacherWindow, &TalkWindow::windowReturnAnswer, this, &Teacher::windowQuestionResponse);

}

void Teacher::processCollideWithPlayer()
{
    // if user has already seen the last message (that meaning that user have finished the registeration)
    // then user open the window again, will always see the last message
    messageIndex = 0;
    windowFameResponse();
}

void Teacher::setTeacherState(Teacher::TeacherState state)
{
    currentState = state;
    switch (state) {
    case TeacherState::Stand :
        setItemPath(":/animation/animation/teacher/stand/stand", npcStandFrame);
        break;
    case TeacherState::Say:
        setItemPath(":/animation/animation/teacher/say/say", teacherSayFrame);
        break;
    }
}


void Teacher::windowFameResponse()
{
    teacherWindow->setDisplayText(messages.at(messageIndex));
    switch (messageIndex) {
    case 0:
        teacherWindow->setButtonVisible("right", true);
        teacherWindow->setButtonText("right", "Next");
        teacherWindow->setButtonVisible("left", false);
        break;
    case 1:
        teacherWindow->setButtonVisible("right", true);
        teacherWindow->setButtonText("right", "Next");
        teacherWindow->setButtonVisible("left", true);
        teacherWindow->setButtonText("left", "Previous");
        break;
    case 2:
        emit checkBankCard();
        break;
    case 3:
        teacherWindow->setButtonVisible("right", true);
        teacherWindow->setButtonText("right", "End");
        teacherWindow->setButtonVisible("left", false);
        break;
    case 4:
        teacherWindow->setButtonVisible("right", true);
        teacherWindow->setButtonText("right", "Yes");
        teacherWindow->setButtonVisible("left", true);
        teacherWindow->setButtonText("left", "No");
        break;
    }

}

void Teacher::windowQuestionResponse(bool answer)
{
    setTeacherState(TeacherState::Stand);
    teacherWindow->close();
    if (messageIndex==messages.length()-1 && answer){
        // and emit signal that user end the game
        emit endGame();
    }
    messageIndex = 0;

}

Teacher::TeacherState Teacher::getTeacherState() const
{
    return currentState;
}

void Teacher::getIfHasBankCard(bool ifHasBankCard)
{
    if (ifHasBankCard){
        ifPlayerHasBankCard = true;
    }
}

