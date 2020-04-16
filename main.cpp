#include "lib/lib.h"
#include "lib/statics.h"
#include "lib/udf.h"

int main()
{
	unsigned NEL_Y = 3+1;
	unsigned NEL_X = 2+1; double DX = 0.1;
	unsigned NEL_Z = 2+1; double DZ = 0.1;
	structuredHexMesh MyCube("Root Mesh", NEL_X, NEL_Y, NEL_Z);

	//Defining the mesh-surface that will be extruded later
	//with SweepFace to create a 3D hexaedral structured-mesh
	{
    		vec3 Surface[NEL_X*NEL_Z];

    		for (int j=0; j<NEL_Z; j++) {
        		for (int i=0; i<NEL_X; i++) {

            			Surface[NEL_X*j+i] = vec3(DX*(double)i, 0.0, DZ*(double)j);
        		}
    		}

	    	int vertexNEL = sizeof(Surface)/sizeof(vec3);
		MyCube.SweepFace(Surface, NEL_X, NEL_Z, NEL_Y-1,PI/(float) (NEL_Y-1), vec3(-0.5,0.0,0.0));
	}	
		
		
	for(int i = 0; i<MyCube.Log_Cells_Max(); i++) {
		MyCube.loadVertexId(i);
		//MyCube.LogMembers();
		MyCube.Log_Cell();
	}
	return 0;
}	

