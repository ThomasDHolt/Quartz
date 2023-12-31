#include "qtpch.h"
#include <Quartz.h>

#include "imgui/imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"
#include "Quartz/Levels/LevelLibrary.h"

class ExampleLayer : public Quartz::Layer
{
public:
#define MAX_MAP_WIDTH 50
#define MAX_MAP_HEIGHT 10

	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray.reset(Quartz::VertexArray::Create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Quartz::Ref<Quartz::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Quartz::VertexBuffer::Create(vertices, sizeof(vertices)));

		Quartz::BufferLayout layout =
		{
			{ Quartz::ShaderDataType::Float3, "a_Position" },
			{ Quartz::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0,1,2 };
		Quartz::Ref<Quartz::IndexBuffer> indexBuffer;
		indexBuffer.reset(Quartz::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Quartz::VertexArray::Create());

		float squareVertices[4 * 5] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Quartz::Ref<Quartz::VertexBuffer> squareVB;
		squareVB.reset(Quartz::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		Quartz::BufferLayout squareVBLayout =
		{
			{ Quartz::ShaderDataType::Float3, "a_Position" },
			{ Quartz::ShaderDataType::Float2, "a_TexCoord" }
		};

		squareVB->SetLayout(squareVBLayout);
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		Quartz::Ref<Quartz::IndexBuffer> squareIB;
		squareIB.reset(Quartz::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = Quartz::Shader::Create("vertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform *  vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			
			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader = Quartz::Shader::Create("flatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");
		auto testLevel = m_LevelLibrary.Load("assets/levels/TestLevel.txt");

		//TODO: Maybe make a LoadContent method where assets such as textures and levels can be loaded rather than doing this in the layer constructor?

		m_Texture = Quartz::Texture2D::Create("assets/textures/Checkerboard.png");
		m_NJTexture = Quartz::Texture2D::Create("assets/textures/nj.png");

		m_BrickTexture = Quartz::Texture2D::Create("assets/textures/RedBrick.png");
		m_DoorTexture = Quartz::Texture2D::Create("assets/textures/RedBrickDoor.png");

		m_GrassTexture = Quartz::Texture2D::Create("assets/textures/Grass.png");
		m_BushTexture = Quartz::Texture2D::Create("assets/textures/Bush.png");

		m_SingularVerticalPathTexture = Quartz::Texture2D::Create("assets/textures/Path_Vertical_Singular.png");
		m_LeftVerticalPathTexture = Quartz::Texture2D::Create("assets/textures/Path_Vertical_Left.png");
		m_RightVerticalPathTexture = Quartz::Texture2D::Create("assets/textures/Path_Vertical_Right.png");

		std::dynamic_pointer_cast<Quartz::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Quartz::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Quartz::Timestep pTimestep) override
	{
		// Update
		m_CameraController.OnUpdate(pTimestep);

		// --Rendering------------------------------
		Quartz::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Quartz::RenderCommand::Clear();

		Quartz::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 squareScale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Quartz::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Quartz::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		auto textureShader = m_ShaderLibrary.Get("Texture");
		auto level = m_LevelLibrary.Get("TestLevel");

		//TODO: Pop this in a method, perhaps called DrawLevel which takes in a reference to a Level that we retrieve from the Level Library?

		for (int y = 0; y < level->GetData().size(); y++)
		{
			auto row = level->GetRow(y);
			for (int x = 0; x < row.length(); x++)
			{
				if (row[x] == '#')
				{
					m_BrickTexture->Bind();

					glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
					glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * squareScale;
					Quartz::Renderer::Submit(textureShader, m_SquareVA, squareTransform);
				}
				else if (row[x] == 'D')
				{
					m_DoorTexture->Bind();

					glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
					glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * squareScale;
					Quartz::Renderer::Submit(textureShader, m_SquareVA, squareTransform);
				}
				else if (row[x] == '\'')
				{
					m_GrassTexture->Bind();

					glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
					glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * squareScale;
					Quartz::Renderer::Submit(textureShader, m_SquareVA, squareTransform);
				}
				else if (row[x] == 'B')
				{
					glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
					glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * squareScale;
					m_GrassTexture->Bind();
					Quartz::Renderer::Submit(textureShader, m_SquareVA, squareTransform);
					m_BushTexture->Bind();
					Quartz::Renderer::Submit(textureShader, m_SquareVA, squareTransform);
				}
				else if (row[x] == 'P')
				{
					if (x > 0 && row[x - 1] == 'P')
					{
						m_RightVerticalPathTexture->Bind();

						glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
						glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * squareScale;
						Quartz::Renderer::Submit(textureShader, m_SquareVA, squareTransform);
					}
					else if (x < row.length() && row[x + 1] == 'P')
					{
						m_LeftVerticalPathTexture->Bind();

						glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
						glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * squareScale;
						Quartz::Renderer::Submit(textureShader, m_SquareVA, squareTransform);
					}
					else
					{
						m_SingularVerticalPathTexture->Bind();

						glm::vec3 pos(x * 0.1f, y * 0.1f, 0.0f);
						glm::mat4 squareTransform = glm::translate(glm::mat4(1.0f), pos) * squareScale;
						Quartz::Renderer::Submit(textureShader, m_SquareVA, squareTransform);
					}
				}
			}
		}

		/*m_Texture->Bind();
		Quartz::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_NJTexture->Bind();
		Quartz::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));*/

		// Triangle render
		//Quartz::Renderer::Submit(m_Shader, m_VertexArray);

		Quartz::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Quartz::Event& pEvent) override
	{
		m_CameraController.OnEvent(pEvent);
	}
private:
	Quartz::ShaderLibrary m_ShaderLibrary;
	Quartz::LevelLibrary m_LevelLibrary;
	Quartz::Ref<Quartz::Shader> m_Shader;
	Quartz::Ref<Quartz::VertexArray> m_VertexArray;

	Quartz::Ref<Quartz::Shader> m_FlatColorShader;
	Quartz::Ref<Quartz::VertexArray> m_SquareVA;

	Quartz::Ref<Quartz::Texture2D> m_Texture, m_NJTexture;
	Quartz::Ref<Quartz::Texture2D> m_BrickTexture, m_DoorTexture;
	Quartz::Ref<Quartz::Texture2D> m_GrassTexture, m_BushTexture;
	Quartz::Ref<Quartz::Texture2D> m_SingularVerticalPathTexture, m_LeftVerticalPathTexture, m_RightVerticalPathTexture;

	Quartz::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
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