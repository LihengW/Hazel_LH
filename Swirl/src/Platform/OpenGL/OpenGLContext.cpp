#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>


Swirl::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	SW_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void Swirl::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	SW_CORE_ASSERT(status, "Failed to initialize Glad!");

	SW_CORE_TRACE("OpenGL Info:");
	SW_CORE_TRACE("  Vendor: {0}", (const void*)glGetString(GL_VENDOR));
	SW_CORE_TRACE("  Renderer: {0}", (const void*)glGetString(GL_RENDERER));
	SW_CORE_TRACE("  Version: {0}", (const void*)glGetString(GL_VERSION));

#ifdef HZ_ENABLE_ASSERTS
	int versionMajor;
	int versionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

	SW_CORE_INFO("OpenGL Version:" + std::to_string(versionMajor) + "." + std::to_string(versionMinor));
	
#endif
}

void Swirl::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
