#ifndef PSHADERPROGRAM_H_H
#define PSHADERPROGRAM_H_H

#include <QOpenGLFunctions_3_2_Core>

class PShaderProgram : protected QOpenGLFunctions_3_2_Core {
        protected:
                 GLuint ShaderID;
             GLuint CompileShaderScr(GLuint shaderId, const char * shader_scr) ;
        private:
            GLuint VertexShaderID;
            GLuint FragmentShaderID;
            GLuint GeometryShaderID;

        public:
            PShaderProgram(const char * vertex_src, const char * fragment_src);
            PShaderProgram(const char * vertex_src, const char * fragment_src, const char * geometry_src) ;
            ~PShaderProgram() ;
            void Use() ;
            virtual void Render();
        };

#define PG_SHADER(shader_text) static shader_text
#define GLSL330(src) "#version 330 core\n" #src
PG_SHADER(const char* model_vertex_shader = GLSL330(
    layout(location = 0) in vec4 vertex_position;
    layout(location = 1) in vec3 vertex_normal;
    layout(location = 2) in vec3 ambient;
    layout(location = 3) in vec3 diffuse;
    layout(location = 4) in vec3 specular;
    layout(location = 5) in vec4 shininess;

    struct PGMaterial {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float shininess;
    };

    uniform mat4 Translate;
    uniform mat4 Scale;

    out vec3 Normal;
    out vec3 FragPos;

    out PGMaterial Matl;



    layout(std140) uniform Renderer_UBO
    {
        mat4 WorldProjection;
        mat4 WorldView;
        mat4 GUIProjection;
        vec4 CenterOfFog;
    };


    void main() {
        Matl.ambient = ambient;
        Matl.diffuse = diffuse;
        Matl.specular = specular;
        Matl.shininess = shininess.x;
        //Note(Marc): this next line should be uptimise so 1 less call is made
        gl_Position = WorldProjection  * WorldView * (Translate* Scale) * vertex_position;
        FragPos = vec3(WorldView*(Translate * Scale) * vertex_position);
        Normal = mat3(transpose(inverse(WorldView *  Translate * Scale))) * vertex_normal;
    }
));

PG_SHADER(const char* Model_FragShader = GLSL330(
    struct PGMaterial {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        float shininess;
    };
    struct PGLight {
        vec4 position;
        vec4 ambient;
        vec4 diffuse;
        vec4 specular;
    };


    layout(std140) uniform Renderer_UBO
    {
        mat4 WorldProjection;
        mat4 WorldView;
        mat4 GUIProjection;
        vec4 CenterOfFog;
    };
    layout(std140) uniform SceneAdvanceLightData_UBO
    {
        PGLight Light;
    };

    in vec3 Normal;
    in vec3 FragPos;
    in PGMaterial Matl;

    out vec4 color;

    void main() {
        // Ambient
        vec3 ambient = vec3(Light.ambient) * Matl.ambient;

        // Diffuse
        vec3 LightPos = vec3(WorldView * Light.position);
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(LightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = vec3(Light.diffuse) * (diff * Matl.diffuse);

        vec3 viewDir = normalize(-FragPos); // The viewer is at(0, 0, 0) so viewDir is(0, 0, 0) - Position = > -Position
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), Matl.shininess);
        vec3 specular = vec3(Light.specular) * (spec * Matl.specular);

        //Combine each	colors
        color = vec4((ambient + diffuse + specular), 1.0f);

    }
));
    PG_SHADER(const char* line_vertex_shader = GLSL330(
        layout(location = 0) in vec4 vertex_position;
        layout(location = 1) in vec4 vertex_color;

        out vec4 FragColor;

        layout(std140) uniform Renderer_UBO
        {
            mat4 WorldProjection;
            mat4 WorldView;
            mat4 GUIProjection;
            vec4 CenterOfFog;
        };

        void main() {
            FragColor = vertex_color;
            gl_Position = WorldProjection  * WorldView * vertex_position;
        }
    ));
        PG_SHADER(const char* FragShaderColor4fIn = GLSL330(
            in vec4 FragColor;
            out vec4 color;

            void main() {
                color = FragColor;
            }
        ));
#endif // PSHADERPROGRAM_H
