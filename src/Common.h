#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <random>
#include <iterator>
#include <windows.h>
#include <algorithm>
#include <memory>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/cstdint.hpp>
#include <boost/range/algorithm/random_shuffle.hpp>
#include <boost/container/stable_vector.hpp>
#include <boost/container/string.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>

#define MAX_DECK_SIZE 52
#define MAX_SUITS 4
#define MAX_VALUE 13

enum StandingState
{
    STANDING_STATE_NOT_STANDING,
    STANDING_STATE_STANDING
};

enum BustState
{
    BUST_STATE_NO_BUST,
    BUST_STATE_BUST
};

enum WinState
{
    WIN_STATE_LOSE,
    WIN_STATE_WIN
};

//typedef boost::int8_t int8;
//typedef boost::int16_t int16;
//typedef boost::int32_t int32;
//typedef boost::int64_t int64;
//typedef boost::uint8_t uint8;
//typedef boost::uint16_t uint16;
//typedef boost::uint32_t uint32;
//typedef boost::uint64_t uint64;