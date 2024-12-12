#include "glassball.h"
#include <QtMath>

Glassball::Glassball()
{
    float r = 1;
    float PI = 3.14159;

    QVector<Vertex> temp;
    for (int i = -90; i < 90; i++)
    {
        for (int j = 0; j < 360; j++)
        {
            float x0 = r * ::cos(i * PI / 180) * ::cos(j * PI / 180);
            float y0 = r * ::cos(i * PI / 180) * ::sin(j * PI / 180);
            float z0 = r * ::sin(i * PI / 180);

            float x1 = r * ::cos(i * PI / 180) * ::cos((j + 1) * PI / 180);
            float y1 = r * ::cos(i * PI / 180) * ::sin((j + 1) * PI / 180);
            float z1 = r * ::sin(i * PI / 180);

            float x2 = r * ::cos((i + 1) * PI / 180) * ::cos((j + 1) * PI / 180);
            float y2 = r * ::cos((i + 1) * PI / 180) * ::sin((j + 1) * PI / 180);
            float z2 = r * ::sin((i + 1) * PI / 180);

            float x3 = r * ::cos((i + 1) * PI / 180) * ::cos(j * PI / 180);
            float y3 = r * ::cos((i + 1) * PI / 180) * ::sin(j * PI / 180);
            float z3 = r * ::sin((i + 1) * PI / 180);

            temp.append({{x0, y0, z0}, {1, 0}, {-x0, -y0, -z0}});
            temp.append({{x1, y1, z1}, {1, 1}, {-x1, -y1, -z1}});
            temp.append({{x2, y2, z2}, {0, 1}, {-x2, -y2, -z2}});

            temp.append({{x0, y0, z0}, {1, 0}, {-x0, -y0, -z0}});
            temp.append({{x3, y3, z3}, {0, 0}, {-x3, -y3, -z3}});
            temp.append({{x2, y2, z2}, {0, 1}, {-x2, -y2, -z2}});
        }
    }
    setVertices(temp);

    auto _texture = new QOpenGLTexture(QImage(":/texture/glass.png"));
    _texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    setTexture(_texture);

    setMaterial(MaterialType::GLASS);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/glassball.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/glassball.frag");
    setShaderProgram(_program);
}

Glassball::~Glassball()
{

}
