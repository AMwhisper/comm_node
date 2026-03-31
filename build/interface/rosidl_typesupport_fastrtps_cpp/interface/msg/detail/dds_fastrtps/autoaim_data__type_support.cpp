// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from interface:msg/AutoaimData.idl
// generated code does not contain a copyright notice
#include "interface/msg/detail/autoaim_data__rosidl_typesupport_fastrtps_cpp.hpp"
#include "interface/msg/detail/autoaim_data__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace interface
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_interface
cdr_serialize(
  const interface::msg::AutoaimData & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: yaw_angle_diff
  cdr << ros_message.yaw_angle_diff;
  // Member: pitch_angle_diff
  cdr << ros_message.pitch_angle_diff;
  // Member: fire
  cdr << ros_message.fire;
  // Member: source_timestamp
  cdr << ros_message.source_timestamp;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_interface
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  interface::msg::AutoaimData & ros_message)
{
  // Member: yaw_angle_diff
  cdr >> ros_message.yaw_angle_diff;

  // Member: pitch_angle_diff
  cdr >> ros_message.pitch_angle_diff;

  // Member: fire
  cdr >> ros_message.fire;

  // Member: source_timestamp
  cdr >> ros_message.source_timestamp;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_interface
get_serialized_size(
  const interface::msg::AutoaimData & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: yaw_angle_diff
  {
    size_t item_size = sizeof(ros_message.yaw_angle_diff);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: pitch_angle_diff
  {
    size_t item_size = sizeof(ros_message.pitch_angle_diff);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: fire
  {
    size_t item_size = sizeof(ros_message.fire);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: source_timestamp
  {
    size_t item_size = sizeof(ros_message.source_timestamp);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_interface
max_serialized_size_AutoaimData(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: yaw_angle_diff
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: pitch_angle_diff
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: fire
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: source_timestamp
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  return current_alignment - initial_alignment;
}

static bool _AutoaimData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const interface::msg::AutoaimData *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _AutoaimData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<interface::msg::AutoaimData *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _AutoaimData__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const interface::msg::AutoaimData *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _AutoaimData__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_AutoaimData(full_bounded, 0);
}

static message_type_support_callbacks_t _AutoaimData__callbacks = {
  "interface::msg",
  "AutoaimData",
  _AutoaimData__cdr_serialize,
  _AutoaimData__cdr_deserialize,
  _AutoaimData__get_serialized_size,
  _AutoaimData__max_serialized_size
};

static rosidl_message_type_support_t _AutoaimData__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_AutoaimData__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace interface

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_interface
const rosidl_message_type_support_t *
get_message_type_support_handle<interface::msg::AutoaimData>()
{
  return &interface::msg::typesupport_fastrtps_cpp::_AutoaimData__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, interface, msg, AutoaimData)() {
  return &interface::msg::typesupport_fastrtps_cpp::_AutoaimData__handle;
}

#ifdef __cplusplus
}
#endif
