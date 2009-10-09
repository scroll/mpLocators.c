#include "mpCurvedArrow.h"
#include <maya/MFnDagNode.h>

const MTypeId mpCurvedArrow::nodeId( 0x87117 );
const MString mpCurvedArrow::nodeName( "mpCurvedArrow" );

MObject mpCurvedArrow::aColor;
MObject mpCurvedArrow::aTransparency;
MObject mpCurvedArrow::aBackAlpha;
MObject mpCurvedArrow::aRotate;
MObject mpCurvedArrow::aLineWidth;
MObject mpCurvedArrow ::aDrawType;

void mpCurvedArrow::draw( M3dView & view, const MDagPath & path,
M3dView::DisplayStyle style, M3dView::DisplayStatus status )
{
    MObject thisNode = thisMObject();
	float r, g, b, a;
    float rotx, roty, rotz, ba;
    int lw, dt;
    MObject color;
    MObject rotate;
    //drawType
    MPlug drPlug = MPlug( thisNode, aDrawType );
    drPlug.getValue( dt );
    _COMMON_ATTR_READ_;

    view.beginGL();
    glPushMatrix();
	glRotatef(rotx ,1.0,0.0,0.0);
	glRotatef(roty ,0.0,1.0,0.0);
	glRotatef(rotz ,0.0,0.0,1.0);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    //draw Infront
	glDepthFunc(GL_LESS);
    glColor4f( r, g, b, a );
    drawStyle(style, dt, lw);
    //draw Behind
    glDepthFunc(GL_GREATER);
    glColor4f( r, g, b, ba );
    drawStyle(style, dt, lw);
    
    glPopAttrib();
    glPopMatrix();
    view.endGL();
}

MBoundingBox mpCurvedArrow::boundingBox() const
{   
    MPoint corner1(-1, 0.6, 1);
    MPoint corner2(1, 0, -1);
	MBoundingBox bbox = MBoundingBox( corner1, corner2 );
    return bbox;
}

void *mpCurvedArrow::creator()
{
    return new mpCurvedArrow();
}

MStatus mpCurvedArrow::initialize()
{
    MFnNumericAttribute nAttr;
	MFnEnumAttribute enumAttr;
    _COMMON_ATTR_INIT_;
    aDrawType = enumAttr.create( "drawType" , "dt");		
	enumAttr.addField("wireframe", 0);				
	enumAttr.addField("shaded", 1);				
	enumAttr.addField("normal", 2);					
	enumAttr.setHidden(false);					
	enumAttr.setKeyable(true);					
	enumAttr.setDefault(2);						
    addAttribute(aDrawType);
    return MS::kSuccess;
}

void mpCurvedArrow::drawShaded()
{
    unsigned int idx;
    glBegin (GL_TRIANGLES);
    for (idx = 0; idx < crvdArrwTriSize; idx ++) {
        unsigned int id = crvdArrwTriangleIds[idx];
        glVertex3d(curvedArrowVerts[id][0],curvedArrowVerts[id][1],curvedArrowVerts[id][2]);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (idx = 0; idx < 7; idx ++ ) {
        unsigned int id = qs1[idx];
        glVertex3d(curvedArrowVerts[id][0],curvedArrowVerts[id][1],curvedArrowVerts[id][2]);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (idx = 6; idx < 13; idx ++ ) {
        unsigned int id = qs1[idx];
        glVertex3d(curvedArrowVerts[id][0],curvedArrowVerts[id][1],curvedArrowVerts[id][2]);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (idx = 12; idx < 19; idx ++ ) {
        unsigned int id = qs1[idx];
        glVertex3d(curvedArrowVerts[id][0],curvedArrowVerts[id][1],curvedArrowVerts[id][2]);
    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (idx = 18; idx < 26; idx ++ ) {
        unsigned int id = qs1[idx];
        glVertex3d(curvedArrowVerts[id][0],curvedArrowVerts[id][1],curvedArrowVerts[id][2]);
    }
    glEnd();
}

void mpCurvedArrow::drawWireframe(float lw)
{
    unsigned int idx;
    glLineWidth(lw);
    glBegin (GL_LINE_LOOP);
    for (idx = 0; idx < crvdArrwVertSize; idx ++ ){
        glVertex3d(curvedArrowVerts[idx][0],curvedArrowVerts[idx][1],curvedArrowVerts[idx][2]);
    }
    glEnd();
}

