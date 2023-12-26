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
    if (nxt_pattern_element == "*" || nxt_pattern_element == "?") {
        if (check_pattern(input_line, pattern,
                          input_index,
                          pattern_index + cur_pattern_element.size() + nxt_pattern_element.size()))
            return true;
    }

    if (pattern[pattern_index] == '\\') { //special character set handle
        pattern_index += 2;
        if (!check_slash_pattern(cur_pattern_element, input_line[input_index]))
            return false;
    } else if (pattern[pattern_index] == '.') { //always match
        pattern_index +=1;
    } else if (pattern[pattern_index] == '[') { //match from given group of characters
        pattern_index += cur_pattern_element.size();
        if (!check_bracket_group_pattern(cur_pattern_element, input_line[input_index]))
            return false;
    } else if (pattern[pattern_index] == '(') { //match segment with different options
        std::set<std::string> alternation_options = generate_options(cur_pattern_element);
        //each time we replace the substring of the options by just the pattern itself
        for (std::string option : alternation_options) {
            if (check_pattern(input_line,
                              pattern.substr(0,pattern_index) + option + pattern.substr(pattern_index + cur_pattern_element.size()),
                              input_index,
                              pattern_index))
                return true;
        }
        return false;
    }else { //compare if the character is the same
        if (pattern[pattern_index] != input_line[input_index])
            return false;
        pattern_index += 1;
    }


    if (nxt_pattern_element == "+" || nxt_pattern_element == "*") {
        //after first match, we can replace + with *
        pattern[pattern_index] = '*';
        std::cout << pattern << std::endl;
        if (check_pattern(input_line, pattern,
                      input_index + 1,
                      pattern_index-cur_pattern_element.size()))
            return true;
    }

    if (nxt_pattern_element == "+" || nxt_pattern_element == "*" || nxt_pattern_element == "?") {
        return check_pattern(input_line, pattern,
                             input_index + 1,
                             pattern_index + nxt_pattern_element.size());
    } else {

        return check_pattern(input_line, pattern,
                             input_index + 1,
                             pattern_index);
    }

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
