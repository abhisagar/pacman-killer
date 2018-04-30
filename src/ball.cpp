#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, color_t color, GLfloat radi) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speedy = 0.1;
    flag=0;
    start = y;
    acc = 0.005;
    radius = radi;
    speedwater = 0.005;
    speed_x = 0.0;

    GLfloat g_vertex_buffer_data[100000], n = 0.0f, o = 0.0f, m=radi;

    angle = 1.0;
    j=0;
    for (i=0;i<360;i++) {
        g_vertex_buffer_data[j] = 0.0f;g_vertex_buffer_data[j+1] = 0.0f;g_vertex_buffer_data[j+2] = 0.0f;
        j+=3;
        g_vertex_buffer_data[j] = m; g_vertex_buffer_data[j+1] = n; g_vertex_buffer_data[j+2] = o;
        j+=3;
        float val = PI/180;
        m = radi*cos(angle*val);
        n = radi*sin(angle*val);
        g_vertex_buffer_data[j] = m; g_vertex_buffer_data[j+1] = n; g_vertex_buffer_data[j+2] = o;
        angle += 1;
        j+=3;
    }

    this->object = create3DObject(GL_TRIANGLES, 360*3, g_vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick() {

    this->position.x += speed_x;
//    printf("%f\n", speed_x);

    if (this->position.y > start || flag == 1) {
        this->position.y += speedy;
//        if (this->position.y >start)
            speedy -= acc;
        if (this->position.y <= start){
            if (this->position.y < start)
                this->position.y = start;
            flag=0;
        }
    }

//    if (this->position.y<=-1.0 && this->position.y>=-1.8 &&
//            this->position.x < -2.2 && this->position.x > -3.8) {
//        float segment = 0.64 - (-1.08-this->position.y)*(-1.08-this->position.y);
//        if (this->position.x < (-3.0 - segment))
//            this->position.x = (-3.0 - segment);
//        if (this->position.x > (-3.0 + segment))
//            this->position.x = (-3.0 + segment);
//        this->position.y -= speedwater;
//        flag=0;
//    }

    if (this->position.x <-2.2 && this->position.x >-3.8) {
        float segment = (0.8 - (-3.0 - this->position.x)*(-3.0- this->position.x));
        if (this->position.y < 1.1)
            this->position.y -= speedwater;
        if (this->position.y < (-1.0 - segment)) {
            this->position.y = (-1.0 - segment);
            if (this->position.x >-3.0)
                this->position.x -= speedwater;
            if (this->position.x < -3.0)
                this->position.x += speedwater;
        }
    }

    if (this->position.y == start)
        speed_x = 0.0;

    if (this->position.x >-2.2 || this->position.x <-3.8)
        if (this->position.y < start)
            this->position.y = start;
}


//bounding_box_t Ball::bounding_box() {
//    float x = this->position.x, y = this->position.y;
//    bounding_box_t bbox = { x, y, 0.4, 0.4 };
//    return bbox;
//}
