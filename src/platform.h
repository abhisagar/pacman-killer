#ifndef PLATFORM_H
#define PLATFORM_H


class Platform
{
public:
    Platform() {}
    Platform(float length, float width, float centerx, float centery, color_t color);
    glm::vec4 lwc;
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
private:
    VAO *object;
};

#endif // PLATFORM_H
