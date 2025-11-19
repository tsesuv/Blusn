#include <iostream>
#include <cstdlib>

////////////////////////////////////////////////////////

bool IsREPL = true;

////////////////////////////////////////////////////////

bool version(void);
bool help(void);

////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	if(1 < argc) IsREPL = false;

	return 0;
}

////////////////////////////////////////////////////////

bool version(void)
{
	std::cout << "      UnSynk @ Evaluator" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << " Version: 1.0.0 Pre-Alpha" << std::endl;
	std::cout << " Build  : 2025111901"      << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "enter `@ /?' you get more helps.\n" << std::endl;

	return true;
}

bool help(void)
{
	std::cout << "      UnSynk @ Evaluator" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Usage:"                   << std::endl;
	std::cout << "	@ </hidden:{true|false}> </delay:{true|false}> </src:[\\file\\path.@]" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "	/hidden	:	Enable output hidden flag." << std::endl;
	std::cout << "	/delay	:	Enable delay execute flag." << std::endl;
	std::cout << "	/src	:	Configuration source file path." << std::endl;
	std::cout << "	/?		:	Print this help message." << std::endl;
	std::cout << "	/help	:	Print this help message." << std::endl;
	std::cout << "	/h		:	Print this help message." << std::endl;
	std::cout << "	/v		:	Print software informations." << std::endl;
	std::cout << "	/version:	Print software informations." << std::endl;

	return true;
}
