// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from interface:msg/AutoaimData.idl
// generated code does not contain a copyright notice
#include "interface/msg/detail/autoaim_data__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "interface/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "interface/msg/detail/autoaim_data__struct.h"
#include "interface/msg/detail/autoaim_data__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif


// forward declare type support functions


using _AutoaimData__ros_msg_type = interface__msg__AutoaimData;

static bool _AutoaimData__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _AutoaimData__ros_msg_type * ros_message = static_cast<const _AutoaimData__ros_msg_type *>(untyped_ros_message);
  // Field name: yaw_angle_diff
  {
    cdr << ros_message->yaw_angle_diff;
  }

  // Field name: pitch_angle_diff
  {
    cdr << ros_message->pitch_angle_diff;
  }

  // Field name: fire
  {
    cdr << ros_message->fire;
  }

  return true;
}

static bool _AutoaimData__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _AutoaimData__ros_msg_type * ros_message = static_cast<_AutoaimData__ros_msg_type *>(untyped_ros_message);
  // Field name: yaw_angle_diff
  {
    cdr >> ros_message->yaw_angle_diff;
  }

  // Field name: pitch_angle_diff
  {
    cdr >> ros_message->pitch_angle_diff;
  }

  // Field name: fire
  {
    cdr >> ros_message->fire;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_interface
size_t get_serialized_size_interface__msg__AutoaimData(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _AutoaimData__ros_msg_type * ros_message = static_cast<const _AutoaimData__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name yaw_angle_diff
  {
    size_t item_size = sizeof(ros_message->yaw_angle_diff);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name pitch_angle_diff
  {
    size_t item_size = sizeof(ros_message->pitch_angle_diff);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name fire
  {
    size_t item_size = sizeof(ros_message->fire);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _AutoaimData__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_interface__msg__AutoaimData(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_interface
size_t max_serialized_size_interface__msg__AutoaimData(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: yaw_angle_diff
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: pitch_angle_diff
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: fire
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _AutoaimData__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_interface__msg__AutoaimData(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_AutoaimData = {
  "interface::msg",
  "AutoaimData",
  _AutoaimData__cdr_serialize,
  _AutoaimData__cdr_deserialize,
  _AutoaimData__get_serialized_size,
  _AutoaimData__max_serialized_size
};

static rosidl_message_type_support_t _AutoaimData__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_AutoaimData,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, interface, msg, AutoaimData)() {
  return &_AutoaimData__type_support;
}

#if defined(__cplusplus)
}
#endif
