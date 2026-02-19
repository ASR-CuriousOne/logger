#include <functional>
#include <string_view>

namespace Logger {
struct Channel {
  std::string_view name;

  constexpr Channel(std::string_view n) : name(n) {}

  bool operator==(const Channel &other) const { return this == &other; }
};

inline constexpr Channel General{"General"};
} // namespace Logger
