#include "Mode.h"

#define RESET_COLOR_FONT "\033[0m"
#define BLACK_COLOR_FONT "\033[30m"              /* Black */
#define RED_COLOR_FONT "\033[31m"                /* Red */
#define GREEN_COLOR_FONT "\033[32m"              /* Green */
#define YELLOW_COLOR_FONT "\033[33m"             /* Yellow */
#define BLUE_COLOR_FONT "\033[34m"               /* Blue */
#define MAGENTA_COLOR_FONT "\033[35m"            /* Magenta */
#define CYAN_COLOR_FONT "\033[36m"               /* Cyan */
#define WHITE_COLOR_FONT "\033[37m"              /* White */
#define BOLDBLACK_COLOR_FONT "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED_COLOR_FONT "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN_COLOR_FONT "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW_COLOR_FONT "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE_COLOR_FONT "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA_COLOR_FONT "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN_COLOR_FONT "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE_COLOR_FONT "\033[1m\033[37m"   /* Bold White */

// utility functions
// generate color font string with given color
std::string greenStr(std::string str)
{
    return GREEN_COLOR_FONT + str + RESET_COLOR_FONT;
}

std::string redStr(std::string str)
{
    return RED_COLOR_FONT + str + RESET_COLOR_FONT;
}

std::string yellowStr(std::string str)
{
    return YELLOW_COLOR_FONT + str + RESET_COLOR_FONT;
}

std::string blueStr(std::string str)
{
    return BLUE_COLOR_FONT + str + RESET_COLOR_FONT;
}

std::string magentaStr(std::string str)
{
    return MAGENTA_COLOR_FONT + str + RESET_COLOR_FONT;
}

std::string cyanStr(std::string str)
{
    return CYAN_COLOR_FONT + str + RESET_COLOR_FONT;
}

std::string whiteStr(std::string str)
{
    return WHITE_COLOR_FONT + str + RESET_COLOR_FONT;
}

void BaseMode::execute()
{
    bool continueFlag = true;

    while (continueFlag)
    {
        generateAndPrintQuestion();

        continueFlag = processInput();
    }

    printStatics();
}

bool BaseMode::processInput()
{
    std::string str;
    std::cout << "input:";

    auto start = std::chrono::high_resolution_clock::now();
    std::cin >> str;
    auto end = std::chrono::high_resolution_clock::now();

    if (str == "quit")
    {
        return false;
    }

    auto costTime =
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
            .count();

    m_costTime.push_back(costTime);
    m_response.push_back(str);

    return true;
}

bool BaseMode::checkAnswer(const int index)
{
    return m_response[index] == m_answer[index];
}

void BaseMode::printStatics()
{
    int correctCount = 0;

    for (int i = 0; i < static_cast<int>(m_response.size()); i++)
    {
        std::cout << "************************************" << std::endl;

        std::cout << "question " << i + 1 << std::endl;
        std::cout << "question:       " << m_question[i] << std::endl;
        std::cout << "your answer:    " << m_response[i] << std::endl;
        std::cout << "correct answer: " << m_answer[i] << std::endl;
        std::cout << "cost time:      " << std::fixed << std::setprecision(3)
                  << static_cast<double>(m_costTime[i]) / 1000 << "s"
                  << std::endl;

        if (checkAnswer(i))
        {
            std::cout << greenStr("correct") << std::endl;
            correctCount++;
        }
        else
        {
            std::cout << redStr("wrong") << std::endl;
        }
    }

    double correctRation = static_cast<double>(correctCount) /
                           static_cast<double>(m_response.size());
    auto equalCostTime = static_cast<double>(std::accumulate(
                             m_costTime.begin(), m_costTime.end(), 0)) /
                         1000 / m_costTime.size();

    std::cout << "-------------------------------------------" << std::endl;

    std::cout << cyanStr("STATICS") << std::endl;
    std::cout << "correct count:   " << greenStr(std::to_string(correctCount)) << std::endl;
    std::cout << "wrong count:     " << redStr(std::to_string(m_response.size() - correctCount)) << std::endl;
    std::cout << "total count:     " << m_response.size() << std::endl;

    std::cout << "correct ratio:   " << std::fixed << std::setprecision(2)
              << correctRation * 100 << "%" << std::endl;
    std::cout << "equal cost time: " << std::fixed << std::setprecision(3)
              << equalCostTime << "s" << std::endl;

    std::cout << "-------------------------------------------" << std::endl;
}

BaseModeWithRandom::BaseModeWithRandom()
{
    auto seed = m_rd();
    m_gen.seed(seed);
}

template <typename... Args>
RandomDistributionGenerator::RandomDistributionGenerator(Args... ranges) : m_numDists{std::uniform_int_distribution<>(ranges.first, ranges.second)...}
{
}

