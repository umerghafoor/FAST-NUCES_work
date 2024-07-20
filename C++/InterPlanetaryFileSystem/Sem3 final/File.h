#pragma once
#include<string>
using namespace std;

class File
{
public:
	string path;
	string name;


	File(const string& name, const string& path)
		: path(path), name(name)
	{
	}

	File(const File& other) {
		path = other.path;
		name = other.name;
	}

	File& operator=(const File& other);

	File() = default;
};

