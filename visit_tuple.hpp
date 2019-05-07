#ifndef PRINT_IP_PROJECT_VISIT_TUPLE_HPP
#include <tuple>
#include <functional>
#define PRINT_IP_PROJECT_VISIT_TUPLE_HPP


namespace {
	template<size_t index>
	struct visit_tuple_implementation : visit_tuple_implementation<index - 1> {
		using base =  visit_tuple_implementation<index - 1>;
		template<typename Callable, typename Tuple>
		constexpr static void visit(Callable&& visitor, Tuple&& t) {
			base::visit(std::forward<Callable>(visitor), std::forward<Tuple>(t));
			base::template visit<index>(std::forward<Callable>(visitor), std::forward<Tuple>(t));
		}
	protected:
		template<size_t index_, typename Callable, typename Tuple>
		constexpr static void visit(Callable&& visitor, Tuple&& t) {
			base::template visit<index_>(std::forward<Callable>(visitor), std::forward<Tuple>(t));
		}
	};
	template<>
	struct visit_tuple_implementation<0> {
		template<typename Callable, typename Tuple>
		constexpr static void visit(Callable&& visitor, Tuple&& t) {
			visit<0>(std::forward<Callable>(visitor), std::forward<Tuple>(t));
		}
	protected:
		template<size_t index, typename Callable, typename Tuple>
		constexpr static void visit(Callable&& visitor, Tuple&& t) {
			std::invoke(visitor, std::get<index>(t), index);
		}
	};
}

//provides an ability to visit any element of any tuple (even tuple of different types tuple<typename...Ts>, where Ts are different)
//usage:
//
//visit([](auto&& tuple_element){
//   /*some stuff here*/
//},
//some_tuple);
//
template<typename Callable, typename Tuple, size_t size = std::tuple_size_v<std::remove_reference_t<Tuple>>>
constexpr void visit(Callable && visitor, Tuple && visitable) {
	visit_tuple_implementation<(size - 1)>::template
		visit(std::forward<Callable>(visitor), std::forward<Tuple>(visitable));
}


#endif // !PRINT_IP_PROJECT_VISIT_TUPLE_HPP
