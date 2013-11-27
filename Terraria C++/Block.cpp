#include "Block.h"

Block::Block(int ID, bool Breakable, int Ticks)
{
	_id = ID;
	_breakable = Breakable;
	_ticks = Ticks;
}