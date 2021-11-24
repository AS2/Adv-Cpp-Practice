// engine.cpp: определяет точку входа для приложения.
//

#include "def.h"

using namespace std;

int main() {
	Engine engine;

	firstNorm fn;
	infNorm infN;
	somethingFromVector sfv;
	Wrapper wrapperFn(&fn, &firstNorm::FirstNorm, {{"arg1", 0}, {"arg2", 0}}),
			wrapperInfN(&infN, &infNorm::InfNorm, { {"a1", 120}, {"d2", 91}}),
			wrapperSFV2(&sfv, &somethingFromVector::SquareLength2, { {"a1", 3}, {"d2", 0} }), 
			wrapperSFV3(&sfv, &somethingFromVector::SquareLength3, { {"a1", 1}, {"bebra", 2}, {"hmm", 1} });

	engine.register_command(&wrapperFn, "firstNorm");
	engine.register_command(&wrapperInfN, "infNorm");
	engine.register_command(&wrapperSFV2, "vec2_length^2");
	engine.register_command(&wrapperSFV3, "vec3_length^2");

	std::cout << engine.execute("firstNorm", { {"arg1", 5}, {"arg2", 10} }) << std::endl;
	std::cout << engine.execute("infNorm", { {"d2", 5}, {"a1", 8} }) << std::endl;
	std::cout << "vec2_length^2 : " << engine.execute("vec2_length^2", { {"d2", 4}}) << std::endl;
	std::cout << "vec3_length^2 : " << engine.execute("vec3_length^2", { {"a1", 3}}) << std::endl;
}
