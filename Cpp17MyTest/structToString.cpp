#include <iostream>
#include <string>
#include <vector>

#include "structToString.h"

RunningState splitStr(const std::string& str, const std::string& pattern, std::vector<std::string>& strVec)
{
	 if (str == "") {
		 return RunningState::Running_ERROR;
	}
		
	std::string strs = str + pattern;
	size_t pos = strs.find(pattern);

	while (pos != strs.npos)
	{
		std::string temp = strs.substr(0, pos);
		if (temp.size() > 0) strVec.push_back(temp);
		strs = strs.substr(pos + 1, strs.size());
		pos = strs.find(pattern);
	}

	return RunningState::Running_OK;
}


RunningState faceToString(const Face& face, std::string& str) {
	if (face.faceNum < 1 || face.faceNum > 50) {
		str = "";
		return RunningState::Running_OK;
	}

	std::string separator = ",";
	str = "face," + std::to_string(face.faceNum) + separator;
	for (int i = 0; i < face.faceNum; i++) {
		str += (face.isSmile[i] ? "1" : "0") + separator;
		str += std::to_string(face.xmin[i]) + separator;
		str += std::to_string(face.xmax[i]) + separator;
		str += std::to_string(face.ymin[i]) + separator;
		if (i == face.faceNum - 1) {
			str += std::to_string(face.ymax[i]);
		} else {
			str += std::to_string(face.ymax[i]) + separator;
		}
	}
	return RunningState::Running_OK;
}


RunningState stringToFace(const std::string& str, Face& face) {
	face.faceNum = 0;
	if (str.empty()) {
		return RunningState::Running_ERROR;
	}

	std::string separator = ",";
	std::vector<std::string> strVec;
	RunningState ret = splitStr(str, separator, strVec);
	if (ret != RunningState::Running_OK || strVec[0] != "face") {
		return RunningState::Running_ERROR;
	}
	face.faceNum = std::stoi(strVec[1]);

	const int faceSize = 5;
	if (face.faceNum < 1 || strVec.size() != face.faceNum * faceSize + 2) {
		face.faceNum = 0;
		return RunningState::Running_ERROR;
	}

	for (int i = 0; i < face.faceNum; i++) {
		face.isSmile[i] = (strVec[i * faceSize + 2] == "1");
		face.xmin[i] = std::stoi(strVec[i * faceSize + 3]);
		face.xmax[i] = std::stoi(strVec[i * faceSize + 4]);
		face.ymin[i] = std::stoi(strVec[i * faceSize + 5]);
		face.ymax[i] = std::stoi(strVec[i * faceSize + 6]);
	}

	return RunningState::Running_OK;
}

RunningState printFaceInfo(const Face& face)
{
	if (face.faceNum < 1) {
		std::cout << "face is empty" << std::endl;
		return RunningState::Running_ERROR;
	}

	std::cout << "face: " << face.faceNum << std::endl;
	std::string fillSpace = "  : ";
	for (int i = 0; i < face.faceNum; i++) {
		std::cout << "-- " << i + 1 << ":" << std::endl;
		std::cout << fillSpace << face.xmin[i] << std::endl;
		std::cout << fillSpace << face.xmax[i] << std::endl;
		std::cout << fillSpace << face.ymin[i] << std::endl;
		std::cout << fillSpace << face.ymax[i] << std::endl;
	}
	return RunningState::Running_OK;
}
