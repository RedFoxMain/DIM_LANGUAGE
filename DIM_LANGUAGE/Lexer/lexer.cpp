#include "lexer.h"

// Имплементация Advance
void Lexer::Advance(int step) {
	position_ += step;
	current_char_ = (position_ < text_.length()) ? text_[position_] : '\0';
}

// Добавить логический оператор к токенам
Token Lexer::AddBinaryOperator(const Type& type, const std::string& code, const std::string& value, const int& position) {
	Token token(type, code, value, position);
	Advance(2);
	return token;
}

// Имплементация GetString
Token Lexer::GetString(int first_quote_position, int second_quote_position) {
	std::string temp_string = text_.substr(first_quote_position, second_quote_position - first_quote_position + 1);
	int position = position_ - temp_string.length();
	Advance(temp_string.size());
	++string_literals_count_;
	std::string code = "C" + std::to_string(string_literals_count_);
	// Если нет такого литерала заносим в словарь и выводим
	CODE_STRING_LITERALS.try_emplace(temp_string, code);

	// Если выводим
	Token exist_token(Type::TYPE_STRING, code, temp_string, position);
	return exist_token;
}

// Имплементация GetCommand
Token Lexer::GetCommand() {
	std::string temp_string = "";
	int position = position_ - temp_string.length();
	while (std::isalnum(current_char_)) {
		temp_string += current_char_;
		Advance();
	}

	// Проверяем, является ли temp_string командой
	bool is_registry_command = std::find(begin(REGISTRY_COMMANDS_), end(REGISTRY_COMMANDS_), temp_string) != end(REGISTRY_COMMANDS_);
	if (is_registry_command) {
		if (temp_string == "or") {
			Token or_token(Type::TYPE_OR, BinaryLogicAndMathOperationCode_[temp_string], temp_string, position);
			return or_token;
		}
		if (temp_string == "and") {
			Token and_token(Type::TYPE_AND, BinaryLogicAndMathOperationCode_[temp_string], temp_string, position);
			return and_token;
		}
		Token command_token(Type::TYPE_COMMAND, WordsCode_[temp_string], temp_string, position);
		return command_token;
	}

	// Если temp_string нет в REGISTRY_COMMANDS_ вероятно это переменная
	++varible_count_;
	std::string code = "I" + std::to_string(varible_count_);
	// Если нет такой переменной заносим в словарь и выводим
	CODE_VARIBLES.try_emplace(temp_string, code);
	Token my_varible(Type::TYPE_VARIBLE, CODE_VARIBLES[temp_string], temp_string, position);
	return my_varible;
}

// Имплементация GetDigit
Token Lexer::GetDigit() {
	std::string temp_digit = "";
	int position = position_ - temp_digit.length();

	while (std::isdigit(current_char_) || current_char_ == Separator_Tokens::DOT_TOKEN) {
		temp_digit += current_char_;
		Advance();
	}
	// Проверяем, является ли temp_digit числом с плавающей точкой
	bool is_float = (temp_digit.find(Separator_Tokens::DOT_TOKEN) != std::string::npos);
	++digit_count_;
	std::string code = "N" + std::to_string(digit_count_);
	Type type = is_float ? Type::TYPE_FLOAT : Type::TYPE_INT;
	// Если нет такого числа заносим в словарь и выводим
	CODE_DIGITS.try_emplace(temp_digit, code);

	// Если есть выводим
	Token exist_token(type, CODE_DIGITS[temp_digit], temp_digit, position);
	return exist_token;
}

// Главный метод для анализа токенов
std::vector<Token> Lexer::Lex() {
	std::vector<Token> tokens;
	int first_quote_position = -1, second_quote_position;

	Token my_tokens;
	while (position_ < text_.length()) {
		int next_index = position_ + 1;
		auto next_value = text_[next_index];
		// Пропустить пробелы
		if (std::isspace(current_char_)) {
			Advance();
			continue;
		}

		if (current_char_ == Separator_Tokens::QUOTE_TOKEN) { first_quote_position = position_; } // найти позицию "

		// Получить >=
		if (current_char_ == Logic_Operation_Tokens::GREATER_TOKEN && next_value == Logic_Operation_Tokens::EQUAL_TOKEN) {
			tokens.push_back(AddBinaryOperator(Type::TYPE_GREATER_EQUAL, BinaryLogicAndMathOperationCode_[">="], ">=", position_));
			continue;
		}

		// Получить <=
		if (current_char_ == Logic_Operation_Tokens::LESS_TOKEN && next_value == Logic_Operation_Tokens::EQUAL_TOKEN) {
			tokens.push_back(AddBinaryOperator(Type::TYPE_LESS_EQUAL, BinaryLogicAndMathOperationCode_["<="], "<=", position_));
			continue;
		}

		// Получить ==
		if (current_char_ == Logic_Operation_Tokens::EQUAL_TOKEN && next_value == Logic_Operation_Tokens::EQUAL_TOKEN) {
			tokens.push_back(AddBinaryOperator(Type::TYPE_EQUAL_EQUAL, BinaryLogicAndMathOperationCode_["=="], "==", position_));
			continue;
		}

		// Получить !=
		if (current_char_ == Logic_Operation_Tokens::FACTORIAL_TOKEN && next_value == Logic_Operation_Tokens::EQUAL_TOKEN) {
			tokens.push_back(AddBinaryOperator(Type::TYPE_NOT_EQUAL, BinaryLogicAndMathOperationCode_["!="], "!=", position_));
			continue;
		}

		// Получить ++
		if (current_char_ == Math_Operation_Tokens::ADD_TOKEN && next_value == Math_Operation_Tokens::ADD_TOKEN) {
			tokens.push_back(AddBinaryOperator(Type::TYPE_INCREMENT, BinaryLogicAndMathOperationCode_["++"], "++", position_));
			continue;
		}

		// Получить --
		if (current_char_ == Math_Operation_Tokens::SUBDIVIDE_TOKEN && next_value == Math_Operation_Tokens::SUBDIVIDE_TOKEN) {
			tokens.push_back(AddBinaryOperator(Type::TYPE_DECREMENT, BinaryLogicAndMathOperationCode_["--"], "--", position_));
			continue;
		}

		// Собрать цифры
		if (std::isdigit(current_char_) || next_value == Separator_Tokens::DOT_TOKEN) {
			tokens.push_back(GetDigit());
			continue;
		}

		// Собрать строку
		if (first_quote_position > 0) {
			second_quote_position = text_.find(QUOTE_TOKEN, first_quote_position + 1);
			tokens.push_back(GetString(first_quote_position, second_quote_position));
			first_quote_position = -1;
			continue;
		}

		// Собрать команду
		if (std::isalpha(current_char_)) {
			tokens.push_back(GetCommand());
			continue;
		}

		Token token;
		token.type = TOKEN_TABLE_[current_char_];
		token.code = (SeparatorCode_.count(current_char_) > 0) ? SeparatorCode_[current_char_] : MathAndUnaryLogicOperationCode_[current_char_];
		token.value = current_char_;
		token.token_position = position_;
		tokens.push_back(token);

		Advance(); // Следующий символ
	}
	return tokens;
}