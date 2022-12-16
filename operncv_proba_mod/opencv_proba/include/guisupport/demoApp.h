#ifndef _DEMOAPP_H_
#define _DEMOAPP_H_

/********************************************************************
 FILE: $Id: demoApp.h,v 1.1 1999/06/28 21:30:49 hugo Exp $
 AUTHOR: Hugo DesRosiers.
 DATE: 1999/06/07.

 Description: Generic and portable Demo Application framework.

 History:
	1999/06/07 [HD]: Creation.
 
           -- COPYRIGHT VIRTUAL TECHNOLOGIES, INC. 1999 --
********************************************************************/


class GuiLink;


class DemoApp
{
  protected:
	static void *specialInfo;
  
  public:
	static void setSpecialInfo(void *someData);

  protected:
    GuiLink *gui;
    unsigned int m_width, m_height;
    unsigned int m_XinitPosition, m_YinitPosition;
	char *name;

  public:
	DemoApp(char *aName);
	virtual ~DemoApp(void);
    virtual void initWindow(void);
    virtual void prepareDisplayScene(void);
    virtual void displayScene(void);
    virtual void finishDisplayScene(void);
    virtual void manageEvents(void);
    virtual void run(void);

	virtual char *getName(void);

};

#endif		/* _DEMOAPP_H_ */
