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

class ModeStrategy
{
public:
    void setStrategy(std::unique_ptr<ModeStrategy> strategy);

    virtual void executeStrategy() = 0;

    virtual ~ModeStrategy() = default;

protected:
    std::unique_ptr<BaseMode> m_questionMode;
};

class ExaminationMode : public ModeStrategy
{
public:
    virtual void executeStrategy() override;
};

class RunningMode : public ModeStrategy
{
public:
    virtual void executeStrategy() override;
};

class BaseMode
{
public:
    virtual void generateAndPrintQuestion();

    bool processInput();

    void printStatics();

    virtual std::string generateQuestion() = 0;

    virtual std::string generateAnswer() = 0;

    virtual bool checkAnswer(const int index);

protected:
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