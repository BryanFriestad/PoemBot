#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>

/*
 * A class to read data from a csv file.
 */
class CSVReader
{
	std::string fileName;
	std::string delimeter;

public:
	CSVReader(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm)
	{ }

	// Function to fetch data from a CSV File
	std::vector<std::string> getData();
};

/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
std::vector<std::string> CSVReader::getData()
{
	std::fstream file(fileName);

	std::vector<std::string> dataList;

	std::string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		uint32_t pos = 0;
		std::string token = line;
		while((pos = line.find(delimeter)) != std::string::npos){
            token = line.substr(0, pos);
            dataList.push_back(token);
            line.erase(0, pos + delimeter.length());
		}
		dataList.push_back(token);
	}
	// Close the File
	file.close();

	return dataList;
}

int main()
{
	char c = 'A';
	for(;c < '['; c++){
        std::string filename = "C:\\Users\\Bryan Friestad\\Desktop\\projects\\PoemBot\\PoemBot\\word_lists\\";
        filename += c;
        filename += "word.csv";
        std::cout << filename << std::endl;
        // Creating an object of CSVWriter
        CSVReader reader(filename);

        // Get the data from CSV File
        std::vector<std::string> dataList = reader.getData();
        for(std::string data : dataList)
        {
            std::cout<<data << std::endl;
        }
        std::cout<<std::endl;
	}
	// Print the content of row by row on screen

	return 0;

}
