#include "porcupine.h"
#include "main.h"

// 4 equilateral triangles will be built here
Porcupine::Porcupine(float x, float y, float side, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.01;
    flag=0;
    if (this->position.x < -3.8)
        flag=4;
    if (this->position.x >= 3.6)
        flag=7;
    sd = side;

    float height = sqrt(3)*(0.5)*side;

    GLfloat g_vertex_buffer_data[100010] = {

        0.0,0.0,0.0,
        side/2,height,0.0,
        side,0,0,

        side,0,0,
        (1.5)*side,height,0,
        2*side,0,0,

    };

    this->object = create3DObject(GL_TRIANGLES,12, g_vertex_buffer_data, color, GL_FILL);
}

void Porcupine::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Porcupine::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Porcupine::tick() {

    if (this->position.x >= -4.2 && this->position.x < -4.0)
        flag=5;
    if (this->position.x <= -5.8 && this->position.x > -6.0)
        flag=4;

    if (this->position.x <= 3.6 && this->position.x > 3.4)
        flag=7;

    if (this->position.x >= 5.8 && this->position.x < 6.0)
        flag=8;

    if (this->position.x >= 2.8 && this->position.x <3.0)
        flag=1;
    if (this->position.x <= -1.8 && this->position.x > -2.0)
        flag=0;
    if (flag == 1 || flag == 5 || flag == 8)
        this->position.x -= speed;
    else if (flag == 0 || flag == 4 || flag == 7)
        this->position.x += speed;
}
