#include "plankenemy.h"
#include "main.h"

Plankenemy::Plankenemy(float x, float y, color_t color, GLfloat radi, float sped, float rot)
{
    this->position = glm::vec3(x, y, 0);
    radius = radi;
    speed = sped;
    plankrot = rot;
    this->rotation = rot;
    clr = color;

    GLfloat g_vertex_buffer_data[100000], n = 0.0f, o = 0.0f, m=radi;

    float angle = 1.0;
    int j=0;
    for (int i=0;i<360;i++) {
        g_vertex_buffer_data[j] = 0.0f;g_vertex_buffer_data[j+1] = 0.0f;g_vertex_buffer_data[j+2] = 0.0f;
        j+=3;
        g_vertex_buffer_data[j] = m; g_vertex_buffer_data[j+1] = n; g_vertex_buffer_data[j+2] = o;
        j+=3;
        float val = M_PI/180;
        m = radi*cos(angle*val);
        n = radi*sin(angle*val);
        g_vertex_buffer_data[j] = m; g_vertex_buffer_data[j+1] = n; g_vertex_buffer_data[j+2] = o;
        angle += 1;
        j+=3;
    }

    this->object = create3DObject(GL_TRIANGLES, 360*3, g_vertex_buffer_data, color, GL_FILL);

    GLfloat g_vertex_buffer_data1[10000] = {

        radius,radius,0,
        radius + 0.08,radius,0,
        radius,-radius, 0,

        radius, -radius, 0,
        radius+0.08, radius,0,
        radius+0.08, -radius,0,
    };

    this->object1 = create3DObject(GL_TRIANGLES, 6, g_vertex_buffer_data1, color, GL_FILL);

}

void Plankenemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
}

void Plankenemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Plankenemy::tick() {
    this->position.x += speed;
}
