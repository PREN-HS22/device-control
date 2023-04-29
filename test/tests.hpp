#pragma once
#include <Arduino.h>

#define TEST(f) Serial.println(); Serial.println("Testing [" #f "]:"); f()
