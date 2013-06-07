/*########################################################################
	Filename: 	MenuWndHook.cpp
	----------------------------------------------------
	Remarks:	...
	----------------------------------------------------
	Author:		成真
	Email:		anyou@sina.com
				anyou@msn.com
	Created:	7/4/2003 17:38
  ########################################################################*/

#include "stdafx.h"
#include "resource.h"
#include "MenuWndHook.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifndef SPI_GETDROPSHADOW
#define SPI_GETDROPSHADOW   0x1024
#endif
const TCHAR CoolMenu_oldProc[] = _T("CoolMenu_oldProc");

/*========================================================================
	说明:	检测系统是否开启了菜单阴影(主要针对于Windows XP, Windows 2003
		及他更高的版本).	
==========================================================================*/
BOOL WINAPI IsShadowEnabled()
{
	BOOL bEnabled = FALSE;
	if (SystemParametersInfo(SPI_GETDROPSHADOW, 0, &bEnabled, 0))
	{
		return bEnabled;
	}
	return FALSE;
}

/*========================================================================
	说明:		截取屏幕上指定区域内的图像.
==========================================================================*/
HBITMAP WINAPI GetScreenBitmap(LPCRECT pRect)
{
    HDC     hDC;
    HDC     hMemDC;
    HBITMAP hNewBitmap = NULL;
	
    if ((hDC = ::GetDC(NULL)) != NULL )
    {
        if ((hMemDC = ::CreateCompatibleDC(hDC)) != NULL)
        {
            if ((hNewBitmap = ::CreateCompatibleBitmap(hDC, pRect->right - pRect->left, pRect->bottom - pRect->top)) != NULL)
            {
                HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hNewBitmap);
                ::BitBlt(hMemDC, 0, 0, pRect->right - pRect->left, pRect->bottom - pRect->top,
					hDC, pRect->left, pRect->top, SRCCOPY);
                ::SelectObject(hMemDC, (HGDIOBJ)hOldBitmap);
            }
            ::DeleteDC(hMemDC);
        }
        ::ReleaseDC(NULL, hDC);
    }
    return hNewBitmap;
}

/*========================================================================
	说明:	在指定的矩形区域内绘制阴影.	
==========================================================================*/
void DrawShadow(CDC *pDC, CRect rect)
{
	COLORREF oldcolor = RGB(255, 255, 255);
	BYTE newValR, newValG, newValB;
	BYTE AlphaArray[] = {140, 170, 212, 240};
	BYTE AlphaArray2[] = {170, 205, 220, 240, 240, 250, 255};
	
	// 底部的阴影 -----------------------------------------
	int i, j;
	for (j = 0; j < 4; j++)
	{
		for (i = 6; i <= rect.right - 5; i++)
		{
			oldcolor = pDC->GetPixel(i, rect.bottom - (4 - j));
			newValR = GetRValue(oldcolor) * AlphaArray[j] / 255;  
			newValG = GetGValue(oldcolor) * AlphaArray[j] / 255;  
			newValB = GetBValue(oldcolor) * AlphaArray[j] / 255;  
			pDC->SetPixel(i, rect.bottom - (4 - j), RGB(newValR, newValG, newValB));
		}
	}
	
	// 右边的阴影 -----------------------------------------
	for (i = 0; i < 4; i++)
	{
		for (j = 6; j <= rect.bottom - 5; j++)
		{
			oldcolor = pDC->GetPixel(rect.right - (4 - i), j);
			newValR = GetRValue(oldcolor) * AlphaArray[i] / 255;  
			newValG = GetGValue(oldcolor) * AlphaArray[i] / 255;  
			newValB = GetBValue(oldcolor) * AlphaArray[i] / 255;  
			pDC->SetPixel(rect.right - (4 - i), j, RGB(newValR, newValG, newValB));
		}
	}
	
	// 其他部位的阴影 --------------------------------------
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if ((i + j) > 6) break;
			BYTE alpha = AlphaArray2[i + j];
			oldcolor = pDC->GetPixel(rect.right - 4 + i, rect.bottom - 4 + j);
			newValR = GetRValue(oldcolor) * alpha / 255;  
			newValG = GetGValue(oldcolor) * alpha / 255;  
			newValB = GetBValue(oldcolor) * alpha / 255;  
			pDC->SetPixel(rect.right - 4 + i, rect.bottom - 4 + j, RGB(newValR, newValG, newValB));
			
			oldcolor = pDC->GetPixel(rect.right - 4 + i, rect.top + 5 - j);
			newValR = GetRValue(oldcolor) * alpha / 255;  
			newValG = GetGValue(oldcolor) * alpha / 255;  
			newValB = GetBValue(oldcolor) * alpha / 255;  
			pDC->SetPixel(rect.right - 4 + i, rect.top + 5 - j, RGB(newValR, newValG, newValB));
			
			oldcolor = pDC->GetPixel(rect.left - i + 5, rect.bottom - 4 + j);
			newValR = GetRValue(oldcolor) * alpha / 255;  
			newValG = GetGValue(oldcolor) * alpha / 255;  
			newValB = GetBValue(oldcolor) * alpha / 255;  
			pDC->SetPixel(rect.left - i + 5, rect.bottom - 4 + j, RGB(newValR, newValG, newValB));
		}
	}
}

