#include "print_ip.hpp"
#include "global_constants.hpp"

int main(int argc, char* argv[]) {
	using namespace global_constants;
	using namespace print_ip_ns;

	//an utility class instance (a wrapper), that invokes print_ip function internally
	ip_printer out;

	out("char = ", const_char, '\n');
	out("short = ", const_short, '\n');
	out("int = ", const_int, '\n');
	out("long long = ", const_long_long, '\n');
	out("std::string = ", const_std_string, '\n');
	out("std::vector<uint8_t> = ", const_std_vector_uint8_t, '\n');
	out("std::list<uint8_t> = ", const_std_list_uint8_t, '\n');
	out("std::tuple = ", const_tuple, '\n');
}
