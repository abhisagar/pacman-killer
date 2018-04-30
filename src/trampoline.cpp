#include "trampoline.h"
#include "main.h"
#include "ball.h"

Trampoline::Trampoline(float x, float y, float width, float length, float radi, color_t color) {

    this->rotation = 0;
    this->position = glm::vec3(x, y, 0);
    radius = radi;

    GLfloat g_vertex_buffer_data[100100] = {

        // 1st ractangle
        x,y,0,
        x+width,y,0,
        x,y-length,0,

        x,y-length,0,
        x+width,y-length,0,
        x+width,y,0,

        // 2nd ractangle
        x+width+(2*radi),y,0,
        x+(2*width)+(2*radi),y,0,
        x+width+(2*radi),y-length,0,

        x+width+(2*radi),y-length,0,
        x+(2*width)+(2*radi),y-length,0,
        x+(2*width)+(2*radi),y,0
    };

    float n = y, o = 0.0f, m=x+width;

    angle = 180.0;
    int j=36;
    for (int i=36;i<216;i++) {
        g_vertex_buffer_data[j] = x+width+radi;
        g_vertex_buffer_data[j+1] = y;
        g_vertex_buffer_data[j+2] = o;
        j+=3;
        g_vertex_buffer_data[j] = m;
        g_vertex_buffer_data[j+1] = n;
        g_vertex_buffer_data[j+2] = o;
        j+=3;
        float val = PI/180;
        m = (x+width+radi) + radi*cos(angle*val);
        n = y + radi*sin(angle*val);
        g_vertex_buffer_data[j] = m;
        g_vertex_buffer_data[j+1] = n;
        g_vertex_buffer_data[j+2] = o;
        angle += 1;
        j+=3;
    }

    this->object = create3DObject(GL_TRIANGLES,12 + 180*3, g_vertex_buffer_data, color, GL_FILL);

}

void Trampoline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Trampoline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
