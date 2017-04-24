#ifndef PMODELSHADERPROGRAM_H
#define PMODELSHADERPROGRAM_H

#include "pshaderprogram.h"
#include "pmodelvao.h"

#include <QVector3D>
#include <QMatrix4x4>

class PModelShaderProgram : protected PShaderProgram {
        protected:
        private:
            GLuint Unif_Translate;
            GLuint Unif_Scale;
        public:
            PModelShaderProgram();
            ~PModelShaderProgram() ;
             void Render(QVector3D possition, QVector3D size);
        };

#endif // PMODELSHADERPROGRAM_H
