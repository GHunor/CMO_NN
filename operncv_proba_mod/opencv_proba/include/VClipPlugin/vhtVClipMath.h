#ifndef VHT_VCLIP_MATH_H
#define VHT_VCLIP_MATH_H
/********************************************************************
 FILE: $Id: vhtVClipMath.h,v 1.1 2000/06/05 19:45:46 ullrich Exp $
 AUTHOR: Chris Ullrich.
 DATE: March 1st, 1999.

 DESCRIPTION:

 HISTORY:
 
           -- COPYRIGHT VIRTUAL TECHNOLOGIES, INC. 1998 --
********************************************************************/

#include <vhtVector3d.h>
#include <vhtTransform3D.h>
#include <vclip.h>

//: VHT<-> VClip math conversion.
// Provide convenience routines for converting from VHT formatted vectors
// and matrices to VClip format.
class vhtVClipMath
{
public:

    inline static void convTransToSe3( const vhtTransform3D &vhtXForm, Se3 &vclipXForm );
    //: Convert a vhtTransform3D to a Se3.
    // Removes any scaling in the vhtXForm.
    inline static void convSe3ToTrans( const Se3 &vclipXForm, vhtTransform3D &vhtXForm );
    //: Convert a Se3 to a vhtTransform3D.
    // Se3 matrices have no scaling component.

    inline static void convVec3dToVect3( const vhtVector3d &vhtVec3d, Vect3 &vclipVect3 );
    //: Convert vhtVector3d to Vect3.
    inline static void convVect3ToVec3d( const Vect3 &vclipVect3, vhtVector3d &vhtVec3d );
    //: Convert Vect3 to vhtVector3d.
};


void 
vhtVClipMath::convTransToSe3( const vhtTransform3D &vhtXForm, Se3 &vclipXForm )
{
  // calculate axis-angle
  vhtVector3d axis;
  double angle;
  vhtQuaternion vhtQ;
  vhtXForm.getRotation( vhtQ );
  
  angle = vhtQ.getAngle();
  vhtQ.getAxis( axis );
  Vect3 rAxis( axis[0], axis[1], axis[2] );
  
  Quat q;
  if( axis.length() > 0.0 ) {
    q.set( angle, rAxis );
  } else {
    q.set( angle, rAxis, 0 ); // don't normalize
  }
  
  vhtVector3d tmp;    
  vhtXForm.getTranslation( tmp );
  Vect3 trans( tmp[0], tmp[1], tmp[2] );
  
  vclipXForm = Se3( q, trans ); 
}

void 
vhtVClipMath::convSe3ToTrans( const Se3 &vclipXForm, vhtTransform3D &vhtXForm )
{
    Quat q = vclipXForm.rot();

    vhtVector3d axis;
    vhtVClipMath::convVect3ToVec3d( q.axis(), axis );

    vhtXForm.setIdentity();
    vhtXForm.rotate( axis, q.angle() );

    vhtVector3d trans;
    vhtVClipMath::convVect3ToVec3d( vclipXForm.trans(), trans );
    vhtXForm.setTranslation( trans );
}


void 
vhtVClipMath::convVec3dToVect3( const vhtVector3d &vhtVec3d, Vect3 &vclipVect3 )
{
    for( int i=0; i < 3; i++ ) {
		vclipVect3[i] = vhtVec3d[i];
    }
}

void 
vhtVClipMath::convVect3ToVec3d( const Vect3 &vclipVect3d, vhtVector3d &vhtVec3d )
{
    for( int i=0; i < 3; i++ ) {
		vhtVec3d[i] = vclipVect3d[i];
    }
}
#endif


