#include <iostream>
#include <string>
#include <set>

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


std::set<char> generate_group(const std::string &group) {
    std::set<char> legal_letters;
    for (char letter: group) {
        legal_letters.insert(letter);
    }
    return legal_letters;
}


//match pattern element by element
bool match_pattern(const std::string &input_line, const std::string &pattern) {
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
                if (letters.count(input_line[input_index])) {
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
    return pattern_index == pattern.size() && input_index < input_line.size();
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
