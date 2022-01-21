#include <iostream>
#include <map>
#include "mutex"

std::mutex c_c_st_cb;

// 1. На современных шоколадных фабриках используются нагреватели с компьютерным управлением. Смесь молока и шоколада в
//нагревателе доводится до кипения и передается на следующий этап изготовления. Ниже приведен код класса, управляющего
//таким нагревателем. Сейчас попытка создать новый объект данного класса будет успешной и это приведет к неверному
//управлению бойлером. Оптимизируйте его так, чтобы любые другие объекты обращаясь к этому нагревателю получали
//только один экземпляр, если он существует.

// Исходный
class ChocolateBoiler {
private:
    bool _empty;
    bool _boiled;
public:
    ChocolateBoiler() {
        _empty = true;
        _boiled = false;
    }

    bool isEmpty() const {
        return _empty;
    }

    bool isBoiled() const {
        return _boiled;
    }

    void fill() {
        if (isEmpty()) {
            _empty = false;
            _boiled = false;
        }
    }

    void drain() {
        if (!isEmpty() && isBoiled()) {
            _empty = true;
        }
    }

    void boil() {
        if (!isEmpty() && !isBoiled()) {
            _boiled = true;
        }
    }
};

//Синглтон
class SingleToneChocolateBoiler {
private:
    //защищенные параметры
    bool _empty;
    bool _boiled;

    //защищенный конструктор
    SingleToneChocolateBoiler() {
        _empty = true;
        _boiled = false;
    }

    //защищенный деструктор
    ~SingleToneChocolateBoiler() {
        delete _uniqueInstance;
    }

    //проверка есть ли вообще экземпляр класса
    static SingleToneChocolateBoiler *_uniqueInstance;

public:
    //отключаем конструктор копирования
    SingleToneChocolateBoiler(SingleToneChocolateBoiler &other) = delete;

    //отключаем оператор присваивания
    void operator=(SingleToneChocolateBoiler &) = delete;

    //точка входа
    static SingleToneChocolateBoiler *GetInstance() {
        if (_uniqueInstance == nullptr) {
            _uniqueInstance = new SingleToneChocolateBoiler();
        }
    }

    [[nodiscard]] bool isEmpty() const {
        return _empty;
    }

    [[nodiscard]] bool isBoiled() const {
        return _boiled;
    }

    void fill() {
        if (isEmpty()) {
            _empty = false;
            _boiled = false;
        }
    }

    void drain() {
        if (!isEmpty() && isBoiled()) {
            _empty = true;
        }
    }

    void boil() {
        if (!isEmpty() && !isBoiled()) {
            _boiled = true;
        }
    }
};

SingleToneChocolateBoiler *SingleToneChocolateBoiler::_uniqueInstance = nullptr;


//2. Автоматы в наше время все чаще заменяют людей. Появились автоматы, наливающие напитки, продающие сухарики,
//контактные линзы, автоматы выдающие ваши интернет заказы. Обычно все эти автоматы связаны между собой в сеть и
//управляются с клиента. Раз в месяц необходимо составлять отчет о состоянии автоматов. Но проблема в том, что ресурсов
//на клиенте недостаточно, чтобы постоянно опрашивать сраазу все автоматы в режиме реального времени.
//
//Реализуйте паттерн Proxy для данного кода. Заместитель должен хранить в себе еще одно дополнительное
//поле с датой получения данных. При вызове любого из отчетов, должна происходить проверка времени последнего
//запроса данных. Если прошло более одного часа, то тогда вызываем метод с отчетом в реальном объекте. Если меньше,
//то выводим на экран сохраненные данные с прошлого отчета. Для времени удобно использовать #include <ctime>

class ISellSystem {
public:
    virtual void changePrice(std::string, float) = 0;

    virtual void sellProduct(std::string) = 0;

    virtual void addProduct(std::string, size_t) = 0;
};


class Automaton : ISellSystem {
private:
    std::string location;
    double recieved_money;
    double spent_money;
    std::map<std::string, float> goods_price;
    std::map<std::string, float> goods_count;

public:
    Automaton(const std::string &location, double recievedMoney) : location(location), recieved_money(recievedMoney) {
        spent_money = 0.0;
    }

    void changePrice(std::string name, float newPrice) override {
        goods_price[name] = newPrice;
    }

    void sellProduct(std::string name) {
        if (goods_count[name] > 0) {
            recieved_money += goods_price[name];
        } else {
            std::cerr << "Not enough goods" << std::endl;
        }
    }

    void addProduct(std::string name, size_t count) {
        goods_count[name] += count;
    }

    double allMoneyReport() const {
        return recieved_money - spent_money;
    }

    const std::string &getLocationReport() const {
        return location;
    }

    void goodsCountReport() const {
        for (auto&[product, count]: goods_count) {
            std::cout << product << ": " << count << std::endl;
        }
    };

    void goodsPriceReport() const {
        for (auto&[product, price]: goods_price) {
            std::cout << product << ": " << price << std::endl;
        }
    };
};


int main() {
    std::cout << "____1/1_____" << std::endl;
    SingleToneChocolateBoiler *s_t_c_b = SingleToneChocolateBoiler::GetInstance();
    SingleToneChocolateBoiler *s_t_c_b_2 = SingleToneChocolateBoiler::GetInstance();
    std::cout << "s_t_c_b print" << std::endl;
    std::cout << "isEmpty " << s_t_c_b->isEmpty() << std::endl;
    std::cout << "isBoiled " << s_t_c_b->isBoiled() << std::endl;
    std::cout << "s_t_c_b_2 fill + boil" << std::endl;
    s_t_c_b_2->fill();
    s_t_c_b_2->boil();
    std::cout << "s_t_c_b print" << std::endl;
    std::cout << "isEmpty " << s_t_c_b->isEmpty() << std::endl;
    std::cout << "isBoiled " << s_t_c_b->isBoiled() << std::endl;

    std::cout << std::endl;
    std::cout << "____1/2_____" << std::endl;


    return 0;
}
