#ifndef PRINT_IP_PROJECT_GLOBAL_CONSTANTS_HPP
#include <vector>
#include <list>
#include <array>
#define PRINT_IP_PROJECT_GLOBAL_CONSTANTS_HPP
namespace global_constants {
	using namespace std;
	constexpr char const_char(-1);
	constexpr short const_short(0);
	constexpr int const_int(2130706433);
	constexpr long long const_long_long(8875824491850138409);
	const std::string const_std_string{ "127.0.0.1" };
	const std::vector<uint8_t> const_std_vector_uint8_t{ 198, 168, 110, 100 };
	const std::list<uint8_t> const_std_list_uint8_t{ 192, 168, 120, 101 };
	std::tuple	const_tuple{
		std::tuple{const_char, const_short, const_int, const_long_long, std::tuple{const_std_string, const_std_vector_uint8_t}},
		const_std_list_uint8_t,
		string_view("188"),
		"168",
		array<uint8_t, 2>{22,30},
	};
	constexpr auto const_char_value = "255";
	constexpr auto const_short_value = "0.0";
	constexpr auto const_int_value = "127.0.0.1";
	constexpr auto const_long_long_value = "123.45.67.89.101.112.131.41";
	constexpr auto const_std_string_value = "127.0.0.1";
	constexpr auto const_std_vector_uint8_t_value = "198.168.110.100";
	constexpr auto const_std_list_uint8_t_value = "192.168.120.101";

	constexpr auto const_tuple_value = "255.0.0.127.0.0.1.123.45.67.89.101.112.131.41.127.0.0.1.198.168.110.100.192.168.120.101.188.168.22.30";
}
#endif // !1
