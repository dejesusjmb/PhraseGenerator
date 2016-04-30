#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <map>

class TextProcessor
{
public:
	TextProcessor(std::string fileName) : fileName_(fileName) {}
	void generateTextsBasedOnKeywords(std::string&, std::string&);
	std::string getFileName() { return fileName_; }

private:
	void readInputFile();
	void filterInputFileContent();
	void populateContentMap();
	std::vector<std::string> getWordsBasedOn(std::string&, std::string&);
	void printGeneratedWords(std::vector<std::string>);
	bool isAlphabet(char);
	
	std::string fileName_;
	std::string fileContent_;
	std::map <std::pair <std::string, std::string>, std::string> contentMap_;
};

void TextProcessor::generateTextsBasedOnKeywords(std::string& firstInput, std::string& secondInput)
{
	readInputFile();
	filterInputFileContent();		
	populateContentMap();
	printGeneratedWords(getWordsBasedOn(firstInput, secondInput));
}

void TextProcessor::readInputFile()
{
	std::ifstream inputFile(fileName_.c_str());

	if (inputFile.is_open())
	{
		std::string line;
		while (getline(inputFile, line))
		{
			fileContent_.append(" " + line);
		}
		inputFile.close();
	}
	else
		std::cout << "Unable to open file!" << std::endl;
}

void TextProcessor::filterInputFileContent()
{
	fileContent_.erase(std::remove_if(fileContent_.begin(), fileContent_.end(),
		std::bind1st(std::mem_fun(&TextProcessor::isAlphabet), this)), fileContent_.end());
	std::transform(fileContent_.begin(), fileContent_.end(), fileContent_.begin(), ::tolower);
}

bool TextProcessor::isAlphabet(char c)
{
	return !isalpha(c) && (c != ' ');
}

void TextProcessor::populateContentMap()
{
	std::istringstream iss(fileContent_);
	std::vector<std::string> contentVec;
	std::string word;
	
    	while(iss >> word)
    	{
    		contentVec.push_back(word);
    	}

    	for (int i=0; i<contentVec.size()-2; ++i)
    	{
    		std::pair <std::string, std::string> pairKeys = std::make_pair (contentVec[i], contentVec[i+1]);
    		contentMap_[pairKeys] = contentVec[i+2];
    	} 
}

std::vector<std::string> TextProcessor::getWordsBasedOn(std::string& firstWord, std::string& secondWord)
{
	std::vector<std::pair <std::string, std::string>> usedWords = {std::make_pair (firstWord, secondWord)};
	std::string nextWord = contentMap_[std::make_pair(firstWord, secondWord)];
	
	std::vector<std::string> generatedWords = {firstWord, secondWord};
	
	while (nextWord != "")
	{
		generatedWords.push_back(nextWord);
		firstWord = secondWord;
		secondWord = nextWord;
		
		if (usedWords.end() != std::find(usedWords.begin(), usedWords.end(), std::make_pair (firstWord, secondWord)))
			break;
		else
		{
			usedWords.push_back(std::make_pair (firstWord, secondWord));
			nextWord = contentMap_[std::make_pair(firstWord, secondWord)];
		}
	}
	
	return generatedWords;
}

void TextProcessor::printGeneratedWords(std::vector<std::string> generatedWords)
{
	for(const auto& word: generatedWords)
		std::cout << word << " ";
	std::cout << std::endl;
}
