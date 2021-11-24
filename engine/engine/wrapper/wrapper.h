#pragma once

#include <list>
#include <string>
#include <map>

#include "../tested_classes/testedClasses.h"

/**
@brief Wrapper command's arguments struct
@details Wrapper command's arguments struct, which contains two arrays (std::vector) : 1st - arguments names (string array), 2nd - arguments values (integer array)
*/
struct CommandArguments {
	std::vector<std::string> commandArgsName;		///< arguments names
	std::vector<int> commandArgsValues;				///< arguments values
};

/**
@brief Wrapper command executer class
@details Wrapper command executer class, which stores lambda-function; this function calls templated class method function caller
*/
class Command {
private:
	std::function<int(const std::vector<int>& args)> funcCaller;	///< stored templated class method caller-function 

	/**
	@brief Class method caller-function (templated func)
	@details Caller-function, which call 'method' from 'class' pointer. It gives to method tuple from array, where tuple created by using sequence of size_t
	@param[in] Class *cls - class pointer
	@param[in] Function method - function, which stored into 'Class' type
	@return int - result of class method
	*/
	template<typename Class, typename Function, size_t ...indexies>
	static int CallFunc(Class* cls, Function method, const std::vector<int>& args, std::index_sequence<indexies...>) {
		return (cls->*method)(args[indexies]...);
	}
public:
	/**
	@brief Set default 'Command' constructor
	*/
	Command() = default;

	/**
	@brief Templated 'Command' constructor
	@details 'Command' constructor, created for different classes with different methods, which has variadic template arguments. It's create caller-function
	@param[in] Class *cls - class pointer
	@param[in] int(Class::* newCommand)(Args...) - class method pointer
	*/
	template<class Class, typename ...Args>
	Command(Class* cls, int(Class::* newCommand)(Args...)) {
		funcCaller = [cls, newCommand](const std::vector<int>& funcArgs) {
			return CallFunc(cls, newCommand, funcArgs, std::make_index_sequence<sizeof...(Args)>{});
		};
	}

	/**
	@brief Execute stored class method
	@param[in] const std::vector<int>& funcArgs - array with arguments for method
	@return int - result of stored class method
	*/
	int executeCommand(const std::vector<int>& funcArgs) {
		return funcCaller(funcArgs);
	}
};


/**
@brief Wrapper class
@details Wrapper for 'int(*func)(args...)' class'es methods
*/
class Wrapper {
private:
	Command command;						///< wrapped command
	CommandArguments commandArguments;		///< command arguments

	/**
	@brief Check, are command arguments have similar names
	@param[in] const std::vector<std::pair<std::string, int>>& args - command arguments
	@return bool - true - if have similar names, false - if not
	*/
	bool IsHaveSimilarArgsNames(const std::vector<std::pair<std::string, int>>& args) {
		for (int i = 0; i < args.size(); i++)
			for (int j = i + 1; j < args.size(); j++)
				if (args[i].first == args[j].first)
					return true;
		return false;
	}
public:
	/**
	@brief Delete default Wrapper constructor to protect from using methods without initialized fields
	*/
	Wrapper() = delete;


	/**
	@brief Templated 'Wrapper' constructor
	@details 'Wrapper' constructor, which wrapping different class methods with thier arguments
	@warning Throw exception if : 1) cls or newCommand are nullptr, 2) if size of 'newCommand' arguments is not same as arguments size, 3) if some arguments have same names
	@param[in] Class *cls - class pointer
	@param[in] int(Class::* newCommand)(Args...) - class method pointer
	@param[in] const std::vector<std::pair<std::string, int>> args - definition of argument names and their initial values
	*/
	template<typename Class, typename ...Args>
	Wrapper(Class* cls, int(Class::* newCommand)(Args...), const std::vector<std::pair<std::string, int>> args) {
		if (cls == nullptr || newCommand == nullptr)
			throw std::exception("Wrapper init : unexpected 'nullptr' from function's params");
		if (IsHaveSimilarArgsNames(args))
			throw std::exception("Wrapper init : Two arguments have same names!");
		if (args.size() != sizeof...(Args))
			throw std::exception("Wrapper init : Inits uncorrect count of arguments");

		command = Command(cls, newCommand);

		commandArguments.commandArgsName = std::vector<std::string>(args.size());
		commandArguments.commandArgsValues = std::vector<int>(args.size());
		int i = 0;
		for (auto arg : args) {
			commandArguments.commandArgsName[i] = arg.first;
			commandArguments.commandArgsValues[i++] = arg.second;
		}
	}

	/**
	@brief Correct command arguments method
	@details Correct method arguments by finding them by names and update values
	@warning Throw exception if some argument has name, which doesn't inited
	@param[in] const std::vector<std::pair<std::string, int>> args - new values of initialized arguments
	@return none.
	*/
	void correctArguments(std::vector<std::pair<std::string, int>> args) {
		bool isFounded = true;

		for (int i = 0; i < args.size(); i++) {
			isFounded = false;
			for (int j = 0; j < commandArguments.commandArgsName.size(); j++)
				if (args[i].first == commandArguments.commandArgsName[j]) {
					isFounded = true;
					commandArguments.commandArgsValues[j] = args[i].second;
					break;
				}

			if (!isFounded)
				throw std::exception("Wrapper correct arguments (engine execute) : unknown argument name");
		}
	}

	/**
	@brief Execute wrappered command method
	@details Execute wrappered command with correcting command arguments
	@warning Throw exception if some argument has name, which doesn't inited
	@param[in] const std::vector<std::pair<std::string, int>> args - new values of initialized arguments
	@return int - result of stored class method.
	*/
	int executeCommand(std::vector<std::pair<std::string, int>> args = {}) {
		correctArguments(args);
		return command.executeCommand(commandArguments.commandArgsValues);
	}
};
