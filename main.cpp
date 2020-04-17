#include "lib/lib.h"
#include "lib/statics.h"
#include "lib/udf.h"

int main()
{
	unsigned NEL_Y = 100+1; float DY = 0.1f;
	unsigned NEL_X = 2+1; float DX = 0.5f;
	unsigned NEL_Z = 2+1; float DZ = 0.5f;
	structuredHexMesh MyCube("Root Mesh", NEL_X, NEL_Y, NEL_Z);

	//Defining the mesh-surface that will be extruded later
	//with SweepFace to create a 3D hexaedral structured-mesh
	{
    		vec3 Surface[NEL_X*NEL_Z];

    		for (int j=0; j<NEL_Z; j++) {
        		for (int i=0; i<NEL_X; i++) {

            			Surface[NEL_X*j+i] = vec3(DX*(float)i, 0.0f, DZ*(float)j);
        		}
    		}

	    	int vertexNEL = sizeof(Surface)/sizeof(vec3);
		float radius = 1000000.0f;
//		MyCube.SweepFace(Surface, NEL_X, NEL_Z, NEL_Y-1, PI/(float) (NEL_Y-1), vec3(-1000.0f,0.0f,0.0f));
		MyCube.SweepFace(Surface, NEL_X, NEL_Z, NEL_Y-1, DY/radius, vec3(-1.0f*radius,0.0f,0.0f));
	}	
		
	vec3 offset{-0.5f, -5.0f, -0.5f};
	MyCube.DisplaceMesh( offset );
	for(unsigned int i = 0; i<MyCube.Log_Cells_Max(); ++i) {
		MyCube.loadVertexId(i);
		MyCube.CenterC8();
		//MyCube.LogMembers();
		//MyCube.Log_Cell();
	}

	MyCube.LogMembers();

	Window window("samuel Engine v0.0", 1600,720);
	while (!window.closed())
	{
		//MyCube.RotateXMesh(0.01f);
		//MyCube.RotateYMesh(0.01f);
		MyCube.RotateZMesh(0.01f);

		window.update(&MyCube);
		system("sleep 0.01");
		//window.display();
	}
	
	return 0;
}	

