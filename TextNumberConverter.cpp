#include "TextNumberConverter.h"

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
	dict[zero] = '0';
	dict[one] = '1';
	dict[two] = '2';
	dict[three] = '3';
	dict[four] = '4';
	dict[five] = '5';
	dict[six] = '6';
	dict[seven] = '7';
	dict[eight] = '8';
	dict[nine] = '9';
	return dict;
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
			vec_numb.insert(std::end(vec_numb), std::begin(temp), std::end(temp));
			numbers_size.push_back(temp.size());
			if (temp.size() < 9) {
				break;
			}
		}
	}
	if (inFile) infile.close();

	int index = 0;
	std::string out = "";
	for each (std::string var in vec_numb)
	{
		if (dict.find(var) != dict.end()) {
			out += dict[var];
		}
		else {
			out += 'e';
		}
		if (numbers_size[index] == out.size())
		{
			if (outFile) {
				outfile << out << std::endl;
			}
			else {
				std::cout << out << std::endl;
			}
			index++;
			out = "";
		}
	}
	if (outFile) {
		outfile.close();
		std::cout << "Saved to file " << outfile_path << std::endl;
	};
}