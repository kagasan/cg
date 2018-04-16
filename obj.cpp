#include "obj.h"
#include <sstream>

OBJ::OBJ(const std::string &filename){
	read(filename);
}

void OBJ::read(const std::string &filename){
	vertex.resize(1);
	face.clear();
	ifs.open(filename);
	for (std::string line; getline(ifs, line);){
		if (line[0] == '#')continue;
		else if (line[0] == 'v'){
			std::stringstream ss;
			ss << line;
			char keyword;
			Point3d p;
			ss >> keyword >> p.x >> p.y >> p.z;
			vertex.push_back(p);
		}
		else if (line[0] == 'f'){
			std::stringstream ss;
			ss << line;
			char keyword;
			Point3i p;
			ss >> keyword >> p.x >> p.y >> p.z;
			face.push_back(p);
		}
	}
}