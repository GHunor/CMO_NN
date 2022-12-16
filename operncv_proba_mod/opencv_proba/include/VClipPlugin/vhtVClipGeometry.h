#ifndef VHT_VCLIP_GEOMETRY_H
#define VHT_VCLIP_GEOMETRY_H

class vhtVClipHull;
class vhtVertexGeometry;
class vhtVector3d;

#include <vhtGeometry.h>

//: VClip geometry.
class vhtVClipGeometry : public vhtGeometry
{
protected:

    vhtVClipGeometry( void ) {;}
    //: No default constructor.

public:
    vhtVClipHull       *m_convexHull;
    vhtVertexGeometry  *m_geometryTemplate;

    vhtVClipGeometry( vhtVertexGeometry *geomTemplate );
    //: Build a VClip geometry representation.

    virtual ~vhtVClipGeometry( void );
    //: Destruct geometry.

    virtual double   getBoundingRadius( void );
    //: Return the maximal vertex radius.

    virtual const vhtVector3d &getBoundingCenter( void );
    //: Return the center of geometry.

    virtual vhtVClipHull *getConvexHull( void );
    //: Return the convex hull in vclip format.

    virtual void render( void );
    //: Render this collision geometry.
};

#endif
