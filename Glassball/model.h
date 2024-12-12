#pragma once

#include <QMatrix4x4>
#include <QVector3D>
#include <QVector4D>
#include <QOpenGLExtraFunctions>
#include <QOpenGLVertexArrayObject> 
#include <QOpenGLBuffer> 
#include <QOpenGLShaderProgram> 
#include <QOpenGLTexture>
#include "camera.h"
#include "light.h"

struct Vertex
{
	QVector3D pos;
	QVector2D texture;
	QVector3D normal;
};

struct Material
{
    QVector4D ambient = {0, 0, 0, 1};
    QVector4D diffuse = {1, 1, 1, 1};
    QVector4D specular = {0, 0, 0, 1};
    float shininess = 10;
};

static const int VertexFloatCount = 8;

class Model : public QOpenGLExtraFunctions
{
public:
    enum MaterialType
    {
        BRASS, PEWTER, GOLD, SILVER, BRONZE, WOOD, BRICK, GLASS, TILE, SNOW, LIME
    };

	Model();
	~Model();
public:
	void setScale(float val) { m_scale = val; }
	void setRotate(const QVector3D &rotate) { m_rotate = rotate; }
	void setPos(const QVector3D &pos) { m_pos = pos; }
	float scale() { return m_scale; }
	QVector3D rotate() { return m_rotate; }
	QVector3D pos() { return m_pos; }
public:
	void setVertices(const QVector<Vertex> &vertices) { m_vertices = vertices; }
	void setTexture(QOpenGLTexture *texture, int index = -1);
	void setShaderProgram(QOpenGLShaderProgram *program) { m_program = program; }
	void setMaterial(const Material &material, int index  = -1);
    void setMaterial(MaterialType type, int index = -1);
    void setGlobalAmbient(const QVector4D &global_ambient) {m_global_ambient = global_ambient;}
public:
	void setCamera(Camera *camera) { m_camera = camera; }
	void setProjection(const QMatrix4x4 &projection) { m_projection = projection; }
	void setLight(Light *light) { m_light = light; }
public:
	QMatrix4x4 model();
public:
	virtual void init();
	virtual void update();
	virtual void paint();
protected:
	QVector3D m_pos{ 0,0,0 };
	QVector3D m_rotate{ 0,0,0 };
    QVector4D m_global_ambient{1, 1, 1, 1};
	float m_scale = 1;

	QVector<Vertex> m_vertices;
	QMap<int, QOpenGLTexture *> m_textures;
	QMap<int, Material> m_materials;

	QOpenGLVertexArrayObject m_vao;
	QOpenGLBuffer m_vbo;
	QOpenGLShaderProgram *m_program = nullptr;

	QMatrix4x4 m_projection;
	Camera *m_camera = nullptr;
	Light *m_light = nullptr;

    float *m_vertexBuffer = nullptr;
    int m_vertexCount = 0;
};
