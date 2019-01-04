
#ifdef _WIN32
#define PATH ""
#elif defined __unix__
#define PATH ""
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <bitset>         // std::bitset




int print(bool all, std::vector<std::string> _hex, std::set<std::string> uniqLabels, std::vector<std::string> target, std::vector<int> index, std::string _programName) {

	if (all) {
		int counter = 0;
		for (auto i : uniqLabels) {
			//std::cout << "Found in Unique Index: " << val << std::endl;
			std::cout << i << " " << index[counter] << std::endl;
			counter++;
		}
	}
	else
	{
		bool check = false;
		for (auto i : target) {
			for (auto j : uniqLabels) {
				if (i == j) {
					check = true;
				}
			}
			if (check != true) {
				// If an invalid option is encountered (not -all or one of the properties from the property file), emit an error message, including the offending argument.
				std::cerr << "bad option: " << i << " program: "  << _programName << std::endl;
				return -1;
			}
		}

		int counter = 0;
		for (auto i : target) {
			//std::cout << "Found in Unique Index: " << val << std::endl;
			std::cout << i << " " << index[counter] << std::endl;
			counter++;
		}
	}
	return 0;

}

std::string utfonverter(char symbol[5], std::istream &iFile, std::string _programName, std::string _dataFile) {
	// forming a 4-byte number out of those values

	//auto symbol = "?";
	//auto symbol = "?";
	//auto symbol = "??";

	std::string _hexValue;
	std::stringstream ss;
	ss << std::hex;


	//Returns the number of UTF-8 characters
	//or -1 if the array* does not contain a valid UTF8 string.
	int expectedLength = 0;


	if ((symbol[0] & 0b10000000) == 0b00000000) {
		expectedLength = 1;
	//	std::cout << "Length: " << expectedLength << std::endl;
		ss << (short)symbol[0];
		std::string _hexValue = ss.str();
		while (_hexValue.length() < 4) {
			_hexValue = "0" + _hexValue;
		}
		//std::cout << _hexValue << std::endl;
		return _hexValue;
	}
	else if ((symbol[0] & 0b11100000) == 0b11000000) {
		expectedLength = 2;
	//	std::cout << "Length: " << expectedLength << std::endl;
		symbol[1] = iFile.get();
		//CE
		short oneChar = symbol[0] & 0xff;
		//A9
		short secChar = symbol[1] & 0xff;

		oneChar = oneChar & 0b00111111;
		secChar = secChar & 0b01111111;

		oneChar = oneChar << 6;
		oneChar = oneChar | secChar;

		ss << oneChar;
		_hexValue = ss.str();
		while (_hexValue.length() < 4) {
			_hexValue = "0" + _hexValue;
		}
		//std::cout << _hexValue << std::endl;
		return _hexValue;

	}
	else if ((symbol[0] & 0b11110000) == 0b11100000) {
		expectedLength = 3;
	//	std::cout << "Length: " << expectedLength << std::endl;
		symbol[1] = iFile.get();
		symbol[2] = iFile.get();
		//e4
		short oneChar = symbol[0] & 0xff;
		//b7
		short secChar = symbol[1] & 0xff;
		//8a
		short therChar = symbol[2] & 0xff;

		oneChar = oneChar & 0b00011111;
		secChar = secChar & 0b01111111;
		therChar = therChar & 0b01111111;

		oneChar = oneChar << 12;
		secChar = secChar << 6;

		oneChar = oneChar | secChar | therChar;


		ss << oneChar;

		_hexValue = ss.str();
		while (_hexValue.length() < 4) {
			_hexValue = "0" + _hexValue;
		}
	//	std::cout << _hexValue << std::endl;
		return _hexValue;

	}
	else if ((symbol[0] & 0b11111000) == 0b11110000) {
		expectedLength = 4;
	//	std::cout << "Length: " << expectedLength << std::endl;
		symbol[1] = iFile.get();
		symbol[2] = iFile.get();
		symbol[3] = iFile.get();

		//e4
		int oneChar = symbol[0] & 0xff;
		//b7
		int secChar = symbol[1] & 0xff;
		//8a
		int therChar = symbol[2] & 0xff;

		int fourChar = symbol[3] & 0xff;

		oneChar = oneChar & 0b00001111;
		secChar = secChar & 0b01111111;
		therChar = therChar & 0b01111111;
		fourChar = fourChar & 0b01111111;

		oneChar = oneChar << 18;
		secChar = secChar << 12;
		therChar = therChar << 6;

		oneChar = oneChar | secChar | therChar | fourChar;


		ss << oneChar;

		_hexValue = ss.str();
		while (_hexValue.length() < 4) {
			_hexValue = "0" + _hexValue;
		}
		//std::cout << _hexValue << std::endl;
		return _hexValue;
	}
	else
	{
		int fourChar = symbol[0] & 0xff;
		ss << fourChar;
		_hexValue = ss.str();
		_hexValue = "0x" + _hexValue;
		std::cerr << "improperly-formatted bytee: "  << "Filename: " << _dataFile << " program: " << _programName << " Byte: " << _hexValue << std::endl;
		return "-1";
	}

	return _hexValue;
}

