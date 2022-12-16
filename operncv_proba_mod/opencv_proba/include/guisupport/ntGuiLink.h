#ifndef _NTGUI_LINK_H_
#define _NTGUI_LINK_H_
/********************************************************************
 FILE: $Id: ntGuiLink.h,v 1.3 2001/11/02 01:35:50 bdiscoe Exp $
 AUTHOR: Hugo DesRosiers.
 DATE: 1999/06/08.

 Description: Extension of GUI functionality for the NT platform.

 History:
	1999/06/15 [HD]: Creation.
 
           -- COPYRIGHT VIRTUAL TECHNOLOGIES, INC. 1999 --
********************************************************************/

#define _WIN32_WINNT 0x0400			// avoid winsock problem
#include <windows.h>
#include "guiLink.h"

class NTGuiLink;


class HwndMappers
{
  public:
	NTGuiLink *guiWindow;
    HWND mswinWindow;

  public:
	HwndMappers(NTGuiLink *aGui, HWND aHandle);
};


class NTGuiLink : public GuiLink
{
  private:
	static HwndMappers *mappingTable[32];
	static unsigned int freeMappers;
	static unsigned int nbrMappers;
    static bool didInitialization;

  private:
    static bool CreateRGBPalette(HDC hDC);
	static unsigned char ComponentFromIndex(int i, UINT nbits, UINT shift);
	static NTGuiLink *locateGuiFromHwnd(HWND aWnd);
	static LRESULT CALLBACK mainWndProc(HWND, UINT, WPARAM, LPARAM);
	static LRESULT CALLBACK dialogProc(HWND, UINT, WPARAM, LPARAM);

  protected:
	WNDCLASS winClass;
	HWND hWindow;
	HDC drawContext;
	HGLRC renderContext;
	HINSTANCE appHandle;
	PAINTSTRUCT ps;
	int lastError;

  protected:
	bool initOpenGL(void);

  public:
    NTGuiLink(DemoApp *anApp, HINSTANCE aHandle);
	virtual ~NTGuiLink(void);
	virtual bool createWindow(unsigned int w, unsigned int h, unsigned int xOrig, unsigned int yOrig);
    virtual void showAndMakeKeyWindow(void);
	virtual void beginDrawing(void);
	virtual void finishDrawing(void);
    virtual int runModalLoop(void);
};

#endif		/* _NTGUI_LINK_H_ */
