#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>

#include "straightsModel.h"

int main(int argc, char* argv[]) {
  int seed = 0;
  if (argc > 1) {
    try {
      seed = std::stoi(argv[1]);
    } catch (const std::invalid_argument& ia) {
      seed = std::chrono::system_clock::now().time_since_epoch().count();
      std::cout << "Invalid seed given. Continuing with random seed: " << seed
                << std::endl;
    } catch (const std::exception& e) {
      std::cout << "An exception occured. Aborting." << std::endl;
      throw;
    }
  } else {
    seed = std::chrono::system_clock::now().time_since_epoch().count();
  }

  StraightsModel m{seed};
  m.play();
}
