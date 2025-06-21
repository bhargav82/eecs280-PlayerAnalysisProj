/* In this file we will define objects and functions that we use
 * when calcualating players statistics.
 */

#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H
#include <string>
#include <vector>

struct Player {
	std::string name;
	int age;
	std::string country;
	int height_cm;
	int weight_kg;
	std::string club;
	std::string value;

	std::vector<int> stats;

	/* You will want to add things here */
	/* The first columns "player,country,height,weight,age,club" and the last
         * "value" could be stored seperate, but the stats you may want to keep
	 * as an array?
	 */
};

/* Example of a function definition:
 * Calculate the year a player was born from their age.
 * We know the data was last updated in June 2025 so we assume it is up-to-date.
 * Takes in an instance of Struct Player, returns the year he was born.
 */
int ageToYearBorn ( Player &p );
const std::vector<std::string> parse_arguments(int argc, const char* argv[]);
const std::vector<std::string> find_flags(const std::vector<std::string>& arguments);
const std::vector<Player> create_player_vector(const std::string& fileName);
const std::vector<Player> filtered_players(const std::vector<Player>& total_list_players, const std::string& filter);
const std::vector<std::string> non_flag_inputs(const std::vector<std::string> &arguments);



void print_histogram(Player& p);

int similarity( Player &a, Player &b );


/* You will need to define and implement these functions
 * How exactly is up to you,
 * i.e., do you want to pass in sets of Players or set of values
 */

/* similarity(); -- compeare two players' attributes and calculate a similarity score
 * Look at the columns "ball_control" to "gk_reflexes" as an array of skill stats.
 * Similarity should be the Euclidian distance between the stats vectors / arrays of
 * player a and player b.
 */


/* count()  -- should return the number if items in a set */

/* sum() -- should return the sum of a set */

/* mean() -- should return the average value of the set */

/* min() -- should return the smallest value in a set */

/* max() -- should return the largest value in a set */

/* filter() -- should return all values given filter is a match */

/* optional functions (bonus):
 * percentile() -- for a given player and stat, calculate his rank in the set given.
 * The type of querie we are answering could be
 * "Where does Casper Eklund stamina rank against his teammates at Hammarby IF".
 * How would we answer such a  query?
 */

#endif
