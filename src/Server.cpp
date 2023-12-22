#include <iostream>
#include <string>
#include <set>

void throw_not_find_pattern() { throw std::runtime_error("Unhandled pattern"); }

bool check_is_single_index(const std::string &input ,
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
    for (char letter : group) {
        legal_letters.insert(letter);
    }
    return legal_letters;
}

bool match_pattern(const std::string &input_line , const std::string &pattern) {
    if (pattern.length() == 1) {
        return input_line.find(pattern) != std::string::npos;
    } else if (pattern[0] == '\\') {
        if (pattern == "\\d") {
            // check if there is a single digit from the input line
            for (auto character: input_line) {
                if (check_is_digit(character)) {
                    return true;
                }
            }
        } else if (pattern == "\\w") {
            for (auto character: input_line) {
                if (check_is_alphanumeric(character)) {
                    return true;
                }
            }
        }
    } else if (pattern[0] == '[' && pattern[pattern.size() - 1] == ']') {
        //we have to match for a group of character
        std::set<char> legal_letters = generate_group(pattern);
        legal_letters.erase('[');
        legal_letters.erase(']');
        for (auto character: input_line) {
            if (check_is_in_character_group(character , legal_letters)) {
                return true;
            }
        }
    } else {
        throw_not_find_pattern();
    }
    return false;
}


int main(int argc , char *argv[]) {
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
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    std::string input_line;
    std::getline(std::cin , input_line);

    try {
        if (match_pattern(input_line , pattern)) {
            //std::cout << "Pattern Find" << std::endl;
            return 0;
        } else {
            return 1;
        }
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
