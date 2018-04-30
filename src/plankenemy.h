#include "main.h"

#ifndef PLANKENEMY_H
#define PLANKENEMY_H


class Plankenemy
{
public:
    Plankenemy() {}
    Plankenemy (float x, float y, color_t color, GLfloat radi, float sped, float rot);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius, speed, rotation, plankrot;
    color_t clr;
private:
    VAO *object;
    VAO *object1;
};

#endif // PLANKENEMY_H
