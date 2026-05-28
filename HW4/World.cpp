#include "World.hpp"
#include "Painter.hpp"
#include "Constants.hpp"
#include <fstream>
#include <stdexcept>
#include <algorithm>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);

    if (!stream) {
        throw std::runtime_error("Cannot open world file: " + worldFilePath);
    }
    /**
     * TODO: хорошее место для улучшения.
     * Чтение границ мира из модели
     * Обратите внимание, что здесь и далее мы многократно
     * читаем в объект типа Point, последовательно
     * заполняя координаты x и у. Если что-то делаем
     * многократно - хорошо бы вынести это в функцию
     * и не дублировать код...
     */
    stream >> topLeft >> bottomRight;
    physics.setWorldBox(topLeft, bottomRight);

    Point coordinates;
    Point velocity;
    Color color;
    double radius;
    bool isCollidable;

    // Здесь не хватает обработки ошибок, но на текущем
    // уровне прохождения курса нас это устраивает
    while (stream.peek(), stream.good()) {
        // Читаем координаты центра шара (x, y) 
        stream >> coordinates; 
        // Читаем вектор его скорости (vx, vy)
        stream >> velocity;
        // Читаем три составляющие цвета шара
        stream >> color;
        // Читаем радиус шара
        stream >> radius;
        stream >> std::boolalpha >> isCollidable;
        Ball ball{radius, color, isCollidable};
        ball.setCenter(coordinates);
        ball.setVelocity(velocity);
        balls.push_back(ball);
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    for (const Dust& dust : dusts) {
       dust.draw(painter);
    }
    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    std::vector<Collision> collisions = physics.update(balls, ticks);
    for (const Collision& collision : collisions) {
        const double numDusts = 10.0;
        for (int i = 0; i < static_cast<int>(numDusts); ++i) {
            const double angle = i * 2.0 * Constants::PI / numDusts;
            Dust dust(collision.radius, collision.color);
            dust.setCenter(collision.point);
            const double dustVelocity = collision.velocity * 0.8;
            dust.setVelocity(Velocity(dustVelocity, angle));
            dusts.push_back(dust);
        }
    }
    for (Dust& dust: dusts) {
        dust.move(double(ticks) * timePerTick);
    }
    dusts.erase(
        std::remove_if(dusts.begin(), dusts.end(),
        [](const Dust& dust) {
            return !dust.isAlive();
        }),
        dusts.end()
    );
}
