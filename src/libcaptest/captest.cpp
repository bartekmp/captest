#include <cstdio>
#include <cstring>
#include <iostream>

#include "captest.h"

namespace captest {

bool setFileCapabilities(const fs::path &filepath,
                         const std::string &capabilities) {
  cap_t caps = cap_from_text(capabilities.c_str());
  if (!caps) {
    std::cerr << "Unable to parse tested capabilities, error: "
              << std::strerror(errno) << "\n";
    return false;
  }

  if (cap_set_file(filepath.string().c_str(), caps) != 0) {
    std::cerr << "Unable to set tested capabilities, error: "
              << std::strerror(errno) << "\n";
    cap_free(caps);
    return false;
  }

  std::cout << "Set " << capabilities << " on " << filepath.string() << "\n";

  cap_free(caps);
  return true;
}

int executeCapabilityTest(const std::string &binaryPath,
                          const std::string &capabilities) {
  std::filesystem::path filePath{binaryPath};
  if (!std::filesystem::exists(filePath)) {
    std::cerr << "Tested file doesn't exist at path: " << filePath.string()
              << "\n";
  }

  cap_t originalCaps = cap_get_file(filePath.string().c_str());
  if (!originalCaps) {
    if (errno == ENODATA) {
      std::cout << "File capability set is empty for file " << filePath.string()
                << "\n";
    } else {
      std::cerr << "Failed to get file capabilities, error: "
                << std::strerror(errno) << "\n";
      return 1;
    }
  }

  ScopedCapabilities scopeGuard(filePath, originalCaps);

  if (!setFileCapabilities(filePath, capabilities)) {
    std::cerr << "Failed setting custom capabilities on " << filePath.string()
              << "\n";
    return 1;
  }

  int retCode = system(filePath.string().c_str());

  return retCode;
}
} // namespace captest
