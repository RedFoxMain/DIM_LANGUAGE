#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <cctype>

#include "../Tokens/tokens.h"
#include "../Error/error.h"

using String_Dictionary = std::unordered_map<std::string, std::string>;
using Char_Dictionary = std::unordered_map<char, std::string>;
using Char_And_String_Dictionary = std::unordered_map<char, Type>;

// Сама структура токена
struct Token {
	Type type = Type::TYPE_DEFAULT;
	std::string code = "";
	std::string value = "";
	int token_position = 0;
	Token() {}
	Token(Type type_, std::string code_, std::string value_, int position_) : type(type_), code(code_), value(value_), token_position(position_) {}
};

class Lexer {
public:
	//friend class Parser;
	Lexer(const std::string& original_text) : text_(original_text) { Advance(); } // Конструктор
	String_Dictionary CODE_VARIBLES; // Сигнатуры переменных в DIM коде
	String_Dictionary CODE_STRING_LITERALS; // Сигнатуры строк в DIM коде
	String_Dictionary CODE_DIGITS; // Сигнатуры цифр в DIM коде
	void Advance(int step = 1); // Следующий символ
	Token AddBinaryOperator(const Type& type, const std::string& code, const std::string& value, const int& position); // Добавить логический оператор к токенам
	Token GetString(int first_quote_position, int second_quote_position); // Получить строку
	Token GetCommand(); // Получить команду
	Token GetDigit(); // Получить цыфру
	std::vector<Token> Lex(); // Разобрать текст на токены

private:
	// Зарегистрированные команды
	std::vector<std::string> REGISTRY_COMMANDS_ = { "println", "readln", "in", "len", "while", "for", "if", "else", "len", "or", "and", "var", "range", "array", "append", "size" };
	
	// Таблица токенов
	Char_And_String_Dictionary TOKEN_TABLE_ = {
		{Math_Operation_Tokens::ADD_TOKEN, Type::TYPE_ADD},						// +
		{Math_Operation_Tokens::SUBDIVIDE_TOKEN, Type::TYPE_SUBDIVIDE},			// -
		{Math_Operation_Tokens::MULTIPLY_TOKEN, Type::TYPE_MULTIPLY},			// *
		{Math_Operation_Tokens::DIVIDE_TOKEN, Type::TYPE_DIVIDE},				// /
		{Math_Operation_Tokens::PERCENT_TOKEN, Type::TYPE_PERCENT},
		{Logic_Operation_Tokens::GREATER_TOKEN, Type::TYPE_GREATER},		    // >
		{Logic_Operation_Tokens::LESS_TOKEN, Type::TYPE_LESS},					// <
		{Barackets_Tokens::LSB_TOKEN, Type::TYPE_LSB},							// [
		{Barackets_Tokens::RSB_TOKEN, Type::TYPE_RSB},							// ]
		{Barackets_Tokens::LRB_TOKEN, Type::TYPE_LRB},							// (
		{Barackets_Tokens::RRB_TOKEN, Type::TYPE_RRB},							// )
		{Barackets_Tokens::LFB_TOKEN, Type::TYPE_LFB},							// {
		{Barackets_Tokens::RFB_TOKEN, Type::TYPE_RFB},							// }
		{Separator_Tokens::COMMENT_TOKEN, Type::TYPE_COMMENT},					// ~
		{Logic_Operation_Tokens::EQUAL_TOKEN, Type::TYPE_EQUAL},				// =
		{Separator_Tokens::NEXT_LINE, Type::TYPE_NL},
		{Separator_Tokens::COMMA_TOKEN, Type::TYPE_COMMA},
	};
	String_Dictionary WordsCode_ = {
		{"println", "W1"}, {"readln", "W2"}, {"if", "W3"},
		{"else", "W4"}, {"while", "W5"}, {"for", "W6"},
		{"len", "W7"}, {"var", "W8"}, {"in", "W9"}, 
		{"range", "W10"}, {"array", "W11"}
	};
	Char_Dictionary SeparatorCode_ = {
		{'{', "S1"}, {'}', "S2"}, {'(', "S3"},
		{')', "S4"}, {'\n', "S5"},
		{'\t', "S6"}, {'[', "S7"}, {']', "S8"}, {'~', "S9"},
		{',',"S10"}
	};
	Char_Dictionary MathAndUnaryLogicOperationCode_ = {
		{'+', "O1"}, {'-', "O2"}, {'/', "O3"},
		{'*', "O4"}, {'%', "O5"},
		{'>', "L1"}, {'<', "L2"}, {'=', "L3"}
	};
	String_Dictionary BinaryLogicAndMathOperationCode_ = {
		{">=", "L4"}, {"<=", "L5"}, {"==", "L6"},
		{"!=", "L7"}, {"or", "L8"}, {"and", "L9"},
		{"++", "O6"}, {"--", "O7"}
	};
	int varible_count_ = 0; // счетчик переменных
	int string_literals_count_ = 0; // счетчик строковых литералов
	int digit_count_ = 0; // счетчик цифр
	std::string text_ = ""; // код 
	int position_ = -1; // Позиция элемента
	unsigned char current_char_ = '\0'; // Текущий символ
};
#endif