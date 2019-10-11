#include <bspch.h>
#include "StringFormatting.h"

namespace bs {

	std::vector<std::string> split(const std::string& str, const char& separator)
	{
		std::vector<std::string> results;
		std::string::const_iterator start = str.begin();
		std::string::const_iterator end = str.end();
		std::string::const_iterator next = std::find(start, end, separator);
		while (next != end) {
			results.push_back(std::string(start, next));
			start = next + 1;
			next = std::find(start, end, separator);
		}
		results.push_back(std::string(start, next));
		return results;
	}

}