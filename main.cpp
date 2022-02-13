#include <iostream>
#include "L1.h"

int main() {
    CreatorPlayer player_1(100, 28.5, "Mikola");
    GuardianPlayer guard_player_1(player_1);

    CaretakerPlayer caretaker_player_1(player_1, guard_player_1);

    std::cout << caretaker_player_1.getName() << std::endl;
    std::cout << caretaker_player_1.getHp() << std::endl;
    caretaker_player_1.changeHp(50);
    caretaker_player_1.changeHp(50);
    std::cout << caretaker_player_1.getName() << std::endl;
    std::cout << caretaker_player_1.getHp() << std::endl;
    std::cout << player_1.getHp() << std::endl;


    return 0;
}
