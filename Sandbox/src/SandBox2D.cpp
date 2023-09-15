#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	Hazel::Renderer2D::Init();
	m_Textureslots.push_back(Hazel::Texture2D::Create("assets/textures/dog.jpg"));
}

void Sandbox2D::OnDetach()
{
	Hazel::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Hazel::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.6f, 1 });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, {0.2f, 0.3f, 0.8f, 1.0f});
	Hazel::Renderer2D::DrawQuad({ 1.0f, 0.0f }, { 1.5f, 1.5f }, m_Textureslots[0]);
	Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 3.0f, 3.0f }, m_Textureslots[0], {0.6f, 0.1f, 0.2f, 1.0f});
	Hazel::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}