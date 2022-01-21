#include <iostream>
#include <map>
#include "mutex"
#include "ctime"

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

    //указатель на самого себя.
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

    void sellProduct(std::string name) override {
        if (goods_count[name] > 0) {
            recieved_money += goods_price[name];
        } else {
            std::cerr << "Not enough goods" << std::endl;
        }
    }

    void addProduct(std::string name, size_t count) override {
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

class ProxyAutomaton : public ISellSystem{

// сделано то что снизу, но оно совсем не верно. Потому что я дурачек =)
private:
    std::string location;
    double all_money_report{};
    // у в прокси остаольное неописано что должно храниться, и не указано что должно от прокси передаваться.

    time_t last_report_time{};

    Automaton *_real_automation{};

    [[nodiscard]] bool CheckAccess() const {
        // ну типа всегда доступен) но для этого я бы положил флаг в Automaton раный тру, и пробовал бы его достовать
        std::cout << "Proxy access done" << std::endl;
        return true;
    }

    void log_time() {
        last_report_time = time(nullptr);
    }

    void proxy_automat_take() {
        // остальные репорты соут, следовательно если мы гетером не будем забирать массивы, то это только стучаться туда
        // посему будем считать что остальные репорты нас в прокси не интересуют
        location = _real_automation->getLocationReport();
        all_money_report = _real_automation->allMoneyReport();
        log_time();
    }

    void print_proxy_report(){
//        Печатаем интересующие репорты из памяти прокси
        std::cout << "location - " << location << std::endl;
        std::cout << "all_money_report - " << all_money_report << std::endl;
    }

public:
    ProxyAutomaton(Automaton *_real_obj) : _real_automation(new Automaton(*_real_obj)) {
        proxy_automat_take();
    }

    ~ProxyAutomaton(){
        delete _real_automation;
    }

    void changePrice(std::string name, float newPrice) override {
        // поскольку мы правим массив с данным, то по сути стучимся в автомат
        if(CheckAccess()) {
            _real_automation->changePrice(name, newPrice);
        } else {
            std::cout << "Not connect" << std::endl;
        }

    }

    void sellProduct(std::string name) override {
        // поскольку мы правим массив с данным, то по сути стучимся в автомат
        if(CheckAccess()) {
            _real_automation->sellProduct(name);
        } else {
            std::cout << "Not connect" << std::endl;
        }

    }

    void addProduct(std::string name, size_t count) override {
        // поскольку мы правим массив с данным, то по сути стучимся в автомат
        if(CheckAccess()) {
            _real_automation->addProduct(name, count);
        } else {
            std::cout << "Not connect" << std::endl;
        }
    }


    [[nodiscard]] time_t get_log_time() const {
        // доступ, что бы вытащить время
        return last_report_time;
    }

    void proxy_report() {
        // при наличии доступа, если данным более часа 3600 сек, достаем свежие репорты и печатаем их,
        // ежели репорты свежее часа просто печатаем их из памяти прокси.
        if(CheckAccess()) {
            time_t this_time = time(nullptr);
            if((this_time - last_report_time) > static_cast<time_t>(3600)) {
                proxy_automat_take();
                print_proxy_report();
            } else {
                print_proxy_report();
            }
        }
    }
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

    auto* real_automat = new Automaton("Ashan", 100);
    auto* proxy_automat = new ProxyAutomaton(real_automat);
    proxy_automat->proxy_report();


    return 0;
}
