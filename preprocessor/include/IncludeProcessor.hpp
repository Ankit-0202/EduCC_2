#ifndef INCLUDE_PROCESSOR_HPP
#define INCLUDE_PROCESSOR_HPP

#include <optional>
#include <string>
#include <vector>

class IncludeProcessor {
public:
  IncludeProcessor(const std::vector<std::string> &systemPaths,
                   const std::vector<std::string> &userPaths);

  // Given a header file name, return its full path if found.
  // The 'isSystem' flag indicates whether to use system include directories.
  std::optional<std::string> locateHeader(const std::string &filename,
                                          bool isSystem);

  // Reads the file content from a given path.
  std::string readFile(const std::string &path);

private:
  std::vector<std::string> m_systemPaths;
  std::vector<std::string> m_userPaths;
};

#endif // INCLUDE_PROCESSOR_HPP
