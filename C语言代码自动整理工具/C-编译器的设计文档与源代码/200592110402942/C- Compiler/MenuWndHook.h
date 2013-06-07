/*########################################################################
	Filename: 	MenuWndHook.h
	----------------------------------------------------
	Remarks:	...
	----------------------------------------------------
	Author:		����
	Email:		anyou@sina.com
				anyou@msn.com
	Created:	7/4/2003 17:37
  ########################################################################*/

#if !defined(_ANYOU_MENUWNDHOOK_H)
#define _ANYOU_MENUWNDHOOK_H

#if _MSC_VER > 1000
#pragma once
#endif 

#include <afxtempl.h>

/*########################################################################
			  ------------------------------------------------
							 CMenuWndHook ��
			  ------------------------------------------------
  ########################################################################*/
class CMenuWndHook
{
// ���� ---------------------------------------------------------
public:
    CMenuWndHook(HWND hWnd);
	~CMenuWndHook();
	static void InstallHook();
	static void UnInstallHook();

// ��Ϣ ----------------------------------------------------------
public:
	static LRESULT CALLBACK CoolMenuProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WindowHook (int code, WPARAM wParam, LPARAM lParam);

	void OnNcCalcsize(NCCALCSIZE_PARAMS* lpncsp);
	void OnShowWindow(BOOL bShow);
	void OnNcDestroy();
	void OnPrint(CDC* pDC);
	void OnNcPaint();
	void OnWindowPosChanging(WINDOWPOS* pWindowPos);

// ���� ----------------------------------------------------------
public:
	static CMenuWndHook* AddWndHook(HWND hwnd);
	static CMenuWndHook* GetWndHook(HWND hwnd);

// ���� -----------------------------------------------------------
protected:
	HWND m_hWnd;
	CBitmap m_bmpBack;

	static CMap<HWND, HWND, CMenuWndHook*, CMenuWndHook*> m_WndMenuMap;
    static HHOOK m_hMenuHook;
public:
	static COLORREF m_crFrame[4];
};

#endif // !defined(_ANYOU_MENUWNDHOOK_H)
