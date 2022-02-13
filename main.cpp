#include <iostream>
#include "L1.h"

int main() {
    CreatorPlayer player_1(100, 28.5, "Mikola");
    GuardianPlayer guard_player_1(player_1);

    CaretakerPlayer caretaker_player_1(player_1, guard_player_1);

    std::cout << "Start condition player" << std::endl;
    std::cout << caretaker_player_1.getName() << std::endl;
    std::cout << caretaker_player_1.getHp() << std::endl;

    std::cout << std::endl;
    std::cout << "add 50 HP player in caretaker_player_1, cout in player_1" << std::endl;
    caretaker_player_1.changeHp(50);
    std::cout << player_1.getName() << std::endl;
    std::cout << player_1.getHp() << std::endl;

    std::cout << std::endl;
    std::cout << "add 50 HP player in caretaker_player_1, cout in player_1" << std::endl;
    caretaker_player_1.changeHp(50);
    std::cout << player_1.getName() << std::endl;
    std::cout << player_1.getHp() << std::endl;

    std::cout << std::endl;
    std::cout << "reset last state in caretaker_player_1 (guard_player_1), cout in player_1" << std::endl;
    caretaker_player_1.last_state_return();
    std::cout << player_1.getName() << std::endl;
    std::cout << player_1.getHp() << std::endl;



    return 0;
}
