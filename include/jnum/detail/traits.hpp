#ifndef JNUM_DETAIL_TRAITS_HPP
#define JNUM_DETAIL_TRAITS_HPP

namespace jnum::detail {
template <class Tp>
struct has_is_jnum {
private:
  struct two {
    char lx;
    char lxx;
  };

  template <class Up>
  static two test(...);

  template <class Up>
  static char test(typename Up::is_jnum* = nullptr);

public:
  static const bool value = (sizeof(test<Tp>(nullptr)) == 1);
};

template <class Tp, bool = has_is_jnum<Tp>::value>
struct is_jnum : public Tp::is_jnum {
};

template <class Tp>
struct is_jnum<Tp, false> : public std::false_type {
};

template <class T, class A>
using rebind_to = typename std::allocator_traits<A>::template rebind_alloc<T>;
} // namespace jnum::detail

#endif // JNUM_DETAIL_TRAITS_HPP
