#pragma once

#include "Swirl.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

class Sandbox2D : public Swirl::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Swirl::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Swirl::Event& e) override;

private:
	Swirl::OrthographicCameraController m_CameraController;
	//Swirl::Ref<Swirl::PerspectiveCamera> m_PerspectiveCamera;

	//Temp
	Swirl::Ref<Swirl::VertexArray> m_SquareVA;
	std::vector<Swirl::Ref<Swirl::Texture2D>> m_Textureslots;

	// profilling part
	struct ProfileResult
	{
		const char* Name;
		float Time;
	};

	std::vector<ProfileResult> m_ProfileResults;
};

