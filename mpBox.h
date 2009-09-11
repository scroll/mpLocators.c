#ifndef _MPBOX_H_
#define _MPBOX_H_

#include "mpLocator.h"

class mpBox : public mpLocator
{
public:
    virtual void draw( M3dView & view, const MDagPath & path, M3dView::DisplayStyle style, M3dView::DisplayStatus status );
    virtual MBoundingBox boundingBox() const; 

    static void *creator();
    static MStatus initialize();
    
public:
    static const MTypeId nodeId;
    static const MString nodeName;

private:
    void drawCube(float xsize, float ysize, float zsize);
    // Attributes
    static MObject aColor;
    static MObject aTransparency;
    static MObject aBackAlpha;
    static MObject aLineWidth;
    static MObject aDrawType;
    static MObject aRotate;

    static MObject aXsize;
    static MObject aYsize;
    static MObject aZsize;
};

#endif
