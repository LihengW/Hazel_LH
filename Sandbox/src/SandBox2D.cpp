#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include <chrono>

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		: m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}

	void Stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		m_Stopped = true;

		float duration = (end - start) * 0.001f;
		m_Func({ m_Name, duration });
	}
private:
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};

#define PROFILE_SCOPE(name) Timer timer##__LINE__(name, [&](ProfileResult profileResult) { m_ProfileResults.push_back(profileResult); })


Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
	//m_PerspectiveCamera = Swirl::CreateRef<Swirl::PerspectiveCamera>(glm::radians(60.0f), 1280.0f / 720.0f, 0.5f, 50.0f);
	//m_PerspectiveCamera->SetPosition({ -2.0f, 0.0f, 0.0f });
}

void Sandbox2D::OnAttach()
{
	Swirl::Renderer2D::Init();
	m_Textureslots.push_back(Swirl::Texture2D::Create("assets/textures/dog.jpg"));
}

void Sandbox2D::OnDetach()
{
	Swirl::Renderer2D::Shutdown();
}

void Sandbox2D::OnUpdate(Swirl::Timestep ts)
{
	PROFILE_SCOPE("Sandbox2D::OnUpdate");
	
	// Update
	{
		PROFILE_SCOPE("CameraController::OnUpdate");
		m_CameraController.OnUpdate(ts);
	}

	// Render
	{
		PROFILE_SCOPE("RenderCommand::Perparation");
		Swirl::RenderCommand::SetClearColor({ 0.2f, 0.3f, 0.3f, 1 });
		Swirl::RenderCommand::Clear();
	}

	{
		PROFILE_SCOPE("Render2D::Render");
		{
			PROFILE_SCOPE("Render2D::BeginScene");
			Swirl::Renderer2D::BeginScene(m_CameraController.GetCamera());
		}
		{
			PROFILE_SCOPE("Render2D::SmallQuad");
			Swirl::Renderer2D::DrawQuad({ 0.0f, 0.0f, 0.3f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
		}
		{
			PROFILE_SCOPE("Render2D::MidQuad");
			Swirl::Renderer2D::DrawQuad({ 1.0f, 0.0f, 0.0f }, { 1.5f, 1.5f }, m_Textureslots[0]);
		}
		{
			PROFILE_SCOPE("Render2D::LargeQuad");
			Swirl::Renderer2D::DrawQuad({ -1.0f, 0.0f, 0.0f }, { 3.0f, 3.0f }, m_Textureslots[0], { 0.6f, 0.1f, 0.2f, 1.0f });
		}
		{
			PROFILE_SCOPE("Render2D::EndScene");
			Swirl::Renderer2D::EndScene();
		}
	}

}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	for (auto& result : m_ProfileResults)
	{
		char label[50];
		strcpy_s(label, "%.3fms ");
		strcat_s(label, result.Name);
		ImGui::Text(label, result.Time);
	}
	m_ProfileResults.clear();
	ImGui::End();
}

void Sandbox2D::OnEvent(Swirl::Event& e)
{
	m_CameraController.OnEvent(e);
}