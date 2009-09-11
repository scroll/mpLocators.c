#include "mpBox.h"
#include <maya/MFnDagNode.h>

const MTypeId mpBox::nodeId( 0x87119 );
const MString mpBox::nodeName( "mpBox" );

MObject mpBox::aColor;
MObject mpBox::aTransparency;
MObject mpBox::aBackAlpha;
MObject mpBox::aRotate;
MObject mpBox::aLineWidth;
MObject mpBox ::aDrawType;

MObject mpBox::aXsize;
MObject mpBox::aYsize;
MObject mpBox::aZsize;

void mpBox::draw( M3dView & view, const MDagPath & path,
M3dView::DisplayStyle style, M3dView::DisplayStatus status )
{
    MObject thisNode = thisMObject();
	float r, g, b, a;
    float rotx, roty, rotz;
    float ba, xsize, ysize, zsize;
    int lw, dt;
    MObject color;
    MObject rotate;
    //lineWidth
    MPlug lwPlug = MPlug(thisNode, aLineWidth );
    lwPlug.getValue( lw );
    //rotate
    MPlug rPlug = MPlug( thisNode , aRotate);
    rPlug.getValue( rotate );
    MFnNumericData rotatedata( rotate ); 
	rotatedata.getData( rotx, roty, rotz );
    //transparency
    MPlug tPlug = MPlug( thisNode, aTransparency );
    tPlug.getValue( a );
    //backAlpha
    MPlug baPlug = MPlug( thisNode, aBackAlpha );
    baPlug.getValue( ba );
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
    //color
	MPlug cPlug = MPlug( thisNode, aColor );
    cPlug.getValue( color ); 
	MFnNumericData colordata( color ); 
	colordata.getData( r, g, b );

    view.beginGL();
    glPushMatrix();
	glRotatef(rotx ,1.0,0.0,0.0);
	glRotatef(roty ,0.0,1.0,0.0);
	glRotatef(rotz ,0.0,0.0,1.0);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDepthFunc(GL_LESS);
    glColor4f( r, g, b, a );
    
    drawStyle(style, dt, lw);
    drawCube(xsize, ysize, zsize);
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

	aColor = nAttr.createColor( "color", "col" );
	nAttr.setDefault( 0.1, 0.1, 0.8 );
	nAttr.setKeyable(1);
	nAttr.setReadable(1);
	nAttr.setWritable(1);
	nAttr.setStorable(1);
	nAttr.setMin(0, 0, 0);
	nAttr.setMax(1, 1, 1);

	aRotate = nAttr.createPoint( "rotate", "rot" );
	nAttr.setDefault( 0.0, 0.0, 0.0 );
	nAttr.setKeyable(1);
	nAttr.setReadable(1);
	nAttr.setWritable(1);
	nAttr.setStorable(1);
	
	aTransparency = nAttr.create( "transparency", "t", MFnNumericData::kDouble);
	nAttr.setDefault(0.5f);
	nAttr.setKeyable(1);
	nAttr.setReadable(1);
	nAttr.setWritable(1);
	nAttr.setStorable(1);
	nAttr.setMin(0.0f);
	nAttr.setMax(1.0f);

	aBackAlpha = nAttr.create( "backAlpha", "ba", MFnNumericData::kDouble);
	nAttr.setDefault(0.2f);
	nAttr.setKeyable(1);
	nAttr.setReadable(1);
	nAttr.setWritable(1);
	nAttr.setStorable(1);
	nAttr.setMin(0.0f);
	nAttr.setMax(1.0f);

	aLineWidth = nAttr.create( "lineWidth", "lw", MFnNumericData::kInt);
	nAttr.setDefault(1.0f);
	nAttr.setKeyable(1);
	nAttr.setReadable(1);
	nAttr.setWritable(1);
	nAttr.setStorable(1);
	nAttr.setMin(1.0f);
	nAttr.setMax(10.0f);

	aDrawType = enumAttr.create( "drawType" , "dt");
	enumAttr.addField("wireframe", 0);
	enumAttr.addField("shaded", 1);
	enumAttr.addField("normal", 2);
	enumAttr.setHidden(false);
	enumAttr.setKeyable(true);
	enumAttr.setDefault(2);

 	addAttribute(aColor);
 	addAttribute(aRotate);
	addAttribute(aTransparency);
	addAttribute(aBackAlpha);
	addAttribute(aLineWidth);
	addAttribute(aDrawType);

    // add the custom attributes for mpBox  //
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

    addAttribute(aXsize);
	addAttribute(aYsize);
	addAttribute(aZsize);

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

