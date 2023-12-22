#include <iostream>
#include <string>

void throw_not_find_pattern() { throw std::runtime_error("Unhandled pattern"); }

bool check_is_single_index(const std::string &input,
                           const std::string &pattern) {
  return input == pattern;
}

bool check_is_digit(const std::string &input) {
  if (input.size() == 1) {
    return input[0] <= '9' && input[0] >= '0';
  } else {
    return false;
  }
}

bool match_pattern(const std::string &input_line, const std::string &pattern) {
  if (pattern.length() == 1) {
    return input_line.find(pattern) != std::string::npos;
  } else if (pattern[0] == '\\') {
    return check_is_digit(input_line);
  } else {
    throw_not_find_pattern();
    return false;
  }
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
    std::cerr << "Expected first argument to be '-E'" << std::endl;
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
