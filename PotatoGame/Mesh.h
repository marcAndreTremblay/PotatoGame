#if !defined(PG_MESH_H)
#define PG_MESH_H


#include "stdafx.h"

#include "Core.h"
#include "List.h"
#include "String.h"
#include "BuildableObject.h"
#include "Shader.h"

namespace PG {
	namespace Engine {
		class Mesh : public BuildableObject {
		protected:
			PGShader* Shader;
			GLuint VAO;
			GLuint VBO;
		private:
		public:
			Mesh(PGShader* shader)
				:BuildableObject() {
				this->Shader = shader;
				glGenVertexArrays(1, &this->VAO);
				glGenBuffers(1, &this->VBO);
			}
			~Mesh() {
				delete(this->Shader);
				glDeleteVertexArrays(1, &this->VAO);
				glDeleteBuffers(1, &this->VBO);
			}
			void Mesh::Build() override = 0;
			void Mesh::Render();
		};
	}

}
#endif