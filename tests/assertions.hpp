#pragma once
#include <Arduino.h>

#define assert(e, msg) Serial.print(msg); Serial.print((e) ? " - OK\n\r" : " - ERROR\n\r")
#define assertTrue(e) assert((e), "Assertion (true): [" #e "]")
#define assertFalse(e) assert(!(e), "Assertion (false): [" #e "]")
#define assertEqual(a, b) assert((a) == (b), "Assertion [" #a " == " #b "]")
#define assertNotEqual(a, b) assert((a) != (b), "Assertion [" #a " != " #b "]")
#define assertGt(a, b) assert((a) > (b), "Assertion [" #a " > " #b "]")
#define assertLt(a, b) assert((a) < (b), "Assertion [" #a " < " #b "]")
#define assertNear(a, b, e) assert((a) >= ((b) - (e)) && (a) <= ((b) + (e)), "Assertion [" #a " ~ " #b "] |e: " #e "|")
