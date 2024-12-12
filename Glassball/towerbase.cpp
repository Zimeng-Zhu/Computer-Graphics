#include "towerbase.h"
#include <QtMath>

TowerBase::TowerBase()
{
    float r = 1, h = 8;
    float PI = 3.14159;

    QVector<Vertex> temp;
    for (int i = 0; i < 360; i++)
    {
        float x0 = 0, y0 = h, z0 = 0;
        float x1 = r * ::cos(i * PI / 180), y1 = h, z1 = r * ::sin(i * PI / 180);
        float x2 = r * ::cos((i + 1) * PI / 180), y2 = h, z2 = r * ::sin((i + 1) * PI / 180);

        float x3 = 0, y3 = 0, z3 = 0;
        float x4 = r * ::cos(i * PI / 180), y4 = 0, z4 = r * ::sin(i * PI / 180);
        float x5 = r * ::cos((i + 1) * PI / 180), y5 = 0, z5 = r * ::sin((i + 1) * PI / 180);

        float tx0 = 0.5, ty0 = 0.5;
        float tx1 = 0.5 + 0.5 * ::cos(i * PI / 180), ty1 = 0.5 + 0.5 * ::sin(i * PI / 180);
        float tx2 = 0.5 + 0.5 * ::cos((i + 1) * PI / 180), ty2 = 0.5 + 0.5 * ::sin((i + 1) * PI / 180);

        float tx3 = float(i) / 360, ty3 = 0;
        float tx4 = float(i + 1) / 360, ty4 = 0;
        float tx5 = float(i) / 360, ty5 = 1;
        float tx6 = float(i + 1) / 360, ty6 = 1;

        temp.append({{x0, y0, z0}, {tx0, ty0}, {x0, y0, z0}});
        temp.append({{x1, y1, z1}, {tx1, ty1}, {x1, y1, z1}});
        temp.append({{x2, y2, z2}, {tx2, ty2}, {x2, y2, z2}});

        temp.append({{x3, y3, z3}, {tx0, ty0}, {x3, y3, z3}});
        temp.append({{x4, y4, z4}, {tx1, ty1}, {x4, y4, z4}});
        temp.append({{x5, y5, z5}, {tx2, ty2}, {x5, y5, z5}});

        temp.append({{x1, y1, z1}, {tx3, ty3}, {x1, y1, z1}});
        temp.append({{x4, y4, z4}, {tx5, ty5}, {x4, y4, z4}});
        temp.append({{x2, y2, z2}, {tx4, ty4}, {x2, y2, z2}});

        temp.append({{x2, y2, z2}, {tx4, ty4}, {x2, y2, z2}});
        temp.append({{x5, y5, z5}, {tx6, ty6}, {x5, y5, z5}});
        temp.append({{x4, y4, z4}, {tx5, ty5}, {x4, y4, z4}});
    }
    setVertices(temp);

    auto _texture = new QOpenGLTexture(QImage(":/texture/castlewall.jpg"));
    _texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    setTexture(_texture);

    setMaterial(MaterialType::BRICK);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/towerbase.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/towerbase.frag");
    setShaderProgram(_program);
}

TowerBase::~TowerBase()
{

}


