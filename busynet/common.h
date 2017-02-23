#pragma once

namespace busynet
{
// Rust language Primitive Types
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed long isize;
typedef unsigned long usize;
typedef float f32;
typedef double f64;

#define DISABLE_COPY(Class)      \
  Class(const Class &) = delete; \
  Class &operator=(const Class &) = delete;
}