int GeneratePropertyCount(const std::vector<std::string> &_hex, const std::vector<std::string> &_category, std::string _hexValue, std::vector<int> &index, const std::vector<std::string> &target, std::set<std::string> &uniqLabels, bool all, std::string filename) {

		// Special case for escape charators, append 0 to front match hex container elements format
		std::string specialCase = "0";

		if (_hexValue.length() == 1) {
			_hexValue = specialCase + _hexValue;
		}

		std::transform(_hexValue.begin(), _hexValue.end(), _hexValue.begin(), ::toupper);
		for (int i = 0; i < _category.size(); i++) {
			std::string  _hexContainerValue = _hex[i];
			//find parsed charator hex value inside hex vector container
			if (_hexValue == _hexContainerValue) {
				//	std::cout << "Match: " << _hex[i] << " " << _hexContainerValue << std::endl;
				//	std::cout << "Cat: " << _category[i] << std::endl; 
				if (all) {
					int count = 0;
					for (auto val : uniqLabels) {
						if (_category[i] == val) {
							//std::cout << "Found in Unique Index: " << val << std::endl;
							index[count]++;
						}
						count++;
					}
				}
				else {
					int count2 = 0;
					for (auto val : target) {
						if (_category[i] == val) {
							//std::cout << "Found in Unique Index: " << val << std::endl;
							index[count2]++;
						}
						count2++;
					}
				}
			}
		}
		return 0;
}
// convert integer into string manually
// convert string into hex manually
int GenerateCatergoryCodes(std::vector<std::string> &_category, std::string propertyFileName, std::set<std::string> &uniqLabels, std::string _programName) {
	// Substring category extraction
	std::ifstream file(PATH + propertyFileName);
	// Input from file or terminal
	std::string input = "";

	if (file.fail()) {
		std::cerr << "cannot find property file" << propertyFileName << " Program: " << _programName << std::endl;
	}
	std::string category = "";
	while (!file.eof()) {
		std::getline(file, input);
		// Prevent empty line pushback
		if (!(input.empty()))
		{	
			size_t pos = 0;
			// The property is the third field
			for (int i = 0; i < 3; i++) {	
				pos = input.find(';', pos);
				if (pos != std::string::npos) { pos += 1; /* std::cout << "position: " << pos << '\n';*/ }
				else {
					std::cerr << "Invalid property format." << propertyFileName << " Program: " << _programName << std::endl;
					return -1;
				}
			}

			input = input.substr(pos-3, 2);
			//if(isalpha(input.at(0)) && isalpha(input.at(1)) && isupper(input.at(0)) && islower(input.at(1)))
			//{
			//	std::cerr << "Invalid property format." << propertyFileName << " Program: " << _programName << std::endl;
			//		return -1;
			//}
		//	std::cout << "label: " << input << std::endl;

			// unique category labels for increments
			_category.push_back(input);
			uniqLabels.insert(input);

		}
		else {
			//std::cerr << "Empty line." << std::endl;
		}
	}
	file.close();

	//for (int i = 0; i < _hex.size(); i++) {
	//	std::cout << "Hex: " << _hex[i] << " Category: " << _category[i] << std::endl;
	//}
	//for (std::string i : _set) {
	//	std::cout << "Set: " << i << std::endl;
	//}
	return 0;
}

