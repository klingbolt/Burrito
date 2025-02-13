#pragma once

#include <string>

class OptionalInt {
 public:
    OptionalInt()
        : is_null(true), value(0) {
    }

    explicit OptionalInt(int val)
        : is_null(false), value(val) {
    }

    void set_value(int val) {
        is_null = false;
        value = val;
    }

    int get_value() {
        return value;
    }

    bool has_value() {
        return !is_null;
    }

    void reset() {
        is_null = true;
        value = 0;
    }

 private:
    bool is_null;
    int value;
};

bool is_string_valid_integer(const std::string test);
