#include <iostream>

#include <string>

void cli() {

  bool done = false;
  std::string input;

  while (!done) {
    std::cout << "Enter Command: ";
    std::getline(std::cin, input);

    if (input == "q") {
      done = true;
    } else if (input == "h") {
      std::cout << "\nCommand List:\n"
                << "h: Display this help text\n"
                << "q: Exit the program\n"
                << "n: Do nothing\n"

                << std::endl;
    } else if (input == "n") {
      std::cout << "This did nothing!\n";

    } else {
      std::cout << "Unrecognized Command" << std::endl;
    }
  }
}
