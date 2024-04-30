#ifndef TOKENS_H
#define TOKENS_H

// ��� ������
enum Type {
	TYPE_DEFAULT,			// ��� Default
	TYPE_VARIBLE,			// ��� ����������
	TYPE_INT,				// ��� �������������� �����
	TYPE_FLOAT,				// ��� ������������� �����
	TYPE_STRING,			// ��� ������
	TYPE_COMMAND,			// ����������������� ��������
	TYPE_COMMENT,			// �����������
	TYPE_EOL,				// ��� ����� ������
	TYPE_COMMA,				// ��� �������
	TYPE_QUOTE,				// ��� �������
	TYPE_SUBDIVIDE,			// ��� �������������� ��������
	TYPE_ADD,
	TYPE_DIVIDE,
	TYPE_PERCENT,
	TYPE_MULTIPLY,
	TYPE_INCREMENT,
	TYPE_DECREMENT,
	TYPE_GREATER,			// ��� ���������� ��������
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

// �������������� ��������
enum Math_Operation_Tokens {
	ADD_TOKEN = 43,
	SUBDIVIDE_TOKEN = 45,
	MULTIPLY_TOKEN = 42,
	DIVIDE_TOKEN = 47,
	PERCENT_TOKEN = 37
};

// ���������� ��������
enum Logic_Operation_Tokens {
	GREATER_TOKEN = 62,
	LESS_TOKEN = 60,
	EQUAL_TOKEN = 61,
	FACTORIAL_TOKEN = 33,
	OR_TOKEN = 124,
	AND_TOKEN = 38
};

// ������
enum Barackets_Tokens {
	// [ � ] ��� �������
	LSB_TOKEN = 91,
	RSB_TOKEN = 93,

	// { � }
	LFB_TOKEN = 123,
	RFB_TOKEN = 125,

	// ( � )
	LRB_TOKEN = 40,
	RRB_TOKEN = 41
};

// �����������
enum Separator_Tokens {
	// ����������
	COMMENT_TOKEN = 126,
	// �����
	DOT_TOKEN = 46,
	// �������
	COMMA_TOKEN = 44,
	// Quote
	QUOTE_TOKEN = 34,
	// �������� �����
	NEXT_LINE = 10
};
#endif // !TOKENS_H