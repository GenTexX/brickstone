#include "FileHandler.h"

FileHandler::FileHandler() {



}

FileHandler::FileHandler(const std::string& path, bool create) : _filename(path) {
	if (create) {
		this->_file.open(path, std::fstream::out);
	} else {
		this->_file.open(path, std::fstream::in | std::fstream::out);
	}

}

FileHandler::~FileHandler() {


	this->_file << std::fflush;
	this->_file.close();

}

void FileHandler::setPath(const std::string& path) {

	this->_file.close();
	this->_filename = path;
	this->_file.open(path, std::ios::in | std::ios::out);

}

std::string FileHandler::read() {

	if (!this->_file.is_open()) return NULL;

	std::stringstream content;

	this->_file.seekg(std::ios::beg);

	content << this->_file.rdbuf();
	
	return content.str();

}

std::string FileHandler::read(std::size_t beg, std::size_t end) {

	if (!this->_file.is_open()) return "";
	if (end < beg && end) return "";

	this->_file.seekg(beg, std::ios::beg);
	std::string content(end ? end - beg : end , ' ');

	if (!end)
		content = this->read();
	else 
		this->_file.read(&content[0], end - beg);
	
	this->_file.seekg(std::ios::beg);

	return content;

}

std::string FileHandler::readLine() {

	if (!this->_file.is_open()) return "";

	std::string line;

	if (!(std::getline(this->_file, line))) {
		return "\z";
	}

	return line;

}

void FileHandler::append(const std::string& str) {

	if (!this->_file.is_open()) return;


	this->_file << str;

}

void FileHandler::write(const std::string& str) {

	if (!this->_file.is_open()) return;

	this->_file.close();
	this->_file.open(this->_filename, std::ios::in | std::ios::out | std::ios::ate | std::ios::trunc);

	this->_file << str;

	this->_file.open(this->_filename, std::ios::in | std::ios::out);



}