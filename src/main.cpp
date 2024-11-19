#include "Context.h"

int main()
{
    Context context;
    std::string input;

    while (true)
    {
        std::cout << "mode list:" << std::endl;
        std::cout << "1. two digits times one digits : 12 * 1" << std::endl;
        std::cout << "2. one digits plus one digits : 1 + 1" << std::endl;
        std::cout << "3. one digits times one digits : 1 * 1" << std::endl;
        std::cout << "4. three digits divide two digits : 123 / 12" << std::endl;

        std::cout << "please input mode (1 - 4), or input 'quit' to exit: ";
        std::cin >> input;

        if (input == "quit")
        {
            std::cout << "Bye~" << std::endl;
            break;
        }

        if (input == "1")
        {
            context.setStrategy(std::make_unique<TwoDigitsTimesOneDigit>(10, 100, 1, 10));
        }
        else if (input == "2")
        {
            context.setStrategy(std::make_unique<OneDigitPlusOneDigit>(1, 9, 1, 9));
        }
        else if (input == "3")
        {
            context.setStrategy(std::make_unique<OneDigitTimesOneDigit>(1, 9, 1, 9));
        }
        else if (input == "4")
        {
            context.setStrategy(std::make_unique<ThreeDigitsDivideTwoDigits>(100, 999, 10, 99));
        }
        else
        {
            std::cout << "invalid mode" << std::endl;
            continue;
        }

        context.executeStrategy();
    }

    return 0;
}
