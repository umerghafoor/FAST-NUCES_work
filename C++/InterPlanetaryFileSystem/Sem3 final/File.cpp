#include "File.h"

File& File::operator=(const File& other)
{
	path = other.path;
	name = other.name;

	return *this;
}