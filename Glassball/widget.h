#ifndef WIDGET_H
#define WIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "camera.h"
#include "light.h"
#include "glassballbase.h"
#include "castlebase.h"
#include "castleroof.h"
#include "towerbase.h"
#include "towerroof.h"
#include "background.h"
#include "ground.h"
#include "glassball.h"
#include "snow.h"
#include "ceil.h"
#include <QMediaPlayer>


class Widget : public QOpenGLWidget, public QOpenGLExtraFunctions
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;

    virtual void timerEvent(QTimerEvent *event);

    void changeLightColor();
    void changeCastleRotateStatus();
    void changeLightRotateStatus();
    void changeMusicStatus();
    void changeSnowStatus();

private:
    QMatrix4x4 m_projection;

    Camera m_camera;
    Light m_light;
    Model *ground, *ceil, * glassballbase, * castlebase, *castleroof, *glassball;
    QVector<Model *> backgrounds, towerbases, towerroofs, snows;
    float castle_angle = 0;
    float light_angle = 90;
    bool light_direction = false;   //false向左，true向右
    bool castle_rotate_status = false;
    bool light_rotate_status = false;
    bool music_status = false;
    bool snow_status = false;
    QMediaPlayer *player;



};
#endif // WIDGET_H
