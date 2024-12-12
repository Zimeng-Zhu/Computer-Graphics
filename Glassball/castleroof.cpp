#include "castleroof.h"

CastleRoof::CastleRoof()
{
    float l = 1, w = 0.75, h = 0.75;
    setVertices({
        {{-l,  0,  w}, {0, 0}, {-l,  0,  w}},
        {{l, 0,  w}, {1, 0}, {l, 0,  w}},
        {{-l, 0, -w}, {0, 1}, {-l, 0, -w}},
        {{l, 0,  -w}, {1, 1}, {l, 0,  -w}},
        {{l, 0,  w}, {1, 0}, {l, 0,  w}},
        {{-l, 0, -w}, {0, 1}, {-l, 0, -w}},

        {{0,  h,  0}, {0.5, 0}, {0,  h,  0}},
        {{-l, 0,  w}, {0, 1}, {-l, 0,  w}},
        {{l, 0, w}, {1, 1}, {l, 0, w}},

        {{0,  h,  0}, {0.5, 0}, {0,  h,  0}},
        {{l, 0,  w}, {0, 1}, {l, 0,  w}},
        {{l, 0, -w}, {1, 1}, {l, 0, -w}},

        {{0,  h,  0}, {0.5, 0}, {0,  h,  0}},
        {{l, 0,  -w}, {0, 1}, {l, 0,  -w}},
        {{-l, 0, -w}, {1, 1}, {-l, 0, -w}},

        {{0,  h,  0}, {0.5, 0}, {0,  h,  0}},
        {{-l, 0,  -w}, {0, 1}, {-l, 0,  -w}},
        {{-l, 0, w}, {1, 1}, {-l, 0, w}},
        });

    auto _texture = new QOpenGLTexture(QImage(":/texture/castleroof.jpg"));
    _texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    setTexture(_texture);

    setMaterial(MaterialType::TILE);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/castleroof.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/castleroof.frag");
    setShaderProgram(_program);
}

CastleRoof::~CastleRoof()
{

}
