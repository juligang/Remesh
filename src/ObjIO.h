/*---------------------------------------------------------------------

ObjIO offers import and export support for obj files.

Obj files are very simple ascii based mesh description files which store
vertices, normals and texturecoordinates of n-polygonal meshes.
The format was originally developed by AliasWavefront a long time ago.
Despite being a little out of age it is very well known and supported
throught the industry.

----------------------------------------------------------------------*/
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

#include "Math.h"
#include "StringManip.h"
#include "MeshRetile.h"

namespace dk
{
	///
	/// \brief offers functions for reading and writing object files from and to disk
	///
	namespace io
	{
        MeshRetile          *importFromObjFile( std::string fileName );  ///< reads and creates a MeshRetile from the given *.obj file. returns 0 if it fails
        void exportToObjFile( MeshRetile *mesh, std::string fileName );  ///< creates and writes a Obj file from the given mesh
        void testObjFile();
	} // namespace io
} // namespace dk
