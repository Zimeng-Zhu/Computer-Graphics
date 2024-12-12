#include "widget.h"
#include <QDebug>
#include <QOpenGLDebugLogger>
#include <limits>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include <QPushButton>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    QPushButton * changelightcolor = new QPushButton(this);
    changelightcolor->setText("改变灯光颜色");
    changelightcolor->setFont(QFont("宋体", 18));
    changelightcolor->setGeometry(2160, 0, 400, 100);
    connect(changelightcolor, &QPushButton::clicked, this, &Widget::changeLightColor);

    QPushButton * castlerotate = new QPushButton(this);
    castlerotate->setText("城堡旋转/停止旋转");
    castlerotate->setFont(QFont("宋体", 18));
    castlerotate->setGeometry(2160, 100, 400, 100);
    connect(castlerotate, &QPushButton::clicked, this, &Widget::changeCastleRotateStatus);

    QPushButton * snow = new QPushButton(this);
    snow->setText("开始/停止下雪");
    snow->setFont(QFont("宋体", 18));
    snow->setGeometry(2160, 200, 400, 100);
    connect(snow, &QPushButton::clicked, this, &Widget::changeSnowStatus);

    QPushButton * lightrotate = new QPushButton(this);
    lightrotate->setText("灯光旋转/停止旋转");
    lightrotate->setFont(QFont("宋体", 18));
    lightrotate->setGeometry(2160, 300, 400, 100);
    connect(lightrotate, &QPushButton::clicked, this, &Widget::changeLightRotateStatus);

    QPushButton * music = new QPushButton(this);
    music->setText("播放/停止音乐");
    music->setFont(QFont("宋体", 18));
    music->setGeometry(2160, 400, 400, 100);
    connect(music, &QPushButton::clicked, this, &Widget::changeMusicStatus);

    player = new QMediaPlayer;
    player->setMedia(QUrl("qrc:/music/music.mp3"));

    auto newFormat = this->format();
    newFormat.setSamples(16);
    this->setFormat(newFormat);

    startTimer(1000 / 60);

    m_camera.move(-30, 0, -15);
    m_camera.look(0, 0, 0);
    m_camera.update();

    m_light.setPos({ 0, -7, 0});
    m_light.setColor(QColor(255, 255, 255));

    installEventFilter(&m_camera);
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    for (int i = 0; i < 3; ++i)
    {
        auto background = new Background();
        background->setCamera(&m_camera);
        background->setLight(&m_light);
        background->setScale(30);
        if (i == 0) background->setPos({ 0, 0, -30 });
        if (i == 1)
        {
            background->setRotate({0, 90, 0});
            background->setPos({ -30, 0, 0 });
        }
        if (i == 2)
        {
            background->setRotate({0, -90, 0});
            background->setPos({ 30, 0, 0 });
        }
        background->init();
        backgrounds << background;
    }

    ground = new Ground();
    ground->setCamera(&m_camera);
    ground->setLight(&m_light);
    ground->setScale(30);
    ground->setRotate({-90, 0, 0});
    ground->setPos({ 0, -30, 0 });
    ground->init();

    ceil = new Ceil();
    ceil->setCamera(&m_camera);
    ceil->setLight(&m_light);
    ceil->setScale(30);
    ceil->setRotate({90, 0, 0});
    ceil->setPos({ 0, 30, 0 });
    ceil->init();

    glassballbase = new GlassballBase();
    glassballbase->setCamera(&m_camera);
    glassballbase->setLight(&m_light);
    glassballbase->setScale(8);
    glassballbase->setPos({ 0, -30, 0 });
    glassballbase->init();

    castlebase = new CastleBase();
    castlebase->setCamera(&m_camera);
    castlebase->setLight(&m_light);
    castlebase->setScale(4);
    castlebase->setPos({ 0, -19, 0 });
    castlebase->init();

    castleroof = new CastleRoof();
    castleroof->setCamera(&m_camera);
    castleroof->setLight(&m_light);
    castleroof->setScale(4);
    castleroof->setPos({ 0, -16, 0 });
    castleroof->init();

    for (int i = 0; i < 4; i++)
    {
        auto towerbase = new TowerBase();
        towerbase->setCamera(&m_camera);
        towerbase->setLight(&m_light);
        if (i == 0) towerbase->setPos({ 4.7, -22, 3.7 });
        if (i == 1) towerbase->setPos({ 4.7, -22, -3.7 });
        if (i == 2) towerbase->setPos({ -4.7, -22, -3.7 });
        if (i == 3) towerbase->setPos({ -4.7, -22, 3.7 });
        towerbase->init();
        towerbases << towerbase;
    }

    for (int i = 0; i < 4; i++)
    {
        auto towerroof = new TowerRoof();
        towerroof->setCamera(&m_camera);
        towerroof->setLight(&m_light);
        if (i == 0) towerroof->setPos({ 4.7, -14, 3.7 });
        if (i == 1) towerroof->setPos({ 4.7, -14, -3.7 });
        if (i == 2) towerroof->setPos({ -4.7, -14, -3.7 });
        if (i == 3) towerroof->setPos({ -4.7, -14, 3.7 });
        towerroof->init();
        towerroofs << towerroof;
    }

    glassball = new Glassball();
    glassball->setCamera(&m_camera);
    glassball->setLight(&m_light);
    glassball->setScale(10);
    glassball->setPos({ 0, -16, 0 });
    glassball->init();

    for (int i = 0; i < 80; i++)
    {
        auto snow = new Snow();
        snow->setCamera(&m_camera);
        snow->setLight(&m_light);
        snow->setScale(0.1);
        snow->setPos({0, -19, 0});
        snow->init();
        snows << snow;
    }
}

