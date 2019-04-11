#pragma once
#include <string>
#include <vector>

class FileReader {
public:
	FileReader();
	~FileReader();

	static std::vector<std::string> readDir(std::string path);

private:
	static std::vector<std::string> readDir(std::string path, int depth);
};

