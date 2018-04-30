#include "ball.h"
#include "pond.h"
#include "main.h"

Pond::Pond(float x, float y,float radi, color_t color) {

    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
    radius = radi;

    GLfloat g_vertex_buffer_data[100010];
    float n = 0.0, o = 0.0f, m=radius;

    angle = 180.0;
    int j=0;
    for (int i=0;i<180;i++) {
        g_vertex_buffer_data[j] = 0.0;
        g_vertex_buffer_data[j+1] = 0.0;
        g_vertex_buffer_data[j+2] = 0.0;
        j+=3;
        g_vertex_buffer_data[j] = m;
        g_vertex_buffer_data[j+1] = n;
        g_vertex_buffer_data[j+2] = o;
        j+=3;
        float val = PI/180;
        m = (radius)*cos(angle*val);
        n = (radius)*sin(angle*val);
        g_vertex_buffer_data[j] = m;
        g_vertex_buffer_data[j+1] = n;
        g_vertex_buffer_data[j+2] = o;
        angle += 1;
        j+=3;
    }

    this->object = create3DObject(GL_TRIANGLES,180*3, g_vertex_buffer_data, color, GL_FILL);

}

void Pond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Pond::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

