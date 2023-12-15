#include "qtpch.h"
#include "OrthographicCameraController.h"

#include "Quartz/Input.h"
#include "Quartz/KeyCodes.h"

namespace Quartz
{
	OrthographicCameraController::OrthographicCameraController(float pAspectRatio, bool pRotation)
		: m_AspectRatio(pAspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(pRotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(QT_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * ts.GetSeconds();
		else if (Input::IsKeyPressed(QT_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * ts.GetSeconds();

		if (Input::IsKeyPressed(QT_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * ts.GetSeconds();
		else if (Input::IsKeyPressed(QT_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * ts.GetSeconds();

		if (m_Rotation)
		{
			if (Input::IsKeyPressed(QT_KEY_Q))
				m_CameraRotation -= m_CameraRotationSpeed * ts.GetSeconds();
			if (Input::IsKeyPressed(QT_KEY_E))
				m_CameraRotation += m_CameraRotationSpeed * ts.GetSeconds();

			m_Camera.SetRotation(m_CameraRotation);
		}
		
		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(QT_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(QT_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= (e.GetYOffset() / 2.0f);
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_AspectRatio -= (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);

		return false;
	}
}