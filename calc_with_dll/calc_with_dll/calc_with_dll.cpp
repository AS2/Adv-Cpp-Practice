// calc_with_dll.cpp: определяет точку входа для приложения.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "calc_with_dll.h"

using namespace std;

void process() {
	calculator calc("../../../../calc_with_dll/DLLs Code/build/plugins");
	const std::string exitString = "exit";
	std::string stringFromStdin;
	double res;

	while (1) {
		calc_error::getInstance().UpdateError(calc_error::NO_ERR, "No error");
		std::cout << "Input expression (print 'exit' to close programm): ";

		std::getline(std::cin, stringFromStdin);

		if (stringFromStdin == exitString)
			break;

		stringFromStdin.erase(std::remove(stringFromStdin.begin(), stringFromStdin.end(), ' '), stringFromStdin.end());
		stringFromStdin.erase(std::remove(stringFromStdin.begin(), stringFromStdin.end(), '\t'), stringFromStdin.end());

		res = calc.executeExpression(stringFromStdin);
		if (calc_error::getInstance().errorType != calc_error::NO_ERR)
			std::cout << "ERROR: " << calc_error::getInstance().errorMessage << std::endl;
		else
			std::cout << stringFromStdin << " = " << res << std::endl;
	}
}

int main() {
	// 16 bytes from 'calc_error' singleton
  process();
	_CrtDumpMemoryLeaks();
	return 0;
}
