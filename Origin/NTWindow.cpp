#include "NTWindow.h"


namespace illidan
{
	HINSTANCE NTWindow::s_Instance;
	std::map<LPCWSTR, WNDCLASSEX*> NTWindow::s_WndClassCache;


	LRESULT CALLBACK NTWindow::WinPro(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		switch (msg)
		{
		case WM_CLOSE:
			DestroyWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	int NTWindow::RegisterInstance(HINSTANCE instance)
	{
		s_Instance = instance;

		return 0;
	}

	int NTWindow::RegisterNTWindowClass(LPCWSTR pName)
	{
		if (s_WndClassCache.find(pName) != s_WndClassCache.end())
		{
			return 1;
		}

		//注册窗口类
		WNDCLASSEX* pWCE = new WNDCLASSEX();
		pWCE->cbSize = sizeof(WNDCLASSEX);
		pWCE->style = CS_HREDRAW | CS_VREDRAW;
		pWCE->lpfnWndProc = NTWindow::WinPro;
		pWCE->cbClsExtra = 0;
		pWCE->cbWndExtra = 0;
		pWCE->hInstance = s_Instance;
		pWCE->hIcon = (HICON)LoadIcon(s_Instance, MAKEINTRESOURCE(101));
		pWCE->hCursor = LoadCursor(NULL, IDC_ARROW);
		pWCE->hbrBackground = CreateSolidBrush(RGB(0,0,0));
		pWCE->lpszMenuName = NULL;
		pWCE->lpszClassName = pName;
		pWCE->hIconSm = (HICON)LoadIcon(s_Instance, MAKEINTRESOURCE(101));
		DWORD res = RegisterClassEx(pWCE);
		if (res == 0)
		{
			DWORD err = GetLastError();
			return -1;
		}

		s_WndClassCache.insert(std::pair<LPCWSTR, WNDCLASSEX*>(pName, pWCE));

		return 0;
	}

	int NTWindow::ClearNTWindowClass()
	{
		for (std::map<LPCWSTR, WNDCLASSEX*>::iterator it = s_WndClassCache.begin(); it != s_WndClassCache.end(); ++it)
		{
			delete it->second;
		}
		s_WndClassCache.clear();

		return 0;
	}


	NTWindow::NTWindow()
		:
		m_pWCName(0), m_pWName(0), m_Width(0), m_Height(0), m_WND(0), m_HDC(0)
	{
	}

	//Simple do it;
	NTWindow::NTWindow(const NTWindow& that)
		:
		m_pWCName(that.m_pWCName), m_pWName(that.m_pWName), m_Width(that.m_Width), m_Height(that.m_Height), m_WND(that.m_WND), m_HDC(that.m_HDC)
	{
	}

	//Simple do it;
	NTWindow& NTWindow::operator=(const NTWindow& that)
	{
		if (this != &that)
		{
			m_pWCName = that.m_pWCName;
			m_pWName = that.m_pWName;
			m_Width = that.m_Width;
			m_Height = that.m_Height;
			m_WND = that.m_WND;
			m_HDC = that.m_HDC;
		}
		return *this;
	}


	//Simple do it;
	NTWindow::~NTWindow()
	{
		m_pWCName = 0;
		m_pWName = 0;
		m_Width = 0;
		m_Height = 0;
		m_WND = 0;
		m_HDC = 0;
	}

	int NTWindow::Construtor(LPCWSTR pWCName, LPCWSTR pWName, int width, int height)
	{
		m_pWCName = pWCName;
		m_pWName = pWName;
		m_Width = width;
		m_Height = height;

		//计算窗口大小和位置
		int screenW = GetSystemMetrics(SM_CXSCREEN);
		int screenH = GetSystemMetrics(SM_CYSCREEN);

		RECT rect
		{
			(screenW - m_Width) / 2,
			(screenH - m_Height) / 2,
			rect.left + m_Width,
			rect.top + m_Height
		};

		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

		//创建窗口并显示
		m_WND = CreateWindowEx(NULL, m_pWCName, m_pWName, WS_OVERLAPPEDWINDOW, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, s_Instance, NULL);
		ShowWindow(m_WND, SW_SHOW);
		UpdateWindow(m_WND);

		//获取HDC
		m_HDC = GetDC(m_WND);

		return 0;
	}

	int NTWindow::UpdateNTWindow()
	{
		//消息循环
		MSG msg;
		while (true)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT)
				{
					break;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			Update();
		}

		return 0;
	}

	void NTWindow::Init()
	{

	}

	void NTWindow::Update()
	{

	}
}