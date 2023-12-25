#include "Utilities.h"


void throw_not_find_pattern() { throw std::runtime_error("Unhandled pattern"); }

bool check_is_single_index(const std::string &input,
                           const std::string &pattern) {
    return input == pattern;
}

bool check_is_digit(char input) {
    return input <= '9' && input >= '0';
}

bool check_is_letter(char input) {
    return (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z');
}

bool check_is_alphanumeric(char input) {
    return check_is_digit(input) || check_is_letter(input) || input == '_';
}

bool check_is_in_character_group(char input, std::set<char> group) {
    return group.count(input);
}

//EFFECTS: return the next single element in pattern
//         return "" if no more elements
string next_pattern_element(const std::string &pattern,
                            int pattern_index){
    if (pattern_index == pattern.size()) {
        //no more element
        return "";
    }
    if (pattern[pattern_index] == '\\') {
        return pattern.substr(pattern_index , 2);
    } else if (pattern[pattern_index] == '[') {
        int end_element = pattern;
        int cnt = 1;
        while (pattern[end_element] != ']') {
            end_element += 1;
            cnt += 1;
        }
        return pattern.substr(pattern_index , cnt);
    } else {
        return pattern.substr(pattern_index , 1);
    }
}


std::set<char> generate_group(const std::string &group) {
    std::set<char> legal_letters;
    for (char letter: group) {
        legal_letters.insert(letter);
        //std::cout << letter << std::endl;
    }
    return legal_letters;
}