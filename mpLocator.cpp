#include "mpLocator.h"

// MObject mpLocator::aColor;
// MObject mpLocator::aTransparency;
// MObject mpLocator::aBackAlpha;
// MObject mpLocator::aRotate;
// MObject mpLocator::aLineWidth;
// MObject mpLocator::aDrawType;

bool mpLocator::isBounded() const
{
    return true;
}

bool mpLocator::drawLast() const
{
    return true;
}

void mpLocator::drawStyle(M3dView::DisplayStyle style,
                      int drawType , float lw)
{
    if (style != M3dView::kFlatShaded || style != M3dView::kGouraudShaded)
        drawWireframe(lw);
    else if (drawType)
        drawShaded();
    else if (!drawType)
        drawWireframe(lw);
    // else
    //     drawShaded();
}

    
void mpLocator::drawShaded()
{
    glEnable (GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
}

void mpLocator::drawWireframe(float lw)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(lw);
}

// MStatus mpLocator::initialize()
// {
// 	MFnNumericAttribute nAttr;
// 	MFnEnumAttribute enumAttr;

// 	aColor = nAttr.createColor( "color", "col" );
// 	nAttr.setDefault( 0.1, 0.1, 0.8 );
// 	nAttr.setKeyable(1);
// 	nAttr.setReadable(1);
// 	nAttr.setWritable(1);
// 	nAttr.setStorable(1);
// 	nAttr.setMin(0, 0, 0);
// 	nAttr.setMax(1, 1, 1);

// 	aRotate = nAttr.createPoint( "rotate", "rot" );
// 	nAttr.setDefault( 0.0, 0.0, 0.0 );
// 	nAttr.setKeyable(1);
// 	nAttr.setReadable(1);
// 	nAttr.setWritable(1);
// 	nAttr.setStorable(1);
	
// 	aTransparency = nAttr.create( "transparency", "t", MFnNumericData::kDouble);
// 	nAttr.setDefault(0.5f);
// 	nAttr.setKeyable(1);
// 	nAttr.setReadable(1);
// 	nAttr.setWritable(1);
// 	nAttr.setStorable(1);
// 	nAttr.setMin(0.0f);
// 	nAttr.setMax(1.0f);

// 	aBackAlpha = nAttr.create( "backAlpha", "ba", MFnNumericData::kDouble);
// 	nAttr.setDefault(0.2f);
// 	nAttr.setKeyable(1);
// 	nAttr.setReadable(1);
// 	nAttr.setWritable(1);
// 	nAttr.setStorable(1);
// 	nAttr.setMin(0.0f);
// 	nAttr.setMax(1.0f);

// 	aLineWidth = nAttr.create( "lineWidth", "lw", MFnNumericData::kInt);
// 	nAttr.setDefault(1.0f);
// 	nAttr.setKeyable(1);
// 	nAttr.setReadable(1);
// 	nAttr.setWritable(1);
// 	nAttr.setStorable(1);
// 	nAttr.setMin(1.0f);
// 	nAttr.setMax(10.0f);

// 	aDrawType = enumAttr.create( "drawType" , "dt");
// 	enumAttr.addField("wireframe", 0);
// 	enumAttr.addField("shaded", 1);
// 	enumAttr.addField("normal", 2);
// 	enumAttr.setHidden(false);
// 	enumAttr.setKeyable(true);
// 	enumAttr.setDefault(2);

//  	addAttribute(aColor);
//  	addAttribute(aRotate);
// 	addAttribute(aTransparency);
// 	addAttribute(aBackAlpha);
// 	addAttribute(aLineWidth);
// 	addAttribute(aDrawType);
// }
