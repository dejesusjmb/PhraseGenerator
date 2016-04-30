#include <iostream>
#include "TextProcessor.hpp"

class UserInterface
{
public:
	void getUserInput();
	void printOutput();

private:
	std::string firstInput_;
	std::string secondInput_;
	std::string fileName_;
};

void UserInterface::getUserInput()
{
	std::cout << "Input filename (input Reference.txt if you want to use default file): ";
	getline(std::cin, fileName_);
	std::cout << "Input first word: ";
	getline(std::cin, firstInput_);
	std::cout << "Input second word: ";
	getline(std::cin, secondInput_);
}

void UserInterface::printOutput()
{
	TextProcessor textProcessor(fileName_);
	textProcessor.generateTextsBasedOnKeywords(firstInput_, secondInput_);
}
