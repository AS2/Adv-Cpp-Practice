#pragma once

#include <cmath>

/**
@brief firstNorm class
@details class with method, which returns first norm
*/
class firstNorm {
public:
	int FirstNorm(int a, int b) {
		return (int)std::fabs(b - a);
	}
};


/**
@brief infNorm class
@details class with method, which returns infinite norm
*/
class infNorm {
public:
	int InfNorm(int a, int b) {
		return std::max(a, b);
	}
};

/**
@brief 'somethingFromVector' class
@details class with methods, which make some (strange) vector operations and different stuff
*/
class somethingFromVector {
public:
	int SquareLength2(int a, int b) {
		return a * a + b * b;
	}

	int SquareLength3(int a, int b, int c) {
		return a * a + b * b + c * c;
	}

	int PrintSmth() {
		std::cout << "hello, I'm vector!" << std::endl;
		return 0;
	}
};
