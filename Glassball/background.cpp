#include "background.h"

Background::Background()
{
    setVertices({
        {{-1,  1,  0}, {0, 0}, {0, 0, 1}},
        {{1, 1,  0}, {1, 0}, {0, 0, 1}},
        {{-1,  -1,  0}, {0, 1}, {0, 0, 1}},
        {{1,  -1,  0}, {1, 1}, {0, 0, 1}},
        {{1, 1,  0}, {1, 0}, {0, 0, 1}},
        {{-1, -1,  0}, {0, 1}, {0, 0, 1}},
        });

    auto _texture = new QOpenGLTexture(QImage(":/texture/wall.jpg"));
    _texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    setTexture(_texture);

    setMaterial(MaterialType::TILE);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/background.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/background.frag");
    setShaderProgram(_program);
}

Background::~Background()
{

}
