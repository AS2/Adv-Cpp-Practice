// engine.cpp: определяет точку входа для приложения.
//

#include "def.h"

using namespace std;

void BadTest_WrapperInit_ArgsSameNames() {
	firstNorm fn;
	Wrapper bad_wrap_args_same_names(&fn, &firstNorm::FirstNorm, { {"a", 1}, {"a", 2} });
}

void BadTest_WrapperInit_NoEnoughtArgs() {
	firstNorm fn;
	Wrapper bad_wrap_not_enough_args(&fn, &firstNorm::FirstNorm, { {"a", 1} });
}

void BadTest_WrapperInit_TooMuchArgs() {
	firstNorm fn;
	Wrapper bad_wrap_too_many_args(&fn, &firstNorm::FirstNorm, { {"a", 1}, {"b", 2}, {"c", 2} });
}

void BadTest_EngineInitWrapper_nullptrWrapper() {
	Engine engine;
	engine.register_command(nullptr, "commandN");
}

void BadTest_EngineInitWrapper_WrappersHaveSameNames() {
	Engine engine;

	firstNorm fn;
	infNorm infN;

	Wrapper wrapperFn(&fn, &firstNorm::FirstNorm, { {"arg1", 0}, {"arg2", 0} }),
		wrapperInfN(&infN, &infNorm::InfNorm, { {"a1", 120}, {"d2", 91} });

	engine.register_command(&wrapperFn, "commandN+1");
	engine.register_command(&wrapperInfN, "commandN+1");
}

void BadTest_EngineExecuteWrapper_BadWrapperName() {
	Engine engine;

	firstNorm fn;

	Wrapper wrapperFn(&fn, &firstNorm::FirstNorm, { {"arg1", 0}, {"arg2", 0} });

	engine.register_command(&wrapperFn, "commandN+1");

	engine.execute("commandN", {});
}

void BadTest_EngineExecuteWrapper_BadWrapperArgsName() {
	Engine engine;

	firstNorm fn;

	Wrapper wrapperFn(&fn, &firstNorm::FirstNorm, { {"arg1", 0}, {"arg2", 0} });

	engine.register_command(&wrapperFn, "commandN+1");

	engine.execute("commandN+1", { {"badArgName", 30} });
}



void processTest() {
	Engine engine;

	// create different wrappers
	firstNorm fn;
	infNorm infN;
	somethingFromVector sfv;
	Wrapper wrapperFn(&fn, &firstNorm::FirstNorm, { {"arg1", 0}, {"arg2", 0} }),
			wrapperInfN(&infN, &infNorm::InfNorm, { {"a1", 120}, {"d2", 91} }),
			wrapperSFV2(&sfv, &somethingFromVector::SquareLength2, { {"a1", 3}, {"d2", 0} }),
			wrapperSFV3(&sfv, &somethingFromVector::SquareLength3, { {"a1", 1}, {"bebra", 2}, {"hmm", 1} }),
			wrapperEmptyArgs(&sfv, &somethingFromVector::PrintSmth, {});

	// register them
	engine.register_command(&wrapperFn, "firstNorm");
	engine.register_command(&wrapperInfN, "infNorm");
	engine.register_command(&wrapperSFV2, "vec2_length^2");
	engine.register_command(&wrapperSFV3, "vec3_length^2");
	engine.register_command(&wrapperEmptyArgs, "EmptyArgs");

	// call them
	engine.execute("EmptyArgs");
	std::cout << "vec2_length^2 : " << engine.execute("vec2_length^2", { {"d2", 4} }) << std::endl;
	std::cout << "vec3_length^2 : " << engine.execute("vec3_length^2", { {"a1", 3} }) << std::endl;

	std::cout << engine.execute("firstNorm", { {"arg1", 5}, {"arg2", 10} }) << std::endl;
	std::cout << engine.execute("infNorm", { {"d2", 5}, {"a1", 8} }) << std::endl;

	// CHECK DIFFERENT BAD SITUATIONS

	//BadTest_WrapperInit_ArgsSameNames();
	//BadTest_WrapperInit_NoEnoughtArgs();
	//BadTest_WrapperInit_TooMuchArgs();

	//BadTest_EngineInitWrapper_nullptrWrapper();
	//BadTest_EngineInitWrapper_WrappersHaveSameNames();

	//BadTest_EngineExecuteWrapper_BadWrapperName();
	//BadTest_EngineExecuteWrapper_BadWrapperArgsName();
}

int main() {
	processTest();
	return 0;
}
