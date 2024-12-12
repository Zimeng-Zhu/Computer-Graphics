#include "ground.h"

Ground::Ground()
{
    setVertices({
        {{-1,  1,  0}, {0, 0}, {0,  0,  1}},
        {{1, 1,  0}, {1, 0}, {0,  0,  1}},
        {{-1,  -1,  0}, {0, 1}, {0,  0,  1}},
        {{1,  -1,  0}, {1, 1}, {0,  0,  1}},
        {{1, 1,  0}, {1, 0}, {0,  0,  1}},
        {{-1, -1,  0}, {0, 1}, {0,  0,  1}},
        });

    auto _texture = new QOpenGLTexture(QImage(":/texture/ground.png"));
    _texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    setTexture(_texture);

    setMaterial(MaterialType::WOOD);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/ground.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/ground.frag");
    setShaderProgram(_program);
}

Ground::~Ground()
{

}
