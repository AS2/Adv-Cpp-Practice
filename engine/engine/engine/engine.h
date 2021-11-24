#pragma once

#include <map>
#include <vector>
#include <string>

#include "../wrapper/wrapper.h"

class Engine {
private:
	std::map<std::string, Wrapper*> commands;
public:
	void register_command(Wrapper* command, std::string commandName) {
		commands[commandName] = command;
	}

	int execute(std::string commandName, std::vector<std::pair<std::string, int>> args) {
		// TODO : Place check on valid command name

		return commands[commandName]->executeCommand(args);
	}
};