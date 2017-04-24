#ifndef CUSTUMOPENGLWIDGET_H
#define CUSTUMOPENGLWIDGET_H

#include "pmodelshaderprogram.h"
#include "plight.h"
#include "pcamera.h"
#include "plinevao.h"
#include "pmodelvao.h"
#include "plineshaderprogram.h"

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLTexture>
#include <QOpenGLFunctions_3_2_Core>
#include <QMatrix4x4>
#include <QMatrix3x3>
#include <QVector4D>
#include <QVector3D>

class CustumOpenGlWidget :
        public QOpenGLWidget ,
        protected QOpenGLFunctions_3_2_Core
{
    Q_OBJECT
private:

             PLineVAO * line_mesh;
            //Renderer
            PModelShaderProgram* model_shader;
            PLineShaderProgram* line_shader;
            PLight the_one_light;
            PCamera* camera;
            QMatrix4x4 projection_m;
             QMatrix4x4 ortho_m;
            //Renderer info
            GLuint Renderer_UBO_Ref_Id; //ubo binding point 1
            GLuint SceneAdvanceLight_UBO_Ref_Id; //ubo binding point 3

             void SetWorldView(QMatrix4x4* matrix);
             void SetWorldProjection(QMatrix4x4* matrix);
             void SetUIProjection(QMatrix4x4* matrix);
             void PushLightData(PLight * light);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
public:

    explicit CustumOpenGlWidget(QWidget *parent = 0);
    ~CustumOpenGlWidget();

signals:

public slots:
};



#endif // CUSTUMOPENGLWIDGET_H
