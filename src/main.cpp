#include <string>
#include <math.h>
#include <iostream>
#include <unistd.h>

#include "MeshRetile.h"
#include "ObjIO.h"
#include "RetileSurface.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;

void printUsage()
{
    cout << "The retile program performs retiling on an input mesh.\n\n";

    cout << "USAGE:\n"
    "retile [OPTIONS] FILE\n\n";

    cout << "FILE\tinput geometry filename (OBJ format)\n\n";

    cout << "OPTIONS:\n"
            "-o FILE\toutput geometry filename (default: output.obj)\n"
            "-i N\tnumber of iterations for redistribution (default: 20)\n"
            "-v N\ttarget number of output vertices (default: same as input mesh -- ignored if -f option is specified)\n"
            "-f F\tfactor for the target number of output vertices, based on the number of vertices in the input geometry (default: 1.0)\n\n";
}

int main(int argc, char* argv[])
{
    /// Process arguments ///

    // At least one argument required (the input file)
    if (argc < 2)
    {
        printUsage();
        return -1;
    }

    // Default parameters
    string inputFilename, outputFilename("output.obj");
    int iterationCount = 20, targetVertexCount = -1;
    float targetVertexCountFactor = 1.f;
    bool factorIsProvided = false;

    // Set the parameters based on the provided options
    int c;
    while ((c = getopt (argc, argv, "o:i:v:f:")) != -1)
      switch (c)
        {
        case 'o':
          outputFilename = optarg;
          break;
        case 'i':
          iterationCount = atoi(optarg);
          break;
        case 'v':
          targetVertexCount = atoi(optarg);
          break;
      case 'f':
        targetVertexCountFactor = atof(optarg);
        factorIsProvided = true;
        break;
        case '?':
          if (optopt == 'o' || optopt == 'i' || optopt == 'v' || optopt == 'f')
            fprintf (stderr, "Option -%c requires an argument.\n", optopt);
          else if (isprint (optopt))
            fprintf (stderr, "Unknown option `-%c'.\n", optopt);
          else
            fprintf (stderr,
                     "Unknown option character `\\x%x'.\n",
                     optopt);
          return 1;
        default:
          abort();
        }

    // Ignore absolute number of target output vertices if a factor has been provided
    if (factorIsProvided)
        targetVertexCount = -1;

    // Should be just one more argument at the end (the input file)
    if (optind == argc)
    {
        cerr << "Missing argument. To view usage, call with no argument.\n";
        return 1;
    }
    else if (optind < argc - 1)
    {
        cerr << "Too many arguments. To view usage, call with no argument.\n";
        return 1;
    }
    else
    {
        inputFilename = argv[optind];
    }

    cout << "============================== RETILING ==============================" << endl;
    cout << "Input file: " << inputFilename << endl;
    cout << "Output file: " << outputFilename << endl;
    cout << "Number of iterations: " << iterationCount << endl;
    cout << "Number of output vertices: ";
    if (targetVertexCount == -1)
        cout << targetVertexCountFactor << " (factor)";
    else
        cout << targetVertexCount;
    cout << endl;
    cout << "======================================================================" << endl;
    /////////////////////////

    dk::MeshRetile *inMesh= dk::io::importFromObjFile(inputFilename);
    dk::io::testObjFile();

    MeshEx *mx = new MeshEx(inMesh);

    delete inMesh;

    //    dk::io::testFile();

    int numPoints = targetVertexCount == -1 ? (int)(mx->getMesh()->vertices.size() * targetVertexCountFactor) : targetVertexCount;
    cout << "Input mesh vertex count: " << mx->getMesh()->vertices.size() << endl;
    cout << "Output mesh target vertex count: " << numPoints << endl;
    cout << "======================================================================" << endl;

    std::cout << "Retiling mesh ..... " << std::endl;
    RetileSurface retile(iterationCount);
    RetileSurface::ConstrainedVertexSet cvs;

    // perform retiling of the mesh
    retile.retile( mx, numPoints, cvs );

    std::cout << "Finish Retiling mesh ..... " << std::endl;
    {
        std::cout << "Saving file ..... " << std::endl;
        dk::MeshRetile *outMesh = mx->getMesh();
        std::cout << "CREATIN SAVING MESH ..... " << std::endl;
//        dk::io::exportToObjFile( outMesh, "/prod/r_d/jguzman/examples/Texturing/GregTurkretile/sphere_result_500V.obj");
//        std::string outputFileName ="/prod/r_d/jguzman/examples/Texturing/GregTurkretile/Simulations/MeshResult/Fluid_1_L0.obj";
        dk::io::exportToObjFile( outMesh, outputFilename);
        std::cout << "SAVING file [" << outputFilename <<"] Number of points: " << numPoints<< " DONE ..... "<< std::endl;
        delete outMesh;
    }

    std::cout << "Done ..... " << std::endl;
    delete mx;


    return 0;
}
