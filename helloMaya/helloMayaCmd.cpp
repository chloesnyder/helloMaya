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
#include <maya/MSyntax.h>
#include <maya/MItDag.h>
#include <maya/MArgDatabase.h>
#define EXPORT _declspec(dllexport)
#define NFLAG "-n"
#define NFLAGLONG "-name"
#define IDENTFLAG "-i"
#define IDENTFLAGLONG "-id"
#define TESTFLAG "-i"
#define TESTFLAGLONG "-identifier"



// Use helper macro to register a command with Maya.  It creates and
// registers a command that does not support undo or redo.  The 
// created class derives off of MPxCommand.
//
//DeclareSimpleCommand( helloMaya, "", "2015");

class helloMaya : public MPxCommand
{
public:
	//http://download.autodesk.com/global/docs/mayasdk2012/en_us/index.html?url=files/Command_plugins_Flags.htm,topicNumber=d28e2752
	static MSyntax newSyntax() {
		MSyntax syntax;
		syntax.addFlag(TESTFLAG, TESTFLAGLONG, MSyntax::kLong);
		syntax.addFlag(NFLAG, NFLAGLONG, MSyntax::kString);
		syntax.addFlag(IDENTFLAG, IDENTFLAGLONG, MSyntax::kLong);
		return syntax;
	}

		virtual MStatus helloMaya::doIt(const MArgList& args)
	{
		MStatus status;
		MString name = "";
		int id = 0;


		MArgDatabase parser(syntax(), args, &status);
		if (status != MS::kSuccess)
		{
			return status;
		}

		if (parser.isFlagSet(TESTFLAG))
		{
			parser.getFlagArgument(TESTFLAG, 0, id);
		}

		if (parser.isFlagSet(NFLAG))
		{
			parser.getFlagArgument(NFLAG, 0, name);
		}


		MString dialogBox = "confirmDialog -message \"name: " + name + "\\nID: " + id + "\" -button \"OK\" -title \"Hello World\";";

		MStatus stat = MGlobal::executeCommand(dialogBox);
		MGlobal::displayInfo("Hello World\n");
		setResult("helloMaya command executed!\n");
		const MStatus failed = MS::kFailure;
		const MStatus success = MS::kSuccess;
		if (stat == failed)
		{
			MGlobal::displayError("error");
			return MS::kFailure;
		}
		if (stat == success)
			return MStatus::kSuccess;


		return status;
	}
	static void *creator() { return new helloMaya; }

};

// Initialize Plugin upon loading
EXPORT MStatus initializePlugin(MObject obj)
{
	MStatus stat;
	MFnPlugin plugin(obj, "CIS660", "1.0", "Any");
	stat = plugin.registerCommand("helloMaya", helloMaya::creator, helloMaya::newSyntax);
	if (!stat) stat.perror("registerCommand failed");
	return stat;
}
// Cleanup Plugin upon unloading
EXPORT MStatus uninitializePlugin(MObject obj)
{
	MStatus stat;
	MFnPlugin plugin(obj);
	stat = plugin.deregisterCommand("helloMaya");
	if (!stat) stat.perror("deregisterCommand failed");
	return stat;
}