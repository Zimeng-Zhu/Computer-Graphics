#include "model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::setTexture(QOpenGLTexture *texture, int index)
{
	if (index == -1)
	{
		if (m_textures.isEmpty())
		{
			index = 0;
		}
		else
		{
			index = m_textures.keys().last() + 1;
		}
	}
	m_textures.insert(index, texture);
}

void Model::setMaterial(const Material &material, int index)
{
	if (index == -1)
	{
		if (m_materials.isEmpty())
		{
			index = 0;
		}
		else
		{
			index = m_materials.keys().last() + 1;
		}
	}
	m_materials.insert(index, material);
}

void Model::setMaterial(MaterialType type, int index)
{
    if (index == -1)
    {
        if (m_materials.isEmpty())
        {
            index = 0;
        }
        else
        {
            index = m_materials.keys().last() + 1;
        }
    }

    Material material;
    switch (type)
        {
        case MaterialType::BRASS:
            material.ambient= QVector4D(0.3294f, 0.2235f, 0.0275f, 1);
            material.diffuse = QVector4D(0.7804f, 0.5686f, 0.1137f, 1);
            material.specular= QVector4D(0.9922f, 0.9412f, 0.8078f, 1 );
            material.shininess = 27.9f;
        break;
        case MaterialType::PEWTER:
            material.ambient= QVector4D(0.1059f, 0.0588f, 0.1137f, 1);
            material.diffuse = QVector4D(0.4275f, 0.4706f, 0.5412f, 1);
            material.specular= QVector4D(0.3333f, 0.3333f, 0.5216f, 1 );
            material.shininess = 9.85f;
        break;
        case MaterialType::GOLD:
            material.ambient= QVector4D(0.2473f, 0.1995f, 0.0745f, 1);
            material.diffuse = QVector4D(0.7516f, 0.6065f, 0.2265f, 1);
            material.specular= QVector4D(0.6283f, 0.5559f, 0.3661f, 1 );
            material.shininess = 51.2f;
        break;
        case MaterialType::SILVER:
            material.ambient= QVector4D( 0.1923f, 0.1923f, 0.1923f, 1 );
            material.diffuse = QVector4D( 0.5075f, 0.5075f, 0.5075f, 1 );
            material.specular= QVector4D( 0.5083f, 0.5083f, 0.5083f, 1 );
            material.shininess = 51.2f;
        break;
        case MaterialType::BRONZE:
            material.ambient = QVector4D ( 0.2125f, 0.1275f, 0.0540f, 1 );
            material.diffuse = QVector4D( 0.7140f, 0.4284f, 0.1814f, 1 );
            material.specular = QVector4D( 0.3936f, 0.2719f, 0.1667f, 1 );
            material.shininess = 25.6f;
        break;
        case MaterialType::WOOD:
            material.ambient = QVector4D ( 0.2f, 0.2f, 0.2f, 1 );
            material.diffuse = QVector4D( 0.6f, 0.5f, 0.3f, 1 );
            material.specular = QVector4D( 0.6f, 0.5f, 0.3f, 1 );
            material.shininess = 30.0f;
        break;
        case MaterialType::BRICK:
            material.ambient = QVector4D ( 0.1f, 0.1f, 0.1f, 1 );
            material.diffuse = QVector4D( 0.5f, 0.5f, 0.5f, 1 );
            material.specular = QVector4D( 0.1f, 0.1f, 0.1f, 1 );
            material.shininess = 0.0f;
        break;
        case MaterialType::GLASS:
            material.ambient = QVector4D ( 0.0f, 0.0f, 0.0f, 1 );
            material.diffuse = QVector4D( 0.8f, 0.8f, 0.8f, 1 );
            material.specular = QVector4D( 1.0f, 1.0f, 1.0f, 1 );
            material.shininess = 100.0f;
        break;
        case MaterialType::TILE:
            material.ambient = QVector4D ( 0.2f, 0.2f, 0.2f, 1 );
            material.diffuse = QVector4D( 0.5f, 0.5f, 0.5f, 1 );
            material.specular = QVector4D( 0.3f, 0.3f, 0.3f, 1 );
            material.shininess = 25.0f;
        break;
        case MaterialType::SNOW:
            material.ambient = QVector4D ( 0.5f, 0.5f, 0.5f, 1 );
            material.diffuse = QVector4D( 1.0f, 1.0f, 1.0f, 1 );
            material.specular = QVector4D( 0.3f, 0.3f, 0.3f, 1 );
            material.shininess = 30.0f;
        break;
        case MaterialType::LIME:
            material.ambient = QVector4D ( 0.1f, 0.1f, 0.1f, 1 );
            material.diffuse = QVector4D( 0.4f, 0.4f, 0.4f, 1 );
            material.specular = QVector4D( 0.2f, 0.2f, 0.2f, 1 );
            material.shininess = 30.0f;
        break;
        }
    m_materials.insert(index, material);
}

