#ifndef TEACHER_HH
#define TEACHER_HH

#include "sceneitem.hh"
#include "Constants.hh"
#include "window/talkwindow.hh"
#include <QObject>

class Teacher : public SceneItem
{
    Q_OBJECT
public:
    Teacher();
    void processCollideWithPlayer() override;
    TalkWindow* teacherWindow;

    // teacher has two state, say and stand
    enum class TeacherState{Stand, Say};

    void setTeacherState(TeacherState state);
    TeacherState getTeacherState() const;

    void getIfHasBankCard(bool ifHasBankCard);

signals:
    // send to the university scene, in the university scene, checking if player has bank card
    void checkBankCard();
    void endGame();
private:
    void windowFameResponse();
    void windowQuestionResponse(bool answer);
    bool ifPlayerHasBankCard = false;
    QVector<QString> messages;
    int messageIndex;
    // teacher current state
    TeacherState currentState = TeacherState::Stand;
};

#endif // TEACHER_HH
