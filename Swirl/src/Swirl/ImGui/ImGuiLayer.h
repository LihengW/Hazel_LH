#pragma once
#include "Swirl/Core/Layer.h"

#include "Swirl/Events/ApplicationEvent.h"
#include "Swirl/Events/KeyEvent.h"
#include "Swirl/Events/MouseEvent.h"

namespace Swirl {
	class HAZEL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}