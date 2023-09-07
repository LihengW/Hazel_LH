#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>


Hazel::OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	HZ_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void Hazel::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	HZ_CORE_ASSERT(status, "Failed to initialize Glad!");

	HZ_CORE_TRACE("OpenGL Info:");
	HZ_CORE_TRACE("  Vendor: {0}", (const void*)glGetString(GL_VENDOR));
	HZ_CORE_TRACE("  Renderer: {0}", (const void*)glGetString(GL_RENDERER));
	HZ_CORE_TRACE("  Version: {0}", (const void*)glGetString(GL_VERSION));

#ifdef HZ_ENABLE_ASSERTS
	int versionMajor;
	int versionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

	HZ_CORE_INFO("OpenGL Version:" + std::to_string(versionMajor) + "." + std::to_string(versionMinor));
	
#endif
}

void Hazel::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}
