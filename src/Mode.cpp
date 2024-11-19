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

        if (m_response[i] == m_answer[i])
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

    std::cout << "-------------------------" << std::endl;

    std::cout << "correct count:   " << greenStr(std::to_string(correctCount)) << std::endl;
    std::cout << "wrong count:     " << redStr(std::to_string(m_response.size() - correctCount)) << std::endl;
    std::cout << "total count:     " << m_response.size() << std::endl;

    std::cout << "correct ratio:   " << std::fixed << std::setprecision(2)
              << correctRation * 100 << "%" << std::endl;
    std::cout << "equal cost time: " << std::fixed << std::setprecision(3)
              << equalCostTime << "s" << std::endl;

    std::cout << "-------------------------" << std::endl;
}

int MultiplyOperation::apply(int a, int b) const { return a * b; }
std::string MultiplyOperation::symbol() const { return "*"; }

int AddOperation::apply(int a, int b) const { return a + b; }
std::string AddOperation::symbol() const { return "+"; }

int DivideOperation::apply(int a, int b) const
{
    if (b == 0)
    {
        throw std::invalid_argument("Division by zero");
    }

    double result = static_cast<double>(a) / b;
    std::string resultStr = std::to_string(result);

    for (char c : resultStr)
    {
        if (c >= '1' && c <= '9')
        {
            return c - '0';
        }
    }

    return 0;
}
std::string DivideOperation::symbol() const { return "/"; }