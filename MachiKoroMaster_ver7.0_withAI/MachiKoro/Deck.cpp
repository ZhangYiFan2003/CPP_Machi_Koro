#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include "Deck.h"


using namespace std;

ostream& operator << (ostream& os, const Color& obj)
{
	os << static_cast<typename underlying_type<Color>::type>(obj);
	return os;
}
ostream& operator << (ostream& os, const Icon& obj)
{
	os << static_cast<typename underlying_type<Icon>::type>(obj);
	return os;
}