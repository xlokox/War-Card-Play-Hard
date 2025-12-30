#include "Game.h"
#include <fstream>
#include <iostream>

int main() {
  Game game;
  game.loadFromFile("Input.txt");
  game.executeCommands();
  game.outputFinalState("Output.txt");

  // Verify output file was created
  std::ifstream checkFile("Output.txt");
  if (checkFile.good()) {
    std::cout << "\nOutput file 'Output.txt' created successfully."
              << std::endl;
  } else {
    std::cerr
        << "\nWarning: Output file 'Output.txt' may not have been created."
        << std::endl;
  }
  checkFile.close();

  return 0;
}