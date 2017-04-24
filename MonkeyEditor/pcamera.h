#ifndef PCAMERA_H
#define PCAMERA_H

#include <QMatrix4x4>
#include <QVector3D>
class PCamera
{
private:
    QMatrix4x4 view_m;
public:
    QVector3D Possition;
    QVector3D LookAt;
    QVector3D Up;

    PCamera();
    ~PCamera();
    QMatrix4x4* GetViewMatrice();
};

#endif // PCAMERA_H
