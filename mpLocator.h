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

#define _COMMON_ATTR_		      \
	static MObject aColor;	      \
	static MObject aTransparency; \
	static MObject aBackAlpha;    \
	static MObject aLineWidth;    \
	static MObject aDrawType;     \
	static MObject aRotate;

#define _COMMON_ATTR_INIT_				\
	do {						\
	aColor = nAttr.createColor( "color", "col" );	\
	nAttr.setDefault( 0.1, 0.1, 0.8 );		\
	nAttr.setKeyable(1);				\
	nAttr.setReadable(1);				\
	nAttr.setWritable(1);				\
	nAttr.setStorable(1);				\
	nAttr.setMin(0, 0, 0);				\
	nAttr.setMax(1, 1, 1);				\
	aRotate = nAttr.createPoint( "rotate", "rot" );	\
	nAttr.setDefault( 0.0, 0.0, 0.0 );		\
	nAttr.setKeyable(1);				\
	nAttr.setReadable(1);				\
	nAttr.setWritable(1);				\
	nAttr.setStorable(1);				\
	aTransparency = nAttr.create( "transparency", "t", MFnNumericData::kFloat); \
	nAttr.setDefault(0.5f);						\
	nAttr.setKeyable(1);						\
	nAttr.setReadable(1);						\
	nAttr.setWritable(1);						\
	nAttr.setStorable(1);						\
	nAttr.setMin(0.0f);						\
	nAttr.setMax(1.0f);						\
	aBackAlpha = nAttr.create( "backAlpha", "ba", MFnNumericData::kFloat); \
	nAttr.setDefault(0.2f);						\
	nAttr.setKeyable(1);						\
	nAttr.setReadable(1);						\
	nAttr.setWritable(1);						\
	nAttr.setStorable(1);						\
	nAttr.setMin(0.0f);						\
	nAttr.setMax(1.0f);						\
	aLineWidth = nAttr.create( "lineWidth", "lw", MFnNumericData::kInt); \
	nAttr.setDefault(1.0f);						\
	nAttr.setKeyable(1);						\
	nAttr.setReadable(1);						\
	nAttr.setWritable(1);						\
	nAttr.setStorable(1);						\
	nAttr.setMin(1.0f);						\
	nAttr.setMax(10.0f);						\
	aDrawType = enumAttr.create( "drawType" , "dt");		\
	enumAttr.addField("wireframe", 0);				\
	enumAttr.addField("shaded", 1);					\
	enumAttr.addField("normal", 2);					\
	enumAttr.setHidden(false);					\
	enumAttr.setKeyable(true);					\
	enumAttr.setDefault(2);						\
 	addAttribute(aColor);						\
 	addAttribute(aRotate);						\
	addAttribute(aTransparency);					\
	addAttribute(aBackAlpha);					\
	addAttribute(aLineWidth);					\
	addAttribute(aDrawType);					\
	} while (0)
									
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
};

#endif
