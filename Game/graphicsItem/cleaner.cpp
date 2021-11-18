#include "cleaner.hh"

Cleaner::Cleaner():SceneItem(":/animation/animation/cleaner/cleaner", npcStandFrame)
{
    cleanerWindow = new TalkWindow();
    cleanerWindow->setDisplayText("Hello! Little Penguin, Welcome to Tampere University!");
    cleanerWindow->setButtonVisible("right", true);
    cleanerWindow->setButtonText("right", "End");
    cleanerWindow->setButtonVisible("left", false);
    connect(cleanerWindow, &TalkWindow::endTalkWindow, [this](){
        cleanerWindow->close();
    });
}

