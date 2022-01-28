#include <iostream>
#include <fstream>


//1 Strategy
//Представьте, что вы разрабатываете текстовый редактор и вам необходимо реализовать деление текста на строки
//(перенос строк). Это удобный функционал, когда текст оказывается слишком длинным и приходится постоянно
//выполнять горизонтальную прокрутку, чтобы его читать. Для выполнения данной задачи было представлено 3 алгоритма:
//Деление текста на строки в зависимости от ширины клиентского окна
//Деление текста на строки указанной ширины (передается в качестве параметра)
//Автоматическое деление текста по предложениям (учитываются знаки препинания .!?)
//Реализуйте паттерн стратегия, чтобы иметь возможность выбирать нужный алгоритм деления на предложения.
//
//Сами методы DivideBy… реализовывать не обязательно. Главное сам паттерн. Но если хочется, то можно)

// ИСХОДНЫЙ
/*
enum class DivideMethod{
    ByScreenWidth,
    ByUserWidth,
    BySentence
};

class ITextWork{
public:
    virtual void Divide(DivideMethod) = 0;
};

class TextEditor: ITextWork{
private:
    size_t EditorWidth;
    std::string all_text;
public:
    TextEditor(){};
    TextEditor(const std::string &text) : all_text(text) {};

    TextEditor(std::ifstream& file) {
        std::string line;
        if (file.is_open()){
            while (getline(file, line))
            {
                all_text+=line;
            }
        }
    }

    void PrintText() const{
        std::cout << all_text << std::endl;
    }

    void Divide(DivideMethod method) override {
        switch (method) {
            case DivideMethod::ByScreenWidth:
                DivideByScreenWidth();
                break;
            case DivideMethod::BySentence:
                DivideBySentence();
                break;
            case DivideMethod::ByUserWidth:
                DivideByUserWidth(EditorWidth);
                break;
            default:
                DivideByScreenWidth();
        }
    }

    void DivideByScreenWidth(){
        std::cout << "DivideByScreenWidth by screen width = " << EditorWidth << std::endl;
    }

    void DivideBySentence(){
        std::cout << "Divided by Sentences" << std::endl;
    }

    void DivideByUserWidth(int userWidth){
        std::cout << "DivideByScreenWidth by screen width = " << userWidth << std::endl;
    }
};
*/

class DivideStrategy {
public:
    virtual void divide(size_t _value) = 0;
};

class DivideByScreenWidth : public DivideStrategy {
public:
    void divide(size_t _value) override {
        std::cout << "DivideByScreenWidth by screen width = " << _value << std::endl;
    }
};

class DivideBySentence : public DivideStrategy {
public:
    void divide(size_t _value) override {
        std::cout << "Divided by Sentences" << std::endl;
    }
};

class DivideByUserWidth : public DivideStrategy {
public:
    void divide(size_t _value) override {
        std::cout << "DivideByScreenWidth by screen width = " << static_cast<int>(_value) << std::endl;
    }
};

class TextDivide {
protected:
    DivideStrategy *_divide_strategy{};
public:
    virtual void useStrategy(size_t _value) = 0;

    virtual void setStrategy(DivideStrategy *) = 0;

    virtual ~TextDivide() = default;
};

class TextEditor : public TextDivide {
private:
    size_t EditorWidth{};
    std::string all_text;
public:
    TextEditor() = default;

    TextEditor(const std::string &text, DivideStrategy *_divide_strategy) : all_text(text) {
        setStrategy(_divide_strategy);
    };

    void useStrategy(size_t _value) override {
        _divide_strategy->divide(_value);
    }

    void setStrategy(DivideStrategy *strategy) override {
        _divide_strategy = strategy;
    }

    ~TextEditor() override = default;

    explicit TextEditor(std::ifstream &file) {
        std::string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                all_text += line;
            }
        }
    }

    void PrintText() const {
        std::cout << all_text << std::endl;
    }
};

//2. Iterator
//Вспомните курс “Сложные моменты С++” :)
//Реализовать паттерн итератор, с помощью которого можно будет проитерироваться по контейнеру с объектами
//(одного любого класса) в оба направления (возьмите контейнеры - список, массив, вектор, дек).
//(Дополнительно) Попробуйте улучшить вашу реализацию, чтобы не было четкой привязки к классу объектов, хранящихся
//в контейнерах.

// подсмотрю решение по позже

//3. Adapter
//Представьте графический редактор, благодаря которому пользователи могут рисовать на экране графические
//элементы (линии, многоугольники, текст и т.д.). Каждый объект имеет возможность быть отрисован на экране и
//подвержен изменению формы. Если с графическими объектами всё просто, то текст всегда обрабатывается иначе.
//Разработайте адаптер для класса TextView, чтобы иметь возможность работать со всеми объектами графического
//редактора одинаковыми методами.

class IShape {
public:
    virtual void scale(double scale_percentage) = 0;// Масштабируем фигуру
    virtual void rotate(double angle) = 0;          // Поворачиваем фигуру
    virtual void flip() = 0;                        // Отражаем фигуру
};

class Figure : IShape {
private:
    int width;
    int height;
    double angle;
    bool isFlipped;
public:
    Figure(int width, int height) : width(width), height(height), angle(0.0), isFlipped(false) {}

    void scale(double scale_percentage) override {
        width *= static_cast<int>(scale_percentage);
        height *= static_cast<int>(scale_percentage);
    }

    void rotate(double _angle) override {
        angle += _angle;
    }

    void flip() override {
        isFlipped = !isFlipped;
    }
};

class IText {
    virtual void newSize(int size) = 0;   // Изменяем размер шрифта текста
    virtual void rotate(double angle) = 0;   // Поворачиваем текст
    virtual void reverse() = 0;              // Изменяем направление текста
};

class Text : IText {
private:
    int size;
    double angle;
    bool isReversed;
    std::string text;
public:
    Text(const std::string &text, int size, double angle, bool isReversed) : text(text), size(size), angle(0.0),
                                                                             isReversed(false) {}

public:
    void newSize(int newSize) override {
        size = newSize;
    }

    void rotate(double newAngle) override {
        angle = newAngle;
    }

    void reverse() override {
        for (int i = 0; i < text.size() / 2; ++i) {
            char c = text[i];
            text[i] = text[text.size() - 1 - i];
            text[text.size() - 1 - i] = c;
        }
    }

    void setSize(int _size) {
        size = _size;
    }

    [[nodiscard]] int getSize() const {
        return size;
    }
};

class TextAdapter : public IShape {
private:
    Text *_text{};
public:
    explicit TextAdapter(Text *text) : _text(text) {};

    void scale(double scale_percentage) override {
        int spam_size = _text->getSize();
        spam_size *= static_cast<int>((scale_percentage / static_cast<double>(100)));
        _text->setSize(spam_size);
    }

    void rotate(double _angle) override {
        _text->rotate(_angle);
    }

    void flip() override {
        _text->reverse();
    }

};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
