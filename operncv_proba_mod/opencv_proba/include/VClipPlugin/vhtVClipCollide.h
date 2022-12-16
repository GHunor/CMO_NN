#ifndef VHT_VCLIP_COLLIDE_H
#define VHT_VCLIP_COLLIDE_H
/********************************************************************
 FILE: $Id: vhtVClipCollide.h,v 1.2 2002/08/28 23:16:41 jsilver Exp $
 AUTHOR: C. Ullrich
 DATE: 1999

 DESCRIPTION:
  - implementation of local mode collisions using VCLIP algorithm
 TODO:
  -
           -- COPYRIGHT VIRTUAL TECHNOLOGIES, INC. 1998 --
********************************************************************/

#if defined(BUILD_WIN32_VH_DLL)

#if defined __BUILD_VCLIP_PLIGGIN_DLL__
#define VCLIP_PLUGGIN_DLL_EXPORT __declspec(dllexport)
#else
#define VCLIP_PLUGGIN_DLL_EXPORT __declspec(dllimport)
#endif

#else
#define VCLIP_PLUGGIN_DLL_EXPORT
#endif


#include <vhtCollide.h>
#include <vclip.h>

class vhtCollisionPair;

//: A VClip based collider.
// This collider uses the VClip algorithm of Mirtich to find MTD's and closest
// features between convex polytopes.  Given a collision pair, VClip uses a 
// constant time technique to track witness points and closest features.
class vhtVClipCollide : public vhtCollide
{
	public:
		VCLIP_PLUGGIN_DLL_EXPORT vhtVClipCollide( unsigned int factoryId );
		//: Construct a VClip collider.

		VCLIP_PLUGGIN_DLL_EXPORT virtual double getMTD( vhtCollisionPair &pair);
		//: Find MTD and features.
		// Runs the VClip algorithm for the provided collision pair.

	private:
		double getVClipMTD( vhtCollisionPair &pair);
    
		ClosestFeaturesHT    m_hashTable;
};

#endif


