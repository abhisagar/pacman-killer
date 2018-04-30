#include "main.h"

#ifndef TRAMPOLINE_H
#define TRAMPOLINE_H


class Trampoline
{
public:
    Trampoline(){}
    Trampoline(float x, float y, float width, float length, float radi, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    float rotation, angle, radius;
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // TRAMPOLINE_H
