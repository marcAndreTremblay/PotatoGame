	#if !defined(PG_GAME_WINDOW_H)
#define PG_GAME_WINDOW_H

#include "stdafx.h"

static void glfw_error_callback(int error, const char* description) {
	fprintf(stderr, description);
}

namespace PGEngine {
	class PGGameWindow {
	protected:
	private:
		int WindowWidth;
		int WindowHeight;
		m4 ortho;
	public:
		GLFWwindow* Gl_Window;
		GLFWmonitor *GL_Monitor;
		PGGameWindow(bool _IsFullScreen = true, int _WindowWidth = 0, int _WindowHeight = 0) {
			if (glfwInit() != GL_FALSE) {
				glfwSetErrorCallback(glfw_error_callback);

				glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
				glfwWindowHint(GLFW_SAMPLES, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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
					this->Gl_Window = glfwCreateWindow(this->WindowWidth, this->WindowHeight, "Potato", glfwGetPrimaryMonitor(), NULL); //Full screen
				}
				else {
					this->WindowWidth = _WindowWidth;
					this->WindowHeight = _WindowHeight;
					this->Gl_Window = glfwCreateWindow(this->WindowWidth, this->WindowHeight, "Potato", NULL, NULL);
					glfwSetWindowPos(this->Gl_Window, (mode->width / 2) - (this->WindowWidth / 2), (mode->height / 2) - (this->WindowHeight / 2));
				}
				if (this->Gl_Window != GL_FALSE) {
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
		~PGGameWindow() {
			glfwTerminate();
		}
		m4* PGGameWindow::GetOrtho() {
			return &ortho;
		}
		int PGGameWindow::GetHeight() {
			return this->WindowHeight;
		}
		int PGGameWindow::GetWidth() {
			return this->WindowWidth;
		}
		void PGGameWindow::SetWindowSize(int width, int height) {
			this->WindowWidth = width;
			this->WindowHeight = height;
			const GLFWvidmode* mode = glfwGetVideoMode(this->GL_Monitor);
			
			glViewport(0, 0, this->WindowWidth, this->WindowHeight);
			glfwSetWindowSize(this->Gl_Window, this->WindowWidth, this->WindowHeight);
			glfwSetWindowPos(this->Gl_Window, (mode->width / 2) - (this->WindowWidth / 2), (mode->height / 2) - (this->WindowHeight / 2));
			ortho = glm::ortho<r32>(0.0f, static_cast<r32>(this->WindowWidth), static_cast<r32>(this->WindowHeight), 0.0f, -1.0f, 1.0f);
		}
	};
}
#endif