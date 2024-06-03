#include "../DIM_LANGUAGE/LIBS/standart/standart.h"
void Run() { std::setlocale(LC_ALL, "Ru"); dim::Dynamic f = 1; for ( dim::Dynamic i : dim::Range ( 1 , 6 ) ) { f = f * i; } dim::println ( f );}