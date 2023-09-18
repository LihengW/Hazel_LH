#pragma once

#include "Hazel.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

class Sandbox2D : public Hazel::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Hazel::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Hazel::Event& e) override;

private:
	Hazel::OrthographicCameraController m_CameraController;
	//Hazel::Ref<Hazel::PerspectiveCamera> m_PerspectiveCamera;

	//Temp
	Hazel::Ref<Hazel::VertexArray> m_SquareVA;
	std::vector<Hazel::Ref<Hazel::Texture2D>> m_Textureslots;

	// profilling part
	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
};