QMatrix4x4 Model::model()
{
	QMatrix4x4 _mat;
	_mat.setToIdentity();
	_mat.translate(m_pos);
	_mat.rotate(m_rotate.x(), 1, 0, 0);
	_mat.rotate(m_rotate.y(), 0, 1, 0);
	_mat.rotate(m_rotate.z(), 0, 0, 1);
	_mat.scale(m_scale);
	return _mat;
}

void Model::init()
{
    initializeOpenGLFunctions();
    if (!m_vao.isCreated())
        m_vao.create();
    if (!m_vbo.isCreated())
        m_vbo.create();
    if (!m_program->isLinked())
        m_program->link();

    if (m_vertexCount < m_vertices.count())
    {
        if (m_vertexBuffer) delete[] m_vertexBuffer;
        m_vertexBuffer = new float[m_vertices.count() * VertexFloatCount];
        m_vertexCount = m_vertices.count();
        int _offset = 0;
        for (auto &vertex : m_vertices)
        {
            m_vertexBuffer[_offset] = vertex.pos.x(); _offset++;
            m_vertexBuffer[_offset] = vertex.pos.y(); _offset++;
            m_vertexBuffer[_offset] = vertex.pos.z(); _offset++;
            m_vertexBuffer[_offset] = vertex.texture.x(); _offset++;
            m_vertexBuffer[_offset] = vertex.texture.y(); _offset++;
            m_vertexBuffer[_offset] = vertex.normal.x(); _offset++;
            m_vertexBuffer[_offset] = vertex.normal.y(); _offset++;
            m_vertexBuffer[_offset] = vertex.normal.z(); _offset++;
        }
    }

    m_vao.bind();
    m_vbo.bind();
    m_vbo.allocate(m_vertexBuffer, sizeof(float) * m_vertices.count() * VertexFloatCount);

    m_program->bind();

    m_program->setAttributeBuffer("vPos", GL_FLOAT, 0 * sizeof(float), 3, VertexFloatCount * sizeof(float));
    m_program->enableAttributeArray("vPos");

    m_program->setAttributeBuffer("vTexture", GL_FLOAT, 3 * sizeof(float), 2, VertexFloatCount * sizeof(float));
    m_program->enableAttributeArray("vTexture");

    m_program->setAttributeBuffer("vNormal", GL_FLOAT, 5 * sizeof(float), 3, VertexFloatCount * sizeof(float));
    m_program->enableAttributeArray("vNormal");
    m_program->release();

    m_vbo.release();
    m_vao.release();
}

void Model::update()
{
}

void Model::paint()
{
    for (auto index : m_textures.keys())
    {
        m_textures[index]->bind(index);
    }
    m_vao.bind();
    m_program->bind();
    // 绑定变换矩阵
    m_program->setUniformValue("projection", m_projection);
    m_program->setUniformValue("view", m_camera->view());
    m_program->setUniformValue("viewPos", m_camera->pos());
    m_program->setUniformValue("model", model());
    // 设定灯光位置与颜色
    m_program->setUniformValue("light.position", m_light->pos());
    m_program->setUniformValue("light.color", m_light->color().redF(), m_light->color().greenF(), m_light->color().blueF());
    m_program->setUniformValue("light.ambient", m_light->ambient());
    m_program->setUniformValue("light.diffuse", m_light->diffuse());
    m_program->setUniformValue("light.specular", m_light->specular());
    auto &_material = m_materials.value(0);
    // 设定材质
    m_program->setUniformValue("material.ambient", _material.ambient);
    m_program->setUniformValue("material.diffuse", _material.diffuse);
    m_program->setUniformValue("material.specular", _material.specular);
    m_program->setUniformValue("material.shininess", _material.shininess);
    //设定环境光
    m_program->setUniformValue("globalAmbient", m_global_ambient);
    // 绘制
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.count());
    m_program->release();
    m_vao.release();
    for (auto texture : m_textures)
    {
        texture->release();
    }
}
