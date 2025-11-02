#include <iostream>
#include <cstdlib>

////////////////////////////////////////////////////////


int version(void);
int help(void);

////////////////////////////////////////////////////////

int version(void)
{
	std::cout << "    UnSynk @ Compiler" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "Version: 1.0.0 Pre-Alpha" << std::endl;
	std::cout << "Build  : 2025103101"      << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "enter `@ /?' you get more helps.\n" << std::endl;

	return -1;
	exit(0);
}

int help(void)
{
	std::cout << "    UnSynk @ Compiler" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "Usage:"                   << std::endl;
	std::cout << "\t@ src.@ </o:filename> </w>" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "\t/o\t:\tSpecify output file name and file path." << std::endl;
	std::cout << "\t/w\t:\tEnable additional warnings." << std::endl;
	std::cout << "\t/?\t:\tPrint this help mesage." << std::endl;

	exit(0);
	return -1;
}

////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		version();
	}

	return 0;
}

////////////////////////////////////////////////////////
