#include "ceil.h"

Ceil::Ceil()
{
    setVertices({
        {{-1,  1,  0}, {0, 0}, {0,  0,  1}},
        {{1, 1,  0}, {1, 0}, {0,  0,  1}},
        {{-1,  -1,  0}, {0, 1}, {0,  0,  1}},
        {{1,  -1,  0}, {1, 1}, {0,  0,  1}},
        {{1, 1,  0}, {1, 0}, {0,  0,  1}},
        {{-1, -1,  0}, {0, 1}, {0,  0,  1}},
        });

    auto _texture = new QOpenGLTexture(QImage(":/texture/ceil.jpg"));
    _texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    setTexture(_texture);

    setMaterial(MaterialType::LIME);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/ceil.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/ceil.frag");
    setShaderProgram(_program);
}

Ceil::~Ceil()
{

}
