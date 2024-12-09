#pragma once

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <memory>
#include <numeric>
#include <random>
#include <vector>
#include <string>
#include <iostream>
#include <utility>
#include <set>

class BaseMode
{
public:
    BaseMode() = default;
    virtual ~BaseMode() = default;

    virtual void generateAndPrintQuestion();

    bool processInput();

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
    int m_num1;
    int m_num2;
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
    int m_num1;
    int m_num2;
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
    int m_num1;
    int m_num2;
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
    int m_num1;
    int m_num2;
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

class ModeStrategy
{
public:
    virtual void execute() = 0;

    virtual void setMode(std::unique_ptr<BaseMode> mode);

    virtual ~ModeStrategy() = default;

protected:
    std::unique_ptr<BaseMode> m_mode{nullptr};
};

class RunningMode : public ModeStrategy
{
public:
    RunningMode() = default;

    virtual ~RunningMode() = default;

    virtual void execute() override;
};

class ExaminationMode : public ModeStrategy
{
public:
    ExaminationMode() = default;

    virtual ~ExaminationMode() = default;

    virtual void execute() override;
};