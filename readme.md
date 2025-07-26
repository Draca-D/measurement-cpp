# measurement-cpp

**A modern C++ header-only library for strongly typed, unit-safe distance measurements and conversions.**

---

## Overview

`measurement-cpp` provides a convenient, compile-time safe way to represent distances using SI and Imperial units with seamless automatic conversion between them. Inspired by `std::chrono`, it uses strong types to avoid mixing incompatible units and allows arithmetic operations like addition and subtraction between distances with different units.

Features:
- Supports SI units (meters, kilometers, millimeters, nanometers, etc.) using standard `std::ratio` prefixes.
- Supports common Imperial units (feet, miles, inches, yards, nautical miles).
- Automatic, lossless conversions between units.
- Strongly typed interfaces preventing unit mismatch errors.
- Header-only and modern C++17 compatible.

---

## Installation

The library is header-only. You can either:

- Add the `include/` directory to your project's include path.
- Or install it system-wide using CMake:

```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build build
sudo cmake --install build
```

## Usage
### Basic usage example:
```cpp
#include <iostream>
#include <measurement/distance.h>

void add(const measurement::si::meters& meters) {
    // Add 1 millimeter to the input distance
    auto local_m = meters + measurement::si::millimeters(1);

    std::cout << local_m.count() << " meters" << std::endl;

    // Convert and print distance in nautical miles
    std::cout << measurement::imperial::nauticalmiles(local_m) << " nautical miles" << std::endl;
}

int main() {
    add(measurement::si::meters(1000));  // 1000 meters
    return 0;
}

```

### Key points:
Use strongly typed units from measurement::si or measurement::imperial namespaces.

Construct units like meters(1000), feet(3), kilometers(1).

Perform arithmetic directly; conversion is implicit and automatic.

Retrieve the raw count with .count() if needed.

## Supported units
### SI units
attometers, femtometers, picometers, nanometers, micrometers, millimeters, centimeters, decimeters, meters, decameters, hectometers, kilometers, megameters, gigameters, terameters, petameters, exameters

### Imperial units
inches, feet, yards, miles, nauticalmiles

## Building tests
To build and run tests (requires GoogleTest):

```bash
cmake -B build -DRUN_TESTS=ON
cmake --build build
ctest --output-on-failure```
