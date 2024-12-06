#pragma once

#include <string>

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