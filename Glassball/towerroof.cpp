#include "towerroof.h"
#include <QtMath>

TowerRoof::TowerRoof()
{
    float r = 1, h = 3;
    float PI = 3.14159;

    QVector<Vertex> temp;
    for (int i = 0; i < 360; i++)
    {
        float x0 = 0, y0 = 0, z0 = 0;
        float x1 = r * ::cos(i * PI / 180), y1 = 0, z1 = r * ::sin(i * PI / 180);
        float x2 = r * ::cos((i + 1) * PI / 180), y2 = 0, z2 = r * ::sin((i + 1) * PI / 180);
        float x3 = 0, y3 = h, z3 = 0;

        float tx0 = 0.5, ty0 = 0.5;
        float tx1 = 0.5 + 0.5 * ::cos(i * PI / 180), ty1 = 0.5 + 0.5 * ::sin(i * PI / 180);
        float tx2 = 0.5 + 0.5 * ::cos((i + 1) * PI / 180), ty2 = 0.5 + 0.5 * ::sin((i + 1) * PI / 180);

        float tx3 = 0.5, ty3 = 0;
        float tx4 = 0.5 - 0.5 * ::cos(i * PI / 360), ty4 = ::sin(i * PI / 360);
        float tx5 = 0.5 - 0.5 * ::cos((i + 1) * PI / 360), ty5 = ::sin((i + 1) * PI / 360);

        temp.append({{x0, y0, z0}, {tx0, ty0}, {x0, y0, z0}});
        temp.append({{x1, y1, z1}, {tx1, ty1}, {x1, y1, z1}});
        temp.append({{x2, y2, z2}, {tx2, ty2}, {x2, y2, z2}});

        temp.append({{x3, y3, z3}, {tx3, ty3}, {x3, y3, z3}});
        temp.append({{x1, y1, z1}, {tx4, ty4}, {x1, y1, z1}});
        temp.append({{x2, y2, z2}, {tx5, ty5}, {x2, y2, z2}});
    }
    setVertices(temp);

    auto _texture = new QOpenGLTexture(QImage(":/texture/castleroof.jpg"));
    _texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    setTexture(_texture);

    setMaterial(MaterialType::TILE);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/towerroof.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/towerroof.frag");
    setShaderProgram(_program);
}

TowerRoof::~TowerRoof()
{

}
