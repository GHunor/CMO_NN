#ifndef _VHT_VCLIP_VERTEX_GEOMETRY_H
#define _VHT_VCLIP_VERTEX_GEOMETRY_H

class vhtConvexHull;

#include <vhtVertexGeometry.h>

class vhtVClipVertexGeometry : public vhtVertexGeometry
{

public:
    vhtVClipVertexGeometry( void );
    //: Construct a VClip vertex based geometry.
    virtual ~vhtVClipVertexGeometry( void );
    //: destruct

	 // Commented out by JH 9-11-09
    //const virtual vhtConvexHull *getConvexHull( void );
    //: Return the VClip represented convex hull.
};

#endif
