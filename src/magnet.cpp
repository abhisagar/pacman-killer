#include "magnet.h"
#include "main.h"

Magnet::Magnet(float x, float y, float width, float radi, color_t color) {

    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    radius = radi;
    float length = 2*radi;
//    here length = two times radius;

    GLfloat g_vertex_buffer_data[100010] = {

        // first triangle
        0.0, 0.0, 0.0,
        0.0, -length,0.0,
        -width,0.0,0.0,

        // 2nd triangle
        -width,0.0,0.0,
        -width,-length,0.0,
        0.0,-length,0.0,

    };

    float m = -width, n = 0.0, o=0.0, angle=90;
    int j=18;
    for (int i=0;i<182;i++) {
        g_vertex_buffer_data[j] = -width;
        g_vertex_buffer_data[j+1] = -radi;
        g_vertex_buffer_data[j+2] = o;
        j+=3;
        g_vertex_buffer_data[j] = m;
        g_vertex_buffer_data[j+1] = n;
        g_vertex_buffer_data[j+2] = o;
        j+=3;
        float val = M_PI/180;
        m = -width + radi*cos(angle*val);
        n =  - radi + radi*sin(angle*val);
        g_vertex_buffer_data[j] = m;
        g_vertex_buffer_data[j+1] = n;
        g_vertex_buffer_data[j+2] = o;
        angle += 1;
        j+=3;
    }

    this->object = create3DObject(GL_TRIANGLES,182*3+6, g_vertex_buffer_data, color, GL_FILL);

}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

