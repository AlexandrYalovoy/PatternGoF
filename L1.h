//
// Created by alexa on 13.02.2022.
//

#ifndef PATTERNGOF_L1_H
#define PATTERNGOF_L1_H

#include <utility>
#include "vector"
#include "string"
#include "iostream"

//Memento
//Сохранение состояния объектов не всегда связано с хранением в оперативной памяти. Иногда требуется выполнить
//сохранение так, чтобы можно было вернуться к нему в любой момент, даже после перезапуска приложения. И в этом
//случае очень подходит механизм сохранения в файл. Но, чтобы избежать проблем с запуском на разных платформах,
//рекомендуется использовать сериализацию.
//Реализуйте паттерн Хранитель для ниже расположенного кода так, чтобы данные об объекте player сериализировались
//в бинарный файл. Тему по сериализации можно освежить из урока с курса по сложным моментам

/*
class Player{
private:
    float hp;
    int speed;
    std::string name;
public:
    Player(float hp, int speed, const std::string &name) : hp(hp), speed(speed), name(name) {}

    void changeSpeed(int change){
        speed += change;
    }

    void changeHp(int change){
        hp += change;
    }

    float getHp() const {
        return hp;
    }

    int getSpeed() const {
        return speed;
    }

    const std::string &getName() const {
        return name;
    }

};
*/


// Создатель
// Создает игрока, предусмотрено 3 конструктора, дефолтный деструктор
// О других классах не знает, наличие сеттеров меня смущает, не безопасно это. Враги могут внести изменение без снимка
class CreatorPlayer {
private:
    float hp;
    int speed;
    std::string name;
public:
    CreatorPlayer() {
        hp = 0.0;
        speed = 0;
        name = "N/A";
    }

    CreatorPlayer(float _hp, int _speed, std::string _name) {
        hp = _hp;
        speed = _speed;
        name = std::move(_name);
    }

    CreatorPlayer(const CreatorPlayer &_mem_player_exempl) {
        hp = _mem_player_exempl.getHp();
        speed = _mem_player_exempl.getSpeed();
        name = _mem_player_exempl.getName();
    }

    ~CreatorPlayer() = default;

    [[nodiscard]] float getHp() const {
        return hp;
    }

    [[nodiscard]] int getSpeed() const {
        return speed;
    }

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    // тут сеттеры плохо но без них никак
    void setHp(float _hp) {
        CreatorPlayer::hp = _hp;
    }

    void setSpeed(int _speed) {
        CreatorPlayer::speed = _speed;
    }

    void setName(const std::string &_name) {
        CreatorPlayer::name = _name;
    }
};

//Хранитель
// Хранит состояния игрока в векторе, но так же и стартовое значение начала защиты, дабы его вертать когда вектор
// иссякнет. Ну и чтоб было можно понять с кого первоначально начали хранение если перепутается что.
class GuardianPlayer {
private:
    CreatorPlayer _protected_create_payer_exempl;
    std::vector<CreatorPlayer> _vector_create_player_temp{};
public:
    GuardianPlayer() = default;

    ~GuardianPlayer() = default;

    explicit GuardianPlayer(CreatorPlayer &_create_payer_exempl) {
        _protected_create_payer_exempl = _create_payer_exempl;
        add_player_temp(_create_payer_exempl);
    }

    void add_player_temp(CreatorPlayer _create_player) {
        _vector_create_player_temp.push_back(_create_player);
    }

    CreatorPlayer pop_player_temp() {
        if (!_vector_create_player_temp.empty()) {
            size_t index_second = _vector_create_player_temp.size() - 1;
            CreatorPlayer temp_cp = _vector_create_player_temp[index_second];
            _vector_create_player_temp.pop_back();
            return temp_cp;
        } else {
            std::cout << "Not save temp" << std::endl;
            return _protected_create_payer_exempl;
        }

    }

};

// Опекун
// Собственно через этот класс мы должны редактировать игрока, он по сути снимает копию ложит ее в гварда, а после
// вносит изменения в плеера. Если у нас откат, достаем крайнее значение из вектора методами гварда,
// затираем игрока значением из темп.
class CaretakerPlayer {
private:
    CreatorPlayer &_creator_player;
    GuardianPlayer &_guardian_player;
public:
    CaretakerPlayer(CreatorPlayer &ref_creator_player, GuardianPlayer &ref_guardian_player)
            : _creator_player(ref_creator_player), _guardian_player(ref_guardian_player) {}

    ~CaretakerPlayer() = default;

    void changeSpeed(int change) {
        _guardian_player.add_player_temp(_creator_player);
        int spam_speed = _creator_player.getSpeed() + change;
        _creator_player.setSpeed(spam_speed);
    }

    void changeHp(int change) {
        _guardian_player.add_player_temp(_creator_player);
        float spam_hp = _creator_player.getHp() + static_cast<float>(change);
        _creator_player.setHp(spam_hp);
    }

    void last_state_return() {
        CreatorPlayer spam_temp{};
        spam_temp = _guardian_player.pop_player_temp();
        _creator_player = spam_temp;
    }

    [[nodiscard]] float getHp() const {
        return _creator_player.getHp();
    }

    [[nodiscard]] int getSpeed() const {
        return _creator_player.getSpeed();
    }

    [[nodiscard]] const std::string &getName() const {
        return _creator_player.getName();
    }
};


#endif //PATTERNGOF_L1_H