/*########################################################################
			  ------------------------------------------------
								class CMenuWndHook
			  ------------------------------------------------
  ########################################################################*/
CMap <HWND, HWND, CMenuWndHook*, CMenuWndHook*> CMenuWndHook::m_WndMenuMap;
HHOOK CMenuWndHook::m_hMenuHook = NULL;
COLORREF CMenuWndHook::m_crFrame[4] = 
	{::GetSysColor(COLOR_3DSHADOW), 
	 ::GetSysColor(COLOR_3DSHADOW), 
	 ::GetSysColor(COLOR_MENU), 
	 ::GetSysColor(COLOR_MENU)};

CMenuWndHook::CMenuWndHook (HWND hWnd)
: m_hWnd(hWnd)
{

}

CMenuWndHook::~CMenuWndHook ()
{
    WNDPROC oldWndProc = (WNDPROC)::GetProp(m_hWnd, CoolMenu_oldProc);
    if (oldWndProc != NULL)
    {
        ::SetWindowLong(m_hWnd, GWL_WNDPROC, (DWORD)(ULONG)oldWndProc);
        ::RemoveProp(m_hWnd, CoolMenu_oldProc);
    }
    m_WndMenuMap.RemoveKey(m_hWnd);
	if (m_bmpBack.m_hObject != NULL )
    {
         m_bmpBack.DeleteObject();
    }
}

void CMenuWndHook::InstallHook()
{
    if (m_hMenuHook == NULL )
    {
        m_hMenuHook = ::SetWindowsHookEx(WH_CALLWNDPROC, WindowHook, 
						AfxGetApp()->m_hInstance, ::GetCurrentThreadId());
    }
}

void CMenuWndHook::UnInstallHook()
{
    POSITION pos = m_WndMenuMap.GetStartPosition();
    while (pos != NULL)
    {
        HWND hwnd;
        CMenuWndHook* pMenuWndHook;
        m_WndMenuMap.GetNextAssoc(pos, hwnd, pMenuWndHook);
        delete pMenuWndHook;
		pMenuWndHook = NULL;
    }
    m_WndMenuMap.RemoveAll();
	
    if (m_hMenuHook != NULL)
    {
        ::UnhookWindowsHookEx(m_hMenuHook);
    }
}

CMenuWndHook* CMenuWndHook::GetWndHook(HWND hwnd)
{
    CMenuWndHook* pWnd = NULL;
    if (m_WndMenuMap.Lookup(hwnd, pWnd))
    {
        return pWnd;
    }
    return NULL;
}

CMenuWndHook* CMenuWndHook::AddWndHook(HWND hwnd)
{
	CMenuWndHook* pWnd = NULL;
	if (m_WndMenuMap.Lookup(hwnd, pWnd))
	{
	   return pWnd;
	}

	pWnd = new CMenuWndHook(hwnd);
	if (pWnd != NULL)
	{
		m_WndMenuMap.SetAt(hwnd, pWnd);
	}
	return pWnd;
}

/*########################################################################
			  ------------------------------------------------
								  消息过程
			  ------------------------------------------------
  ########################################################################*/
LRESULT CALLBACK CMenuWndHook::WindowHook(int code, WPARAM wParam, LPARAM lParam)
{
    CWPSTRUCT* pStruct = (CWPSTRUCT*)lParam;
	
    while (code == HC_ACTION)
    {
        HWND hWnd = pStruct->hwnd;
		
        if (pStruct->message != WM_CREATE && pStruct->message != 0x01E2)
        {
            break;
        }

        // 是否为菜单类 ----------------------------------------
        TCHAR strClassName[10];
        int Count = ::GetClassName (hWnd, strClassName, sizeof(strClassName) / sizeof(strClassName[0]));
        if (Count != 6 || _tcscmp(strClassName, _T("#32768")) != 0 )
        {
            break;
        }
		
		// 是否已经被子类化 ------------------------------------
        if (::GetProp(pStruct->hwnd, CoolMenu_oldProc) != NULL )
        {
            break;
        }
        VERIFY(AddWndHook(pStruct->hwnd) != NULL);

        // 取得原来的窗口过程 ----------------------------------
        WNDPROC oldWndProc = (WNDPROC)(long)::GetWindowLong(pStruct->hwnd, GWL_WNDPROC);
        if (oldWndProc == NULL)
        {
            break;
        }
		
        ASSERT(oldWndProc != CoolMenuProc);
        // 保存到窗口的属性中 ----------------------------------
        if (!SetProp(pStruct->hwnd, CoolMenu_oldProc, oldWndProc) )
        {
            break;
        }

        // 子类化 ----------------------------------------------
        if (!SetWindowLong(pStruct->hwnd, GWL_WNDPROC,(DWORD)(ULONG)CoolMenuProc) )
        {
            ::RemoveProp(pStruct->hwnd, CoolMenu_oldProc);
            break;
        }
        break;
    }
    return CallNextHookEx (m_hMenuHook, code, wParam, lParam);
}

