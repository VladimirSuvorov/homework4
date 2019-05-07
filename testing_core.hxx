#ifndef PRINT_IP_PROJECT_TESTS_HXX
#include <sstream>
#include <gtest/gtest.h>
#include "print_ip.hpp"
#include "global_constants.hpp"
#define PRINT_IP_PROJECT_TESTS_HXX

//utility class for testing purposes only
class print_ip_tester : private print_ip_ns::ip_printer<std::stringstream> {
public:
	using base =  print_ip_ns::ip_printer<std::stringstream>;
	print_ip_tester(std::stringstream& ss) :
		base(ss)
	{}

	template<typename Data>//1st param - takes the printable ip data, 2nd - a string representation of the data must be after printing ip out.
	bool test(Data&& data, std::string_view should_be) {
		using namespace std;
		(*this)("", forward<Data>(data), "");
		string result;
		out_ >> result;
		out_.clear();
		return (result == should_be);
	}
};

//generates test_##TYPE##_output_is_correct function family for all the underlying types.
//thats all why this macro exists.
#define DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION_FOR_TYPE(TYPE)\
bool test_##TYPE##_output_is_correct(print_ip_tester& pit){\
	using namespace global_constants;\
	return pit.test(TYPE, TYPE##_value);\
}
DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION_FOR_TYPE(const_char)
DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION_FOR_TYPE(const_short)
DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION_FOR_TYPE(const_int)
DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION_FOR_TYPE(const_long_long)
DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION_FOR_TYPE(const_std_string)
DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION_FOR_TYPE(const_std_vector_uint8_t)
DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION_FOR_TYPE(const_std_list_uint8_t)
DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION_FOR_TYPE(const_tuple)
#undef DEFINE_OUTPUT_CORRECTNESS_CHECK_FUNCTION


int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}


#endif
