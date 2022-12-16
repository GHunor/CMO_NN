/********************************************************************
 FILE: $Id: vhtVClipHull.h,v 1.3 2000/07/22 09:14:42 ullrich Exp $
 AUTHOR: C Ullrich
 DATE: 1998

 DESCRIPTION:
  vhtVClipHull is a convex hull class for the VClip collision detection
  library.  Objects of this type are constructed automatically by 
  vhtVertexGeometry when it is used.

 HISTORY:
  -

           -- COPYRIGHT VIRTUAL TECHNOLOGIES, INC. 1998 --
********************************************************************/
#ifndef VHT_VCLIP_HULL_H
#define VHT_VCLIP_HULL_H

#include <vhtConvexHull.h>
#include <vector>

using namespace std;

class Vertex;
class Polyhedron;
class PolyTree;
class vhtCollide;

//: A VClip formatted convex hull.
// The VClip collider requires that it's convex hull geometry input be formatted
// in a particular way. This class takes care of that orginization.
// Classes of this type will be automatically created by vhtVertexGeometry.
// Note that convex hull creation is a time consuming process, so real
// time geometry modification may require a significant amount of computing power.
class vhtVClipHull : public vhtConvexHull
{
    friend vhtCollide;

public:
    vhtVClipHull(void);
    //: Default constructor.
    vhtVClipHull( const vhtVClipHull &hull );
    //: Copy constructor.
    vhtVClipHull( vhtArray &vertices );
    //: Build a convex hull.
    // Constructs a vhtVClipHull from the provided vertex list.  Each entry
    // in vertices should be a pointer to a vhtVector3d object.
    virtual ~vhtVClipHull(void);
    //: Destructor.

    void setVertices( vhtArray &vertices );
    //: Set the vertices.
    // Builds a convex hull from the provided list of vertices.  Each entry
    // in vertices should be a pointer to a vhtVector3d object.

    virtual int  check(void );
    //: Check the euler condition.
    // For correctly formatted geometry, this should return 0.

    inline PolyTree    *getPolyTree(void) { return m_polyTree; }
    //: Get the vClip polytree.
    // Returns the associated polytree.  

private:
    vector<Vertex *>  m_vertexList;
    Polyhedron       *m_polyhedron;
    PolyTree         *m_polyTree;
};

#endif


