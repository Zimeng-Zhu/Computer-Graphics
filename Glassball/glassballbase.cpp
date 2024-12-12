#include "glassballbase.h"
#include <QtMath>

GlassballBase::GlassballBase()
{
    float r1 = 1, r2 = 1.5, h = 1;
    float PI = 3.14159;

    QVector<Vertex> temp;
    for (int i = 0; i < 360; i++)
    {
        float x0 = 0, y0 = h, z0 = 0;
        float x1 = r1 * ::cos(i * PI / 180), y1 = h, z1 = r1 * ::sin(i * PI / 180);
        float x2 = r1 * ::cos((i + 1) * PI / 180), y2 = h, z2 = r1 * ::sin((i + 1) * PI / 180);

        float x3 = 0, y3 = 0, z3 = 0;
        float x4 = r2 * ::cos(i * PI / 180), y4 = 0, z4 = r2 * ::sin(i * PI / 180);
        float x5 = r2 * ::cos((i + 1) * PI / 180), y5 = 0, z5 = r2 * ::sin((i + 1) * PI / 180);

        float tx0 = 0.5, ty0 = 0.5;
        float tx1 = 0.5 + 0.5 * ::cos(i * PI / 180), ty1 = 0.5 + 0.5 * ::sin(i * PI / 180);
        float tx2 = 0.5 + 0.5 * ::cos((i + 1) * PI / 180), ty2 = 0.5 + 0.5 * ::sin((i + 1) * PI / 180);

        float tx3 = 0.5 - 0.5 * (r1 / r2) * ::cos(i * PI / 360), ty3 = (r1 / r2) * ::sin(i * PI / 360);
        float tx4 = 0.5 - 0.5 * (r1 / r2) * ::cos((i + 1) * PI / 360), ty4 = (r1 / r2) * ::sin((i + 1) * PI / 360);
        float tx5 = 0.5 - 0.5 * ::cos(i * PI / 360), ty5 = ::sin(i * PI / 360);
        float tx6 = 0.5 - 0.5 * ::cos((i + 1) * PI / 360), ty6 = ::sin((i + 1) * PI / 360);

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

    auto _texture = new QOpenGLTexture(QImage(":/texture/glassballbase.jpg"));
    _texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    setTexture(_texture);

    setMaterial(MaterialType::SILVER);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/glassballbase.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/glassballbase.frag");
    setShaderProgram(_program);
}

GlassballBase::~GlassballBase()
{

}
