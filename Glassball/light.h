#pragma once

#include <QObject>
#include <QVector3D>
#include <QVector4D>
#include <QColor>

class Light : public QObject
{
	Q_OBJECT

public:
	Light();
	~Light();
public:
	void setPos(const QVector3D &pos) { m_pos = pos; }
	QVector3D pos() { return m_pos; }

	void setColor(const QColor &color)  { m_color = color; }
	QColor color() { return m_color; }

    void setAmbient(const QVector4D & ambient)  {m_ambient = ambient;}
    QVector4D ambient() {return m_ambient;}

    void setDiffuse(const QVector4D & diffuse)  {m_diffuse = diffuse;}
    QVector4D diffuse() {return m_diffuse;}

    void setSpecular(const QVector4D & specular)  {m_specular = specular;}
    QVector4D specular() {return m_specular;}
protected:
	QVector3D m_pos{ 0,0,0 };
	QColor m_color;
    QVector4D m_ambient{1, 1, 1, 1};
    QVector4D m_diffuse{1, 1, 1, 1};
    QVector4D m_specular{1, 1, 1, 1};
};
