#include <iostream>
#include "libcaptest/captest.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0] << " <file_path> <capabilities>\n";
    return 1;
  }

  const auto returnCode{captest::executeCapabilityTest(argv[1], argv[2])};
  std::cout << "Program returned: " << returnCode << "\n";

  return 0;
}