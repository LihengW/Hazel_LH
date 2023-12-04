#include "Swirl.h"
#include "Swirl/Core/EntryPoint.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui/imgui.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Sandbox2D.h"

class ExampleLayer : public Swirl::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{

		// First Buffer ( Triangle )
		m_VertexArray = Swirl::VertexArray::Create();

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Swirl::Ref<Swirl::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Swirl::VertexBuffer::Create(vertices, sizeof(vertices)));
		Swirl::BufferLayout layout = {
			{ Swirl::ShaderDataType::Float3, "a_Position" },
			{ Swirl::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Swirl::Ref<Swirl::IndexBuffer> indexBuffer;
		indexBuffer.reset(Swirl::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Second Buffer (Square)
		m_SquareVA = Swirl::VertexArray::Create();
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Swirl::Ref<Swirl::VertexBuffer> squareBuffer;
		squareBuffer.reset(Swirl::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		Swirl::BufferLayout squareLayout = {
			{ Swirl::ShaderDataType::Float3, "a_Position" },
			{ Swirl::ShaderDataType::Float2, "a_TexCoord" }
		};
		squareBuffer->SetLayout(squareLayout);
		m_SquareVA->AddVertexBuffer(squareBuffer);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Swirl::Ref<Swirl::IndexBuffer> squareIB;
		squareIB.reset(Swirl::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// Triangle Shader
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = v_Color;
			}
		)";

		m_Shader = Swirl::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		// Square Shader
		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader = Swirl::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLib.Load("assets/shaders/Texture.glsl");

		m_Texture = Swirl::Texture2D::Create("assets/textures/dog.jpg");
		m_ChernoLogoTexture = Swirl::Texture2D::Create("assets/textures/ChernoLogo.png");

		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);

	}

	void OnUpdate(Swirl::Timestep ts) override
	{
		m_CameraController.OnUpdate(ts);

		Swirl::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Swirl::RenderCommand::Clear();

		Swirl::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));
		m_FlatColorShader->Bind();

		for (int y = -10; y < 10; y++)
		{
			for (int x = -10; x < 10; x++)
			{
				glm::vec3 pos(x * 0.06f, y * 0.06f, 0.0f);
				m_FlatColorShader->SetFloat3("u_Color", pos);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Swirl::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		Swirl::Renderer::Submit(m_Shader, m_VertexArray);

		auto textureShader = m_ShaderLib.Get("Texture");

		m_Texture->Bind();
		Swirl::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

		m_ChernoLogoTexture->Bind();
		Swirl::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

		Swirl::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Swirl::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}

private:
	Swirl::Ref<Swirl::Shader> m_Shader;
	Swirl::Ref<Swirl::VertexArray> m_VertexArray;

	Swirl::Ref<Swirl::Shader> m_FlatColorShader;
	Swirl::Ref<Swirl::VertexArray> m_SquareVA;

	Swirl::Ref<Swirl::Texture2D> m_Texture, m_ChernoLogoTexture;
	Swirl::Ref<Swirl::Shader> m_TextureShader;

	Swirl::ShaderLib m_ShaderLib;


	Swirl::OrthographicCameraController m_CameraController;
	glm::vec3 m_CameraPosition = glm::vec3();
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public Swirl::Application
{
public:
	Sandbox() 
	{ 
		PushLayer(new Sandbox2D());
		PushOverlay(new Swirl::ImGuiLayer());
	};
	~Sandbox() {};

private:
	int id = 0;

};

Swirl::Application* Swirl::CreateApplication()
{
	return new Sandbox();
}