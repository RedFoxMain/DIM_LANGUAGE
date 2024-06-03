#include <fstream>

#include "../Tokens/tokens.h"
#include "../Lexer/lexer.h"
#include "../Configuration/config.h"


using Dictionary = std::unordered_map<std::string, std::string>;

class Parser {
public:
	explicit Parser(std::vector<Token> data) : hiddenData_(data) {} // Конструктор
	void TarnslateToCpp(); // первести в cpp код
	void GetStrings(const Dictionary& strings); // Получить словарь строк
	void GetDigits(const Dictionary& digits); // получить словарь цифр
	void GetVariables(const Dictionary& digits); // Получить переменные
	bool InVector(const std::vector<std::string>& list, const std::string& word);
	void MakeFile(const std::string& data); // Создать .cpp файл 

	template<typename K, typename V>
	static std::unordered_map<K, V> ReverseMap(const std::unordered_map<K, V>& map);

private:
	std::vector<Token> hiddenData_; // Вектор закодированных ключевых слов DIM
	Dictionary STRING_LITERALS_CODE_;
	Dictionary VARIBLES_CODE_;
	Dictionary DIGITS_CODE_;

	// (ОПН) Обратная Польская Нотация
	Dictionary OPN = {
	{"W1", "dim::println"}, {"W2", "dim::readline<dim::Dynamic>"}, {"W3", "if"},
	{"W4", "else"},   {"W5", "while"},   {"W6", "for"},
	{"W7", "size()"}, {"W8", "dim::Dynamic"},  {"W9", ":"},
	{"W10", "dim::Range"}, {"W11", "std::vector<dim::Dynamic>"},
	{"S1", "{"}, {"S2", "}"}, {"S3", "("}, {"S4", ")"}, {"S5", "\n"}, {"S6", "\t"},
	{"S7", "["}, {"S8", "]"}, {"S9", "//"}, {"S10", ","},
	{"O1", "+"}, {"O2", "-"}, {"O3", "/"}, {"O4", "*"},
	{"O5", "%"}, {"L1", ">"}, {"L2", "<"}, {"L3", "="},
	{"L4", ">="}, {"L5", "<="}, {"L6", "=="}, {"L7", "!="},
	{"L8", "||"}, {"L9", "&&"}, {"O6", "++"}, {"O7", "--"}
	};
};