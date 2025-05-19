#include <SFML/Graphics.hpp>
#include <sstream>
#include <string>
#include "pair.h"
#include "vector.h"

// Утилита для конвертации числа в строку
template <typename T>
std::string to_string(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}


int main() {

    // Создаем окно
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Vector Demo");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // Замените на путь к вашему шрифту
        return 1;
    }

    // Создаем вектор типа Vector<Pair<Vector<int>, Vector<Pair<int, double>>>>
    Vector<Pair<Vector<int>, Vector<Pair<int, double>>>> vec;

    // Заполняем вектор данными
    Vector<int> int_vec1;
    int_vec1.push_back(1);
    int_vec1.push_back(2);
    int_vec1.push_back(3);

    Vector<Pair<int, double>> pair_vec1;
    pair_vec1.push_back(Pair<int, double>(1, 1.5));
    pair_vec1.push_back(Pair<int, double>(2, 2.5));
    pair_vec1.push_back(Pair<int, double>(3, 3.5));

    Vector<int> int_vec2;
    int_vec2.push_back(4);
    int_vec2.push_back(5);
    int_vec2.push_back(6);

    Vector<Pair<int, double>> pair_vec2;
    pair_vec2.push_back(Pair<int, double>(4, 4.5));
    pair_vec2.push_back(Pair<int, double>(5, 5.5));
    pair_vec2.push_back(Pair<int, double>(6, 6.5));

    vec.push_back(
        Pair<Vector<int>, Vector<Pair<int, double>>>(int_vec1, pair_vec1));
    vec.push_back(
        Pair<Vector<int>, Vector<Pair<int, double>>>(int_vec2, pair_vec2));

    // Основной цикл приложения
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        // Отображаем первую матрицу (Vector<int>)
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::Black);
        text.setPosition(50, 50);
        text.setString("First Matrix (Vector<int>):");
        window.draw(text);

        float y = 80;
        for (size_t i = 0; i < vec.size(); ++i) {
            std::string row;
            for (size_t j = 0; j < vec.at(i).first.size(); ++j) {
                row += to_string(vec.at(i).first.at(j)) + " ";
            }
            text.setString(row);
            text.setPosition(50, y);
            window.draw(text);
            y += 30;
        }

        // Отображаем вторую матрицу (Vector<Pair<int, double>>)
        text.setPosition(50, y + 30);
        text.setString("Second Matrix (Vector<Pair<int, double>>):");
        window.draw(text);

        y += 60;
        for (size_t i = 0; i < vec.size(); ++i) {
            std::string row;
            for (size_t j = 0; j < vec.at(i).second.size(); ++j) {
                row += "(" + to_string(vec.at(i).second.at(j).first) + ", " +
                       to_string(vec.at(i).second.at(j).second) + ") ";
            }
            text.setString(row);
            text.setPosition(50, y);
            window.draw(text);
            y += 30;
        }

        // Демонстрация методов Vector
        y += 30;
        text.setPosition(50, y);
        text.setString("Vector Methods Demo:");
        window.draw(text);
        y += 30;

        // Демонстрация методов
        Vector<Pair<Vector<int>, Vector<Pair<int, double>>>> demo_vec = vec;

        // 1. size(), capacity(), max_size()
        text.setString("size: " + to_string(demo_vec.size()) +
                       ", capacity: " + to_string(demo_vec.capacity()) +
                       ", max_size: " + to_string(demo_vec.max_size()));
        text.setPosition(50, y);
        window.draw(text);
        y += 30;

        // 2. push_back()
        demo_vec.push_back(
            Pair<Vector<int>, Vector<Pair<int, double>>>(int_vec1, pair_vec1));
        text.setString("After push_back, size: " + to_string(demo_vec.size()));
        text.setPosition(50, y);
        window.draw(text);
        y += 30;

        // 3. pop_back()
        demo_vec.pop_back();
        text.setString("After pop_back, size: " + to_string(demo_vec.size()));
        text.setPosition(50, y);
        window.draw(text);
        y += 30;

        // 4. emplace_back()
        demo_vec.emplace_back(int_vec2, pair_vec2);
        text.setString("After emplace_back, size: " +
                       to_string(demo_vec.size()));
        text.setPosition(50, y);
        window.draw(text);
        y += 30;

        // 5. insert()
        demo_vec.insert(
            demo_vec.begin(),
            Pair<Vector<int>, Vector<Pair<int, double>>>(int_vec1, pair_vec1));
        text.setString("After insert at begin, size: " +
                       to_string(demo_vec.size()));
        text.setPosition(50, y);
        window.draw(text);
        y += 30;

        // 6. erase()
        demo_vec.erase(demo_vec.begin());
        text.setString("After erase at begin, size: " +
                       to_string(demo_vec.size()));
        text.setPosition(50, y);
        window.draw(text);
        y += 30;

        // 7. clear()
        demo_vec.clear();
        text.setString("After clear, size: " + to_string(demo_vec.size()) +
                       ", empty: " + to_string(demo_vec.empty()));
        text.setPosition(50, y);
        window.draw(text);
        y += 30;

        // 8. assign()
        demo_vec.assign(2, Pair<Vector<int>, Vector<Pair<int, double>>>(
                               int_vec1, pair_vec1));
        text.setString("After assign(2, value), size: " +
                       to_string(demo_vec.size()));
        text.setPosition(50, y);
        window.draw(text);
        y += 30;

        // 9. swap()
        Vector<Pair<Vector<int>, Vector<Pair<int, double>>>> other_vec;
        other_vec.push_back(
            Pair<Vector<int>, Vector<Pair<int, double>>>(int_vec2, pair_vec2));
        demo_vec.swap(other_vec);
        text.setString(
            "After swap, demo_vec size: " + to_string(demo_vec.size()) +
            ", other_vec size: " + to_string(other_vec.size()));
        text.setPosition(50, y);
        window.draw(text);
        y += 30;

        // 10. reserve() и resize()
        demo_vec.reserve(10);
        demo_vec.resize(3, Pair<Vector<int>, Vector<Pair<int, double>>>(
                               int_vec1, pair_vec1));
        text.setString("After reserve(10) and resize(3), size: " +
                       to_string(demo_vec.size()) +
                       ", capacity: " + to_string(demo_vec.capacity()));
        text.setPosition(50, y);
        window.draw(text);

        window.display();
    }

    return 0;
}
