#ifndef PRINT_IP_PROJECT_SFINAE_CHECKS_HPP
#define PRINT_IP_PROJECT_SFINAE_CHECKS_HPP

template<typename...Ts>
struct type_sequence {};//utility, for convinience only


template<typename T>
struct has_substr {
	template<typename U>
	static auto check(U c)->type_sequence<
		decltype(std::declval<U>().substr(std::declval<size_t>(), std::declval<size_t>()))
	>;
	static std::false_type check(...);
	//std::is_same_v<decltype(check(std::declval<T>())), std::true_type>
	constexpr static bool value = !std::is_same_v <std::false_type, decltype(check(std::declval<T>()))>;
};
template<typename T>
constexpr bool is_string_v = ((has_substr<T>::value) || std::is_pointer_v<T>);
//if something has substr it probably a some string-like type. 
//If it is a pointer - probably it is a zero-terminated string of some implementation specific characters, 
//where T is an implementation specific character.





template<typename T>
struct has_const_iterators {
	template<typename U>
	static auto check(U c)->type_sequence<
		decltype(std::cbegin(std::declval<U>())),
		decltype(std::cend(std::declval<U>()))
	>;
	static std::false_type check(...);
	//std::is_same_v<decltype(check(std::declval<T>())), std::true_type>
	constexpr static bool value = !std::is_same_v <std::false_type, decltype(check(std::declval<T>()))>;

};
template<typename T>
constexpr bool has_const_iterators_v = has_const_iterators<T>::value;

#endif // !PRINT_IP_PROJECT_SFINAE_CHECKS_HPP
