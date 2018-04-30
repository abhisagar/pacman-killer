#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy
{
public:
    Enemy() {}
    Enemy (float x, float y, color_t color, GLfloat radi, float sped);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    float radius, speed, rotation;
    color_t clr;
private:
    VAO *object;
};

#endif // ENEMY_H
