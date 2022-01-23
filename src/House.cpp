#include "House.h"
#include <iostream>
#include "MyTools.h"
#include "HouseBuilder.h"
#include "ScreenSingleton.h"

bool House::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void House::Draw() const
{
	/*ScreenSingleton::getInstance().SetColor(CC_Yellow);
	ScreenSingleton::getInstance().GotoXY(x, y - 5);
	std::cout << "  ########  ";
	ScreenSingleton::getInstance().GotoXY(x, y - 4);
	std::cout << "##        ##";
	ScreenSingleton::getInstance().GotoXY(x, y - 3);
	std::cout << "############";
	ScreenSingleton::getInstance().GotoXY(x, y - 2);
	std::cout << "#          #";
	ScreenSingleton::getInstance().GotoXY(x, y - 1);
	std::cout << "#          #";
	ScreenSingleton::getInstance().GotoXY(x, y);
	std::cout << "############";*/

	ScreenSingleton::getInstance().SetColor(CC_Yellow);
	ScreenSingleton::getInstance().GotoXY(x, y - 5);
    for(auto i : look) {
        for (size_t j = 0; j < columns; ++j) {
            std::cout << i[j] << " ";
        }
        std::cout << '\n';
    }

}
