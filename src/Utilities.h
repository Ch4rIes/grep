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

bool check_is_in_character_group(char input, std::set<char> group);


std::set<char> generate_group(const std::string &group);

#endif //INC_91CE01D83F783997_UTILITIES_H