void Widget::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(60, (float)w / h, 0.001, 1000);

    for (auto background : backgrounds)   background->setProjection(m_projection);
    ground->setProjection(m_projection);
    ceil->setProjection(m_projection);
    glassballbase->setProjection(m_projection);
    castlebase->setProjection(m_projection);
    castleroof->setProjection(m_projection);
    for (auto towerbase : towerbases)   towerbase->setProjection(m_projection);
    for (auto towerroof : towerroofs)   towerroof->setProjection(m_projection);
    glassball->setProjection(m_projection);
    for (auto snow : snows)   snow->setProjection(m_projection);
}

void Widget::paintGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    for (auto background : backgrounds)   background->paint();
    ground->paint();
    ceil->paint();
    glassballbase->paint();
    castlebase->paint();
    castleroof->paint();
    for (auto towerbase : towerbases)   towerbase->paint();
    for (auto towerroof : towerroofs)   towerroof->paint();
    for (auto snow : snows)   snow->paint();
    glassball->paint();

    glDisable(GL_DEPTH_TEST);
    QPainter _painter(this);
//    auto _rect = this->rect();
    _painter.setPen(Qt::black);
//    _painter.drawLine(_rect.center() + QPoint{ 0, 5 }, _rect.center() + QPoint{ 0, 15 });
//    _painter.drawLine(_rect.center() + QPoint{ 0, -5 }, _rect.center() + QPoint{ 0, -15 });
//    _painter.drawLine(_rect.center() + QPoint{ 5, 0 }, _rect.center() + QPoint{ 15, 0 });
//    _painter.drawLine(_rect.center() + QPoint{ -5, 0 }, _rect.center() + QPoint{ -15, 0 });

    _painter.drawText(QPoint{ 5, 15 }, QString(u8"摄像机位置: (%1, %2, %3)")
        .arg(m_camera.pos().x(), 0, 'f', 3).arg(m_camera.pos().y(), 0, 'f', 3).arg(m_camera.pos().z(), 0, 'f', 3));
    _painter.drawText(QPoint{ 5, 30 }, QString(u8"摄像机角度: (%1, %2, %3)")
        .arg(m_camera.yaw(), 0, 'f', 3).arg(m_camera.pitch(), 0, 'f', 3).arg(m_camera.roll(), 0, 'f', 3));
}

