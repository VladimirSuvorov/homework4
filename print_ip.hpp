#ifndef PRINT_IP_PROJECT_PRINT_IP_HPP
#include <iterator>
#include <iostream>
#include <new>
#include <cstddef>
#include "sfinae_checks.hpp"
#include "visit_tuple.hpp"
#define PRINT_IP_PROJECT_PRINT_IP_HPP


namespace print_ip_ns {
	//out - where should out (for testing purposes, prints not only to the std::cout, but to any Ostream, having << operator) 
	//v - what to out (integral types, string-like types, containers (all having cbegin-cend), tuples)
	//NOTE: this declaration is required, it is used in definitions of implementaions, the final definition you can see at the bottom of this header
	template<typename T, typename Ostream>
	Ostream& print_ip(Ostream& out, T&& v);

	namespace {
		template<typename T, typename U, typename = std::enable_if_t<std::is_same_v<T, U>>>
		using must_be_same = T;

		template<typename T, typename = std::enable_if_t<std::is_integral_v<std::decay_t<T>>>>
		using Integral = T;


		//similar to tag dispatch, but not exact tag dipatch
		namespace parameter_types {

			struct having_const_itereators_tag {};
			struct integral_tag {};
			struct tuple_tag {};
			struct string_tag {};


			template<typename T,
				bool has_const_iterators_ = has_const_iterators_v<std::decay_t<T>>,
				bool is_integral_v_ = std::is_integral_v<std::decay_t<T>>,
				bool is_string_v_ = is_string_v<std::decay_t<T>>
			>
				struct type_tag;


			template<typename T>
			struct type_tag<T, true, false, false> {
				using type = having_const_itereators_tag;
			};
			template<typename T>
			struct type_tag<T, false, true, false> {
				using type = integral_tag;
			};
			template<typename T, bool has_const_iterators_>
			struct type_tag<T, has_const_iterators_, false, true> {
				using type = string_tag;
			};
			template<typename T>
			struct type_tag<T, false, false, false> {
				using type = tuple_tag;
			};

			template<typename T>
			using type_tag_t = typename type_tag<T>::type;

		}

		template<typename T, typename type_tag = parameter_types::type_tag_t<T>>
		struct print_implementation;//no definition by default, its OK.

		//Bellow you can see 4 specializations: for container, for integral, for tuple and for string types respectively
		template<typename T>
		struct print_implementation<T, parameter_types::having_const_itereators_tag> {
			template<typename U, typename Ostream, typename = must_be_same<U, T>>
			constexpr static Ostream& print(Ostream& out, U&& v) {
				using namespace std;
				auto from = cbegin(v);
				for (; from != prev(cend(v)); ++from)
					print_ip_ns::print_ip(out, *from) << '.';
				return print_ip_ns::print_ip(out, *from);
			}
		};
		template<typename T>
		struct print_implementation<T, parameter_types::integral_tag> {
			template<typename U, typename Ostream, typename = must_be_same<U, T>>
			constexpr static Ostream& print(Ostream& out, U&& v) {
				using namespace std;
				byte bytes[sizeof(decay_t<T>)];
				new(bytes) decay_t<T>(v);
				auto it(crbegin(bytes));
				for (; it != (crend(bytes) - 1); ++it)
					out << to_integer<uint16_t>(*it) << '.';
				return static_cast<Ostream&>(out << to_integer<uint16_t>(*it));
			}
		};
		template<typename T>
		struct print_implementation<T, parameter_types::tuple_tag> {
			template<typename U, typename Ostream, typename = must_be_same<U, T>>
			constexpr static Ostream& print(Ostream& out, U&& v) {
				visit([&](auto && value, size_t index) {
					using namespace std;
					print_ip_ns::print_ip(out, forward<remove_reference_t<decltype(value)>>(value));
					out << ((index < (tuple_size_v<remove_reference_t<T>>-1)) ? "." : "");
				}, std::forward<T>(v));
				return out;
			}
		};
		template<typename T>
		struct print_implementation<T, parameter_types::string_tag> {
			template<typename U, typename Ostream, typename = must_be_same<U, T>>
			constexpr static Ostream& print(Ostream& out, U&& v) {
				return static_cast<Ostream&>(out << v);
			}
		};
	}


	//exact function for the task
	//out - where should out (for testing purposes, prints not only to the std::cout, but to any Ostream, having << operator) 
	//v - what to out (integral types, string-like types, containers (all having cbegin-cend), tuples)
	template<typename T, typename Ostream>
	Ostream& print_ip(Ostream& out, T&& v) {
		return print_implementation<T>::print(out, std::forward<T>(v));
	}


	//Utility class to specify the same Ostream where should the print_ip fuction print out
	template<typename Ostream = decltype(std::cout)>
	class ip_printer {
	public:
		ip_printer(Ostream& out = std::cout) :
			out_(out) {}

		template<typename T>
		ip_printer& print(T&& v) {
			print_ip_ns::print_ip(out_, std::forward<T>(v));
			return *this;
		}

		template<typename Prefix, typename T, typename Suffix>
		ip_printer& operator()(Prefix&& p, T&& v, Suffix&& s) {
			out_ << std::forward<Prefix>(p);
			print(std::forward<T>(v));
			out_ << std::forward<Suffix>(s);
			return *this;
		}

		template<typename T>
		ip_printer& operator<<(T&& v) {
			return print(std::forward<T>(v));
		}


	protected:
		Ostream& out_;
	};
}
#endif // !PRINT_IP_PROJECT_PRINT_IP_HPP
