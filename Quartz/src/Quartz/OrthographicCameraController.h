#pragma once

#include "Renderer/OrthographicCamera.h"
#include "Quartz/Core/Timestep.h"

#include "Quartz/Events/Event.h"
#include "Quartz/Events/ApplicationEvent.h"
#include "Quartz/Events/MouseEvent.h"

namespace Quartz
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float pAspectRatio, bool pRotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 1.0f;
		float m_CameraRotationSpeed = 1.0f;
	};
}