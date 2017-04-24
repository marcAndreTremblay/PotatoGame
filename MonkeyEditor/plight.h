#ifndef PLIGHT_H
#define PLIGHT_H

#include <QVector4D>

class PLight
{
public:
    QVector4D position;
    QVector4D ambient;
    QVector4D diffuse;
    QVector4D specular;
    PLight();
};

#endif // PLIGHT_H
