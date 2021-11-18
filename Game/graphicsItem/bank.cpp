#include "bank.hh"

Bank::Bank():SceneItem("", 0)
{
    // store all messages in the vector
    messages.append("Hello! Little Penguin, Welcome to Tampere Bank");
    messages.append("Would you like to open a bank card?");
    messages.append("You have a bank card now, Bye!");
    bankWindow = new TalkWindow();
    windowFameResponse();
    connect(bankWindow, &TalkWindow::endTalkWindow, [this](){
        messageIndex = 0;
        windowFameResponse();
        bankWindow->close();
    });
    connect(bankWindow, &TalkWindow::NextTalkWindow, [this](){
        messageIndex += 1;
        windowFameResponse();
    });
    connect(bankWindow, &TalkWindow::PreviousTalkWindow, [this](){
        messageIndex -= 1;
        windowFameResponse();
    });
    connect(bankWindow, &TalkWindow::windowReturnAnswer, this, &Bank::windowQuestionResponse);
}

void Bank::processCollideWithPlayer()
{
       messageIndex = 0;
       windowFameResponse();
}

void Bank::windowFameResponse()
{
    bankWindow->setDisplayText(messages.at(messageIndex));
    if (!messageIndex){
        bankWindow->setButtonVisible("right", true);
        bankWindow->setButtonText("right", "Next");
        bankWindow->setButtonVisible("left", false);
        return;
    }

    if (messageIndex == messages.length() - 1){
        bankWindow->setButtonVisible("right", true);
        bankWindow->setButtonText("right", "End");
        bankWindow->setButtonVisible("left", false);
        return;
    }

    if (messageIndex == 1){
        bankWindow->setButtonVisible("right", true);
        bankWindow->setButtonText("right", "Yes");
        bankWindow->setButtonVisible("left", true);
        bankWindow->setButtonText("left", "No");
    }
}

void Bank::windowQuestionResponse(bool answer)
{
    if (answer && messageIndex == 1){
        messageIndex = messageIndex + 1;
        windowFameResponse();
        return;
    }

    else if (!answer && messageIndex == 1){
        messageIndex = 0;
        windowFameResponse();
        this->bankWindow->close();
    }
}
