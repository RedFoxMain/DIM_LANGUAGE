#include "parser.h"

template<typename K, typename V>
static std::unordered_map<K, V> Parser::reverse_map(const std::unordered_map<K, V>& map) {
	std::unordered_map<V, K> result;
	for (const auto& key_value : map) { result.emplace(key_value.second, key_value.first); }
	return result;
}

void Parser::GetStrings(const Dictionary& strings) {
	STRING_LITERALS_CODE_ = reverse_map(strings);
}

void Parser::GetDigits(const Dictionary& digits) {
	DIGITS_CODE_ = reverse_map(digits);
}

void Parser::GetVariables(const Dictionary& varibles) {
	VARIBLES_CODE_ = reverse_map(varibles);
}

bool Parser::InVector(const std::vector<std::string>& list, const std::string& word) {
	return std::find(begin(list), end(list), word) != end(list);
}

void Parser::MakeFile(const std::string& data) {
	extern const std::string path_to_main_folder;
	std::ofstream out(path_to_main_folder + "\\RUN\\release.cpp");
	if (out.is_open()) { out << data; }
	out.close();
}

void Parser::TarnslateToCpp() {
	std::string cpp_code = "#include \"../DIM_LANGUAGE/LIBS/standart/standart.h\"\nint main() { std::setlocale(LC_ALL, \"Ru\"); ";
	size_t max_size = hiddenData_.size();
	for (size_t index = 0; index < max_size; ++index) {
		Type current_type = hiddenData_[index].type;  // текущий тип токена
		std::string current_code = hiddenData_[index].code; // текущий код токена

		// Получить переменные, числа, строки.
		cpp_code += STRING_LITERALS_CODE_[current_code];
		cpp_code += DIGITS_CODE_[current_code];
		cpp_code += VARIBLES_CODE_[current_code];
		cpp_code += OPN[current_code];

		int next_index = index + 1; // следущий индекс
		if (next_index < max_size) {

			std::string next_value = hiddenData_[next_index].value;  // следущее значение
			// ; для цифр
			if ((current_type == Type::TYPE_INT || current_type == Type::TYPE_FLOAT) && !InVector({ ")", "or", "and", "==" }, next_value)) { cpp_code += ";"; }

			// ; для )
			if (current_type == Type::TYPE_RRB && !InVector({ "{", "or", "and", "*", "/", "+", "-", "%"}, next_value)) { cpp_code += ";"; }

			// ; для строк
			else if (current_type == Type::TYPE_STRING && !InVector({ ")", "or", "and", "," }, next_value)) { cpp_code += ";"; }

			// ; для перменных
			else  if (current_type == Type::TYPE_VARIBLE && !InVector({ "=", ">", "<", ">=", "<=", "!=", "--", "++", "%", "+", "-", "/", "*", ")", "and", "or", "==", "," }, next_value)) { cpp_code += ";"; }

			// ; для инкремента и декремента
			else if ((current_type == Type::TYPE_INCREMENT || current_type == Type::TYPE_DECREMENT) && !InVector({ ";" }, next_value) && VARIBLES_CODE_.count(next_value) < 0) { cpp_code += ";"; }
			cpp_code += " ";
		}
	}
	if (cpp_code[cpp_code.size()-1] == Barackets_Tokens::RRB_TOKEN) { cpp_code += ";"; }

	cpp_code += "}";
	MakeFile(cpp_code);
}