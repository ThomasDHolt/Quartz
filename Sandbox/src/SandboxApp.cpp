#include "qtpch.h"
#include <Quartz.h>

#include "imgui/imgui.h"

class ExampleLayer : public Quartz::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f, 0.0f, 0.0f)
	{
		m_VertexArray.reset(Quartz::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Quartz::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Quartz::VertexBuffer::Create(vertices, sizeof(vertices)));

		Quartz::BufferLayout layout =
		{
			{ Quartz::ShaderDataType::Float3, "a_Position" },
			{ Quartz::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		std::shared_ptr<Quartz::IndexBuffer> indexBuffer;
		indexBuffer.reset(Quartz::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Quartz::VertexArray::Create());

		float squareVertices[4 * 3] =
		{
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<Quartz::VertexBuffer> squareVB;
		squareVB.reset(Quartz::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Quartz::BufferLayout squareVBLayout =
		{
			{ Quartz::ShaderDataType::Float3, "a_Position" }
		};

		squareVB->SetLayout(squareVBLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<Quartz::IndexBuffer> squareIB;
		squareIB.reset(Quartz::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Quartz::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Quartz::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Quartz::Timestep pTimestep) override
	{
		if (Quartz::Input::IsKeyPressed(QT_KEY_UP))
			m_CameraPosition.y -= m_CameraMoveSpeed * pTimestep.GetSeconds();
		if (Quartz::Input::IsKeyPressed(QT_KEY_DOWN))
			m_CameraPosition.y += m_CameraMoveSpeed * pTimestep.GetSeconds();
		if (Quartz::Input::IsKeyPressed(QT_KEY_LEFT))
			m_CameraPosition.x += m_CameraMoveSpeed * pTimestep.GetSeconds();
		if (Quartz::Input::IsKeyPressed(QT_KEY_RIGHT))
			m_CameraPosition.x -= m_CameraMoveSpeed * pTimestep.GetSeconds();

		if (Quartz::Input::IsKeyPressed(QT_KEY_A))
			m_CameraRotation -= m_CameraRotationSpeed * pTimestep.GetSeconds();
		if (Quartz::Input::IsKeyPressed(QT_KEY_D))
			m_CameraRotation += m_CameraRotationSpeed * pTimestep.GetSeconds();

		// --Rendering------------------------------
		Quartz::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Quartz::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Quartz::Renderer::BeginScene(m_Camera);

		Quartz::Renderer::Submit(m_BlueShader, m_SquareVA);
		Quartz::Renderer::Submit(m_Shader, m_VertexArray);

		Quartz::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Quartz::Event& pEvent) override
	{

	}
private:
	std::shared_ptr<Quartz::Shader> m_Shader;
	std::shared_ptr<Quartz::VertexArray> m_VertexArray;

	std::shared_ptr<Quartz::Shader> m_BlueShader;
	std::shared_ptr<Quartz::VertexArray> m_SquareVA;

	Quartz::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 1.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 1.0f;
};

class Sandbox : public Quartz::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Quartz::Application* Quartz::CreateApplication()
{
	return new Sandbox();
}