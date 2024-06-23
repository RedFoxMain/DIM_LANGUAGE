#pragma once
#include <iostream>
#include <fstream> 
#include <string>

#include "../Lexer/lexer.h"
#include "../Parser/parser.h"
#include "../Configuration/config.h"

std::string ReadFile(const std::string& file_name) {
	std::string text, line;
	std::ifstream file(file_name, std::ios::in);
	if (file.is_open()) {
		while (file >> line) {
			text += line + ' ';
		}
	}
	file.close();
	return text;
}
void Execute(const std::string& file_name) {
	std::setlocale(LC_ALL, "Ru");
	Lexer lexer(ReadFile(file_name + "\\DIM_LANGUAGE\\WorkSpace\\main.dim"));
	Parser parser(lexer.Lex());
	parser.GetStrings(lexer.CODE_STRING_LITERALS);
	parser.GetDigits(lexer.CODE_DIGITS);
	parser.GetVariables(lexer.CODE_VARIBLES);
	parser.TarnslateToCpp();
}
