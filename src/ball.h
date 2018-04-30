#include "main.h"

#ifndef BALL_H
#define BALL_H
#define PI 3.14159265

class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color, GLfloat radi);
    glm::vec3 position;
    float rotation, radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
    int flag, j, i;
    double speedy, speedwater,speed_x;
    double start;
    double acc;
    float angle;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
