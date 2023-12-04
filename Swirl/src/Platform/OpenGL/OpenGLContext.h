#pragma once
#include "Swirl/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Swirl {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	
	private:
		GLFWwindow* m_WindowHandle;
	};
}