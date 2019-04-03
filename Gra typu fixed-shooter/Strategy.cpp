#include"Strategy.h"

Strategy::Strategy() : fire{new Fire}, speed { 1 }
{}

Strategy::Strategy(const Strategy& object) : fire{ object.fire }, speed{object.speed}
{}	