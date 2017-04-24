#include "pcamera.h"

PCamera::PCamera()
{
    view_m = QMatrix4x4();
}
PCamera::~PCamera()
{

}
QMatrix4x4* PCamera::GetViewMatrice(){
    view_m.lookAt(Possition,LookAt,Up);
    return &view_m;
}
