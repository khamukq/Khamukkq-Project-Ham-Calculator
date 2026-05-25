#include "xamgenerator.h"
#include "randomgenerator.h"
#include <cctype>
#include <vector>
#include <string>

static const std::vector<std::string> XAM_WORDS = {
    "дурак", "идиот", "дебил", "кретин", "олух", "балбес", "тупица",
    "придурок", "долбень", "чурбан", "пентюх", "телепень", "рохля", "тюфяк",
    "тормоз", "бестолочь", "болван", "чмо", "лох", "овощ"
    // добавь остальные слова из твоего списка
};

std::string XamGenerator::generate(const GeneratorParams& params)
{
    std::string result;
    auto& rng = RandomGenerator::instance();

    for (int i = 0; i < params.wordCount; ++i) {
        if (i > 0) result += params.useHyphens ? '-' : ' ';
        result += XAM_WORDS[rng.nextInt(0, XAM_WORDS.size() - 1)];
    }

    if (params.useDigits) {
        result += std::to_string(rng.nextInt(10, 999));
    }

    if (params.useUppercase) {
        for (char& c : result) {
            c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
    }

    return result;
}
