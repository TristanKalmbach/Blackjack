#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <windows.h>
#include <algorithm>
#include <memory>

class Card;

using Cards = std::vector<Card>;

#define MAX_DECK_SIZE 52
#define MAX_SUITS 4
#define MAX_VALUE 13

enum CardValues
{
    Ace = 0,
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King
};

enum class Mechanic
{
    None,
    Hit,
    Stand,
    Double,
    Split
};