        #include "custumopenglwidget.h"

    CustumOpenGlWidget::CustumOpenGlWidget(QWidget *parent) :
        QOpenGLWidget(parent,Qt::Widget)
    {
        //Note(Marc): Make sure we do the right thing here
        QSurfaceFormat format;
            format.setRenderableType(QSurfaceFormat::OpenGL);
            format.setDepthBufferSize(24);
            format.setStencilBufferSize(8);
            format.setVersion(3,3);

            format.setProfile(QSurfaceFormat::CoreProfile);
        makeCurrent();
        setFormat(format);




        camera = new PCamera();
        projection_m = QMatrix4x4();
        ortho_m =  QMatrix4x4();
    }
    CustumOpenGlWidget::~CustumOpenGlWidget(){
        makeCurrent();
        glDeleteBuffers(1,&Renderer_UBO_Ref_Id);
        glDeleteBuffers(1,&SceneAdvanceLight_UBO_Ref_Id);

        delete model_shader;
        delete line_mesh;
    }

    void CustumOpenGlWidget::initializeGL()
    {
        this->makeCurrent();
        this->initializeOpenGLFunctions();


        camera->Possition = QVector3D(-15.f, -15.f, 15.f);
        camera->LookAt = QVector3D(0.f, 0.f, 0.f);
        camera->Up = QVector3D(0.f, 0.f, 1.f);


        projection_m.perspective(45.0f, 4.0f / 3.0f, 0.1f, 150.0f);


        this->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        this->glDepthFunc(GL_LESS);
        this->glEnable(GL_CULL_FACE);
        this->glCullFace(GL_BACK);
        this->glEnable(GL_BLEND);
        this->glEnable(GL_DEPTH_TEST);
        this->glEnable(GL_MULTISAMPLE);


                        //Create some buffer for UBO
                        this->makeCurrent();
                        glGenBuffers(1, &this->Renderer_UBO_Ref_Id);
                        glGenBuffers(1, &this->SceneAdvanceLight_UBO_Ref_Id);



                         this->makeCurrent();
                        glBindBuffer(GL_UNIFORM_BUFFER, this->Renderer_UBO_Ref_Id);
                            glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(QMatrix4x4) + sizeof(QVector4D), NULL, GL_DYNAMIC_DRAW); // allocate bytes of memory
                            glBindBufferBase(GL_UNIFORM_BUFFER, 1, this->Renderer_UBO_Ref_Id);
                            //Set data
                            glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(QMatrix4x4), sizeof(QVector4D), &QVector4D(0.f, 0.f, 0.f, 10.f));
                        glBindBuffer(GL_UNIFORM_BUFFER, 0);

                        glBindBuffer(GL_UNIFORM_BUFFER, this->SceneAdvanceLight_UBO_Ref_Id);
                            glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(QVector4D), NULL, GL_DYNAMIC_DRAW); // allocate bytes of memory
                            glBindBufferBase(GL_UNIFORM_BUFFER, 3, this->SceneAdvanceLight_UBO_Ref_Id);
                        glBindBuffer(GL_UNIFORM_BUFFER, 0);


                        this->the_one_light.position = QVector4D(15.f, 15.f, 14.f, 1.f);

                        this->the_one_light.diffuse = QVector4D(1.f, 1.f, 1.f, 1.f);
                        this->the_one_light.ambient = QVector4D(0.6f, 0.6f, 0.6f, 1.f);
                        this->the_one_light.specular = QVector4D(0.6f, 0.6f, 0.6f, 1.f);

                        this->PushLightData(&the_one_light);

                        model_shader = new PModelShaderProgram();

                         line_shader = new PLineShaderProgram();
                        line_mesh = new PLineVAO();
                        line_mesh->BuildVAO();


                        bool result = this->glGetError();
                        if(result == true){
                            this->glClearColor(0.3f,0.3f, 0.3f, 1.f);

                        }else{
                           this->glClearColor(1.0f, 0.1f, 1.0f, 1.f);
                        }
    }

    void CustumOpenGlWidget::resizeGL(int w, int h)
    {
        SetWorldView(this->camera->GetViewMatrice());
        projection_m.perspective(45.0f, 4.0f / 3.0f, 0.1f, 150.0f);
        SetWorldProjection(&projection_m);
        ortho_m.ortho(0.0f,w,h,0,-1.0f,1.0f);
        SetUIProjection(&ortho_m);    
    }

    void CustumOpenGlWidget::paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        SetWorldView(this->camera->GetViewMatrice());
        PushLightData(&the_one_light);

        line_shader->Render(line_mesh);



        bool result = this->glGetError();
        if(result == true){
            this->glClearColor(0.3f,0.3f, 0.3f, 1.f);

        }else{
           this->glClearColor(1.0f, 0.1f, 1.0f, 1.f);
        }

    }
    void CustumOpenGlWidget::SetWorldView(QMatrix4x4 *_matrix) {
        glBindBuffer(GL_UNIFORM_BUFFER, this->Renderer_UBO_Ref_Id);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(QMatrix4x4), sizeof(QMatrix4x4), _matrix);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    void CustumOpenGlWidget::SetWorldProjection(QMatrix4x4 *_matrix) {
        glBindBuffer(GL_UNIFORM_BUFFER, this->Renderer_UBO_Ref_Id);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(QMatrix4x4), _matrix);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
    void CustumOpenGlWidget::SetUIProjection(QMatrix4x4 *_matrix) {
        glBindBuffer(GL_UNIFORM_BUFFER, this->Renderer_UBO_Ref_Id);
        glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(QMatrix4x4), sizeof(QMatrix4x4), _matrix);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }


    void CustumOpenGlWidget::PushLightData(PLight* _light) {
        glBindBuffer(GL_UNIFORM_BUFFER, this->SceneAdvanceLight_UBO_Ref_Id);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(PLight), _light);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
