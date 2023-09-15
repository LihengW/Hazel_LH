#include "hzpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>


namespace Hazel {

	struct Renderer2DStorage
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> QuadShader;
		Ref<Texture2D> WhiteTex;
	};

	static Renderer2DStorage* s_Data;

	void Renderer2D::Init()
	{
		s_Data = new Renderer2DStorage();
		s_Data->QuadVertexArray = VertexArray::Create();

		float QuadVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};

		Ref<VertexBuffer> QuadVB = Ref<VertexBuffer>(VertexBuffer::Create(QuadVertices, sizeof(QuadVertices)));
		QuadVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord"}
			});
		s_Data->QuadVertexArray->AddVertexBuffer(QuadVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB = Ref<IndexBuffer>(IndexBuffer::Create(squareIndices, sizeof(squareIndices)));
		s_Data->QuadVertexArray->SetIndexBuffer(squareIB);

		s_Data->QuadShader = Shader::Create("assets/shaders/Texture.glsl");

		s_Data->QuadShader->Bind();
		s_Data->QuadShader->SetInt("u_Texture", 0);  // bind to slot 0;


		float whitepixel[4]{ 1.0f, 1.0f, 1.0f, 1.0f };
		s_Data->WhiteTex = Texture2D::Create(1, 1);
		s_Data->WhiteTex->SetData(whitepixel, sizeof(whitepixel));
	}

	void Renderer2D::Shutdown()
	{
		delete s_Data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data->QuadShader->Bind();
		s_Data->QuadShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Data->QuadShader->SetMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data->QuadShader->Bind();
		s_Data->QuadShader->SetFloat4("u_Color", color);
		s_Data->QuadVertexArray->Bind();
		s_Data->WhiteTex->Bind(0);
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& tex, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, tex, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& tex, const glm::vec4& color)
	{
		s_Data->QuadShader->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data->QuadShader->SetMat4("u_Transform", transform);
		s_Data->QuadShader->SetFloat4("u_Color", color);
		
		tex->Bind(0); // texture to slot 0;
		s_Data->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->QuadVertexArray);

	}
}
