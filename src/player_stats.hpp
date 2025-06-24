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


/* You will need to define and implement these functions
 * How exactly is up to you,
 * i.e., do you want to pass in sets of Players or set of values
 */


/* Example of a function definition:
 * Calculate the year a player was born from their age.
 * We know the data was last updated in June 2025 so we assume it is up-to-date.
 * Takes in an instance of Struct Player, returns the year he was born.
 */
int ageToYearBorn ( Player &p );



/* print_histogram() -- prints histogram of player stats [0, 100]
 */
void print_histogram(Player& p, const std::vector<std::string> &headers);


/* to_lower() -- convert string to lowercase, use for user input and change when reading name in, so that .find() is case insensitive
*/
const std::string to_lower(std::string& word);


/* print_player_infocard; -- prints infocard of player, only when just --name is called
 */
void print_player_infocard(Player &p, std::vector<Player> all_players);


/* fixUserInput() -- takes non_flag_inputs (so player names, country names, or club names), makes it universally lowercase and trims white spaces
*/
const std::string fixUserInput(const std::vector<std::string>& non_flag_inputs);


/* parse_arguments() -- go through arguments and store in a vector of strings
*/
const std::vector<std::string> parse_arguments(int argc, char* argv[]);

/* find_flags() -- go through all arguments and find flags (--)
*/
const std::vector<std::string> find_flags(const std::vector<std::string>& arguments);


/* non_flag_inputs() -- go through all arguments, extract non_flag_inputs (everything that is not a file or a flag)
*/
const std::vector<std::string> non_flag_inputs(const std::vector<std::string> &arguments);


/* create_player_vector() -- go through csv and create a vector of players for each problem
*/
const std::vector<Player> create_player_vector(const std::string& fileName);


/* find_csv() -- find csv file (if provided) from vector of arguments
*/
const std::string find_csv(const std::vector<std::string>& arguments);


/* check_flags() -- makes sure flag inputs are valid commands, if not quits program with error message
*/
bool check_flags(const std::vector<std::string>& flags);


/* find_headers() -- goes through csv file and extracts headers from 1st row
*/
const std::vector<std::string> find_headers(const std::string &filename);


/* filter_by_flag() -- main hub for different filter function calls based on different flags
*/
std::vector<Player> filter_by_flag(const std::vector<Player>& all_players, const std::vector<std::string>& flags, const std::vector<std::string>& non_input_flags, const std::vector<std::string>& headers);


/* create_chart() -- if --chart is invoked, keep asking for user input until 1 player, calls histogram function on player
*/
std::vector<Player> create_chart(const std::vector<Player>& all_players, std::string& input, const std::vector<std::string>& headers);


/* country_filter() -- if --country is invoked, print names of all players from that conutry, fixes lowercase input
*/
std::vector<Player> country_filter(const std::vector<Player>& players, std::string country);


/* club_filter() -- if --club is invoked, print names of all players from that club, fixes user input (doesn't have to be in a string)
*/
std::vector<Player> club_filter(const std::vector<Player>& all_players, std::string club_input);


/* marking_filter(), agility_filter(), vision_filter() -- filters based on specific stat, each function takes in a filter and checks for <, >, =
*/
std::vector<Player> marking_filter(const std::vector<Player>& all_players, std::string filter);
std::vector<Player> agility_filter(const std::vector<Player>& all_players, std::string filter);
std::vector<Player> vision_filter(const std::vector<Player>& all_players, std::string filter);



/* similarity(); -- compeare two players' attributes and calculate a similarity score
 * Look at the columns "ball_control" to "gk_reflexes" as an array of skill stats.
 * Similarity should be the Euclidian distance between the stats vectors / arrays of
 * player a and player b.
 */

int similarity( Player &a, Player &b );

/* count()  -- should return the number if items in a set */

/* sum() -- should return the sum of a set */

/* mean() -- should return the average value of the set */

/* min() -- should return the smallest value in a set */
int min(std::vector<int>& nums);

/* max() -- should return the largest value in a set */
int max(std::vector<int>& nums);

/* filter() -- should return all values given filter is a match */

/* optional functions (bonus):
 * percentile() -- for a given player and stat, calculate his rank in the set given.
 * The type of querie we are answering could be
 * "Where does Casper Eklund stamina rank against his teammates at Hammarby IF".
 * How would we answer such a  query?
 */

#endif
