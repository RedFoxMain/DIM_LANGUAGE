#pragma once
#include <iostream>
#include <map>

enum ErrorCode {
	UnknownCharacter
};

class ErrorHandler {
public:
	int error_status = 0;

	template<typename T, typename... Args>
	void UnknownCharacterError(const T& value, const Args&... args) {
		std::printf(value, args...);
	}
};