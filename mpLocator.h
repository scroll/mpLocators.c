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
 	addAttribute(aColor);						\
 	addAttribute(aRotate);						\
	addAttribute(aTransparency);					\
	addAttribute(aBackAlpha);					\
	addAttribute(aLineWidth);					\
	} while (0)

#define _COMMON_ATTR_READ_				\
	do {						\
	MPlug lwPlug = MPlug(thisNode, aLineWidth );	\
	lwPlug.getValue( lw );				\
	MPlug rPlug = MPlug( thisNode , aRotate);	\
	rPlug.getValue( rotate );			\
	MFnNumericData rotatedata( rotate );		\
	rotatedata.getData( rotx, roty, rotz );		\
	MPlug tPlug = MPlug( thisNode, aTransparency );	\
	tPlug.getValue( a );				\
	MPlug baPlug = MPlug( thisNode, aBackAlpha );	\
	baPlug.getValue( ba );				\
	MPlug cPlug = MPlug( thisNode, aColor );	\
	cPlug.getValue( color );			\
	MFnNumericData colordata( color );		\
	colordata.getData( r, g, b );			\
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
	virtual void drawShaded();
	virtual void drawWireframe(float lw);
};

#endif
