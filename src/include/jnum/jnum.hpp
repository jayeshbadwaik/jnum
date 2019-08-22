#ifndef JNUM_JNUM_HPP
#define JNUM_JNUM_HPP

#include <algorithm>
#include <cstring>
#include <jnum/detail/array.hpp>
#include <jnum/detail/traits.hpp>
#include <optional>
#include <string_view>
#include <type_traits>

namespace jnum {
template <class Tp>
struct is_jnum : public detail::is_jnum<Tp> {
};

template <class A>
using string
  = std::basic_string<char, std::char_traits<char>, detail::rebind_to<char, A>>;

template <typename Tp>
inline constexpr bool is_jnum_v = is_jnum<Tp>::value;

template <typename Jnum>
auto to_jnum(typename Jnum::underlying_type const& uv) -> Jnum
{
  static_assert(is_jnum<Jnum>::value);
  constexpr auto const& option_array = Jnum::option_array;
  auto const it
    = std::find_if(std::begin(option_array),
                   std::end(option_array),
                   [uv](auto const& a) { return a.underlying_value() == uv; });
  if (it != std::end(option_array)) {
    return *it;
  }
  throw std::runtime_error("Unexpected underlying_value encountered.");
}

template <typename Jnum>
auto to_jnum(typename Jnum::enum_type const& e) -> Jnum
{
  static_assert(jnum::is_jnum<Jnum>::value);
  constexpr auto const& option_array = Jnum::option_array;
  auto const it = std::find_if(std::begin(option_array),
                               std::end(option_array),
                               [e](auto const& a) { return a == e; });
  if (it != std::end(option_array)) {
    return *it;
  }
  throw std::runtime_error("Unexpected enum value encountered.");
}

template <typename Jnum>
auto to_jnum(std::string_view input) -> Jnum
{
  static_assert(jnum::is_jnum<Jnum>::value);
  constexpr auto const& option_string_array = Jnum::option_string_array;

  auto const it = std::find(
    std::begin(option_string_array), std::end(option_string_array), input);

  if (it != std::end(option_string_array)) {
    auto const index
      = static_cast<std::size_t>(it - std::begin(option_string_array));
    return Jnum::option_array[index];
  }
  throw std::runtime_error("Unexpected string representation encountered.");
}

template <typename Jnum,
          typename = std::enable_if_t<jnum::is_jnum<Jnum>::value>>
auto to_string(Jnum const& jnum) -> std::string_view
{
  constexpr auto const& option_array = Jnum::option_array;
  constexpr auto const& option_string_array = Jnum::option_string_array;

  auto const it
    = std::find(std::begin(option_array), std::end(option_array), jnum);

  auto const index = static_cast<std::size_t>(it - std::begin(option_array));

  return option_string_array[index];
}

template <typename Jnum,
          typename A = std::allocator<void>,
          typename = std::enable_if_t<jnum::is_jnum<Jnum>::value>>
auto to_namespaced_string(Jnum const& jnum, A const& a = A()) -> string<A>
{
  constexpr auto const& option_array = Jnum::option_array;
  constexpr auto const& option_string_array = Jnum::option_string_array;

  auto const it
    = std::find(std::begin(option_array), std::end(option_array), jnum);

  auto const index = static_cast<std::size_t>(it - std::begin(option_array));

  return std::string(Jnum::namespace_string, a) + string<A>("::", a)
         + std::string(Jnum::string, a) + std::string("::", a)
         + std::string(option_string_array[index], a);
}
} // namespace jnum

#endif // JNUM_JNUM_HPP
