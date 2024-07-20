#pragma once
#include<iostream>
class File
{
	int Key;
	std::string FilePath;
public:

	File() = default;

	File(int Key, const std::string& FilePath)
		: Key(Key), FilePath(FilePath)
	{
	}
	int getKey()
	{
		return Key;
	}
};

