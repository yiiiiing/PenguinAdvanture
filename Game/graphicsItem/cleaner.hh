#ifndef CLEANER_HH
#define CLEANER_HH
#include "sceneitem.hh"
#include "Constants.hh"
#include "window/talkwindow.hh"

class Cleaner : public SceneItem
{
public:
    Cleaner();
    TalkWindow* cleanerWindow;
};

#endif // CLEANER_HH
