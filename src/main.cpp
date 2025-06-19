#include <iostream>
#include <fstream>
#include <sstream>
#include "player_stats.hpp"
using namespace std;

int main(int argc, char *argv[]) {

	cout << "hello world" << endl;
	// if arguments are given then do what is asked.
	if( argc > 1 ) {
		cout << "You provided an argument, it is: " << endl;
		cout << argv[1] << endl;
	} else {
		// show menu and allow user to pick a task.
	}


	std::ifstream inputFile;

  	inputFile.open("player_stats.csv");

  	if (!inputFile.is_open()) {
     	std::cerr << "Error opening up file" << std::endl;

  	}

	std::string first_line;
	getline(inputFile, first_line);

	std::vector<Player> all_players;
	std::string line;

  	while (getline(inputFile, line)) {

		Player new_player;

		std::vector<std::string> player_info;
		std::vector<int> player_stats;

		std::stringstream line_stringstream(line);
		std::string token;

    	while (getline(line_stringstream, token, ',')) {
			player_info.push_back(token);
		}

		new_player.name = player_info.at(0);
		new_player.country = player_info.at(1);
		new_player.height_cm = std::stoi(player_info.at(2));
		new_player.weight_kg = std::stoi(player_info.at(3));
		new_player.age = std::stoi(player_info.at(4));
		new_player.club = player_info.at(5);

		
		size_t player_info_length = player_info.size();


		for (size_t i = 6; i < player_info_length - 1; i++) {

			try {
				new_player.stats.push_back(std::stoi(player_info.at(i)));
			}

			catch (const std::invalid_argument& error){
				new_player.stats.push_back(0);
			}
		}

		new_player.value = player_info.at(player_info_length - 1);
		all_players.push_back(new_player);

  	}



	inputFile.close();

	return 0;
	
}
