#ifndef INCLUDE_PROCESSOR_HPP
#define INCLUDE_PROCESSOR_HPP

#include <optional>
#include <string>

class IncludeProcessor {
public:
  // Given an include directive (e.g. #include "file.h" or <stdio.h>),
  // return the absolute path of the file if found.
  std::optional<std::string> locateHeader(const std::string &filename,
                                          bool isSystem);

  // Read a file’s contents into a string.
  std::string readFile(const std::string &path);
};

#endif // INCLUDE_PROCESSOR_HPP
