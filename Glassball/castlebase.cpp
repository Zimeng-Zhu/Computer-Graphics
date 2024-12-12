#include "castlebase.h"

CastleBase::CastleBase()
{
    float l = 1, w = 0.75, h = 0.75;
    setVertices({
        {{-l,  h,  w}, {0, 0}, {-l,  h,  w}},
        {{l, h,  w}, {1, 0}, {l, h,  w}},
        {{-l,  -h,  w}, {0, 1}, {-l,  -h,  w}},
        {{l,  -h,  w}, {1, 1}, {l,  -h,  w}},
        {{l, h,  w}, {1, 0}, {l, h,  w}},
        {{-l, -h,  w}, {0, 1}, {-l, -h,  w}},

        {{l,  h,  -w}, {0, 0}, {l,  h,  -w}},
        {{-l, h,  -w}, {1, 0}, {-l, h,  -w}},
        {{l,  -h,  -w}, {0, 1}, {l,  -h,  -w}},
        {{-l,  -h,  -w}, {1, 1}, {-l,  -h,  -w}},
        {{-l, h,  -w}, {1, 0}, {-l, h,  -w}},
        {{l, -h,  -w}, {0, 1}, {l, -h,  -w}},

        {{l,  h,  w}, {0, 0}, {l,  h,  w}},
        {{l, h,  -w}, {1, 0}, {l, h,  -w}},
        {{l,  -h,  w}, {0, 1}, {l,  -h,  w}},
        {{l,  -h,  -w}, {1, 1}, {l,  -h,  -w}},
        {{l, h,  -w}, {1, 0}, {l, h,  -w}},
        {{l, -h,  w}, {0, 1}, {l, -h,  w}},

        {{-l,  h,  -w}, {0, 0}, {-l,  h,  -w}},
        {{-l, h,  w}, {1, 0}, {-l, h,  w}},
        {{-l,  -h,  -w}, {0, 1}, {-l,  -h,  -w}},
        {{-l,  -h,  w}, {1, 1}, {-l,  -h,  w}},
        {{-l, h,  w}, {1, 0}, {-l, h,  w}},
        {{-l, -h,  -w}, {0, 1}, {-l, -h,  -w}},

        {{-l,  h, -w}, {0, 0}, {-l,  h, -w}},
        {{l, h, -w}, {1, 0}, {l, h, -w}},
        {{-l,  h, w}, {0, 1}, {-l,  h, w}},
        {{l,  h, w}, {1, 1}, {l,  h, w}},
        {{l, h, -w}, {1, 0}, {l, h, -w}},
        {{-l, h, w}, {0, 1}, {-l, h, w}},

        {{-l,  -h,  w}, {0, 0}, {-l,  -h,  w}},
        {{l, -h,  w}, {1, 0}, {l, -h,  w}},
        {{-l,  -h, -w}, {0, 1}, {-l,  -h, -w}},
        {{l,  -h,  -w}, {1, 1}, {l,  -h,  -w}},
        {{l, -h,  w}, {1, 0}, {l, -h,  w}},
        {{-l, -h, -w}, {0, 1}, {-l, -h, -w}},
        });

    auto _texture = new QOpenGLTexture(QImage(":/texture/castlewall.jpg"));
    _texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    _texture->setMagnificationFilter(QOpenGLTexture::Linear);
    setTexture(_texture);

    setMaterial(MaterialType::BRICK);

    auto _program = new QOpenGLShaderProgram();
    _program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/castlebase.vert");
    _program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/castlebase.frag");
    setShaderProgram(_program);
}

CastleBase::~CastleBase()
{

}
