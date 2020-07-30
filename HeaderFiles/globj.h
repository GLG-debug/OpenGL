#pragma once
#ifndef _GLobj_
#define _GLobj_

struct GLobj
{
    Vertex pos;
    Vertex dir; // Вектор направления движка
    Vertex look; // Углы поворота взгляда
    float da; // Величина изменения поворота
    float ds; // Величина изменения движения

    // Конструктор
    GLobj(float _ds = 0.8, float _da = 0.5)
    {
        init(_ds, _da); pos.set(0, 0, 0);
        dir.set(0, 0, 0); look.set(0, 0, 0);
    }
    // Инициализация
    void init(float _ds = 1, float _da = 0.5)
        { da = _da; ds = _ds; }
    // Позиционирование камеры
    void position(float x = 0, float y = 0, float z = 0)
        { pos.set(-x, -y, -z); }
    // Установка направления движения камеры
    void direction(float x = 0, float y = 0, float z = 0)
        { dir.set(x, y, z); }
    // Установка направления взгляда камеры
    void looking(float x = 0, float y = 0, float z = 0)
        { look.set(x, y, z); }
    // Движение камеры вперёд / назад
    void movefb(float steps = 1)
        { pos.move(ds * steps, dir.x, dir.y); }
    // Движение камеры влево / вправо боком
    void movelr(float steps = 1)
        { pos.move(ds * steps, 0, dir.y - 90); }
    // Движение камеры вверх / вниз
    void moveud(float steps = 1)
        { pos.move(ds * steps, dir.x + 90, dir.y); }
    // Изменение направления движения влево / вправо
    void dirlr(float steps = 1) { dir.y += steps * da; }
    // Изменение направления движения влево / вправо
    void dirud(float steps = 1) { dir.x += steps * da; }
    // Изменение направления движения влево / вправо
    void looklr(float steps = 1) { look.y += steps * da; }
    // Изменение направления движения влево / вправо
    void lookud(float steps = 1) { look.x += steps * da; }
};


#endif
