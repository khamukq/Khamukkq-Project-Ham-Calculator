#include "stdgenerator.h"
#include "randomgenerator.h"

static const std::string LOWER = "abcdefghijklmnopqrstuvwxyz";
static const std::string UPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const std::string DIGITS = "0123456789";
static const std::string SYMBOLS = "!@#$%^&*";

std::string StandardGenerator::generate(const GeneratorParams& params)
{
    std::string chars = LOWER;
    if (params.useUppercase) chars += UPPER;
    if (params.useDigits) chars += DIGITS;
    if (params.useSymbols) chars += SYMBOLS;

    std::string result;
    result.reserve(params.length);
    for (int i = 0; i < params.length; ++i) {
        result += RandomGenerator::instance().getChar(chars);
    }
    return result;
}