#include <iostream>
#include "player_stats.hpp"
using namespace std;


int main(int argc, char *argv[]) {

	// find arguments and execute
	// if ( argc > 1 ) {
	// 	std::vector<std::string> args = parse_arguments(argc, argv);
		

	// } 
	// // show menu and allow user to pick a task.
	// else {
	// 	std::cout << argc;
		

	// }


	

	Player p = {"John Doe", 23, "USA", 180, 90, "FC Barcalona", "$13,000,000", {54, 23, 99}};
	print_histogram(p);
	return 0;

}
