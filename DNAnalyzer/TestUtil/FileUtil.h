#pragma once

#include <string>

using namespace std;

class FileUtil
{
public:

	static string read(string file);

	static bool write(string file, string content);
	
	static bool unlink(string file);

	static bool exists(string file);
protected:
	FileUtil();
	~FileUtil();
};

