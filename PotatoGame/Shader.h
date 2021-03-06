#if !defined(PG_SHADER_H)
#define PG_SHADER_H

#include "Core.h"

using namespace PG::Core;
namespace PG {
	namespace Engine {
		class PGShader {
		protected:
		private:
			GLuint VertexShaderID;
			GLuint FragmentShaderID;
			GLuint GeometryShaderID;
			GLuint CompileShaderScr(GLuint shaderId, const char * shader_scr) {
				GLint Result = GL_FALSE;
				int InfoLogLength;

				glShaderSource(shaderId, 1, &shader_scr, NULL);
				glCompileShader(shaderId);

				// Check  Shader status
				glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
				glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);

				if (Result == GL_FALSE && InfoLogLength > 0) {
					char *VertexShaderErrorMessage = (char *)malloc(InfoLogLength + 1);
					glGetShaderInfoLog(shaderId, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
					printf("Compiling Error : %s\n", &VertexShaderErrorMessage[0]);
					printf("While compiling shader : %s\n", shader_scr);
					free(VertexShaderErrorMessage);
				}

				return Result;
			}

		public:
			GLuint ShaderID;
			PGShader(const char * vertex_src, const char * fragment_src) {
				GLint Result = GL_FALSE;
				int InfoLogLength;

				this->VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
				this->FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
				this->GeometryShaderID = -1;

				Result = CompileShaderScr(VertexShaderID, vertex_src);
				Result = CompileShaderScr(FragmentShaderID, fragment_src);

				this->ShaderID = glCreateProgram();
				glAttachShader(this->ShaderID, VertexShaderID);
				glAttachShader(this->ShaderID, FragmentShaderID);

				glLinkProgram(this->ShaderID);

				glGetProgramiv(this->ShaderID, GL_LINK_STATUS, &Result);
				glGetProgramiv(this->ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
				if (Result == GL_FALSE && InfoLogLength > 0) {
					char*  ProgramErrorMessage = (char*)malloc(InfoLogLength);
					glGetProgramInfoLog(this->ShaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
					printf("%s\n", &ProgramErrorMessage[0]);
					free(ProgramErrorMessage);
				}


			}
			PGShader(const char * vertex_src, const char * fragment_src, const char * geometry_src) {
				GLint Result = GL_FALSE;
				int InfoLogLength;

				this->VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
				this->FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
				this->GeometryShaderID = glCreateShader(GL_GEOMETRY_SHADER);

				Result = CompileShaderScr(VertexShaderID, vertex_src);
				Result = CompileShaderScr(FragmentShaderID, fragment_src);
				Result = CompileShaderScr(GeometryShaderID, geometry_src);

				this->ShaderID = glCreateProgram();
				glAttachShader(this->ShaderID, VertexShaderID);
				glAttachShader(this->ShaderID, GeometryShaderID);
				glAttachShader(this->ShaderID, FragmentShaderID);

				glLinkProgram(this->ShaderID);

				glGetProgramiv(this->ShaderID, GL_LINK_STATUS, &Result);
				glGetProgramiv(this->ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
				if (InfoLogLength > 0) {
					char*  ProgramErrorMessage = (char*)malloc(InfoLogLength + 1);
					glGetProgramInfoLog(this->ShaderID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
					printf("%s\n", &ProgramErrorMessage[0]);
					free(ProgramErrorMessage);
				}


			}
			~PGShader() {
				glDeleteShader(this->VertexShaderID);
				glDeleteShader(this->GeometryShaderID);
				glDeleteShader(this->FragmentShaderID);
				glDeleteProgram(this->ShaderID);
			}
			void PGShader::Use() {
				glUseProgram(this->ShaderID);
			}
		};
	}
}
#endif