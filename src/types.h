#ifndef ZERO_TYPES_H
#define ZERO_TYPES_H

#include <cstdint>
#include <SDL2/SDL.h>

using byte = uint8_t;

using i8  = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8  = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

// TODO(naum): Refactor in separate files
struct vec2 { float x, y; };
struct vec3 { float x, y, z; };
struct vec4 { float x, y, w, h; };

/*
const vec2 vec2up = { 0.0f, 1.0f };
const vec2 vec2right = { 1.0f, 0.0f };
*/

inline vec2 operator-(const vec2 a) { return {-a.x, -a.y}; }
inline vec2 operator+(const vec2 a, const vec2 b) { return {a.x + b.x, a.y + b.y}; }
inline vec2 operator-(const vec2 a, const vec2 b) { return a+(-b); }
inline vec2 operator*(const vec2 v, const float s) { return {v.x * s, v.y * s}; }
inline vec2 operator/(const vec2 v, const float s) { return {v.x / s, v.y / s}; }
inline vec2& operator+=(vec2& a, const vec2 b) { return a=a+b; }
inline vec2& operator-=(vec2& a, const vec2 b) { return a=a-b; }
inline vec2& operator*=(vec2& a, const float s) { return a=a*s; }
inline vec2& operator/=(vec2& a, const float s) { return a=a/s; }

inline SDL_Point vec2toPoint(const vec2 v) { return {(i32)v.x, (i32)v.y}; }
inline SDL_Rect vec4toRect(const vec4 v) { return {(i32)v.x, (i32)v.y, (i32)v.w, (i32)v.h}; }

#endif
