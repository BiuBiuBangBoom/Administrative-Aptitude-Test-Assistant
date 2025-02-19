#include "Mode.h"
#include "Common.h"

#include <sstream>
#include <algorithm>
#include <chrono>
#include <memory>
#include <numeric>
#include <vector>
#include <iostream>
#include <utility>
#include <set>

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
        std::cout << "question:       ";

        if (dynamic_cast<FractionCompare *>(this))
        {
            std::cout << std::endl;
        }

        std::cout << m_question[i] << std::endl;
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

int RandomDistributionGenerator::getRandomNumFromDistribution(const int index)
{
    if (index < 0 || index > m_numDists.size())
    {
        return 0;
    }

    return m_numDists[index](m_gen);
}

TwoDigitsTimesOneDigit::TwoDigitsTimesOneDigit()
    : RandomDistributionGenerator(Range(11, 99), Range(2, 9)) {}

std::string TwoDigitsTimesOneDigit::generateQuestion()
{
    m_num1 = getRandomNumFromDistribution(0);
    m_num2 = getRandomNumFromDistribution(1);

    return std::to_string(m_num1) + " * " + std::to_string(m_num2);
}

std::string TwoDigitsTimesOneDigit::generateAnswer()
{
    return std::to_string(m_num1 * m_num2);
}

OneDigitPlusOneDigit::OneDigitPlusOneDigit()
    : RandomDistributionGenerator(Range(2, 9)) {}

std::string OneDigitPlusOneDigit::generateQuestion()
{
    m_num1 = getRandomNumFromDistribution(0);
    std::uniform_int_distribution<> dist(11 - m_num1, 9);
    m_num2 = dist(m_rd);

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
    m_num1 = getRandomNumFromDistribution(0);
    m_num2 = getRandomNumFromDistribution(1);

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
    m_num1 = getRandomNumFromDistribution(0);
    m_num2 = getRandomNumFromDistribution(1);

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
    auto digitsGapBetweentND = getRandomNumFromDistribution(1);
    auto digitsGapBetweentFractions = getRandomNumFromDistribution(1);

    m_num1Denominator = getRandomNumFromDistribution(0);
    m_num2Denominator = getRandomNumFromDistribution(0);

    m_num2Denominator /= static_cast<int>(std::pow(10, digitsGapBetweentFractions));

    if (digitsGapBetweentND == 0)
    {
        std::uniform_int_distribution<> num1NumeratorDis(10000, m_num1Denominator - 1);
        std::uniform_int_distribution<> num2NumeratorDis(10000 / std::pow(10, digitsGapBetweentFractions), m_num2Denominator - 1);

        m_num1Numerator = num1NumeratorDis(m_gen);
        m_num2Numerator = num2NumeratorDis(m_gen);
    }
    else
    {
        m_num1Numerator = static_cast<double>(getRandomNumFromDistribution(0)) / static_cast<int>(std::pow(10, digitsGapBetweentND));
        m_num2Numerator = static_cast<double>(getRandomNumFromDistribution(0)) / static_cast<int>(std::pow(10, digitsGapBetweentND + digitsGapBetweentFractions));
    }

    // print fraction with the stye of numerator1        numerator2
    //                                 -----------   ?   -----------
    //                                 denominator1      denominator2
    // the numerator1 and denominator1 are supposed to be aligned left
    // the numerator2 and denominator2 are supposed to be aligned left
    // the ? is supposed to be aligned center
    std::stringstream oss;
    oss << std::setw(10) << std::left << m_num1Numerator << "        " << std::setw(10) << std::left << m_num2Numerator << "\n"
        << std::setw(10) << std::left << "------" << "   ?   " << std::setw(10) << std::left << "------" << "\n"
        << std::setw(10) << std::left << m_num1Denominator << "        " << std::setw(10) << std::left << m_num2Denominator << "\n";

    return oss.str();
}

std::string FractionCompare::generateAnswer()
{
    double result1 = static_cast<double>(m_num1Numerator) / m_num1Denominator;
    double result2 = static_cast<double>(m_num2Numerator) / m_num2Denominator;

    auto symbol = result1 > result2 ? "(>)" : result1 < result2 ? "(<)"
                                                                : "(=)";

    std::string answer(symbol);

    answer += " " + std::to_string(result1) + " " + symbol[1] + " " + std::to_string(result2);

    return answer;
}

