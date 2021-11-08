#pragma once

#include <string>
#include <memory>
#include <queue>
#include <map>
#include <set>

#include "../error/error.h"
#include "../operators/operator.h"
#include "../token/token.h"

/**
@brief Scanner class
@details Scanner class, which scan inputed string and parse it to token queue
*/
class scanner {
private:
	std::set<std::pair<std::string, char>> opersNamesAndIDs;		///< set with operators names and ID's

	std::queue<token_t> tokenQueue;															///< parsed token queue
	
	void FillOpersNames(const std::map<char, std::unique_ptr<def_operator>>& operators);
	token_t ReadFunc(const char* strBegin);
public:
	/**
		* default scanner constructor
		*/
	scanner() {};


	/**
		* String scanner function
		*	@param[in] operators - operators map
		*	@param[in] strToParse - string to parse
		*/
	void scanString(const std::map<char, std::unique_ptr<def_operator>>& operators, const std::string& strToParse);

	/**
		* String scanner function
		*/
	std::queue<token_t>& GetTokenQueue() { return tokenQueue; };
};
