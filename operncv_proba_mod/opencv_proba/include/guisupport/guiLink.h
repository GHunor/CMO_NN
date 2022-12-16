#ifndef _GUI_LINK_H_
#define _GUI_LINK_H_
/********************************************************************
 FILE: $Id: guiLink.h,v 1.1 1999/06/28 21:30:49 hugo Exp $
 AUTHOR: Hugo DesRosiers.
 DATE: 1999/06/08.

 Description: Generic GUI functionality for VHT demos.

 History:
	1999/06/08 [HD]: Creation.
 
           -- COPYRIGHT VIRTUAL TECHNOLOGIES, INC. 1999 --
********************************************************************/


class DemoApp;
class vhtTransform3D;


class GuiLink
{
  protected:
    DemoApp *owner;
    vhtTransform3D *cameraXForm;
    unsigned int width, height;

  public:
    GuiLink(DemoApp *anApp);
    virtual ~GuiLink(void);
    virtual bool createWindow(unsigned int w, unsigned int h, unsigned int xOrig, unsigned int yOrig);
    virtual void showAndMakeKeyWindow(void);
    virtual void beginDrawing(void);
    virtual void finishDrawing(void);

    virtual void setOglAmbience(void);
    virtual int runModalLoop(void);

    inline DemoApp *getOwner(void) { return owner; }
};

#endif		/* _GUI_LINK_H_ */
