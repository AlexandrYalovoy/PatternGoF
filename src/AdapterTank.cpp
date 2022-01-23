#include <iostream>
#include <vector>

#include "AdapterTank.h"
#include "ScreenSingleton.h"

AdapterTank::AdapterTank(std::string options) : mAdaptee(std::move(options)),
                                                score(0), mTank(nullptr), x(0), y(0),
                                                width(0) {
    std::string temp_str {};
    std::vector<std::string> arr;
    for (char i : mAdaptee) {
        if (i != ';') {
            temp_str += i;
        }
        else {
            arr.push_back(temp_str);
            temp_str.clear();
        }
    }
    arr.push_back(temp_str);
    x = std::strtod(arr[0].c_str(), nullptr);
    y = std::strtod(arr[1].c_str(), nullptr);
    width = std::strtoul(arr[2].c_str(), nullptr, 10);
}


void AdapterTank::Draw() const {

}

void AdapterTank::SetPos(double nx, double ny) {
    mTank->SetPos(x, y);
}

void AdapterTank::SetWidth(uint16_t widthN) {
    mTank->SetWidth(width);
}

bool AdapterTank::isInside(double x1, double x2) const {
    return false;
}



