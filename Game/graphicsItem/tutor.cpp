#include "tutor.hh"

Tutor::Tutor():SceneItem(":/animation/animation/tutor/tutor", npcStandFrame)
{
    // store all messages in the vector
    messages.append("Hello! Little Penguin, Welcome to Tampere! I'm your tutor");
    messages.append("To register as a new student in Tampere University, Please bring your passport to university.");
    messages.append("Remember to bring your bank card to pay your student fee!");
    messages.append("You can take bus 1A to city center to open a bank card or bus 6B to university.");
    messages.append("But I guess you don't have bank card now, so I suggest you taking bus 1A to city center first!");

    messageIndex = 0;

    tutorWindow = new TalkWindow();
    tutorWindow->setDisplayText(messages.at(messageIndex));
    tutorWindow->setButtonText("right", "Next");
    connect(tutorWindow, &TalkWindow::endTalkWindow, [this](){
        tutorWindow->close();
        messageIndex = 0;
    });

    connect(tutorWindow, &TalkWindow::NextTalkWindow, [this](){
        messageIndex += 1;
        windowFameResponse();
    });
    connect(tutorWindow, &TalkWindow::PreviousTalkWindow, [this](){
        messageIndex -= 1;
        windowFameResponse();
    });

}

void Tutor::processCollideWithPlayer()
{
    messageIndex = 0;
    windowFameResponse();
}

void Tutor::setMessage(QVector<QString> newMessages)
{
    messages = newMessages;
}


void Tutor::windowFameResponse()
{
    tutorWindow->setDisplayText(messages.at(messageIndex));
    if (!messageIndex){
        tutorWindow->setButtonVisible("right", true);
        tutorWindow->setButtonText("right", "Next");
        tutorWindow->setButtonVisible("left", false);
        return;
    }

    if (messageIndex == messages.length() - 1){
        tutorWindow->setButtonVisible("right", true);
        tutorWindow->setButtonText("right", "End");
        tutorWindow->setButtonVisible("left", true);
        tutorWindow->setButtonText("left", "Previous");
        return;
    }

    tutorWindow->setButtonVisible("right", true);
    tutorWindow->setButtonText("right", "Next");
    tutorWindow->setButtonVisible("left", true);
    tutorWindow->setButtonText("left", "Previous");
}