int GenerateHexCodes(std::vector<std::string> &_hex, std::string filename, std::string _programName) {

	// Substring hex extraction
	std::string hex = "";
	// Substring category extraction
	std::ifstream file(PATH + filename);
	// Input from file or terminal
	std::string input = "";

	if (file.fail()) {
		std::cerr << "cannot find property file" << filename << " Program: " << _programName << std::endl;
	}
	
	do {
		std::getline(file, input);
		// Prevent empty line pushback
		if (input.empty()) {}
	//	else if(input.length() == 5 && isxdigit(input.at(0)) && isxdigit(input.at(1)))) {
		// The first field is four, five, or six hexadecimal digits
			int pos = input.find(';');
			_hex.push_back(input.substr(0, pos).c_str());
		//	std::cout << "hex: " << input.substr(0, pos).c_str() << std::endl;
	//		}
	} while (!file.eof());
	file.close();

	//for (int i = 0; i < _hex.size(); i++) {
	//	std::cout << "Hex: " << _hex[i]  << std::endl;
	//}
	//for (std::string i : _set) {
	//	std::cout << "Set: " << i << std::endl;
	//}
	return 0;

}

int LoadDataFiles(std::vector<std::string> _targets, std::vector<std::string> _propertiesFile, std::vector<std::string> _dataFiles, bool all, std::string _programName) {

	std::set<std::string> uniqLabels;
	// Contrainer for hex codes
	std::vector<std::string> _hex;
	// Contrainer for category labels
	std::vector<std::string> _category;
	// Index for category match count
	std::vector<int> index;
	std::vector<char> _data;
	//std::cout << "Property file: " << std::endl;
	std::ifstream filopen;
	filopen.open(_propertiesFile[0]);
	if (filopen.fail()) {
	//	// If the property file can’t be read, emit an error message, including the property file name
		std::cerr << "cannot read property file: " << _propertiesFile[0] << "Program: " << _programName << std::endl;
		return -1;
	}
	if (all) {
		if (GenerateHexCodes(_hex, _propertiesFile[0], _programName) == -1) {
			return -1;
		}
		GenerateCatergoryCodes(_category, _propertiesFile[0], uniqLabels, _programName);
		index.resize(uniqLabels.size());
	}
	else {
		if (GenerateHexCodes(_hex, _propertiesFile[0], _programName) == -1) {
			return -1;
		}			
	GenerateCatergoryCodes(_category, _propertiesFile[0], uniqLabels, _programName);
		index.resize(_targets.size());
	}
	filopen.close();



	for (std::string i : _dataFiles) {
		filopen.open(i);
		if (filopen.fail()) {
			std::cerr << "cannot LoadDataFiles(): " << i << "Program: " << _programName << std::endl;
			return -1;
	}
		


		char arrays[5];

		arrays[0] = filopen.get();

		do {
			std::string symbol = utfonverter(arrays,filopen, _programName, i);
			if (symbol == "-1") { return -1; }

		//	std::cout << "string in count " << symbol << std::endl;
		 if (GeneratePropertyCount(_hex, _category, symbol, index, _targets, uniqLabels, all, i) == -1)  // bottlenecked, search for shitty loop
		 {
			 return -1;
		 }
		 arrays[0] = filopen.get();
		} while (!filopen.eof());

		filopen.close();
		     //	std::cout << "vec size " << index.size();
			// Load values into correct categories 

	}
	////std::cout << "Reading Data file: " << std::endl;
	//


	print(all, _hex, uniqLabels, _targets, index, _programName);
	return 0;
}
	
int LoadArguments(int argc, char *argv[]) {
	
	bool properties = true;
	bool all = false;
	std::vector<std::string> _targets;
	std::vector<std::string> _propertiesFile;
	std::vector<std::string> __dataFiles;
	std::string _programName = argv[0];
	// start at 1 because argc[0] is the program name
	for (int count = 1; count < argc; count++) {
		if (std::string(argv[count]).at(0) == '-' && properties == true) {
			if (std::string(argv[count]) == "-all") {
				all = true;
			}
			_targets.push_back(std::string(argv[count]).substr(1, 2));
		}
		else if (properties) {  // read prperties file
								//std::cout << "Reading Properties file: " << std::endl;
			_propertiesFile.push_back(argv[count]);
			properties = false;

		}
		else { // read data files
			if (std::string(argv[count]).at(0) == '-') {
				// Options come first, before filenames, in the command line.
				std::cerr << "invalid argument: " << argv[count] << " Program: " << _programName << std::endl;
				return -1;
			}
			__dataFiles.push_back(argv[count]);
		}
	}


	if (LoadDataFiles(_targets, _propertiesFile, __dataFiles, all, _programName) == -1) { return -1; }
	return 0;
}



int main(int argc, char *argv[]) {
	


	// argument count
	if (argc < 2) {
		std::cerr << "No arguments for: " << argv[0] << std::endl;
		return -1;
	}	

	
	if (LoadArguments(argc, argv) == -1) {
		return -1;
	}

	return 0;
}