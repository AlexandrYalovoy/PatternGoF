#include <iostream>
#include <vector>

/*
1 Abstract Factory
Разработчики начали писать код для пиццерии. Выглядит он следующим образом:

class Pizza{
public:
    virtual void prepare(std::string);
    virtual void bake() {};
    virtual void cut() {};
    virtual void box() {};
};

class CheesePizza:public Pizza{};
class GreekPizza:public Pizza{};
class PepperoniPizza:public Pizza{};

Pizza* orderPizza(std::string type){
    Pizza* pizza = nullptr;
    if (type == "cheese"){
        pizza = new CheesePizza;
    }
    else if (type == "greek"){
        pizza = new GreekPizza;
    }
    else if (type == "pepperoni"){
        pizza = new PepperoniPizza;
    }
    return pizza;
}


Как видите, на каждый тип пиццы создается свой собственный класс.
И в целом это неплохо. Но выбор конкретного класса для создания экземпляра усложняет функцию orderPizza()
и не позволяет закрыть её для изменений. Реализуйте паттерн “абстрактная фабрика” который позволит создавать
пиццу не привязываясь к её типу, чтобы внутри функции orderPizza()  не создавались конкретные экземпляры классов
с пиццами
*/

class Pizza {
public:
    virtual void prepare(std::string) = 0;

    virtual void bake() {}

    virtual void cut() {}

    virtual void box() {}

    virtual ~Pizza() {}
};

class CheesePizza : public Pizza {
public:

    void prepare(std::string) override {
        std::cout << "CheesePizza" << std::endl;
    }

    void bake() override {}

    void cut() override {}

    void box() override {}
};

class GreekPizza : public Pizza {
public:

    void prepare(std::string) override {
        std::cout << "GreekPizza" << std::endl;
    }

    void bake() override {}

    void cut() override {}

    void box() override {}
};

class PepperoniPizza : public Pizza {
public:
    void prepare(std::string) override {
        std::cout << "PepperoniPizza" << std::endl;
    }

    void bake() override {}

    void cut() override {}

    void box() override {}
};

class pizzaBakery {
public:
    virtual Pizza *bakePizza() = 0;

    virtual ~ pizzaBakery() {}
};

class BakeCheesePizza : public pizzaBakery {
public:
    Pizza *bakePizza() override {
        return new CheesePizza;
    }
};

class BakeGreekPizza : public pizzaBakery {
public:
    Pizza *bakePizza() override {
        return new GreekPizza;
    }
};

class BakePepperoniPizza : public pizzaBakery {
public:
    Pizza *bakePizza() override {
        return new PepperoniPizza;
    }
};


struct Order {
    ~Order() { for (const auto &i: order_list) delete i; }

    void info() { for (const auto &i: order_list) i->prepare("  "); }

    std::vector<Pizza *> order_list;

};

class Visitor {
public:
    void addPizza(pizzaBakery &bakery) {
        order.order_list.push_back(bakery.bakePizza());
    }

    void getOrderInfo() {
        order.info();
    }

private:
    Order order;
};

/*
2 Command
Вы решили запрограммировать умную лампочку, которую можно включать и выключать и задавать цвет свечения.
В вашем распоряжении есть следующий класс:

enum class Colors {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    VIOLET,
    WHITE
};

class Light{
public:
    Light():state(false), color(Colors::WHITE){};
    void On(){
        if(!state){
            state = true;
        }
    };

    void Off(){
        if(state){
            state = false;
        }
    };

    void changeColor(Colors newColor){
        color = newColor;
    }

    bool getState() const {
        return state;
    }

private:
    bool state;
    Colors color;
};



Реализуйте паттерн команда, чтобы можно было сохранять состояние лампочки и проигрывать её мерцание как в прямом
так и в обратном направлении.
*/

enum class Colors {
    RED,
    ORANGE,
    YELLOW,
    GREEN,
    CYAN,
    BLUE,
    VIOLET,
    WHITE
};

std::ostream &operator<<(std::ostream &out, const Colors &t) {
    switch (t) {
        case Colors::RED:
            return (out << "RED");
        case Colors::ORANGE:
            return (out << "ORANGE");
        case Colors::YELLOW:
            return (out << "YELLOW");
        case Colors::GREEN:
            return (out << "GREEN");
        case Colors::CYAN:
            return (out << "CYAN");
        case Colors::BLUE:
            return (out << "BLUE");
        case Colors::VIOLET:
            return (out << "VIOLET");
        case Colors::WHITE:
            return (out << "WHITE");
    }
    return (out);
}

class Light {
public:
    Light() : state(false), color(Colors::WHITE) {}

    void On() {
        if (!state) {
            state = true;
        }
    }

    void Off() {
        if (state) {
            state = false;
        }
    }

    void changeColor(Colors newColor) {
        color = newColor;
    }

    [[nodiscard]] bool getState() const {
        return state;
    }

    void info() { std::cout << "light color: " << color << " state: " << getState() << std::endl; }

    Colors getColor() { return color; }

private:
    bool state;
    Colors color;
};

