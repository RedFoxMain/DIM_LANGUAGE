#include "../DIM_LANGUAGE/LIBS/standart/standart.h"
int main() { 
	std::setlocale(LC_ALL, "Ru"); 
	Dynamic a = 1;
	//dim::println(a == 5);
	while (a < 11) {
		if (a % 2 == 0) { dim::println("������: ", a, "\n"); }
		else { dim::println("��������: ", a, "\n"); }
		a = a + 1;
	}
}