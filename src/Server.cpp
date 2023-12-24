#include <iostream>
#include <string>
#include <set>
#include "Utilities"


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
            while (pattern[pattern_index]!=']') {
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
            }else {
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
    return pattern_index == pattern.size() && input_index <= input_line.size();
}

//check if a sub-string of the input line contains the given pattern
bool match_pattern(const std::string &input_line, const std::string &pattern) {
    for (int i = 0 ; i < input_line.size() ; i++) {
        if (check_pattern(input_line.substr(i) , pattern)) {
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
        if (match_pattern(input_line, pattern)) {
            std::cout << "Pattern Find" << std::endl;
            return 0;
        } else {
            return 1;
        }
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
