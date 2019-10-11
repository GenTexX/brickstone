#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

class FileHandler {
private:
	std::string m_Filename;
	std::fstream m_File;
public:
	FileHandler();
	FileHandler(const std::string& path, bool create = false);
	~FileHandler();

	void setPath(const std::string& path);

	std::string read();												//read whole file
	std::string read(std::size_t beg, std::size_t end = 0);			//read from start to end (end = 0 --> read to eof)
	std::string readLine();											//endOfFile = "\z"

	void write(const std::string&);
	void append(const std::string&);

};