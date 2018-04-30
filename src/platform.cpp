#include "main.h"
#include "platform.h"

Platform::Platform(float length, float width, float centerx, float centery, color_t color) {
    this->rotation=0;
    this->position = glm::vec3(centerx, centery, 0);
    this->lwc = glm::vec4(length, width, centerx, centery);

    static const GLfloat g_vertex_buffer_data[] = {

        -(length/2), +(width/2), 0,
        -(length/2), -(width/2), 0,
        +(length/2), +(width/2), 0,

        +(length/2), +(width/2), 0,
        -(length/2), -(width/2), 0,
        +(length/2), -(width/2), 0

    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, g_vertex_buffer_data, color, GL_FILL);
}

void Platform::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
