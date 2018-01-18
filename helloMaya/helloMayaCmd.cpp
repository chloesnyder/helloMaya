//
// Copyright (C) 
// 
// File: helloMayaCmd.cpp
//
// MEL Command: helloMaya
//
// Author: Maya Plug-in Wizard 2.0
//

// Includes everything needed to register a simple MEL command with Maya.
// 
#include <maya/MSimple.h>
#include <maya/MGlobal.h>

// Use helper macro to register a command with Maya.  It creates and
// registers a command that does not support undo or redo.  The 
// created class derives off of MPxCommand.
//
DeclareSimpleCommand( helloMaya, "", "2015");

MStatus helloMaya::doIt( const MArgList& args )
//
//	Description:
//		implements the MEL helloMaya command.
//
//	Arguments:
//		args - the argument list that was passes to the command from MEL
//
//	Return Value:
//		MS::kSuccess - command succeeded
//		MS::kFailure - command failed (returning this value will cause the 
//                     MEL script that is being run to terminate unless the
//                     error is caught using a "catch" statement.
//
{

	MString dialogBox = "confirmDialog -message \"name:  id:\" -button \"OK\" -title \"Hello World\";";	//"confirmDialog -title \"Hello World!\" -message \"name: +";

	MStatus stat = MGlobal::executeCommand(dialogBox);//MS::kSuccess;

	// Since this class is derived off of MPxCommand, you can use the 
	// inherited methods to return values and set error messages
	//
	MGlobal::displayInfo("Hello World\n");
	setResult( "helloMaya command executed!\n" );
	const MStatus failed = MS::kFailure;
	const MStatus success = MS::kSuccess;
	if (stat == failed)
	{
		MGlobal::displayError("error");
		return MS::kFailure;
	}
	if (stat == success)
		return MStatus::kSuccess;
	

	return stat;
}
