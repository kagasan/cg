#include "bmp.h"
#include "obj.h"

#include <algorithm>
#include <cmath>

int main(){

	BMP bmp(700, 900, 0);
	OBJ bunny("bunny.obj");

	std::vector<std::pair<double, int> >zsort(bunny.face.size());
	for (int i = 0; i < bunny.face.size();i++){
		zsort[i].second = i;
		zsort[i].first = bunny.vertex[bunny.face[i].x].z;
		if (zsort[i].first > bunny.vertex[bunny.face[i].y].z){
			zsort[i].first = bunny.vertex[bunny.face[i].y].z;
		}
		if (zsort[i].first > bunny.vertex[bunny.face[i].z].z){
			zsort[i].first = bunny.vertex[bunny.face[i].z].z;
		}
	}
	sort(zsort.begin(), zsort.end());

	for (int z = 0; z < zsort.size();z++){
		int i = zsort[z].second;
		double x12 = bunny.vertex[bunny.face[i].y].x - bunny.vertex[bunny.face[i].x].x;
		double y12 = bunny.vertex[bunny.face[i].y].y - bunny.vertex[bunny.face[i].x].y;
		double z12 = bunny.vertex[bunny.face[i].y].z - bunny.vertex[bunny.face[i].x].z;
		double x23 = bunny.vertex[bunny.face[i].z].x - bunny.vertex[bunny.face[i].y].x;
		double y23 = bunny.vertex[bunny.face[i].z].y - bunny.vertex[bunny.face[i].y].y;
		double z23 = bunny.vertex[bunny.face[i].z].z - bunny.vertex[bunny.face[i].y].z;
		double xc = y12 * z23 - z12*y23;
		double yc = z12 * x23 - x12*z23;
		double zc = x12 * y23 - y12*x23;
		int r = 255 * std::abs(zc) / std::sqrt(xc*xc + yc*yc + zc*zc);
		int g = r;
		int b = r;
		if (0){
			g = 0;
			b = 0;
		}
		bmp.drawTriangle(
			(bunny.vertex[bunny.face[i].x].x * 1024 + 100)*4,
			900-(bunny.vertex[bunny.face[i].x].y * 1024)*4,
			(bunny.vertex[bunny.face[i].y].x * 1024 + 100)*4,
			900 - (bunny.vertex[bunny.face[i].y].y * 1024) * 4,
			(bunny.vertex[bunny.face[i].z].x * 1024 + 100)*4,
			900 - (bunny.vertex[bunny.face[i].z].y * 1024) * 4,
			r, g, b
		);
	}
	
	bmp.write("bunny.bmp");

    return 0;
}