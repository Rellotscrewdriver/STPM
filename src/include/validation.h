#pragma once

#include "includes.h" 
#include <re2/re2.h>

enum idenStr {
    isEmail,
    isLink,
    notValid,
};

class regexValid {
public:
    regexValid() = default;

    bool checkemail(std::string_view refEmail);
    bool checklink(std::string_view refLink);
    idenStr identify(std::string_view string);

    void test();
private:
    inline static const re2::RE2 emailPattern = R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})";
    inline static const re2::RE2 linkNamePattern = R"((([a-zA-Z0-9-]+\.)+[a-zA-Z]{2,}))";
};
