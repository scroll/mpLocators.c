#ifndef _MPLOCATOR_H_
#define _MPLOCATOR_H_

#include <maya/MPxLocatorNode.h> 
#include <maya/MString.h>
#include <maya/MTypeId.h> 
#include <maya/MDataBlock.h>
#include <maya/MDataHandle.h>
#include <maya/M3dView.h>
#include <maya/MFnNumericAttribute.h>
#include <maya/MFnEnumAttribute.h>
#include <maya/MPointArray.h>
#include <maya/MTypes.h>

class mpLocator : public MPxLocatorNode
{
public:
mpLocator() : MPxLocatorNode() {};
	virtual ~mpLocator() {};
	virtual bool isBounded() const;
	virtual bool drawLast() const;
protected:
	void drawStyle(M3dView::DisplayStyle style,
		       int drawType, float lw);
	void drawShaded();
	void drawWireframe(float lw);
	// Attributes
	/* static MObject aColor; */
	/* static MObject aTransparency; */
	/* static MObject aBackAlpha; */
	/* static MObject aLineWidth; */
	/* static MObject aDrawType; */
	/* static MObject aRotate; */
};

#endif