LRESULT CALLBACK CMenuWndHook::CoolMenuProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	WNDPROC oldWndProc = (WNDPROC)::GetProp(hWnd, CoolMenu_oldProc);
    CMenuWndHook* pWnd = NULL;
	
    switch (uMsg)
    {
		case WM_NCCALCSIZE:
			{
				LRESULT lResult = CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnNcCalcsize((NCCALCSIZE_PARAMS*)lParam);
				}
				return lResult;
			}
			break;
		case WM_WINDOWPOSCHANGING:
			{
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnWindowPosChanging((LPWINDOWPOS)lParam);
				}
			}
			break;
		case WM_PRINT:
			{
				LRESULT lResult = CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnPrint(CDC::FromHandle((HDC)wParam));
				}
				return lResult;
			}
			break;
		case WM_NCPAINT:
			{
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnNcPaint();
					return 0;
				}
			}
			break;
		case WM_SHOWWINDOW:
			{
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnShowWindow(wParam != NULL);
				}
			}
			break;
		case WM_NCDESTROY:
			{
				if ((pWnd = GetWndHook(hWnd)) != NULL)
				{
					pWnd->OnNcDestroy();
				}
			}
			break;
    }
    return CallWindowProc(oldWndProc, hWnd, uMsg, wParam, lParam);
}

/*########################################################################
			  ------------------------------------------------
								消息处理函数	
			  ------------------------------------------------
  ########################################################################*/
void CMenuWndHook::OnWindowPosChanging(WINDOWPOS *pWindowPos)
{
	if (!IsShadowEnabled())
	{
		pWindowPos->cx += 4;
		pWindowPos->cy += 4;
	}

	if (!IsWindowVisible(m_hWnd) && !IsShadowEnabled())
    {
       if (m_bmpBack.m_hObject != NULL )
        {
            m_bmpBack.DeleteObject();
        }
        m_bmpBack.Attach(GetScreenBitmap(CRect(pWindowPos->x, pWindowPos->y, pWindowPos->cx, pWindowPos->cy)));
    }
}

void CMenuWndHook::OnNcCalcsize(NCCALCSIZE_PARAMS* lpncsp)
{
	if (!IsShadowEnabled())
	{
		 lpncsp->rgrc[0].right -= 4;
		 lpncsp->rgrc[0].bottom -= 4;
	}
}

void CMenuWndHook::OnNcPaint()
{
    CWindowDC dc(CWnd::FromHandle(m_hWnd));
	OnPrint(&dc);
}

void CMenuWndHook::OnPrint(CDC *pDC)
{
	CRect rc;
	GetWindowRect(m_hWnd, &rc);
    rc.OffsetRect(-rc.TopLeft());
	
	if (!IsShadowEnabled())
	{
		CDC cMemDC;
		cMemDC.CreateCompatibleDC (pDC);
		HGDIOBJ hOldBitmap = ::SelectObject (cMemDC.m_hDC, m_bmpBack);
		pDC->BitBlt (0, rc.bottom - 4, rc.Width() - 4, 4, &cMemDC, 0, rc.bottom - 4, SRCCOPY);
		pDC->BitBlt (rc.right - 4, 0, 4, rc.Height(), &cMemDC, rc.right - 4, 0, SRCCOPY);
		
		DrawShadow(pDC, rc);
		rc.right -= 4;
		rc.bottom -= 4;
	}

	pDC->Draw3dRect(rc, m_crFrame[0], m_crFrame[1]);
	rc.DeflateRect (1, 1);
	pDC->Draw3dRect(rc, m_crFrame[2], m_crFrame[3]);
	rc.DeflateRect (1, 1);
	pDC->Draw3dRect(rc, m_crFrame[2], m_crFrame[3]);
}

void CMenuWndHook::OnNcDestroy()
{
	delete this;
}

void CMenuWndHook::OnShowWindow(BOOL bShow)
{
    if (!bShow)
    {
        delete this;
    }
}

