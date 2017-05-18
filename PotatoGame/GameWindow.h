	#if !defined(PG_GAME_WINDOW_H)
#define PG_GAME_WINDOW_H

#include "Core.h"
using namespace PG::Core;



namespace PG {
	namespace Engine {
		class GameWindow {
		protected:
		private:
			int WindowWidth;
			int WindowHeight;
			m4 ortho;
		public:
			GLFWwindow* Gl_Window;
			GLFWmonitor *GL_Monitor;
			GameWindow(bool _IsFullScreen = true, int _WindowWidth = 0, int _WindowHeight = 0) {
				if (glfwInit() != GL_FALSE) {
					

					
					glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
					glfwWindowHint(GLFW_SAMPLES,4); //Target 9 or 16?
					glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
					glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
					glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


					this->GL_Monitor = glfwGetPrimaryMonitor();
					const GLFWvidmode* mode = glfwGetVideoMode(this->GL_Monitor);

					glfwWindowHint(GLFW_RED_BITS, mode->redBits);
					glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
					glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
					glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
					
					if (_IsFullScreen == true) {
						this->WindowWidth = mode->width;
						this->WindowHeight = mode->height;
						this->Gl_Window = glfwCreateWindow(this->WindowWidth, this->WindowHeight, "Potato", this->GL_Monitor, NULL); //Full screen
					}
					else {
						this->WindowWidth = _WindowWidth;
						this->WindowHeight = _WindowHeight;
						this->Gl_Window = glfwCreateWindow(this->WindowWidth, this->WindowHeight, "Potato", NULL, NULL);
						glfwSetWindowPos(this->Gl_Window, (mode->width / 2) - (this->WindowWidth / 2), (mode->height / 2) - (this->WindowHeight / 2));
					}
					if (this->Gl_Window != GL_FALSE) {
						glfwSetWindowUserPointer(Gl_Window, (void*)this);
						
						glfwMakeContextCurrent(this->Gl_Window);
						glfwSetInputMode(this->Gl_Window, GLFW_STICKY_KEYS, GL_TRUE);
						glfwSetCursorPos(this->Gl_Window, this->WindowWidth / 2, this->WindowHeight / 2);
						glViewport(0, 0, this->WindowWidth, this->WindowHeight);
					}
					ortho = glm::ortho<r32>(0.0f, static_cast<r32>(WindowWidth), static_cast<r32>(WindowHeight), 0.0f, -1.0f, 1.0f);
				}
				else {
					//Todo(Marc): debugg.... 
				}
			}
			~GameWindow() {
				glfwTerminate();
			}
			m4* GameWindow::GetOrtho() {
				return &ortho;
			}
			int GameWindow::GetHeight() {
				return this->WindowHeight;
			}
			int GameWindow::GetWidth() {
				return this->WindowWidth;
			}
			void GameWindow::SetWindowPossition() {
				//Center
				//	const GLFWvidmode* mode = glfwGetVideoMode(this->GL_Monitor);
				//	glfwSetWindowPos(this->Gl_Window, (mode->width / 2) - (this->WindowWidth / 2), (mode->height / 2) - (this->WindowHeight / 2));
			}
			void GameWindow::SetWindowSize(int width, int height) {
				this->WindowWidth = width;
				this->WindowHeight = height;
				glViewport(0, 0, this->WindowWidth, this->WindowHeight);
				glfwSetWindowSize(this->Gl_Window, this->WindowWidth, this->WindowHeight);			
				ortho = glm::ortho<r32>(0.0f, static_cast<r32>(this->WindowWidth), static_cast<r32>(this->WindowHeight), 0.0f, -1.0f, 1.0f);
			}
		};
	}
}
#endif