#include "bmp.h"
#include "obj.h"

int main(){

	BMP bmp(700, 900, 0);
	OBJ bunny("bunny.obj");

	for (int i = 0; i < bunny.face.size();i++){
		bmp.drawTriangle(
			(bunny.vertex[bunny.face[i].x].x * 1000 + 100)*4,
			900-(bunny.vertex[bunny.face[i].x].y * 1000)*4,
			(bunny.vertex[bunny.face[i].y].x * 1000 + 100)*4,
			900 - (bunny.vertex[bunny.face[i].y].y * 1000) * 4,
			(bunny.vertex[bunny.face[i].z].x * 1000 + 100)*4,
			900 - (bunny.vertex[bunny.face[i].x].y * 1000) * 4,
			255, 255, 255
		);
	}
	
	bmp.write();

    return 0;
}