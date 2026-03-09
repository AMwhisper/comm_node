// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interface:msg/AutoaimData.idl
// generated code does not contain a copyright notice

#ifndef INTERFACE__MSG__DETAIL__AUTOAIM_DATA__TRAITS_HPP_
#define INTERFACE__MSG__DETAIL__AUTOAIM_DATA__TRAITS_HPP_

#include "interface/msg/detail/autoaim_data__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<interface::msg::AutoaimData>()
{
  return "interface::msg::AutoaimData";
}

template<>
inline const char * name<interface::msg::AutoaimData>()
{
  return "interface/msg/AutoaimData";
}

template<>
struct has_fixed_size<interface::msg::AutoaimData>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<interface::msg::AutoaimData>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<interface::msg::AutoaimData>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // INTERFACE__MSG__DETAIL__AUTOAIM_DATA__TRAITS_HPP_
