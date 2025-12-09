#pragma once

#include <cstdlib>

// Simple helper to enable verbose debug logging when EDUCC_DEBUG is set.
inline bool educcDebugEnabled() {
  static bool enabled = std::getenv("EDUCC_DEBUG") != nullptr;
  return enabled;
}
