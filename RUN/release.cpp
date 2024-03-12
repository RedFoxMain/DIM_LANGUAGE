#include "../DIM_LANGUAGE/LIBS/standart/standart.h"
int main() { std::setlocale(LC_ALL, "Ru"); for ( Dynamic a : dim::Range ( 1 , 21 , 2 ) ) { dim::println ( a + 1 , " " ); };}