#pragma once
#include "point.h"
#include <fstream>
#include <string>
#include <vector>

class OBJ{
private:
	std::ifstream ifs;
	
public:
	std::vector<Point3d>vertex;
	std::vector<Point3i>face;
	OBJ(const std::string &filename);
	void read(const std::string &filename);
};