#ifndef MAGNET_H
#define MAGNET_H
#include "main.h"

class Magnet
{
public:
    Magnet() {}
    Magnet (float x, float y,float width,float radi, color_t col);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    float rotation, radius;
    void set_position(float x, float y);
private:
    VAO *object;
};

#endif // MAGNET_H
