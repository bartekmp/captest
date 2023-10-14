#pragma once

#include <filesystem>
#include <sys/capability.h>
#include <sys/types.h>
#include <unistd.h>

namespace fs = std::filesystem;

namespace captest {
struct ScopedCapabilities {
private:
  const fs::path filePath;
  cap_t savedCapabilities;

public:
  ScopedCapabilities(const fs::path &path, cap_t caps)
      : filePath{path}, savedCapabilities{caps} {}
  ~ScopedCapabilities() {
    cap_set_file(filePath.string().c_str(), savedCapabilities);
    cap_free(savedCapabilities);
  }
};

bool setFileCapabilities(const fs::path &filepath,
                         const std::string &capabilities);

int executeCapabilityTest(const std::string &binaryPath,
                          const std::string &capabilities);
} // namespace captest