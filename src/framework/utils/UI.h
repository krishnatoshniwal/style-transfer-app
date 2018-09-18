#include<stdio.h>
#include<string>
#include<iostream>
#include "dirent.h"
#include<fstream>
#include<vector>

std::vector<std::string> open(std::string path)
{
	DIR*    dir;
	dirent* pdir;
	std::vector<std::string> files;

	dir = opendir(path.c_str());

	while (pdir = readdir(dir)) {
    files.push_back(pdir->d_name);
	std::cout << pdir->d_name << std::endl;
	}
	return files;
}