#pragma once

#include <iostream>
#include <type_traits>
#include <utility>

namespace type_converter_api {
namespace sfinae {

/// Структура для проверки наличия оператора <<
template<typename T, typename = void>
struct has_left_shift_operator : std::false_type
{
};

/// Структура для проверки наличия оператора <<
template<typename T>
struct has_left_shift_operator<T, std::void_t<decltype((std::declval<std::ostream&>() << std::declval<T>()))>>
    : std::true_type
{
};

/// Результат проверки наличия оператора <<
template<typename T>
constexpr bool has_left_shift_operator_v = has_left_shift_operator<T>::value;

/// Структура для проверки наличия оператора >>
template<typename T, typename = void>
struct has_right_shift_operator : std::false_type
{
};

/// Структура для проверки наличия оператора >>
template<typename T>
struct has_right_shift_operator<T, std::void_t<decltype((std::declval<std::istream&>() >> std::declval<T&>()))>>
    : std::true_type
{
};

/// Результат проверки наличия оператора >>
template<typename T>
constexpr bool has_right_shift_operator_v = has_right_shift_operator<T>::value;

/// Структура для проверки наличия оператора emplace_back
template<typename Container, typename T, typename = void>
struct has_emplace_back : std::false_type
{
};

/// Структура для проверки наличия оператора emplace_back
template<typename Container, typename T>
struct has_emplace_back<Container, T, std::void_t<decltype((std::declval<Container&>().emplace_back(std::declval<T>())))>>
    : std::true_type
{
};

/// Результат проверки наличия оператора emplace_back
template<typename Container, typename T>
constexpr bool has_emplace_back_v = has_emplace_back<Container, T>::value;

} // namespace sfinae
} // namespace type_converter_api