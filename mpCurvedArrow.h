#ifndef _MPCURVEDARROW_H_
#define _MPCURVEDARROW_H_

#include <maya/MTypes.h>

#include "mpLocator.h"

static double3 curvedArrowVerts[] = {
	{0,0,-1.001567},
	{-0.336638,0.327886,-0.751175},
	{-0.0959835,0.327886,-0.751175},
	{-0.0959835,0.500458,-0.500783},
	{-0.0959835,0.604001,-0.0987656},
	{-0.500783,0.500458,-0.0987656},
	{-0.751175,0.327886,-0.0987656},
	{-0.751175,0.327886,-0.336638},
	{-1.001567,0,0},
	{-0.751175,0.327886,0.336638},
	{-0.751175,0.327886,0.0987656},
	{-0.500783,0.500458,0.0987656},
	{-0.0959835,0.604001,0.0987656},
	{-0.0959835,0.500458,0.500783},
	{-0.0959835,0.327886,0.751175},
	{-0.336638,0.327886,0.751175},
	{0,0,1.001567},
	{0.336638,0.327886,0.751175},
	{0.0959835,0.327886,0.751175},
	{0.0959835,0.500458,0.500783},
	{0.0959835,0.604001,0.0987656},
	{0.500783,0.500458,0.0987656},
	{0.751175,0.327886,0.0987656},
	{0.751175,0.327886,0.336638},
	{1.001567,0,0},
	{0.751175,0.327886,-0.336638},
	{0.751175,0.327886,-0.0987656},
	{0.500783,0.500458,-0.0987656},
	{0.0959835,0.604001,-0.0987656},
	{0.0959835,0.500458,-0.500783},
	{0.0959835,0.327886,-0.751175},
	{0.336638,0.327886,-0.751175}
};

static unsigned int qs1[] = {2,30,3,29,4,28,4,12,5,11,6,10,12,20,13,19,14,18,4,12,28,20,27,21,26,22};
static unsigned int crvdArrwTriangleIds[] = {0, 1, 31, 7, 8, 9, 15, 16, 17, 23, 24, 25};
static unsigned int crvdArrwTriSize = sizeof(crvdArrwTriangleIds)/sizeof(crvdArrwTriangleIds[0]);
static unsigned int crvdArrwVertSize = sizeof(curvedArrowVerts)/sizeof(curvedArrowVerts[0]);

class mpCurvedArrow : public mpLocator
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
    void drawWireframe(float lw);
    void drawShaded();
    // Attributes
    _COMMON_ATTR_;
    static MObject aDrawType;
};

#endif
