#ifndef _VHT_VCLIP_COLLISION_FACTORY_H
#define _VHT_VCLIP_COLLISION_FACTORY_H
 
#if defined(BUILD_WIN32_VH_DLL)

#if defined __BUILD_VCLIP_PLIGGIN_DLL__
#define VCLIP_PLUGGIN_DLL_EXPORT __declspec(dllexport)
#else
#define VCLIP_PLUGGIN_DLL_EXPORT __declspec(dllimport)
#endif
#else
#define VCLIP_PLUGGIN_DLL_EXPORT
#endif


class vhtVClipCollide;

#include <vhtCollisionFactory.h>


class vhtVClipCollisionFactory : public vhtCollisionFactory
{
	protected:
		vhtVClipCollide         *m_vclipCollide;

	public:
		VCLIP_PLUGGIN_DLL_EXPORT vhtVClipCollisionFactory( void );

		VCLIP_PLUGGIN_DLL_EXPORT virtual ~vhtVClipCollisionFactory( void );
    
		VCLIP_PLUGGIN_DLL_EXPORT virtual vhtCollisionPair *generateCollisionPair( vhtShape3D &obj1, vhtShape3D &obj2 );

		VCLIP_PLUGGIN_DLL_EXPORT virtual vhtGeometry      *generateCollisionGeometry( vhtShape3D &obj );

		VCLIP_PLUGGIN_DLL_EXPORT virtual void removeCollisionPair( vhtCollisionPair *aPair );

		VCLIP_PLUGGIN_DLL_EXPORT virtual void removeCollisionGeometry( vhtShape3D *obj );
};

#endif
