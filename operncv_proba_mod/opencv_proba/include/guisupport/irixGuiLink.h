#ifndef	_IRIX_GUI_LINK_H_
#define	_IRIX_GUI_LINK_H_
/********************************************************************
 FILE: $Id: irixGuiLink.h,v 1.1 1999/06/28 21:30:49 hugo Exp $
 AUTHOR: Hugo DesRosiers.
 DATE: 1999/06/08.

 Description: GUI functionality defined for Irix + Glut.

 History:
        1999/06/08 [HD]: Creation.

           -- COPYRIGHT VIRTUAL TECHNOLOGIES, INC. 1999 --
********************************************************************/

#include "guiLink.h"


class GlutMaster;
class GlutWindow;


class IrixGuiLink : public GuiLink
{
  protected:
    GlutMaster *m_glutMaster;
    GlutWindow *window;

  public:
    IrixGuiLink(DemoApp *anApp);
    ~IrixGuiLink(void);
    bool createWindow(unsigned int w, unsigned int h, unsigned int xOrig, unsigned int yOrig);
    void finishDrawing(void);
	int runModalLoop(void);
};

#endif	/* _IRIX_GUI_LINK_H_ */
