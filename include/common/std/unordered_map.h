#include <unordered_map>

template<typename Key, typename Value>
using UMap = std::unordered_map<Key, Value>;

template <typename Value = std::string>
using StringUMap = std::unordered_map<std::string, Value>;