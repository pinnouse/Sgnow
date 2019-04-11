#include "FileReader.h"
#include <filesystem>

namespace fs = std::filesystem;


FileReader::FileReader() {}


FileReader::~FileReader() {}

std::vector<std::string> FileReader::readDir(std::string path) {
	return readDir(path, 0);
}

std::vector<std::string> FileReader::readDir(std::string path, int depth) {
	std::vector <std::string> paths = {};
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_directory() && depth < 4) {
			std::vector <std::string> pathsDeeper = readDir(entry.path().generic_string(), depth + 1);
			for (std::string p : pathsDeeper) {
				paths.push_back(p);
			}
		} else if (entry.is_regular_file()) {
			paths.push_back(entry.path().generic_string());
		}
	}
	return paths;
}