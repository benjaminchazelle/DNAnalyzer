#include "stdafx.h"
#include "FileUtil.h"

#include <string>
#include <fstream>
#include <streambuf>
#include <stdio.h>
#include <sys/stat.h>

string FileUtil::read(string file)
{
	std::ifstream t(file);
	std::string str((std::istreambuf_iterator<char>(t)),
		std::istreambuf_iterator<char>());
	
	return str;
}


bool FileUtil::write(string file, string content)
{
	std::ofstream ofs;
	ofs.open(file, std::ofstream::out | std::ofstream::trunc);

	ofs << content;

	ofs.close();

	return true;
}

bool FileUtil::unlink(string file)
{
	return remove(file.c_str()) == 0;
}

bool FileUtil::exists(string file)
{
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}