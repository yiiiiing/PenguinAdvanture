#ifndef BASICSCENE_HH
#define BASICSCENE_HH

#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QSoundEffect>
#include <QVector>
#include <QVector2D>
#include "graphicsItem/player.hh"
#include "map/citymap.hh"
#include "graphicsItem/backgrounditem.hh"
#include "Constants.hh"
#include "graphicsItem/enemy.hh"

class BasicScene : public QGraphicsScene
{
     Q_OBJECT
public:
    explicit BasicScene(QObject *parent = 0);

    // define scene's type
    enum SceneType{Start=0, End, Tampere, Airport, City, University, Hospital, Basic};

    // define current scene
    BasicScene::SceneType mCurrentScene = SceneType::Basic;

    void updateScene();
    virtual void initScene();
    virtual void moveScene();
    virtual void updateItemState();
    void changeWorldShift();
    void applyParallax(qreal ratio, QGraphicsItem *item);

    qreal distanceBetweenPlayerAndItem(QVector2D itemPosition);

    int m_worldShift = 0;

    Player* mPlayer = new Player;

    // add enemys
    QVector<Enemy*> enemys;

    // init enemys
    void initEnemys(QString enemyPath);

    // update enemys
    void updateEnemy();

    // survive all the enemys
    void surviveEnemys();

    // reload the scene if player is die
    virtual void reloadScene();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    BasicScene::SceneType changeScene(SceneType fromScene, SceneType toScene);
    void collideWithEnemy();
    void fellInTrap();

private:
    // define die timer (if player die, then one second later send player to hospital)
    QTimer dieTimer;
    // if player is alive
    bool mPlayerAlive = true;
    QSoundEffect* jumpSound = new QSoundEffect;
    QSoundEffect* attackSound = new QSoundEffect;
    QSoundEffect* dieSound = new QSoundEffect;

};

#endif // BASICSCENE_HH
