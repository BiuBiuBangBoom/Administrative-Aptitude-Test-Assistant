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
    virtual void execute() = 0;
    virtual ~ModeStrategy() = default;
};

class BaseMode : public ModeStrategy
{
public:
    virtual void execute() override;

private:
    virtual void generateAndPrintQuestion() = 0;
    bool processInput();
    void printStatics();

protected:
    std::vector<std::string> m_question;
    std::vector<std::string> m_answer;
    std::vector<std::string> m_response;
    std::vector<long long> m_costTime;
};

class ArithmeticMode : public BaseMode
{
public:
    using Range = std::pair<int, int>;

public:
    template <typename... Args>
    ArithmeticMode(Args... ranges);

public:
    virtual void generateAndPrintQuestion() override;

private:
    virtual std::string generateQuestion() = 0;
    virtual std::string generateAnswer() = 0;

protected:
    std::vector<std::uniform_int_distribution<>> m_numDists;
    std::mt19937 m_gen;

private:
    std::random_device m_rd;
};

class TwoDigitsTimesOneDigit : public ArithmeticMode
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

class OneDigitPlusOneDigit : public ArithmeticMode
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

class OneDigitTimesOneDigit : public ArithmeticMode
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

class ThreeDigitsDivideTwoDigits : public ArithmeticMode
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