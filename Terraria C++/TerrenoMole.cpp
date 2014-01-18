#include "TerrenoMole.h"


TerrenoMole::TerrenoMole(int X, int Y)
{
    _breakeable = 1;
    _ticks = 1;
    _x = X;
    _y = Y;
}

std::array<std::array<int, 5>, 5> TerrenoMole::getDrawSequence() const
{
    std::array<std::array<int, 5>, 5> _terrenoMole = {
        218, 196, 196, 196, 191,
        179, 176, 176, 176, 179,
        179, 176, 176, 176, 179,
        179, 176, 176, 176, 179,
        192, 196, 196, 196, 217};

	return _terrenoMole;
}

/* Gets */
int TerrenoMole::getX() const
{
    return _x;
}
int TerrenoMole::getY() const
{
    return _y;
}
int TerrenoMole::getTicks() const
{
    return _ticks;
}
int TerrenoMole::getBreakeable() const
{
    return _breakeable;
}

/* Sets */
void TerrenoMole::setX(int S)
{
    _x = S;
}
void TerrenoMole::setY(int S)
{
    _y = S;
}
void TerrenoMole::setTicks(int S)
{
    _ticks = S;
}
void TerrenoMole::setBreakeable(int S)
{
    _breakeable = S;
}