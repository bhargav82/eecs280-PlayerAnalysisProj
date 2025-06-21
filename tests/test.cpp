#include <gtest/gtest.h>
#include "../src/player_stats.hpp"



int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// only return a vector of strings containing "--"
TEST(find_filters_test, find_filters) {
    
    std::vector<std::string> input_1 = {"./soccer_players", "--age", "-price", "--club"};
    const std::vector<std::string> result_flags_1 = {"--age", "--club"};
    EXPECT_EQ(find_flags(input_1), result_flags_1);


    std::vector<std::string> input_2 = {"./soccer_players"};
    std::vector<std::string> result_2;
    EXPECT_EQ(find_flags(input_2), result_2);
    
}


TEST(parse_args_test, parse_args) {

    const char* fake_args[] = {"./soccer_players", "country", "--price"};
    std::vector<std::string> result = {"./soccer_players", "country", "--price"};
    EXPECT_EQ(parse_arguments(3, const_cast<char**>(fake_args)), result);


    const char* fake_args_2[] = {"\n"};
    std::vector<std::string> result2;
    EXPECT_EQ(parse_arguments(0, const_cast<char**>(fake_args_2)), result2);
    

    const char* fake_args_3[] = {"23", "./soccer_players", "#@$@{}"};
    std::vector<std::string> result3 = {"23", "./soccer_players", "#@$@{}"};
    EXPECT_EQ(parse_arguments(3, const_cast<char**>(fake_args_3)), result3);

    
}