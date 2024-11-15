// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from interface:msg/AutoaimData.idl
// generated code does not contain a copyright notice

#ifndef INTERFACE__MSG__DETAIL__AUTOAIM_DATA__TRAITS_HPP_
#define INTERFACE__MSG__DETAIL__AUTOAIM_DATA__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "interface/msg/detail/autoaim_data__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace interface
{

namespace msg
{

inline void to_flow_style_yaml(
  const AutoaimData & msg,
  std::ostream & out)
{
  out << "{";
  // member: yaw_angle_diff
  {
    out << "yaw_angle_diff: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_angle_diff, out);
    out << ", ";
  }

  // member: pitch_angle_diff
  {
    out << "pitch_angle_diff: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch_angle_diff, out);
    out << ", ";
  }

  // member: fire
  {
    out << "fire: ";
    rosidl_generator_traits::value_to_yaml(msg.fire, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const AutoaimData & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: yaw_angle_diff
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw_angle_diff: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_angle_diff, out);
    out << "\n";
  }

  // member: pitch_angle_diff
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pitch_angle_diff: ";
    rosidl_generator_traits::value_to_yaml(msg.pitch_angle_diff, out);
    out << "\n";
  }

  // member: fire
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "fire: ";
    rosidl_generator_traits::value_to_yaml(msg.fire, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const AutoaimData & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace interface

namespace rosidl_generator_traits
{

[[deprecated("use interface::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const interface::msg::AutoaimData & msg,
  std::ostream & out, size_t indentation = 0)
{
  interface::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use interface::msg::to_yaml() instead")]]
inline std::string to_yaml(const interface::msg::AutoaimData & msg)
{
  return interface::msg::to_yaml(msg);
}

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
