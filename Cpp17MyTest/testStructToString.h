#ifndef TEST_STRUCT_TO_STRING_H
#define TEST_STRUCT_TO_STRING_H

#include <iostream>
#include <string>
#include <vector>

#include "structToString.h"

void test_structToString() {

	Face face;
	face.faceNum = 2;
	face.isSmile[0] = true;
	face.xmin[0] = 20;
	face.xmax[0] = 80;
	face.ymin[0] = 25;
	face.ymax[0] = 98;

	face.isSmile[1] = false;
	face.xmin[1] = 50;
	face.xmax[1] = 150;
	face.ymin[1] = 100;
	face.ymax[1] = 210;

	std::string str = "";
	RunningState ret = faceToString(face, str);
	if (ret != RunningState::Running_OK) {
		return;
	}

	printFaceInfo(face);
	std::cout << str << std::endl;

	Face face2;
	ret = stringToFace(str, face2);
	if (ret != RunningState::Running_OK) {
		return;
	}
	printFaceInfo(face2);

}

#endif

