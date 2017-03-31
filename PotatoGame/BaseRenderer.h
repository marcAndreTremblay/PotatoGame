#if !defined(PG_GAME_RENDERER_H)	
#define PG_GAME_RENDERER_H

#include "stdafx.h"

#include "Core.h"

#include "List.h"
#include "String.h"
#include "Mesh.h"
#include "PGMeshInstance.h"
#include "TextMesh.h"

#include "AxisMesh.h"

namespace PG {
	namespace Engine {


		class BaseRenderer {
		protected:
			GLuint Renderer_UBO_Ref_Id; //ubo binding point 1
			GLuint SceneLight_UBO_Ref_Id; //ubo binding point 2  //Todo(Marc): Remove thi from renderer
			GLuint SceneAdvanceLight_UBO_Ref_Id; //ubo binding point 3
		private:
			PGTextMesh *textMesh;
		public:
			PGSolidHexagoneMesh * hexagoneMesh;
			PGSquareMesh * squareMesh;
			PGCubeMesh * cubeMesh;
			AxisMesh * axisMesh;
			PGLightedCubeMesh * lightedCubeMesh;
			PGLightedHexagoneMesh *lightedHexagoneMesh;
			PGMaterielHexagoneMesh *materialHexagoneMesh;
			PGUIPanelMesh* ui_panel_Mesh;
			PGUIImageMesh* ui_image_mesh;
			PGMModelMesh* model_renderer;



			BaseRenderer() {
				glewExperimental = true; // Needed for core profile
				if (glewInit() == GLEW_OK) // Initialize GLEW
				{
					glClearColor(0.0f, 0.0f, 0.0f, 1.f);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glDepthFunc(GL_LESS);
					glEnable(GL_CULL_FACE);
					glCullFace(GL_BACK);
					glEnable(GL_BLEND);
					glEnable(GL_DEPTH_TEST);
					glEnable(GL_MULTISAMPLE);
					//glEnable(GL_PROGRAM_POINT_SIZE);
					int max_attribs;
					glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &max_attribs);

				}
				else {
					/*Todo(Marc): Add debug*/
					return;
				}
				this->Build();//todo(marc): make this be call from elsewhere
			}
			~BaseRenderer() {

				glDeleteBuffers(1, &this->Renderer_UBO_Ref_Id);
				glDeleteBuffers(1, &this->SceneLight_UBO_Ref_Id);
				glDeleteBuffers(1, &this->SceneAdvanceLight_UBO_Ref_Id);

				delete(this->textMesh);
				delete(this->squareMesh);
				delete(this->hexagoneMesh);
				delete(this->cubeMesh);
				delete(this->axisMesh);
				delete(this->lightedCubeMesh);
				delete(this->lightedHexagoneMesh);
				delete(this->materialHexagoneMesh);
				delete(this->ui_panel_Mesh);
				delete(this->ui_image_mesh);
			}
			void BaseRenderer::SetWorldView(m4 *_matrix) {
				glBindBuffer(GL_UNIFORM_BUFFER, this->Renderer_UBO_Ref_Id);
				glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), _matrix);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}
			void BaseRenderer::SetWorldProjection(m4 *_matrix) {
				glBindBuffer(GL_UNIFORM_BUFFER, this->Renderer_UBO_Ref_Id);
				glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), _matrix);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}
			void BaseRenderer::SetUIProjection(m4 *_matrix) {
				glBindBuffer(GL_UNIFORM_BUFFER, this->Renderer_UBO_Ref_Id);
				glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::mat4), _matrix);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}


			void BaseRenderer::PushLightPossition(v4 *_vector) {
				glBindBuffer(GL_UNIFORM_BUFFER, this->SceneLight_UBO_Ref_Id);
				glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(v4), _vector);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}
			void BaseRenderer::PushLightColor(v3 *_color_vector) {
				glBindBuffer(GL_UNIFORM_BUFFER, this->SceneLight_UBO_Ref_Id);
				glBufferSubData(GL_UNIFORM_BUFFER, sizeof(v4), sizeof(v3), _color_vector);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}

			void BaseRenderer::PushLightData(PGLight* _light) {
				glBindBuffer(GL_UNIFORM_BUFFER, this->SceneAdvanceLight_UBO_Ref_Id);
				glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(PGLight), _light);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}

			virtual void BaseRenderer::Build() {
				//Gen the UBO Buffer and get ID
				glGenBuffers(1, &this->Renderer_UBO_Ref_Id);
				glGenBuffers(1, &this->SceneLight_UBO_Ref_Id);
				glGenBuffers(1, &this->SceneAdvanceLight_UBO_Ref_Id);


				glBindBuffer(GL_UNIFORM_BUFFER, this->Renderer_UBO_Ref_Id);
				glBufferData(GL_UNIFORM_BUFFER, 3 * sizeof(m4) + sizeof(v3), NULL, GL_DYNAMIC_DRAW); // allocate bytes of memory
				glBindBufferBase(GL_UNIFORM_BUFFER, 1, this->Renderer_UBO_Ref_Id);

					glBindBuffer(GL_UNIFORM_BUFFER, this->Renderer_UBO_Ref_Id);
					glBufferSubData(GL_UNIFORM_BUFFER, 3 * sizeof(glm::mat4), sizeof(v4), &v4(0.f, 0.f, 0.f, 10.f));
					glBindBuffer(GL_UNIFORM_BUFFER, 0);


				glBindBuffer(GL_UNIFORM_BUFFER, this->SceneLight_UBO_Ref_Id);
				glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW); // allocate bytes of memory
				glBindBufferBase(GL_UNIFORM_BUFFER, 2, this->SceneLight_UBO_Ref_Id);


				glBindBuffer(GL_UNIFORM_BUFFER, this->SceneAdvanceLight_UBO_Ref_Id);
				glBufferData(GL_UNIFORM_BUFFER, 4 * sizeof(glm::vec4), NULL, GL_DYNAMIC_DRAW); // allocate bytes of memory
				glBindBufferBase(GL_UNIFORM_BUFFER, 3, this->SceneAdvanceLight_UBO_Ref_Id);
				model_renderer = new PGMModelMesh();
				model_renderer->Build();
				this->ui_image_mesh = new PGUIImageMesh();
				this->ui_image_mesh->Build();

				this->lightedHexagoneMesh = new PGLightedHexagoneMesh();
				this->lightedHexagoneMesh->Build();

				this->hexagoneMesh = new PGSolidHexagoneMesh();
				this->hexagoneMesh->Build();

				this->materialHexagoneMesh = new PGMaterielHexagoneMesh();
				this->materialHexagoneMesh->Build();

				this->squareMesh = new PGSquareMesh();
				this->squareMesh->Build();

				this->cubeMesh = new PGCubeMesh();
				this->cubeMesh->Build();

				this->axisMesh = new AxisMesh();
				this->axisMesh->Build();

				this->lightedCubeMesh = new PGLightedCubeMesh();
				this->lightedCubeMesh->Build();

				this->textMesh = new PGTextMesh();
				this->textMesh->Build();

				this->ui_panel_Mesh = new PGUIPanelMesh();
				this->ui_panel_Mesh->Build();

			}



			//Note(Marc): Move all mes as private a
			void BaseRenderer::RenderUIText(char *text_string, v3 possition, v4 color, r32 scale, Font *font) {
				this->textMesh->Render(text_string, possition, color, scale, font);
			}

		};
	}
}
#endif		