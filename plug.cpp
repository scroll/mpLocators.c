#include "mpBox.h"
#include <maya/MFnPlugin.h>

// Initialize and UnInitialize the plugin

MStatus initializePlugin( MObject obj )
{ 
	MStatus   status;
	MFnPlugin plugin( obj, "Marin Petrov", "0.1", "Any");

    //------------BOX LOCATOR-------------//
	status = plugin.registerNode( mpBox::nodeName, mpBox::nodeId, 
						 &mpBox::creator, &mpBox::initialize,
						 MPxNode::kLocatorNode );
	if (!status) {
		status.perror("could not register mpBox");
		return status;
	}
	return status;
}

MStatus uninitializePlugin( MObject obj)
{
	MStatus   status;
	MFnPlugin plugin( obj );

	status = plugin.deregisterNode( mpBox::nodeId );
	if (!status) {
		status.perror("could not deregister mpBox");
		return status;
	}

	return status;
}
