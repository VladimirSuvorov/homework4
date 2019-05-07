#include "testing_core.hxx"

TEST(test_const_char_output_is_correct, test_const_char_output_is_correct){
    using namespace std;
    stringstream ss;
    print_ip_tester pip{ss};
    bool mustBeTrue = test_const_char_output_is_correct(pip);
    ASSERT_TRUE(mustBeTrue);
}

TEST(test_const_short_output_is_correct, test_const_short_output_is_correct){
    using namespace std;
    stringstream ss;
    print_ip_tester pip{ss};
    bool mustBeTrue = test_const_short_output_is_correct(pip);
    ASSERT_TRUE(mustBeTrue);
}

TEST(test_const_int_output_is_correct, test_const_int_output_is_correct){
    using namespace std;
    stringstream ss;
    print_ip_tester pip{ss};
    bool mustBeTrue = test_const_int_output_is_correct(pip);
    ASSERT_TRUE(mustBeTrue);
}

TEST(test_const_long_long_output_is_correct, test_const_long_long_output_is_correct){
    using namespace std;
    stringstream ss;
    print_ip_tester pip{ss};
    bool mustBeTrue = test_const_long_long_output_is_correct(pip);
    ASSERT_TRUE(mustBeTrue);
}

TEST(test_const_std_string_output_is_correct, test_const_std_string_output_is_correct){
    using namespace std;
    stringstream ss;
    print_ip_tester pip{ss};
    bool mustBeTrue = test_const_std_string_output_is_correct(pip);
    ASSERT_TRUE(mustBeTrue);
}

TEST(test_const_std_vector_uint8_t_output_is_correct, test_const_std_vector_uint8_t_output_is_correct){
    using namespace std;
    stringstream ss;
    print_ip_tester pip{ss};
    bool mustBeTrue = test_const_std_vector_uint8_t_output_is_correct(pip);
    ASSERT_TRUE(mustBeTrue);
}

TEST(test_const_std_list_uint8_t_output_is_correct, test_const_std_list_uint8_t_output_is_correct){
    using namespace std;
    stringstream ss;
    print_ip_tester pip{ss};
    bool mustBeTrue = test_const_std_list_uint8_t_output_is_correct(pip);
    ASSERT_TRUE(mustBeTrue);
}

TEST(test_const_tuple_output_is_correct, test_const_tuple_output_is_correct){
    using namespace std;
    stringstream ss;
    print_ip_tester pip{ss};
    bool mustBeTrue = test_const_tuple_output_is_correct(pip);
    ASSERT_TRUE(mustBeTrue);
}


