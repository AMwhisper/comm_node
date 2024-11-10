// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interface:msg/AutoaimData.idl
// generated code does not contain a copyright notice

#ifndef INTERFACE__MSG__DETAIL__AUTOAIM_DATA__STRUCT_H_
#define INTERFACE__MSG__DETAIL__AUTOAIM_DATA__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/AutoaimData in the package interface.
/**
  * protocol_name: AutoaimData
  * protocol_id: 0X0401
  * protocol_description: 云台控制
 */
typedef struct interface__msg__AutoaimData
{
  float yaw_angle_diff;
  float pitch_angle_diff;
  uint8_t fire;
} interface__msg__AutoaimData;

// Struct for a sequence of interface__msg__AutoaimData.
typedef struct interface__msg__AutoaimData__Sequence
{
  interface__msg__AutoaimData * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interface__msg__AutoaimData__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACE__MSG__DETAIL__AUTOAIM_DATA__STRUCT_H_
