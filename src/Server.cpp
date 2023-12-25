#include <iostream>
#include <string>
#include <set>
#include "Utilities.h"


//checking if the input fits pattern recursively
bool check_pattern(std::string input_line,
                   std::string pattern,
                   int input_index,
                   int pattern_index) {
    //TODO: refactor the loop into recursion

    std::cout << input_index << " " << pattern_index << std::endl;
    if (input_index <= input_line.size() && pattern_index == pattern.size()) {
        //matched
        return true;
    }

    std::string cur_pattern_element = next_pattern_element(pattern, pattern_index);
    std::string nxt_pattern_element = next_pattern_element(pattern, pattern_index + cur_pattern_element.size());

    std::cout << cur_pattern_element << " " << nxt_pattern_element << std::endl;

    // we check if the next pattern element is '+' or '*'
    if (nxt_pattern_element == "*") {
        if (check_pattern(input_line, pattern,
                          input_index,
                          pattern_index + cur_pattern_element.size() + nxt_pattern_element.size()))
            return true;
    }

    if (pattern[pattern_index] == '\\') { //special character set handle
        pattern_index += 2;
        if (!check_slash_pattern(cur_pattern_element, input_line[input_index]))
            return false;
    } else if (pattern[pattern_index] == '[') { //match from given group of characters
        pattern_index += cur_pattern_element.size();
        if (!check_bracket_group_pattern(cur_pattern_element, input_line[input_index]))
            return false;
    } else { //compare if the character is the same
        if (pattern[pattern_index] != input_line[input_index])
            return false;
        pattern_index += 1;
    }


    if (nxt_pattern_element == "+") {
        //after first match, we can replace + with *
        pattern[pattern_index] = '*';
        std::cout << pattern << std::endl;
        if (check_pattern(input_line, pattern,
                      input_index + 1,
                      pattern_index-cur_pattern_element.size()))
            return true;
    }

    if (nxt_pattern_element == "+" || nxt_pattern_element == "*") {
        return check_pattern(input_line, pattern,
                             input_index + 1,
                             pattern_index + nxt_pattern_element.size());
    } else {

        return check_pattern(input_line, pattern,
                             input_index + 1,
                             pattern_index);
    }

}


//match pattern element by element
bool check_pattern(const std::string &input_line, const std::string &pattern) {
    int pattern_index = 0, input_index = 0;

    while (pattern_index < pattern.size() && input_index < input_line.size()) {
        if (pattern[pattern_index] == '\\') {
            //special character set handle
            std::string character_type = pattern.substr(pattern_index, 2);
            pattern_index += 1;
            if (character_type == "\\d") {
                if (!check_is_digit(input_line[input_index])) {
                    return false;
                }
            } else if (character_type == "\\w") {
                if (!check_is_alphanumeric(input_line[input_index])) {
                    return false;
                }
            } else {
                throw_not_find_pattern();
            }
        } else if (pattern[pattern_index] == '[') {
            //match from given group of characters
            std::string segment = "";
            while (pattern[pattern_index] != ']') {
                segment += pattern[pattern_index];
                pattern_index += 1;
            }
            std::set<char> letters = generate_group(segment);
            letters.erase('[');
            letters.erase(']');
            if (letters.count('^')) {
                if (letters.count(input_line[input_index])) {
                    return false;
                }
            } else {
                if (!letters.count(input_line[input_index])) {
                    return false;
                }
            }
        } else {
            //compare if the character is the same
            if (pattern[pattern_index] != input_line[input_index]) {
                return false;
            }
        }
        pattern_index += 1;
        input_index += 1;
    }
    //if input and pattern are both fully matched, we return true
    if (pattern_index == pattern.size() && input_index <= input_line.size()) {
        std::cout << input_line.substr(0, input_index) << std::endl;
        return true;
    }
    return false;
}

//check if a sub-string of the input line contains the given pattern
bool match_pattern(const std::string &input_line, const std::string &pattern) {
    for (int i = 0; i < input_line.size(); i++) {
        if (check_pattern(input_line.substr(i), pattern, 0, 0)) {
            return true;
        }
    }
    return false;
}


int main(int argc, char *argv[]) {
    // You can use print statements as follows for debugging, they'll be visible
    // when running tests.
    std::cout << "Logs from your program will appear here" << std::endl;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        //std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    std::string input_line;
    std::getline(std::cin, input_line);

    try {
        if (pattern[0] == '^') {
            //string anchor case: only matching the entire line
            if (check_pattern(input_line, pattern.substr(1), 0, 0)) {
                std::cout << "MATCHED" << std::endl;
                return 0;
            }
            return 1;
        } else if (pattern[pattern.size() - 1] == '$') {
            if (check_pattern(input_line.substr(input_line.size() - pattern.substr(1).size()),
                              pattern.substr(0, pattern.size() - 1), 0, 0)) {
                std::cout << "MATCHED" << std::endl;
                return 0;
            }
            return 1;
        } else if (match_pattern(input_line, pattern)) {
            std::cout << "MATCHED" << std::endl;
            return 0;
        } else {
            return 1;
        }
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
