#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

typedef std::unordered_map<std::string, std::string> Map;

void remove_zeros(std::string& str)
{
	while (str.front() == '0')
	{
		str.erase(str.begin());
	}
}

std::string oct_to_bin(const std::string& str, const Map& converter)
{
	std::string result = "";

	for (size_t i = 0; i < str.length(); i++)
	{
		std::string temp = converter.at(std::to_string(str[i] - '0'));
		for (size_t j = 1; j < temp.length(); j++)
		{
			result += temp[j];
		}
	}
	
	return result;
}

std::string hex_to_bin(const std::string& str, const Map& converter)
{
	std::string result = "";

	for (size_t i = 0; i < str.length(); i++)
	{
		std::string temp;
		temp += str[i];
		result += converter.at(temp);
	}

	return result;
}
std::string dec_to_bin(const std::string& str)
{
	int number = 0;

	std::stringstream ss;
	ss << str;
	ss >> number;

	std::string result;

	while (number > 0)
	{
		result.insert(result.begin(), (number % 2) + '0');

		number /= 2;
	}
	
	return result;
} 

std::string bin_to_dec(const std::string& str) 
{
	int result = 0;
	for (int i = str.length() - 1; i >= 0; i--)
	{
		result += (int(str[i]) - 48) * pow(2.f, abs(int(i - str.length() + 1)));
	}

	return std::to_string(result);
}

std::string bin_to_another(const std::string& str, const std::string& mode, const Map& converter)
{
	std::string result = "";
	std::string temp = "";

	int count = 0;
	int maxcount = 0;

	if (mode == "bin to hex")
	{
		maxcount = 4;
	}

	else if (mode == "bin to oct")
	{
		maxcount = 3;
	}
	
	for (int i = str.length() - 1; i >= 0; i--)
	{
		if (str[i] == ' ') continue;
		temp.insert(temp.begin(), str[i]);
		count++;
		if (count == maxcount)
		{
			count = 0;
			for (size_t j = 0; j < converter.at(temp).length(); j++)
			{
				result.insert(result.begin(), converter.at(temp)[j]);
			}
			temp.clear();
		}
	}

	if (count != 0)
	{
		for (int i = 0; i < maxcount - count; i++)
		{
			temp.insert(temp.begin(), '0');
		}
		for (size_t j = 0; j < converter.at(temp).length(); j++)
		{
			result.insert(result.begin(), converter.at(temp)[j]);
		}
	}

	return result;
}


int main()
{
	Map converter = {
		//bin to hex
		{"0000", "0"}, {"0001", "1"}, {"0010", "2"}, {"0011", "3"}, {"0100", "4"}, {"0101", "5"},
		{"0110", "6"}, {"0111", "7"}, {"1000", "8"}, {"1001", "9"}, {"1010", "A"}, {"1011", "B"},
		{"1100", "C"}, {"1101", "D"}, {"1110", "E"}, {"1111", "F"},
		//bin to oct
		{"000", "0"}, {"001", "1"}, {"010", "2"}, {"011", "3"}, {"100", "4"}, {"101", "5"},
		{"110", "6"}, {"111", "7"},
		//hex to bin
		{"0", "0000"}, {"1", "0001"}, {"2", "0010"}, {"3", "0011"}, {"4", "0100"}, {"5", "0101"},
		{"6", "0110"}, {"7", "0111"}, {"8", "1000"}, {"9", "1001"}, {"A", "1010"}, {"B", "1011"},
		{"C", "1100"}, {"D", "1101"}, {"E", "1110"}, {"F", "1111"}, 
		//oct to bin
		{"0", "000"}, {"1", "001"}, {"2", "010"}, {"3", "011"}, {"4", "100"}, {"5", "101"},
		{"6", "110"}, {"7", "111"},
	};

	while (true) {
		std::cout << "What do u want to convert? "<<"Example: bin to hex"<< '\n' << "Available modes: dec, bin, hex, oct"<<'\n';

		std::string str;
		std::getline(std::cin, str);

		std::cout << "Enter your value = ";

		std::string code;
		std::getline(std::cin, code);
		
		if (str == "bin to dec") str = bin_to_dec(code);
		else if (str == "hex to bin") str = hex_to_bin(code, converter);
		else if (str == "dec to bin") str = dec_to_bin(code);
		else if (str == "oct to bin") str = oct_to_bin(code, converter);
		else if (str == "dec to hex")
		{
			code = dec_to_bin(code);
			str = bin_to_another(code, "bin to hex", converter);
		}

		else if (str == "hex to dec")
		{
			code = hex_to_bin(code, converter);
			str = bin_to_dec(code);
		}

		else if (str == "hex to oct")
		{
			code = hex_to_bin(code, converter);
			str = bin_to_another(code, "bin to oct", converter);
		}

		else if (str == "oct to hex")
		{
			code = oct_to_bin(code, converter);
			str = bin_to_another(code, "bin to hex", converter);
		}

		else if (str == "dec to oct")
		{
			code = dec_to_bin(code);
			str = bin_to_another(code, "bin to oct", converter);
		}

		else if (str == "oct to dec")
		{
			code = oct_to_bin(code, converter);
			str = bin_to_dec(code);
		}

		else str = bin_to_another(code, str, converter);

		remove_zeros(str);
		
		std::cout <<"Result = " << str << "\n\n";
	}
}