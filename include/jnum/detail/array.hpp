#ifndef JNUM_DETAIL_ARRAY_HPP
#define JNUM_DETAIL_ARRAY_HPP

#include <algorithm>
#include <cstring>
#include <optional>
#include <string_view>
#include <type_traits>

namespace jnum::detail {
template <typename... Ts>
constexpr auto make_array(Ts&&... ts)
  -> std::array<std::common_type_t<Ts...>, sizeof...(ts)>
{
  return {std::forward<Ts>(ts)...};
}
} // namespace jnum::detail

#endif // JNUM_DETAIL_ARRAY_HPP
