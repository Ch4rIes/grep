#ifndef INC_91CE01D83F783997_UTILITIES_H
#define INC_91CE01D83F783997_UTILITIES_H

#include <iostream>
#include <string>
#include <set>

void throw_not_find_pattern();

bool check_is_single_index(const std::string &input,
                           const std::string &pattern);

bool check_is_digit(char input);

bool check_is_letter(char input);

bool check_is_alphanumeric(char input);

//parse a segment of string surrounded by bracket and return a set
bool check_is_in_character_group(char input, std::set<char> group);

//return the next element int the pattern
std::string next_pattern_element(const std::string &pattern,
                            int pattern_index);

//check if input char is in numeric/alphanumeric character set
bool check_slash_pattern(const std::string &cur_pattern_element,
                         char input_char);

//parse character set to predicate and return either input char is in/not-in the character set
bool check_bracket_group_pattern(const std::string &cur_pattern_element,
                         char input_char);


std::set<char> generate_group(const std::string &group);

std::set<std::string> generate_options(std::string group);


#endif //INC_91CE01D83F783997_UTILITIES_H
