#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

#include "Context.h"
#include "Mode.h"

void test()
{
    std::string userInputStr;

    while (userInputStr != "quit")
    {
        srand(time(0)); // 初始化随机种子

        int numbers[6]; // 存储生成的6个三位数

        // 生成6个随机三位数
        for (int i = 0; i < 6; ++i)
        {
            numbers[i] = rand() % 900 + 100; // 100-999范围内的随机数
        }

        // 打印生成的数字
        std::cout << "随机生成的6个三位数为：";
        for (int num : numbers)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;

        // 计算前两位叠加之和
        int sum = 0;
        for (int num : numbers)
        {
            int thirdDigit = num % 10; // 获取个位数（第三位）
            int firstTwo = num / 10;   // 原始前两位数

            // 四舍五入处理
            if (thirdDigit >= 5)
            {
                firstTwo++; // 第三位≥5时前两位进位
            }
            sum += firstTwo;
        }

        auto start = std::chrono::high_resolution_clock::now();

        std::cout << "请输入您的计算结果：";
        std::cin >> userInputStr;

        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);

        if (userInputStr == "quit")
        {
            break;
        }

        auto userInput = std::stoi(userInputStr);

        std::cout << "\n====== 验证结果 ======\n"
                  << "您的答案：" << userInput << std::endl
                  << "正确答案：" << sum << std::endl
                  << "耗时：" << std::fixed << std::setprecision(2) << time_span.count() << "秒\n"
                  << "验证结果：" << (userInput == sum ? "✓ 通过" : "✗ 未通过")
                  << "\n======================" << std::endl;
    }

    return;
}

void process()
{
    Context context;
    std::string input;

    std::cout << "hello!" << std::endl;

    while (true)
    {
        std::cout << "mode list:" << std::endl;
        std::cout << "1. running mode" << std::endl;
        std::cout << "2. running and test mode" << std::endl;
        std::cout << "3. examination mode" << std::endl;
        std::cout << "please input mode (1 - 3), or input 'quit' to exit: ";
        std::cin >> input;

        if (input == "quit")
        {
            std::cout << "Bye~" << std::endl;
            break;
        }

        if (input == "1")
        {
            context.setStrategy(std::make_unique<RunningMode>());
        }
        else if (input == "2")
        {
            context.setStrategy(std::make_unique<RunningAndTestMode>());
        }
        else if (input == "3")
        {
            context.setStrategy(std::make_unique<ExaminationMode>());
        }
        else
        {
            std::cout << "invalid mode" << std::endl;
            continue;
        }

        while (true)
        {
            std::cout << "mode list:" << std::endl;
            std::cout << "1.  two digits times one digits : 12 * 1" << std::endl;
            std::cout << "2.  one digits plus one digits : 1 + 2" << std::endl;
            std::cout << "3.  one digits times one digits : 1 * 2" << std::endl;
            std::cout << "4.  three digits divide two digits : 12 厂 123" << std::endl;
            std::cout << "5.  fraction compare : 1/2 ? 1/3" << std::endl;
            std::cout << "6.  PercentageConvertToFraction : 12%" << std::endl;
            std::cout << "7.  three digits times one digits : 123 * 1" << std::endl;
            std::cout << "8.  estimate growth : 1234 5.6%" << std::endl;
            std::cout << "9.  two digits substaction one digit : 12 - 3" << std::endl;
            std::cout << "10. power number : 256" << std::endl;

            std::cout << "please input mode (1 - 10), or input 'quit' to exit: ";
            std::cin >> input;

            if (input == "quit")
            {
                std::cout << "Bye~" << std::endl;
                break;
            }

            switch (std::stoi(input))
            {
            case 1:
                context.getStrategy()->setMode(std::make_unique<TwoDigitsTimesOneDigit>());
                break;
            case 2:
                context.getStrategy()->setMode(std::make_unique<OneDigitPlusOneDigit>());
                break;
            case 3:
                context.getStrategy()->setMode(std::make_unique<OneDigitTimesOneDigit>());
                break;

            case 4:
                context.getStrategy()->setMode(std::make_unique<ThreeDigitsDivideTwoDigits>());
                break;

            case 5:
                context.getStrategy()->setMode(std::make_unique<FractionCompare>());
                break;

            case 6:
                context.getStrategy()->setMode(std::make_unique<PercentageConvertToFraction>());
                break;

            case 7:
                context.getStrategy()->setMode(std::make_unique<ThreeDigitsTimesOneDigit>());
                break;

            case 8:
                context.getStrategy()->setMode(std::make_unique<EstimateGrowth>());
                break;

            case 9:
                context.getStrategy()->setMode(std::make_unique<TwoDigitsSubOneDigit>());
                break;

            case 10:
                context.getStrategy()->setMode(std::make_unique<PowerNumber>());
                break;

            default:
                std::cout << "invalid mode" << std::endl;
                continue;
            }

            context.executeStrategy();
        }
    }

    return;
}

int main()
{
    process();
}
