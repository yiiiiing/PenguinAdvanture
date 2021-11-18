#include "aircrew.hh"
#include <QDebug>

AirCrew::AirCrew():SceneItem(":/animation/animation/airCrew/stand", npcStandFrame)
{
    // store all messages in the vector
    messages.append("Hello! Little Penguin, Welcome to Tampere!");
    messages.append("It's your first time arriving in Tampere Airports, do you need some introduction?");
    messages.append("You can use arrow keys on keyboard to move and space key to jump.");
    messages.append("You can go up to take train or go down and both way will lead you to the bus stop.");
    messageIndex = 0;

    airCrewWindow = new TalkWindow();
    airCrewWindow->setDisplayText(messages.at(messageIndex));
    airCrewWindow->setButtonText("right", "Next");
    connect(airCrewWindow, &TalkWindow::endTalkWindow, [this](){
        airCrewWindow->close();
        messageIndex = 0;
    });

    connect(airCrewWindow, &TalkWindow::NextTalkWindow, [this](){
        messageIndex += 1;
        windowFameResponse();
    });
    connect(airCrewWindow, &TalkWindow::PreviousTalkWindow, [this](){
        messageIndex -= 1;
        windowFameResponse();
    });
    connect(airCrewWindow, &TalkWindow::windowReturnAnswer, this, &AirCrew::windowQuestionResponse);

}

void AirCrew::processCollideWithPlayer()
{
    messageIndex = 0;
    windowFameResponse();

}


void AirCrew::windowQuestionResponse(bool answer)
{
    //qDebug() << messageIndex;

    //qDebug() << answer ;

    // only message 1 has question to answers
    if (messageIndex==1 && answer){
        messageIndex += 1;
        windowFameResponse();
    }
    else if (messageIndex ==1 && !answer){
        messageIndex = 0;
        airCrewWindow->close();
    }
}

void AirCrew::windowFameResponse()
{
    airCrewWindow->setDisplayText(messages.at(messageIndex));

    switch (messageIndex) {
    // "Hello"
    case 0:
        airCrewWindow->setButtonVisible("right", true);
        airCrewWindow->setButtonText("right", "Next");
        airCrewWindow->setButtonVisible("left", false);
        break;
    // "It's your first time arriving in Tampere Airports, do you need some Introduction"
    case 1:
        airCrewWindow->setButtonVisible("right", true);
        airCrewWindow->setButtonText("right", "Yes");
        airCrewWindow->setButtonVisible("left", true);
        airCrewWindow->setButtonText("left", "No");
        break;
    //"You can use arrow keys on keyboard to move and space key to jump."
    case 2:
        airCrewWindow->setButtonVisible("right", true);
        airCrewWindow->setButtonText("right", "Next");
        airCrewWindow->setButtonVisible("left", true);
        airCrewWindow->setButtonVisible("left", "Previous");
        break;
    // "You can go up to take train or go down and both way will lead you to the bus stop."
    case 3:
        airCrewWindow->setButtonVisible("right", true);
        airCrewWindow->setButtonText("right", "End");
        airCrewWindow->setButtonVisible("left", false);

        break;
    }
}
