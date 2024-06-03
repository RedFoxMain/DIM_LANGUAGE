#include "interpreter.h"

int main() {
	extern const std::string path_to_main_folder;
    Execute(path_to_main_folder);
    Run(); 
	return 0;
}