#ifndef TOKENS_H
#define TOKENS_H

// Тип токена
enum Type {
	TYPE_DEFAULT,			// тип Default
	TYPE_VARIBLE,			// тип Переменная
	TYPE_INT,				// тип целочисленного цисла
	TYPE_FLOAT,				// тип вещественного цисла
	TYPE_STRING,			// тип строки
	TYPE_COMMAND,			// зарезервированная комманда
	TYPE_COMMENT,			// комментарий
	TYPE_EOL,				// тип конец строки
	TYPE_COMMA,				// тип запятая
	TYPE_QUOTE,				// тип кавычки
	TYPE_SUBDIVIDE,			// тип математических операций
	TYPE_ADD,
	TYPE_DIVIDE,
	TYPE_PERCENT,
	TYPE_MULTIPLY,
	TYPE_INCREMENT,
	TYPE_DECREMENT,
	TYPE_GREATER,			// тип логических операций
	TYPE_LESS,
	TYPE_LESS_EQUAL,
	TYPE_GREATER_EQUAL,
	TYPE_EQUAL_EQUAL,
	TYPE_NOT_EQUAL,
	TYPE_EQUAL,
	TYPE_OR,
	TYPE_AND,
	TYPE_LSB,				// [
	TYPE_RSB,				// ]
	TYPE_LRB,				// (
	TYPE_RRB,				// )
	TYPE_LFB,				// {
	TYPE_RFB,				// }
	TYPE_NL
};

// Математические операции
enum Math_Operation_Tokens {
	ADD_TOKEN = 43,
	SUBDIVIDE_TOKEN = 45,
	MULTIPLY_TOKEN = 42,
	DIVIDE_TOKEN = 47,
	PERCENT_TOKEN = 37
};

// Логические операции
enum Logic_Operation_Tokens {
	GREATER_TOKEN = 62,
	LESS_TOKEN = 60,
	EQUAL_TOKEN = 61,
	FACTORIAL_TOKEN = 33,
	OR_TOKEN = 124,
	AND_TOKEN = 38
};

// Скобки
enum Barackets_Tokens {
	// [ и ] для массива
	LSB_TOKEN = 91,
	RSB_TOKEN = 93,

	// { и }
	LFB_TOKEN = 123,
	RFB_TOKEN = 125,

	// ( и )
	LRB_TOKEN = 40,
	RRB_TOKEN = 41
};

// Разделители
enum Separator_Tokens {
	// Коментарии
	COMMENT_TOKEN = 126,
	// Точка
	DOT_TOKEN = 46,
	// Запятая
	COMMA_TOKEN = 44,
	// Quote
	QUOTE_TOKEN = 34,
	// Следущая линия
	NEXT_LINE = 10
};
#endif // !TOKENS_H