void BaseMode::generateAndPrintQuestion()
{
    auto questionStr = generateQuestion();
    std::cout << questionStr << std::endl;

    auto answerStr = generateAnswer();
    m_question.push_back(questionStr);
    m_answer.push_back(answerStr);
}

TwoDigitsTimesOneDigit::TwoDigitsTimesOneDigit()
    : RandomDistributionGenerator(Range(11, 99), Range(2, 9)) {}

std::string TwoDigitsTimesOneDigit::generateQuestion()
{
    m_num1 = m_numDists[0](m_gen);
    m_num2 = m_numDists[1](m_gen);

    return std::to_string(m_num1) + " * " + std::to_string(m_num2);
}

std::string TwoDigitsTimesOneDigit::generateAnswer()
{
    return std::to_string(m_num1 * m_num2);
}

OneDigitPlusOneDigit::OneDigitPlusOneDigit()
    : RandomDistributionGenerator(Range(1, 9), Range(1, 9)) {}

std::string OneDigitPlusOneDigit::generateQuestion()
{
    m_num1 = m_numDists[0](m_gen);
    m_num2 = m_numDists[1](m_gen);

    return std::to_string(m_num1) + " + " + std::to_string(m_num2);
}

std::string OneDigitPlusOneDigit::generateAnswer()
{
    return std::to_string(m_num1 + m_num2);
}

OneDigitTimesOneDigit::OneDigitTimesOneDigit()
    : RandomDistributionGenerator(Range(1, 9), Range(1, 9)) {}

std::string OneDigitTimesOneDigit::generateQuestion()
{
    m_num1 = m_numDists[0](m_gen);
    m_num2 = m_numDists[1](m_gen);

    return std::to_string(m_num1) + " * " + std::to_string(m_num2);
}

std::string OneDigitTimesOneDigit::generateAnswer()
{
    return std::to_string(m_num1 * m_num2);
}

ThreeDigitsDivideTwoDigits::ThreeDigitsDivideTwoDigits()
    : RandomDistributionGenerator(Range(10, 99), Range(100, 999)) {}

std::string ThreeDigitsDivideTwoDigits::generateQuestion()
{
    m_num1 = m_numDists[0](m_gen);
    m_num2 = m_numDists[1](m_gen);

    return std::to_string(m_num1) + " 厂 " + std::to_string(m_num2);
}

std::string ThreeDigitsDivideTwoDigits::generateAnswer()
{
    if (m_num1 == 0)
    {
        throw std::invalid_argument("Division by zero");
    }

    double result = static_cast<double>(m_num2) / m_num1;
    std::string resultStr = std::to_string(result);

    for (char c : resultStr)
    {
        if (c >= '1' && c <= '9')
        {
            return std::to_string(c - '0');
        }
    }

    return std::to_string(0);
}

FractionCompare::FractionCompare()
    : RandomDistributionGenerator(Range(10000, 100000), Range(0, 2)) {}

std::string FractionCompare::generateQuestion()
{
    auto digitsGapBetweentND = m_numDists[1](m_gen);
    auto digitsGapBetweentFractions = m_numDists[1](m_gen);

    m_num1Denominator = m_numDists[0](m_gen);
    m_num2Denominator = m_numDists[0](m_gen);

    m_num2Denominator /= static_cast<int>(std::pow(10, digitsGapBetweentFractions));

    if (digitsGapBetweentND == 0)
    {
        std::uniform_int_distribution<> num1NumeratorDis(10000, m_num1Denominator - 1);
        std::uniform_int_distribution<> num2NumeratorDis(10000, m_num2Denominator - 1);

        m_num1Numerator = num1NumeratorDis(m_gen);
        m_num2Numerator = num2NumeratorDis(m_gen);
    }
    else
    {
        m_num1Numerator = static_cast<double>(m_numDists[0](m_gen)) / static_cast<int>(std::pow(10, digitsGapBetweentND));
        m_num2Numerator = static_cast<double>(m_numDists[0](m_gen)) / static_cast<int>(std::pow(10, digitsGapBetweentND + digitsGapBetweentFractions));
    }

    return std::to_string(m_num1Numerator) + "/" + std::to_string(m_num1Denominator) + " ? " +
           std::to_string(m_num2Numerator) + "/" + std::to_string(m_num2Denominator);
}

std::string FractionCompare::generateAnswer()
{
    double result1 = static_cast<double>(m_num1Numerator) / m_num1Denominator;
    double result2 = static_cast<double>(m_num2Numerator) / m_num2Denominator;

    auto symbol = result1 > result2 ? ">" : result1 < result2 ? "<"
                                                              : "=";

    std::string answer(symbol);

    answer += " " + std::to_string(result1) + " " + symbol + " " + std::to_string(result2);

    return answer;
}

bool FractionCompare::checkAnswer(const int index)
{
    return m_response[index][0] == m_answer[index][0];
}