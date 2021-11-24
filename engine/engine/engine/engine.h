#pragma once

#include <map>
#include <vector>
#include <string>

#include "../wrapper/wrapper.h"

/**
@brief Engine class
@details 'Engine' stores command wrappers and execute them by names and new arguments' values
*/
class Engine {
private:
	std::map<std::string, Wrapper*> commands;	///< wrappers' ptrs with names map
public:
	/**
	@brief Register new wapper ptr into 'commands' map
	@warning Method throw exceptions if : 1) if 'command' is nullptr, 2) if command with same name already registered
	@param[in] Wrapper* command - new command to registered
	@param[in] const std::string& commandName - 'command' name
	@return none.
	*/
	void register_command(Wrapper* command, const std::string& commandName) {
		if (command == nullptr)
			throw std::exception("Engine register command : unexpected 'nullptr' from 'Wrapper *command' pointer");

		if (commands.find(commandName) != commands.end())
			throw std::exception("Engine register command : engine already has command with same name id");

		commands[commandName] = command;
	}

	/**
	@brief Execute command method
	@details Execute command with new aguments' values
	@warning Method throw exceptions if : if command with taken name isn't registered; 2) if arguments are incorrect
	@param[in] const std::string& commandName - 'command' name
	@param[in] std::vector<std::pair<std::string, int>> args - new 'command' arguments' values
	@return int - result of stored class method.
	*/
	int execute(const std::string& commandName, std::vector<std::pair<std::string, int>> args = {}) {
		if (commands.find(commandName) == commands.end())
			throw std::exception("Engine error : unknown command name");

		return commands[commandName]->executeCommand(args);
	}
};