bool FractionCompare::checkAnswer(const int index)
{
    return m_response[index][0] == m_answer[index][1];
}

PercentageConvertToFraction::PercentageConvertToFraction()
    : RandomDistributionGenerator(Range(500, 2000))
{
    for (double i = 5; i <= 20; i = i + 0.5)
    {
        m_fractionsDict.insert(i);
    }
}

std::string PercentageConvertToFraction::generateQuestion()
{
    // use 2 valuable digits to represent the percentage
    m_percentage = getRandomNumFromDistribution(0) / 100.0;

    return std::to_string(static_cast<double>(m_percentage)) + "%";
}

std::string PercentageConvertToFraction::generateAnswer()
{
    std::string res;
    auto target = 100 / static_cast<double>(m_percentage);
    auto lower = m_fractionsDict.lower_bound(target);

    if (lower == m_fractionsDict.end())
    {
        res = std::to_string(*(std::prev(lower)));
    }

    if (lower == m_fractionsDict.begin())
    {
        res = std::to_string(*lower);
    }

    auto prev = std::prev(lower);

    if (std::abs(*prev - target) < std::abs(*lower - target))
    {
        res = std::to_string(*prev);
    }
    else
    {
        res = std::to_string(*lower);
    }

    res += " true value: " + std::to_string(target);
    return res;
}

bool PercentageConvertToFraction::checkAnswer(const int index)
{
    std::istringstream iss(m_response[index]);
    std::string fractionStr;
    iss >> fractionStr;
    return std::stod(m_response[index]) == std::stod(fractionStr);
}

ThreeDigitsTimesOneDigit::ThreeDigitsTimesOneDigit()
    : RandomDistributionGenerator(Range(100, 999), Range(2, 9)) {}

std::string ThreeDigitsTimesOneDigit::generateQuestion()
{
    m_num1 = getRandomNumFromDistribution(0);
    m_num2 = getRandomNumFromDistribution(1);

    return std::to_string(m_num1) + " * " + std::to_string(m_num2);
}

std::string ThreeDigitsTimesOneDigit::generateAnswer()
{
    return std::to_string(m_num1 * m_num2);
}

EstimateGrowth::EstimateGrowth() : RandomDistributionGenerator(Range(1000, 100000), Range(50, 100)) {}

std::string EstimateGrowth::generateQuestion()
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);

    m_num1 = getRandomNumFromDistribution(0);
    m_num2 = getRandomNumFromDistribution(1) / 10.0;

    oss << "A: " << m_num1 << "  r: " << m_num2;

    return oss.str();
}

std::string EstimateGrowth::generateAnswer()
{
    m_result = m_num1 / (1 + m_num2 / 100) * (m_num2 / 100);
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << m_result;

    return oss.str();
}

bool EstimateGrowth::checkAnswer(const int index)
{
    auto response = std::stoi(m_response[index]);
    auto error = std::abs(m_result - response) / m_result;
    std::cout << "error rate: " << error * 100 << "%" << std::endl;

    if (error > m_threshold)
    {
        return false;
    }

    return true;
}

TwoDigitsSubOneDigit::TwoDigitsSubOneDigit() : RandomDistributionGenerator(Range(11, 18)) {}

std::string TwoDigitsSubOneDigit::generateQuestion()
{
    m_num1 = getRandomNumFromDistribution(0);
    std::uniform_int_distribution<> dist(m_num1 - 9, 9);
    m_num2 = dist(m_rd);

    std::string qStr = "()" + std::to_string(m_num1 % 10);
    qStr += " - " + std::to_string(m_num2);
    return qStr;
}

std::string TwoDigitsSubOneDigit::generateAnswer()
{
    return std::to_string(m_num1 - m_num2);
}

PowerNumber::PowerNumber() : RandomDistributionGenerator(Range(1, 19)) {}

std::string PowerNumber::generateQuestion()
{
    m_num1 = getRandomNumFromDistribution(0);

    if (m_num1 < 10)
    {
        m_num2 = 3;
    }
    else
    {
        m_num2 = 2;
    }

    auto powerNumber = static_cast<int>(std::pow(m_num1, m_num2));

    return std::to_string(powerNumber);
}

std::string PowerNumber::generateAnswer()
{
    return std::to_string(m_num1) + " " + std::to_string(m_num2);
}