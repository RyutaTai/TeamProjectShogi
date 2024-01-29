#pragma once

#include <windows.h>

#include "string"


std::string IntegerToString(int num, bool back = false)
{
    std::string result;
    if (num == 0) return "0";

    if (num < 0) {
        result += "-";
        num = -num;
    }

    while (num > 0)
    {
        int digitValue = num % 10;
        char number = digitValue + '0';
        if (back)
            result += number;
        else
            result = number + result;
        num /= 10;
    }
    return result;
}

bool BOOLTobool(BOOL value)
{
    return (value != FALSE);
}

BOOL boolToBOOL(bool value)
{
    return value ? TRUE : FALSE;
}