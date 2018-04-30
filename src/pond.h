#ifndef POND_H
#define POND_H
#include "main.h"

class Pond
{
public:
    Pond() {}
    Pond(float x, float y, float radi, color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    float rotation, angle, radius;
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // POND_H
