#ifndef PORCUPINE_H
#define PORCUPINE_H
#include "main.h"


class Porcupine
{
public:
    Porcupine() {}
    Porcupine(float x, float y, float side, color_t color);
    glm::vec3 position;
    float rotation, radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed, sd;
    int flag;
private:
    VAO *object;
};

#endif // PORCUPINE_H
