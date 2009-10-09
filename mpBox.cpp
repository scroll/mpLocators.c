#include "mpBox.h"
#include <maya/MFnDagNode.h>

const MTypeId mpBox::nodeId( 0x87119 );
const MString mpBox::nodeName( "mpBox" );

MObject mpBox::aColor;
MObject mpBox::aTransparency;
MObject mpBox::aBackAlpha;
MObject mpBox::aRotate;
MObject mpBox::aLineWidth;
MObject mpBox::aXsize;
MObject mpBox::aYsize;
MObject mpBox::aZsize;
MObject mpBox ::aDrawType;

void mpBox::draw( M3dView & view, const MDagPath & path,
M3dView::DisplayStyle style, M3dView::DisplayStatus status )
{
    float xsize, ysize, zsize;
    MObject thisNode = thisMObject();
	float r, g, b, a;
    float rotx, roty, rotz, ba;
    int lw, dt;
    MObject color;
    MObject rotate;
    _COMMON_ATTR_READ_;
    //zsize
    MPlug xsPlug = MPlug( thisNode, aXsize );
    xsPlug.getValue( xsize );
    //ysize
    MPlug ysPlug = MPlug( thisNode, aYsize );
    ysPlug.getValue( ysize );
    //zsize
    MPlug zsPlug = MPlug( thisNode, aZsize );
    zsPlug.getValue( zsize );
    //drawType
    MPlug drPlug = MPlug( thisNode, aDrawType );
    drPlug.getValue( dt );

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
    drawCube(xsize, ysize, zsize);
    //draw Behind
    glDepthFunc(GL_GREATER);
    glColor4f( r, g, b, ba );
    drawStyle(style, dt, lw);
    drawCube(xsize, ysize, zsize);
    
    glPopAttrib();
    glPopMatrix();
    view.endGL();
}

MBoundingBox mpBox::boundingBox() const
{   
    MObject thisNode = thisMObject();
    float x, y, z;
	MPlug xsize = MPlug( thisNode, aXsize );
    xsize.getValue(x);
    MPlug ysize = MPlug( thisNode, aYsize );
    ysize.getValue(y);
    MPlug zsize = MPlug( thisNode, aZsize );
    zsize.getValue(z);

    MPoint corner1(x, y, z);
    MPoint corner2(-x, -y, -z);
	MBoundingBox bbox = MBoundingBox( corner1, corner2 );

    return bbox;
}

void *mpBox::creator()
{
    return new mpBox();
}

MStatus mpBox::initialize()
{

	MFnNumericAttribute nAttr;
	MFnEnumAttribute enumAttr;
    // add the custom attributes for mpBox  //
    _COMMON_ATTR_INIT_;
    aXsize = nAttr.create( "xsize", "xsz", MFnNumericData::kFloat);
	nAttr.setDefault(0.5f);
	nAttr.setKeyable(1);
	nAttr.setReadable(1);
	nAttr.setWritable(1);
	nAttr.setStorable(1);

	aYsize = nAttr.create( "ysize", "ysz", MFnNumericData::kFloat);
	nAttr.setDefault(0.5f);
	nAttr.setKeyable(1);
	nAttr.setReadable(1);
	nAttr.setWritable(1);
	nAttr.setStorable(1);

	aZsize = nAttr.create( "zsize", "zsz", MFnNumericData::kFloat);
	nAttr.setDefault(0.5f);
	nAttr.setKeyable(1);
	nAttr.setReadable(1);
	nAttr.setWritable(1);
	nAttr.setStorable(1);
    
	aDrawType = enumAttr.create( "drawType" , "dt");		
	enumAttr.addField("wireframe", 0);				
	enumAttr.addField("shaded", 1);				
	enumAttr.addField("normal", 2);					
	enumAttr.setHidden(false);					
	enumAttr.setKeyable(true);					
	enumAttr.setDefault(2);						

    addAttribute(aXsize);
	addAttribute(aYsize);
	addAttribute(aZsize);
    addAttribute(aDrawType);

    return MS::kSuccess;
}

void mpBox::drawCube(float xsize, float ysize, float zsize)
{
    glBegin (GL_QUADS);
    glNormal3f (0.0, 0.0, zsize);
    glVertex3f (-xsize, -ysize, zsize);
    glVertex3f (xsize, -ysize, zsize);
    glVertex3f (xsize, ysize, zsize);
	glVertex3f (-xsize, ysize, zsize);

    glNormal3f (0.0, 0.0,-zsize);
    glVertex3f (-xsize, -ysize, -zsize);
    glVertex3f (-xsize, ysize, -zsize);
    glVertex3f (xsize, ysize, -zsize);
    glVertex3f (xsize, -ysize, -zsize);

    glNormal3f (0.0, ysize, 0.0);
    glVertex3f (-xsize, ysize, -zsize);
    glVertex3f (-xsize, ysize, zsize);
    glVertex3f (xsize, ysize, zsize);
    glVertex3f (xsize, ysize, -zsize);

    glNormal3f (0.0, -ysize, 0.0);
    glVertex3f (-xsize, -ysize, -zsize);
    glVertex3f (xsize, -ysize, -zsize);
    glVertex3f (xsize, -ysize, zsize);
    glVertex3f (-xsize, -ysize, zsize);

    glNormal3f (xsize, 0.0, 0.0);
    glVertex3f (xsize, -ysize, -zsize);
    glVertex3f (xsize, ysize, -zsize);
    glVertex3f (xsize, ysize, zsize);
    glVertex3f (xsize, -ysize, zsize);

    glNormal3f (-xsize, 0.0, 0.0);
    glVertex3f (-xsize, -ysize, -zsize);
    glVertex3f (-xsize, -ysize, zsize);
    glVertex3f (-xsize, ysize, zsize);
    glVertex3f (-xsize, ysize, -zsize);
    glEnd();
}
    
void mpBox::drawShaded()
{
    glEnable (GL_CULL_FACE);
    glPolygonMode(GL_FRONT, GL_FILL);
}

void mpBox::drawWireframe(float lw)
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(lw);
}

