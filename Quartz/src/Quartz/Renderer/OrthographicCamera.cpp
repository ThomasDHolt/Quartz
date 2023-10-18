#include "qtpch.h"
#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Quartz
{
	OrthographicCamera::OrthographicCamera(float pLeft, float pRight, float pBottom, float pTop)
		: m_ProjectionMatrix(glm::ortho(pLeft, pRight, pBottom, pTop, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		m_Left = pLeft;
		m_Right = pRight;
		m_Bottom = pBottom;
		m_Top = pTop;

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, -1.0f, 1.0f);
	}
}
