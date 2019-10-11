#include <bspch.h>
#include "FileHandler.h"

FileHandler::FileHandler() {}

FileHandler::FileHandler(const std::string& path, bool create) : m_Filename(path) {
	if (create) {
		this->m_File.open(path, std::fstream::out);
	} else {
		this->m_File.open(path, std::fstream::in | std::fstream::out);
	}

}

FileHandler::~FileHandler() {


	this->m_File << std::fflush;
	this->m_File.close();

}

void FileHandler::setPath(const std::string& path) {

	this->m_File.close();
	this->m_Filename = path;
	this->m_File.open(path, std::ios::in | std::ios::out);

}

/* READ */
std::string FileHandler::read() {

	if (!this->m_File.is_open()) return NULL;

	std::stringstream content;

	this->m_File.seekg(std::ios::beg);

	content << this->m_File.rdbuf();
	
	return content.str();

}

std::string FileHandler::read(std::size_t beg, std::size_t end) {

	if (!this->m_File.is_open()) return "";
	if (end < beg && end) return "";

	this->m_File.seekg(beg, std::ios::beg);
	std::string content(end ? end - beg : end , ' ');

	if (!end)
		content = this->read();
	else 
		this->m_File.read(&content[0], end - beg);
	
	this->m_File.seekg(std::ios::beg);

	return content;

}

std::string FileHandler::readLine() {

	if (!this->m_File.is_open()) return "";

	std::string line;

	if (!(std::getline(this->m_File, line))) {
		return "\z";
	}

	return line;

}


/* WRITE */
void FileHandler::append(const std::string& str) {

	if (!this->m_File.is_open()) return;


	this->m_File << str;

}

void FileHandler::write(const std::string& str) {

	if (!this->m_File.is_open()) return;

	this->m_File.close();
	this->m_File.open(this->m_Filename, std::ios::in | std::ios::out | std::ios::ate | std::ios::trunc);

	this->m_File << str;

	this->m_File.open(this->m_Filename, std::ios::in | std::ios::out);



}