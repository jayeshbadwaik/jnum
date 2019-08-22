#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include <catch2/catch.hpp>
#include <test_jnum/loglevel.hpp>

TEST_CASE("jnum : Type Checking", "[jnum]")
{
  static_assert(
      std::is_same_v<test_jnum::log_level::underlying_type, std::size_t>);
  static_assert(test_jnum::log_level::string == "log_level");
  static_assert(test_jnum::log_level::namespace_string == "test_jnum");
  static_assert(test_jnum::log_level::noption == 2);
  static_assert(
      test_jnum::log_level::option_array[0] == test_jnum::log_level::quiet);
  static_assert(
      test_jnum::log_level::option_array[1] == test_jnum::log_level::normal);
  static_assert(test_jnum::log_level::option_string_array[0] == "quiet");
  static_assert(test_jnum::log_level::option_string_array[1] == "normal");
}

TEST_CASE("jnum : Constructor from underlying_type", "[jnum]")
{
  auto const loglevel = jnum::to_jnum<test_jnum::log_level>(10);
  REQUIRE(loglevel == test_jnum::log_level::normal);

  REQUIRE_THROWS(jnum::to_jnum<test_jnum::log_level>(40));
}

TEST_CASE("jnum : Constructor from underlying_enum", "[jnum]")
{
  auto const underlying_enum = test_jnum::log_level::enum_type::normal;
  auto const loglevel = jnum::to_jnum<test_jnum::log_level>(underlying_enum);
  REQUIRE(loglevel == test_jnum::log_level::normal);

  REQUIRE_THROWS(jnum::to_jnum<test_jnum::log_level>(
      static_cast<test_jnum::log_level::enum_type>(45)));
}

TEST_CASE("jnum : Constructor from string_name", "[jnum]")
{
  auto const loglevel = jnum::to_jnum<test_jnum::log_level>("normal");
  REQUIRE(loglevel == test_jnum::log_level::normal);

  REQUIRE_THROWS(jnum::to_jnum<test_jnum::log_level>("invalid_input"));
}

TEST_CASE("jnum : Convert to string", "[jnum]")
{
  auto const loglevel = jnum::to_jnum<test_jnum::log_level>(10);
  REQUIRE(jnum::to_string(loglevel) == "normal");
}

TEST_CASE("jnum : Convert to namespaced string", "[jnum]")
{
  auto const loglevel = jnum::to_jnum<test_jnum::log_level>(10);
  REQUIRE(
      jnum::to_namespaced_string(loglevel) == "test_jnum::log_level::normal");
}