class Command {
protected:
    Light *light{};
public:
    virtual ~Command() {}

    virtual void Execute() = 0;

    virtual void unSet() = 0;

    void setLight(Light *_light) {
        light = _light;
    }

};

class ChangeLightSettinds : public Command {
    Colors color;
    Colors prevColor;
public:

    explicit ChangeLightSettinds(Colors _color) : color(_color), prevColor(Colors::WHITE) {}

    void Execute() override {
        prevColor = light->getColor();
        light->changeColor(color);
        light->On();
        light->info();
    }

    void unSet() override {
        light->changeColor(prevColor);
    }

};

class LightPlayer {
    std::vector<Command *> m_cmd;
    Light light;
    Command *pCmd;

public:

    LightPlayer() : pCmd(nullptr) {}

    ~LightPlayer() {
        for (Command *ptr: m_cmd) {
            delete ptr;
        }
    }

    void Add(Colors color) {
        pCmd = new ChangeLightSettinds(color);
        pCmd->setLight(&light);
        pCmd->Execute();
        m_cmd.push_back(pCmd);
    }

    void Undo() {
        if (m_cmd.empty()) {
            std::cout << "There is nothing to undo!" << std::endl;
        } else {
            std::cout << "undo " << std::endl;
            pCmd = m_cmd.back();
            pCmd->unSet();
            m_cmd.pop_back();

            delete pCmd;
        }
    }

    void getInfo() {
        light.info();
    }
};

/*
3 Decorator
Вы решили открыть кофейню и вам понадобилось наладить учет производства напитков. Вы создали абстрактный класс,
в котором определили метод для расчета стоимости всех напитков.
class Beverage{            // Абстрактный класс
public:
    virtual std::String getDescription() const;
    virtual double cost() const = 0;
    virtual ~Beverage() {}
};

class HouseBlend: public Beverage{   // Молотый
public:
    double cost() const override {
        return 5.5;
    }
};

class DarkRoast: public Beverage{  // Темной обжарки
public:
    double cost() const override {
        return 6.0;
    }
};

class Decaf: public Beverage{    // Без кофеина
public:
    double cost() const override {
        return 7.3;
    }
};

class Espresso: public Beverage{  // Эспрессо
public:
    double cost() const override {
        return 3.5;
    }
};


Но к кофе можно заказать еще различные  добавки (шоколад, корица, взбитые сливки) или наоборот взять без сахара.
Дополнения не бесплатны, поэтому они должны быть встроены в систему оформления заказов. А отсутствие сахара должно
наоборот снижать стоимость. Понятное дело, что создавать отдельные классы для каждого варианта “сборки” кофе -
не вариант. И тут нам на помощь придет декоратор!
Реализуйте паттерн декоратор с помощью которого можно будет сварить кофе с любым составом добавок.
*/

class Beverage {
public:// Абстрактный класс
    [[nodiscard]] virtual std::string getDescription() const = 0;

    [[nodiscard]] virtual double cost() const = 0;
};

class HouseBlend : public Beverage {   // Молотый
public:
    [[nodiscard]] std::string getDescription() const override {
        return "HouseBlend";
    }

    [[nodiscard]] double cost() const override {
        return 5.5;
    }
};

class DarkRoast : public Beverage {  // Темной обжарки
public:
    [[nodiscard]] std::string getDescription() const override {
        return "DarkRoast";
    }

    [[nodiscard]] double cost() const override {
        return 6.0;
    }
};

class Decaf : public Beverage {    // Без кофеина
public:
    [[nodiscard]] std::string getDescription() const override {
        return "Decaf";
    }

    [[nodiscard]] double cost() const override {
        return 7.3;
    }
};

class Espresso : public Beverage {  // Эспрессо
public:
    [[nodiscard]] std::string getDescription() const override {
        return "Espresso";
    }

    [[nodiscard]] double cost() const override {
        return 3.5;
    }
};

class Decorator : public Beverage {
    Beverage *m_beverage;
public:
    explicit Decorator(Beverage *beverage) : m_beverage(beverage) {}

    virtual std::string getDescription() const override {
        return m_beverage->getDescription();
    }

    virtual double cost() const override {
        return (m_beverage->cost());
    }
};

class AddMilk : public Decorator {
public:
    explicit AddMilk(Beverage *beverage) : Decorator(beverage) {}

    virtual std::string getDescription() const override {
        return Decorator::getDescription() + " with milk";
    }

    virtual double cost() const override {
        return (Decorator::cost() + 0.5);
    }
};

class AddSugar : public Decorator {
public:
    explicit AddSugar(Beverage *beverage) : Decorator(beverage) {}

    virtual std::string getDescription() const override {
        return Decorator::getDescription() + " with sugar";
    }

    virtual double cost() const override {
        return (Decorator::cost() + 0.3);
    }
};

class NoSugar : public Decorator {
public:
    explicit NoSugar(Beverage *beverage) : Decorator(beverage) {}

    virtual std::string getDescription() const override {
        return Decorator::getDescription() + " no sugar";
    }

    virtual double cost() const override {
        return (Decorator::cost() - 0.3);
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