void Widget::timerEvent(QTimerEvent *event)
{
    m_camera.update();

    float PI = 3.14519;

    if (castle_rotate_status)
    {
        castlebase->setRotate({ 0, castle_angle, 0 });
        castleroof->setRotate({ 0, castle_angle, 0 });

        for (int i = 0; i < 4; i++)
        {
            float x, z;
            if (i == 0)
            {
                x = ::cos(-castle_angle * PI / 180 + ::qAtan(0.74)) * 5.98;
                z = ::sin(-castle_angle * PI / 180 + ::qAtan(0.74)) * 5.98;
            }
            if (i == 1)
            {
                x = ::cos(-castle_angle * PI / 180 + 2 * ::qAcos(0.8) + 2 * ::qAcos(0.6) - ::qAtan(0.74)) * 5.98;
                z = ::sin(-castle_angle * PI / 180 + 2 * ::qAcos(0.8) + 2 * ::qAcos(0.6) - ::qAtan(0.74)) * 5.98;
            }
            if (i == 2)
            {
                x = ::cos(-castle_angle * PI / 180 - 2 * ::qAcos(0.8) - 2 * ::qAcos(0.6) + ::qAtan(0.74)) * 5.98;
                z = ::sin(-castle_angle * PI / 180 - 2 * ::qAcos(0.8) - 2 * ::qAcos(0.6) + ::qAtan(0.74)) * 5.98;
            }
            if (i == 3)
            {
                x = ::cos(-castle_angle * PI / 180 - ::qAtan(0.74)) * 5.98;
                z = ::sin(-castle_angle * PI / 180 - ::qAtan(0.74)) * 5.98;
            }
            towerbases[i]->setPos({x, -22, z});
            towerroofs[i]->setPos({x, -14, z});

        }

        if (castle_angle >= 360)    castle_angle -= 360;
        castle_angle++;
    }

    if (light_rotate_status)
    {
        float x = 9 * ::cos(light_angle * PI / 180), y = -16 + 9 * ::sin(light_angle * PI / 180);
        m_light.setPos({x, y, 0});
        if (!light_direction)    light_angle += 1;
        else    light_angle -= 1;
        if (light_angle > 210)
        {
            light_angle = 210;
            light_direction = true;
        }
        if (light_angle < -30)
        {
            light_angle = -30;
            light_direction = false;
        }
    }

    if (snow_status)
    {
        for (auto snow : snows)
        {
            float x = snow->pos().x();
            float y = snow->pos().y() - 0.025;
            float z = snow->pos().z();
            if (x * x + (y + 16) * (y + 16) + z * z >= 81)
            {
                do
                {
                    x = float(qrand() % 100) / 100 * 15 -7.5;
                    y = float(qrand() % 100) / 100 * 4 -11;
                    z = float(qrand() % 100) / 100 * 15 -7.5;
                }while(x * x + (y + 16) * (y + 16) + z * z >= 81);
            }
            snow->setPos({x, y, z});
        }
    }
    repaint();
}

void Widget::changeLightColor()
{
    int r = qrand() % 255;
    int g = qrand() % 255;
    int b = qrand() % 255;
    m_light.setColor(QColor(r, g, b));
}

void Widget::changeCastleRotateStatus()
{
    castle_rotate_status = !castle_rotate_status;
}

void Widget::changeLightRotateStatus()
{
    light_rotate_status = !light_rotate_status;
}

void Widget::changeMusicStatus()
{
    if (music_status)    player->pause();
    else    player->play();
    music_status = !music_status;
}

void Widget::changeSnowStatus()
{
    snow_status = !snow_status;
    if (snow_status)
    {
        for (auto snow : snows)
        {
            float x, y, z;
            do
            {
                x = float(qrand() % 100) / 100 * 15 -7.5;
                y = float(qrand() % 100) / 100 * 18 -25;
                z = float(qrand() % 100) / 100 * 15 -7.5;
            }while(x * x + (y + 16) * (y + 16) + z * z >= 81);
            snow->setPos({x, y, z});
        }
    }
    else
    {
        for (auto snow : snows) snow->setPos({0, -19, 0});
    }
}
