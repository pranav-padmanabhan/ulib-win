/*
 * =====================================================================================
 *
 *       Filename:  udc.cpp
 *
 *    Description:  implement UDevContext
 *
 *        Version:  1.0
 *        Created:  2009-8-23 4:48:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  huys (hys), huys03@gmail.com
 *        Company:  hu
 *
 * =====================================================================================
 */

#define _WIN32_WINNT 0x0500
#define WINVER 0x0500

#include <windows.h>
#include <tchar.h>

#include <cassert>

#include "udc.h"

UDevContext::UDevContext()
: UGDIObject()
{}

UDevContext::~UDevContext()
{}

bool UDevContext::attach(HDC hdc)
{
    assert(NULL == m_hObj);
    m_hObj = hdc;
    return true;
}

bool UDevContext::dettach()
{
    assert(NULL != m_hObj);
    m_hObj = NULL;
    return true;
}

bool UDevContext::getDC( HWND hWnd )
{
    return NULL != (m_hObj = ::GetDC(hWnd));
}

huys::Color UDevContext::setPenColor(huys::Color clr)
{
    //    Select DC_PEN so you can change the color of the pen with
    //    COLORREF SetDCPenColor(HDC hdc, COLORREF color)
    ::SelectObject((HDC)m_hObj, ::GetStockObject(DC_PEN));
    return ::SetDCPenColor((HDC)m_hObj, clr);
}

huys::Color UDevContext::setBrushColor(huys::Color clr)
{
    //    Select DC_BRUSH so you can change the brush color from the 
    //    default WHITE_BRUSH to any other color
    ::SelectObject((HDC)m_hObj, ::GetStockObject(DC_BRUSH));
    return ::SetDCBrushColor((HDC)m_hObj, clr);
}

huys::Color UDevContext::getPenColor()
{
    return ::GetDCPenColor((HDC)m_hObj);
}

huys::Color UDevContext::getBrushColor()
{
    return ::GetDCBrushColor((HDC)m_hObj);
}

HGDIOBJ UDevContext::getCurObj(UINT uObjectType)
{
    return ::GetCurrentObject((HDC)m_hObj, uObjectType);
}

int UDevContext::setStretchBltMode( int iStretchMode )
{
    return ::SetStretchBltMode(*this, iStretchMode);
}

BOOL UDevContext::stretchBlt( int nXOriginDest,
                              int nYOriginDest,
                              int nWidthDest,
                              int nHeightDest,
                              HDC hdcSrc,
                              int nXOriginSrc,
                              int nYOriginSrc,
                              int nWidthSrc,
                              int nHeightSrc,
                              DWORD dwRop )
{
    return ::StretchBlt(*this, nXOriginDest, nYOriginDest,
        nWidthDest, nHeightDest, hdcSrc,
        nXOriginSrc, nYOriginSrc, nWidthSrc, nHeightSrc, dwRop );
}

BOOL UDevContext::bitBlt( int nXOriginDest,
                             int nYOriginDest,
                             int nWidthDest,
                             int nHeightDest,
                             HDC hdcSrc,
                             int nXOriginSrc,
                             int nYOriginSrc,
                             DWORD dwRop )
{
    return ::BitBlt(*this, nXOriginDest, nYOriginDest,
        nWidthDest, nHeightDest, hdcSrc,
        nXOriginSrc, nYOriginSrc, dwRop );
}

void UDevContext::setMapMode( int nMode )
{
    ::SetMapMode((HDC)m_hObj, nMode);
}

int UDevContext::getMapMode()
{
    return ::GetMapMode((HDC)m_hObj);
}

BOOL UDevContext::rectangle(int nLeft, int nTop, int nRight, int nBottom)
{
    return ::Rectangle((HDC)m_hObj, nLeft, nTop, nRight, nBottom);
}

BOOL UDevContext::rectangle(LPCRECT lpRect)
{
    return rectangle(lpRect->left, lpRect->top,
        lpRect->right, lpRect->bottom);
}

int UDevContext::fillRect( LPCRECT lpRect, HBRUSH hBrush )
{
    return ::FillRect((HDC)m_hObj, lpRect, hBrush);
}

int UDevContext::frameRect(LPCRECT lpRect, HBRUSH hBrush)
{
    return ::FrameRect((HDC)m_hObj, lpRect, hBrush);
}

BOOL UDevContext::invertRect(LPCRECT lpRect)
{
    return ::InvertRect((HDC)m_hObj, lpRect);
}

BOOL UDevContext::roundRect(int nLeft, int nTop, int nRight, int nBottom, int nWidth, int nHeight)
{
    return ::RoundRect((HDC)m_hObj, nLeft, nTop, nRight, nBottom, nWidth, nHeight);
}

void UDevContext::setViewportOrg( int x, int y )
{
    ::SetViewportOrgEx((HDC)m_hObj, x, y, NULL);
}

void UDevContext::setWindowOrg( int x, int y )
{
    ::SetWindowOrgEx((HDC)m_hObj, x, y, NULL);
}

BOOL UDevContext::DPToLP(LPPOINT lpPoints, int nCount)
{
    return ::DPtoLP((HDC)m_hObj, lpPoints, nCount);
}

BOOL UDevContext::LPToDP(LPPOINT lpPoints, int nCount)
{
    return ::LPtoDP((HDC)m_hObj, lpPoints, nCount);
}

UPaintDC::UPaintDC(HWND hWnd)
{
    m_hWnd = hWnd;
    m_hObj = ::BeginPaint(m_hWnd, &m_ps);
}

UPaintDC::~UPaintDC()
{
    ::EndPaint(m_hWnd, &m_ps);
}

UPrivateDC::UPrivateDC(HWND hWnd)
: m_hWnd(hWnd)
{
    m_hObj = ::GetDC(m_hWnd);
}

UPrivateDC::~UPrivateDC()
{
    ::ReleaseDC(m_hWnd, (HDC)m_hObj);
}

UMemDC::UMemDC(HDC hdc)
{
    m_hObj = ::CreateCompatibleDC(hdc);
}

UMemDC::~UMemDC()
{
}
