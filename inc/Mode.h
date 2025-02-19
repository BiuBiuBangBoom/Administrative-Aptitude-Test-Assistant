#pragma once

#include <string>
#include <iomanip>
#include <random>
#include <set>
#include <vector>

class BaseMode
{
public:
    BaseMode() = default;
    virtual ~BaseMode() = default;

    virtual void generateAndPrintQuestion();

    void printStatics();

    virtual std::string generateQuestion() = 0;

    virtual std::string generateAnswer() = 0;

    virtual bool checkAnswer(const int index);

public:
    std::vector<std::string> m_question;
    std::vector<std::string> m_answer;
    std::vector<std::string> m_response;
    std::vector<long long> m_costTime;
};

class BaseModeWithRandom : public BaseMode
{
public:
    BaseModeWithRandom();
    virtual ~BaseModeWithRandom() = default;

protected:
    std::mt19937 m_gen;
    std::random_device m_rd;
};

class RandomDistributionGenerator : public BaseModeWithRandom
{
public:
    using Range = std::pair<int, int>;

public:
    template <typename... Args>
    RandomDistributionGenerator(Args... ranges);

protected:
    int getRandomNumFromDistribution(const int index);

private:
    std::vector<std::uniform_int_distribution<>> m_numDists;
};

class TwoDigitsTimesOneDigit : public RandomDistributionGenerator
{
public:
    TwoDigitsTimesOneDigit();
    virtual ~TwoDigitsTimesOneDigit() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;

private:
    int m_num1{};
    int m_num2{};
};

class OneDigitPlusOneDigit : public RandomDistributionGenerator
{
public:
    OneDigitPlusOneDigit();
    virtual ~OneDigitPlusOneDigit() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;

private:
    int m_num1{};
    int m_num2{};
};

class OneDigitTimesOneDigit : public RandomDistributionGenerator
{
public:
    OneDigitTimesOneDigit();
    virtual ~OneDigitTimesOneDigit() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;

private:
    int m_num1{};
    int m_num2{};
};

class ThreeDigitsDivideTwoDigits : public RandomDistributionGenerator
{
public:
    ThreeDigitsDivideTwoDigits();
    virtual ~ThreeDigitsDivideTwoDigits() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;

private:
    int m_num1{};
    int m_num2{};
};

class FractionCompare : public RandomDistributionGenerator
{
public:
    FractionCompare();
    virtual ~FractionCompare() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;
    virtual bool checkAnswer(const int index) override;

private:
    int m_num1Numerator;
    int m_num1Denominator;
    int m_num2Numerator;
    int m_num2Denominator;
};

class PercentageConvertToFraction : public RandomDistributionGenerator
{
public:
    PercentageConvertToFraction();
    virtual ~PercentageConvertToFraction() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;
    virtual bool checkAnswer(const int index) override;

private:
    std::set<double> m_fractionsDict;
    double m_percentage{0};
};

class ThreeDigitsTimesOneDigit : public RandomDistributionGenerator
{
public:
    ThreeDigitsTimesOneDigit();
    virtual ~ThreeDigitsTimesOneDigit() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;

private:
    int m_num1{};
    int m_num2{};
};

class EstimateGrowth : public RandomDistributionGenerator
{
public:
    EstimateGrowth();
    virtual ~EstimateGrowth() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;
    virtual bool checkAnswer(const int index) override;

private:
    int m_num1{0};
    double m_num2{0};
    double m_result{0};
    const double m_threshold{0.01};
};

class TwoDigitsSubOneDigit : public RandomDistributionGenerator
{
public:
    TwoDigitsSubOneDigit();
    virtual ~TwoDigitsSubOneDigit() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;

private:
    int m_num1{};
    int m_num2{};
};

class OneDigitAddOneDigit : public RandomDistributionGenerator
{
public:
    OneDigitAddOneDigit();
    virtual ~OneDigitAddOneDigit() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;

private:
    int m_num1{};
    int m_num2{};
};

class PowerNumber : public RandomDistributionGenerator
{
public:
    PowerNumber();
    virtual ~PowerNumber() = default;

private:
    virtual std::string generateQuestion() override;
    virtual std::string generateAnswer() override;

private:
    int m_num1{};
    int m_num2{};
};
