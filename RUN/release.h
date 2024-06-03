#include "../DIM_LANGUAGE/LIBS/standart/standart.h"
void Run() { std::setlocale(LC_ALL, "Ru"); for ( dim::Dynamic i : dim::Range ( 10 ) ) { dim::println ( i , " " ); };}