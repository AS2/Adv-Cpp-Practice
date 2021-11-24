#pragma once

#include <cmath>

class wrapped_class {
};

class firstNorm : public wrapped_class {
public:
	int FirstNorm(int a, int b) {
		return (int)std::fabs(b - a);
	}
};

class infNorm : public wrapped_class {
public:
	int InfNorm(int a, int b) {
		return std::max(a, b);
	}
};

class somethingFromVector : public wrapped_class {
public:
	int SquareLength2(int a, int b) {
		return a * a + b * b;
	}

	int SquareLength3(int a, int b, int c) {
		return a * a + b * b + c * c;
	}
};
