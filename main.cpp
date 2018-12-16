// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include "InputParser.h"
#include "TextNumberConverter.h"

int main(int argc, char **argv)
{

	InputParser input(argc, argv);


	const std::string &filename = input.getCmdOption("-i");
	const std::string &out_filename = input.getCmdOption("-o");


	convertTextNumbers(filename, out_filename);
	
  return 0;
}

