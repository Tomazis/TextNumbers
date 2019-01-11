#include "TextNumberConverter.h"
#include <random>
#include <windows.h>
#include <algorithm>

std::vector<std::string> convert(std::string *lines)
{
	int numbers = (lines[0].size() % 4) ? lines[0].size() / 4 + 1 : lines[0].size() / 4;
	std::vector<std::string> numb;
	for (int k = 0; k < numbers; k++) {
		numb.push_back("");
	}
	for (int i = 0; i < 4; i++) {
		int offset = 0;
		for (int k = 0; k < numbers; k++) {
			numb[k] += lines[i].substr(offset, 3);
			if (i != 3) {
				numb[k] += "\n";
			}
			offset += 4;
		}
	}
	return numb;
}

std::map<std::string, char> createDict() {
	std::string zero =
		" _ \n"
		"| |\n"
		"|_|\n"
		"   ";
	std::string one =
		"   \n"
		"  |\n"
		"  |\n"
		"   ";
	std::string two =
		" _ \n"
		" _|\n"
		"|_ \n"
		"   ";
	std::string three =
		" _ \n"
		" _|\n"
		" _|\n"
		"   ";
	std::string four =
		"   \n"
		"|_|\n"
		"  |\n"
		"   ";
	std::string five =
		" _ \n"
		"|_ \n"
		" _|\n"
		"   ";
	std::string six =
		" _ \n"
		"|_ \n"
		"|_|\n"
		"   ";
	std::string seven =
		" _ \n"
		"  |\n"
		"  |\n"
		"   ";
	std::string eight =
		" _ \n"
		"|_|\n"
		"|_|\n"
		"   ";
	std::string nine =
		" _ \n"
		"|_|\n"
		" _|\n"
		"   ";
	std::map<std::string, char> dict;
	dict[zero]  = '0';
	dict[one]   = '1';
	dict[two]   = '2';
	dict[three] = '3';
	dict[four]  = '4';
	dict[five]  = '5';
	dict[six]   = '6';
	dict[seven] = '7';
	dict[eight] = '8';
	dict[nine]  = '9';
	return dict;
}


void checksum(std::string code,bool outFile, std::ofstream& outfile) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int counter = 9;
	int sum = 0;
	int checksum = 0;
	for each (char var in code)
	{
		sum += counter * (var - '0');
		counter--;
	}
	if (sum % 11 == 0) {
		if (outFile) {
			outfile << code << std::endl;	
		}
		else {
			SetConsoleTextAttribute(hConsole, 2);
			std::cout << code << std::endl;
		}
	}
	else {
		if (outFile) {
			outfile << code << ": " << "ERR" << std::endl;
		}
		else {
			SetConsoleTextAttribute(hConsole, 4);
			std::cout << code << ": " << "ERR" << std::endl;
		}
	}
	SetConsoleTextAttribute(hConsole, 7);

}

std::string test_generator() {
	std::string num = "";
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 9); // define the range
	for (int n = 0; n < 9; ++n) {
		num += ('0' + distr(eng));
	}
	return num;
}

void convertTextNumbers(std::string infile_path, std::string outfile_path) {
	std::map<std::string, char> dict = createDict();

	std::ifstream infile;
	std::ofstream outfile;
	bool inFile = false;
	bool outFile = false;

	if (!infile_path.empty()) {
		try
		{
			infile.open(infile_path);
			inFile = true;
		}
		catch (const std::exception&)
		{
			std::cout << "Error with opening input file." << std::endl;
		}
	}

	if (!outfile_path.empty()) {
		try
		{
			outfile.open(outfile_path);
			outfile.clear();
			outFile = true;
		}
		catch (const std::exception&)
		{
			std::cout << "Error with opening output file." << std::endl;
		}
	}

	std::string line;
	int counter = 0;
	std::string numbers[4];
	std::vector<std::string> vec_numb;
	std::vector<int> numbers_size;
	while (true) {
		if (inFile) {
			std::getline(infile, line);
			if (!infile) {
				if (infile.eof()) {
					break;
				}
			}
		}
		else {
			std::getline(std::cin, line);
		}
		numbers[counter] = line;
		counter++;
		if (counter == 4) {
			counter = 0;
			std::vector<std::string>temp = convert(numbers);
			if (temp.size() == 9) {
				numbers_size.push_back(temp.size());
				vec_numb.insert(std::end(vec_numb), std::begin(temp), std::end(temp));
			}
		}
	}
	if (inFile) infile.close();

	int index = 0;
	std::string out = "";
	std::vector<std::string> codes;
	std::vector<char> guess;
	bool corrupted = false;
	int matching = 0;
	int counter_err = 0;
	bool repair = false;
	for each (std::string var in vec_numb)
	{
		if (dict.find(var) != dict.end()) {
			out += dict[var];
		}
		else {
			counter_err++;
			repair = false;
			for (const auto &p : dict)
			{
				matching = 0;
				for (int i = 0; i < p.first.size(); i++) {
					if (p.first[i] != var[i]) {
						matching++;
						if (matching > 1) {
							break;
						}
					}
				}
				if (matching < 2) {
					guess.push_back(p.second);
					repair = true;
				}
			}
			if (!repair || counter_err > 1) {
				corrupted = true;
			}
			out += '?';

		}
		if (numbers_size[index] == out.size())
		{
			if (outFile) {
				if (corrupted) {
					outfile << out << ": " << "ILL" << std::endl;
				}
				else {
					if (guess.size() > 0) {
						outfile << out << ": ";
						std::string tmp;
						for each (auto c in guess)
						{
							tmp = out;
							std::replace(tmp.begin(), tmp.end(), '?', c);
							outfile << tmp << " ";
							codes.push_back(tmp);
						}
					}
					else {
						codes.push_back(out);
					}
					outfile << std::endl;
				}
			}
			else {
				if (corrupted){
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, 6);
					std::cout << out << ": " << "ILL" << std::endl;
					SetConsoleTextAttribute(hConsole, 7);
				}
				else {
					if (guess.size() > 0) {
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						SetConsoleTextAttribute(hConsole, 3);
						std::cout << out << ": ";
						std::string tmp;
						for each (auto c in guess)
						{
							tmp = out;
							std::replace(tmp.begin(), tmp.end(), '?', c);
							std::cout << tmp << " ";
							codes.push_back(tmp);
						}
						SetConsoleTextAttribute(hConsole, 7);
					}
					else {
						codes.push_back(out);
					}
					std::cout << std::endl;
				}
			}
			index++;
			out = "";
			corrupted = false;
			counter_err = 0;
			guess.clear();
		}
	}

	//for (int i = 0; i < 200; i++) {
	//	codes.push_back(test_generator());
	//}

	for each (std::string var in codes)
	{
		checksum(var, outFile, outfile);
	}

	if (outFile) {
		outfile.close();
		std::cout << "Saved to file " << outfile_path << std::endl;
	};
}