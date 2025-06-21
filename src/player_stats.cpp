#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include <cmath>
#include "player_stats.hpp"

const std::vector<std::string> parse_arguments(int argc, char* argv[]) {
	

	// return arguments
	std::vector<std::string> arguments; 
	int counter = 0;
	while (counter < argc) {
		arguments.push_back(argv[counter++]);
	}

	return arguments;
	

}


const std::vector<std::string> find_flags(std::vector<std::string> arguments) {

	std::vector<std::string> flags;

	for (std::string arg : arguments)
	{
		std::cout << "You provided an argument, it is: " << arg << std::endl;
		std::string arg_string = arg;
		if (arg_string.find("--") != std::string::npos){
			flags.push_back(arg_string);
		}
	}
	return flags;
}



const std::vector<Player> create_player_vector(std::string fileName) {

	std::ifstream inputFile;

  	inputFile.open(fileName);

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

	return all_players;
	
}




/* We will have to assume the player data is up-to-date */
/* Take in reference to player, returns year born */
int ageToYearBorn ( Player &p ) {
	std::cout << "Calculating what year " << p.name << " was born " << std::endl;
	int age = p.age;

	time_t today = time( NULL ); // gives me a timestape
	tm* local_time = localtime( &today ); // gives me a struct of time info
	/* from the documentation about localtime()  see https://cplusplus.com/reference/ctime/localtime/
	 * "The returned value points to an internal object whose validity or value may be altered 
	 * by any subsequent call to gmtime or localtime."
	 * Thus, we should copy the info out before we call the function again.
	 */
	int month = local_time->tm_mon + 1; // tm_mon is month 0-11 (so we add 1).
	int year = local_time->tm_year; // gives us the year from 1900
	year += 1900;
	std::cout << "Today is the " << month << " month of " << year << std::endl;
	int yearBorn = year - age; // calculate the year born by subtracting age
	std::cout << p.name << " was born in the year " << yearBorn << std::endl;
	return yearBorn;
}

int similarity( Player &a, Player &b ){
	int similarity_percent = 0;

	std::vector<int> player_a_stats = a.stats;
	std::vector<int> player_b_stats = b.stats;

	int min = std::min(a.stats.size(), b.stats.size());
	double summation = 0;

	for (int i = 0; i < min; i++){
		summation += std::pow( a.stats.at(i) - b.stats.at(i), 2);
	}

	summation = std::sqrt(summation);
	similarity_percent = (1/(1 + summation)) * 100;

	return similarity_percent;
}


