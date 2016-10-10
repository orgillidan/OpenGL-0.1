#pragma once

#include "Vector3f.h"

#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment(lib, "OpenGL32.Lib")


namespace illidan
{
	class Camera
	{
	//Member
	private:
		HWND m_WND;

		Vector3f m_Pos;
		Vector3f m_Aim;
		Vector3f m_Up;

		bool m_RButtonDown;
		POINT m_LastPoint;
		POINT m_OriginPoint;
		bool m_bForward;
		bool m_bBack;
		bool m_bLeft;
		bool m_bRight;
		float m_Speed;
	private:
		void RotateView(float angle, float x, float y, float z);

	public:
		Camera(HWND wnd);
		Camera(const Camera& that);
		Camera& operator=(const Camera& that);
		virtual ~Camera();

		void Update(float delta);

	//Virtual
		void OnRButtonDown(WPARAM wParam, LPARAM lParam);
		void OnRButtonUp(WPARAM wParam, LPARAM lParam);
		void OnMouseMove(WPARAM wParam, LPARAM lParam);
		void OnKeyDown(WPARAM wParam, LPARAM lParam);
		void OnKeyUp(WPARAM wParam, LPARAM lParam);
	};
}
