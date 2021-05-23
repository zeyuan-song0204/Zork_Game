/**
*projectName FinalProject
*author  Zeyuan Song
*studentID 19096216
*Date 12/05/2020
*/
#ifndef PARSER_H_
#define PARSER_H_

#include "Command.h"
#include "CommandWords.h"

class Parser {
private:
	CommandWords *commands;

public:
	Parser();
	Command* getCommand();
	void showCommands();
};

#endif /*PARSER_H_*/
