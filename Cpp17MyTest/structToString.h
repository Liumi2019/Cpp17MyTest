#ifndef STRUCT_TO_STRING_H
#define STRUCT_TO_STRING_H

#include <iostream>
#include <string>
#include <vector>

extern "C" {

#define FACE_MAX_NUMBER 50

struct Face {
	int faceNum;
	bool isSmile[FACE_MAX_NUMBER];
	int xmin[FACE_MAX_NUMBER];
	int xmax[FACE_MAX_NUMBER];
	int ymin[FACE_MAX_NUMBER];
	int ymax[FACE_MAX_NUMBER];
};

}

// 定义返回值说明
enum class RunningState {
	Running_ERROR = -1,
	Running_OK = 0
};

RunningState splitStr(const std::string& str, const std::string& pattern, std::vector<std::string>& strVec);

RunningState faceToString(const Face& face, std::string& str);

RunningState stringToFace(const std::string& str, Face& face);

RunningState printFaceInfo(const Face& face);

#endif // !STRUCT_TO_STRING_H
