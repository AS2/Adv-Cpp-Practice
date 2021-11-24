#pragma once

#include <list>
#include <string>
#include <map>

#include <memory>

#include "../tested_classes/testedClasses.h"

struct CommandArguments {
	std::vector<std::string> commandArgsName;
	std::vector<int> commandArgsValues;
};

class Command {
private:
	std::function<int(const std::vector<int>& args)> funcCaller;

	template<typename Class, typename Function, size_t ...indexies>
	static int CallFunc(Class* newCls, Function newFunc, const std::vector<int>& args, std::index_sequence<indexies...>) {
		return (newCls->*newFunc)(args[indexies]...);
	}
public:
	Command() = default;

	template<class Class, typename ...Args>
	Command(Class* cls, int(Class::* newCommand)(Args...)) {
		funcCaller = [cls, newCommand](const std::vector<int>& funcArgs) {
			return CallFunc(cls, newCommand, funcArgs, std::make_index_sequence<sizeof...(Args)>{});
		};
	}

	int executeCommand(const std::vector<int>& funcArgs) {
		return funcCaller(funcArgs);
	}
};

class Wrapper {
private:
	Command command;
	CommandArguments commandArguments;

	bool IsHaveSimilarArgsNames(const std::vector<std::pair<std::string, int>> args) {
		for (int i = 0; i < args.size(); i++)
			for (int j = i + 1; j < args.size(); j++)
				if (args[i].first == args[j].first)
					return true;
		return false;
	}
public:
	Wrapper() = delete;

	template<typename Class, typename ...Args>
	Wrapper(Class* cls,  int(Class::*newCommand)(Args...), const std::vector<std::pair<std::string, int>> args) {
		if (cls == nullptr || newCommand == nullptr)
			throw std::exception("unexpected 'nullptr' from function's params");
		if (IsHaveSimilarArgsNames(args))
			throw std::exception("Two arguments have same names!");
		if (args.size() != sizeof...(Args))
			throw std::exception("Inits uncorrect count of arguments");

		command = Command(cls, newCommand);

		commandArguments.commandArgsName = std::vector<std::string>(args.size());
		commandArguments.commandArgsValues = std::vector<int>(args.size());
		int i = 0;
		for (auto arg : args) {
			commandArguments.commandArgsName[i] = arg.first;
			commandArguments.commandArgsValues[i++] = arg.second;
		}
	}

	int executeCommand(std::vector<std::pair<std::string, int>> args) {
		bool isFounded = false;

		for (int i = 0; i < args.size(); i++) {
			isFounded = false;
			for (int j = 0; j < commandArguments.commandArgsName.size(); j++)
				if (args[i].first == commandArguments.commandArgsName[j]) {
					isFounded = true;
					commandArguments.commandArgsValues[j] = args[i].second;
					break;
				}

			if (!isFounded)
				throw std::exception("UNKNOWN ARGUMENT NAME!");
		}

		return command.executeCommand(commandArguments.commandArgsValues);
	}
};
