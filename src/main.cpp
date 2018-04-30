#include "main.h"
#include "timer.h"
#include "ball.h"
#include "platform.h"
#include "enemy.h"
#include "trampoline.h"
#include "plankenemy.h"
#include "pond.h"
#include "magnet.h"
#include "porcupine.h"
#include <bits/stdc++.h>

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;
Platform pl1, pl2;
Enemy array[2500];
Trampoline tramp;
Plankenemy pearr[2500];
Pond pnd;
Magnet mgt1, mgt2;
Porcupine porcu1, porcu2, porcu3, porcu4;

int cnt = 0, cnt2 = 0, siz=0, level=1, score = 0, auto_pan = 0, pause_flag = 0;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
//    ball1.draw(VP);

    pl1.draw(VP);
    pl2.draw(VP);
    pnd.draw(VP);
    tramp.draw(VP);
    if (cnt>600 && level!=1) {
        mgt1.position.x = ball1.position.x - 3.0;
        mgt2.position.x = ball1.position.x - 3.0;
        mgt1.draw(VP);
        mgt2.draw(VP);
    }
    porcu1.draw(VP);
    porcu2.draw(VP);
    porcu3.draw(VP);
    porcu4.draw(VP);
    ball1.draw(VP);
    for (int i=0;i<300;i++)
        array[i].draw(VP);
    for (int i=0;i<150;i++)
        pearr[i].draw(VP);

//    pe1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_A);
    int right = glfwGetKey(window, GLFW_KEY_D);
    int up = glfwGetKey(window, GLFW_KEY_SPACE);
    int temp1 = glfwGetKey(window, GLFW_KEY_P);
    int pause = glfwGetKey(window, GLFW_KEY_U);

    if (temp1)
        auto_pan = (auto_pan + 1)%2;

    if (pause)
        pause_flag = (pause_flag + 1)%2;


    if (left) {
        ball1.speed_x = 0.0;
        // Do something
        if (ball1.position.x < -2.2 && ball1.position.x > -3.6 &&
                ball1.position.y <= -1.0)
            ball1.set_position(ball1.position.x-0.02, ball1.position.y);
        else
            ball1.set_position(ball1.position.x - 0.1, ball1.position.y);
    }

    else if(right) {
        ball1.speed_x = 0.0;
        if (ball1.position.x < -2.2 && ball1.position.x > -3.6 &&
                ball1.position.y <= -1.0)
            ball1.set_position(ball1.position.x+0.02, ball1.position.y);
        else
            ball1.set_position(ball1.position.x + 0.1, ball1.position.y);
    }

    else if (up) {
        if (ball1.position.x < -2.2 && ball1.position.x > -3.6 &&
                ball1.position.y <= -1.0){
            ball1.speedy = 0.05;
            ball1.flag = 1;
        }
        else if (ball1.flag == 0){
            ball1.flag = 1;
            ball1.speedy = 0.15;
        }
    }
}

bool detect_collision_enemy(Enemy a);
bool detect_collision_tramp();
bool detect_collision_plankenemy(Plankenemy a);

void tick_elements() {

    char title[100010];
    cnt++;
    cnt = cnt%1000;
    cnt2++;
    if ((cnt2>2000 && level < 3) || (cnt2 > 3000 && level == 3)){
        sprintf(title, "Gameover");
        glfwSetWindowTitle(window, title);

        for (int i=0;i<1000000000;i++);

        quit(window);
    }

     if (level == 3 && score >= 120) {
         sprintf(title, "You Won");
         glfwSetWindowTitle(window, title);

         for (int i=0;i<1000000000;i++);

         quit(window);
     }

    int yo, total=2000;
    if (level == 1)
        yo = 35;
    if (level == 2)
        yo = 70;
    if (level == 3) {
        yo = 120;
        total = 3000;
    }

    if (auto_pan)
        sprintf(title, "Level: %d; Score : %d; Get %d score for level up; You have %d seconds; AUTO PANNING IS ON", level, score, yo, (total-cnt2)/100);
    else
        sprintf(title, "Level : %d; Score: %d; Get %d score for level up; You have %d seconds; AUTO PANNING IS OFF", level, score, yo, (total-cnt2)/100);


    if (score >= yo) {

        porcu1.position.x = -1.76;
        porcu2.position.x = -0.0;
        porcu3.position.x = -6.0;
        porcu4.position.x = 3.7;
        cnt=0;
        cnt2=0;
        score=0;
        level++;
        ball1.position.x = -2.0;
        ball1.position.y = -1.0;
        ball1.speed_x = 0.0;
        ball1.speedy = 0.0;

        sprintf(title, "Level Change");
        glfwSetWindowTitle(window, title);

        for (int i=0;i<1000000000;i++);

    }

    glfwSetWindowTitle(window, title);


    ball1.tick();

    for (int i=0;i<300;i++) {
        if (detect_collision_enemy(array[i]) && ball1.speedy<0) {

            if (array[i].clr.r == COLOR_GREEN.r && array[i].clr.g == COLOR_GREEN.g && array[i].clr.b == COLOR_GREEN.b)
                score += 2;
            if (array[i].clr.r == COLOR_BLUE.r && array[i].clr.g == COLOR_BLUE.g && array[i].clr.b == COLOR_BLUE.b)
                score += 3;
            if (array[i].clr.r == COLOR_BROWN.r && array[i].clr.g == COLOR_BROWN.g && array[i].clr.b == COLOR_BROWN.b)
                score += 4;
            if (array[i].clr.r == COLOR_SKYBLUE.r && array[i].clr.g == COLOR_SKYBLUE.g && array[i].clr.b == COLOR_SKYBLUE.b)
                score += 5;
            if (array[i].clr.r == COLOR_YELLOW.r && array[i].clr.g == COLOR_YELLOW.g && array[i].clr.b == COLOR_YELLOW.b)
                score += 6;

            float xc = -500;
            float yc = ((float(rand())/float(RAND_MAX))*(3.2)+0.5);
            float radi = ((float(rand())/float(RAND_MAX))*(0.2)) + 0.1;
            float speed = ((float(rand())/float(RAND_MAX))*(0.04)) + 0.01;
            int temp     = rand()%5+1;
            color_t col;
            if (temp == 1)
                col = COLOR_GREEN;
            else if (temp == 2)
                col = COLOR_BLUE;
            else if (temp == 3)
                col = COLOR_BROWN;
            else if (temp == 4)
                col = COLOR_SKYBLUE;
            else
                col = COLOR_YELLOW;
            array[i] = Enemy(xc, yc, col, radi, speed);
            ball1.speedy = 0.15;
        }
    }

    for (int i=0;i<150;i++) {
        if (detect_collision_plankenemy(pearr[i]) && ball1.speedy < 0) {


            if (pearr[i].clr.r == COLOR_GREEN.r && pearr[i].clr.g == COLOR_GREEN.g && pearr[i].clr.b == COLOR_GREEN.b)
                score += 2;
            if (pearr[i].clr.r == COLOR_BLUE.r && pearr[i].clr.g == COLOR_BLUE.g && pearr[i].clr.b == COLOR_BLUE.b)
                score += 3;
            if (pearr[i].clr.r == COLOR_BROWN.r && pearr[i].clr.g == COLOR_BROWN.g && pearr[i].clr.b == COLOR_BROWN.b)
                score += 4;
            if (pearr[i].clr.r == COLOR_SKYBLUE.r && pearr[i].clr.g == COLOR_SKYBLUE.g && pearr[i].clr.b == COLOR_SKYBLUE.b)
                score += 5;
            if (pearr[i].clr.r == COLOR_YELLOW.r && pearr[i].clr.g == COLOR_YELLOW.g && pearr[i].clr.b == COLOR_YELLOW.b)
                score += 6;


            float val       = PI/180;
            float sx        = ball1.speed_x;
            float sy        = ball1.speedy;
            float an        = pearr[i].rotation;
            float compn     = sx*cos(val*an) + sy*sin(val*an);
            compn           = -compn;
            float compi     = -sy*cos(val*an) + sx*sin(val*an);
            ball1.speed_x   = compn*cos(val*an) + compi*sin(val*an);
            ball1.speedy    = compn*sin(val*an) - compi*cos(val*an);


            float xc = -500;
            float yc = ((float(rand())/float(RAND_MAX))*(3.2)+0.5);
            float radi = ((float(rand())/float(RAND_MAX))*(0.2)) + 0.1;
            float speed = ((float(rand())/float(RAND_MAX))*(0.04)) + 0.01;
            float rot   = ((float(rand())/float(RAND_MAX))*(90)) + 45;
            int temp     = rand()%5+1;
            color_t col;
            if (temp == 1)
                col = COLOR_GREEN;
            else if (temp == 2)
                col = COLOR_BLUE;
            else if (temp == 3)
                col = COLOR_BROWN;
            else if (temp == 4)
                col = COLOR_SKYBLUE;
            else
                col = COLOR_YELLOW;
            pearr[i] = Plankenemy(xc, yc, col, radi, speed, rot);
        }
    }

//    for (int i=0;i<10;i++) {
//        if (array[i].position.x > 10) {
//            array[i].position.x = -10;
//        }
//    }

//    for (int i=0;i<5;i++) {
//        if (pearr[i].position.x > 10) {
//            pearr[i].position.x = -10;
//        }
//    }

    for (int i=0;i<300;i++)
        array[i].tick();

    if (detect_collision_tramp()) {
        ball1.speedy = 0.2;
    }

//    pe1.tick();

    for (int i=0;i<150;i++)
        pearr[i].tick();

    if (cnt>600 && level!=1/* && ball1.position.y < mgt1.position.y
            && ball1.position.y > (mgt1.position.y - 2*mgt1.radius)*/) {
        ball1.speed_x -= 0.003 ;
    }
    porcu1.tick();
    porcu2.tick();
    porcu3.tick();
    porcu4.tick();

    // collision with porcupines
    if ((ball1.position.y == -1) && (ball1.position.x > porcu1.position.x) &&
            (ball1.position.x < porcu1.position.x + 2*porcu1.sd)) {
        score -= 1;
        porcu1.position.x = 3000.0;
    }

    if ((ball1.position.y == -1) && (ball1.position.x > porcu2.position.x) &&
            (ball1.position.x < porcu2.position.x + 2*porcu2.sd)) {
        score -= 1;
        porcu2.position.x = 3000.0;
    }

    if ((ball1.position.y == -1) && (ball1.position.x > porcu3.position.x) &&
            (ball1.position.x < porcu3.position.x + 2*porcu3.sd)) {
        score -= 1;
        porcu3.position.x = 3000.0;
    }

    if ((ball1.position.y == -1) && (ball1.position.x > porcu4.position.x) &&
            (ball1.position.x < porcu4.position.x + 2*porcu4.sd)) {
        score -= 1;
        porcu4.position.x = 3000.0;
    }

    // to show score
    int temp = score;
    char s[101];
//    char *s = (char*)malloc(sizeof(char)*1010);
    sprintf(s, "%d", temp);


//    if (ball1.position.x < -3.8){
//        screen_center_x = -1.0;
//        reset_screen();
//    }
//    else if(ball1.position.x > 3.8){
//        screen_center_x = 1.0;
//        reset_screen();
//    }
//    else{
//        screen_center_x = 0.0;
//        reset_screen();
//    }

    if (auto_pan) {
        screen_center_x = ball1.position.x;
        reset_screen();
    }

//    if (ball1.position.x > 4.8)
//        ball1.position.x = 4.8;
//    if (ball1.position.x < -4.8)
//        ball1.position.x = -4.8;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    pl1     = Platform(1000.0, 2.0, 0.0, -2.2, COLOR_GREEN);
    pl2     = Platform(1000.0, 8.0, 0.0, -3.0, COLOR_BROWN);
    tramp   = Trampoline(1.0, -0.3, 0.1, 0.6, 0.5, COLOR_RED);
    pnd     = Pond (-3,-1.2, 0.8,COLOR_SKYBLUE);
    mgt1    = Magnet(-3, 4, 0.5, 0.5, COLOR_RED);
    mgt2    = Magnet(-3, 3.9, 0.5, 0.4, COLOR_BACKGROUND);
    porcu1  = Porcupine(-1.76,-1.2,0.1,COLOR_GREY);
    porcu2  = Porcupine(0.0,-1.2,0.2,COLOR_GREY);
    porcu3  = Porcupine(-6.0,-1.2,0.2, COLOR_GREY);
    porcu4  = Porcupine(3.7,-1.2,0.1,COLOR_GREY);

//    pe1     = Plankenemy(0.0,0.0,COLOR_GREEN,0.2,0.01,60);

    ball1        = Ball(-2, -1, COLOR_RED, 0.2f);
    ball1.speedy = 0.2;

    for (int i = 0; i< 300; i++) {

        float xc    = ((float(rand())/float(RAND_MAX))*(500))-500.0;
        float yc    = ((float(rand())/float(RAND_MAX))*(4));
        float radi  = ((float(rand())/float(RAND_MAX))*(0.3)) + 0.1;
        float speed = ((float(rand())/float(RAND_MAX))*(0.04)) + 0.01;
        int temp     = rand()%5+1;
        color_t col;
        if (temp == 1)
            col = COLOR_GREEN;
        else if (temp == 2)
            col = COLOR_BLUE;
        else if (temp == 3)
            col = COLOR_BROWN;
        else if (temp == 4)
            col = COLOR_SKYBLUE;
        else
            col = COLOR_YELLOW;
        array[i] = Enemy(xc, yc, col, radi, speed);
    }

    for (int i=0;i<150;i++) {
        float xc    = ((float(rand())/float(RAND_MAX))*(500))-500.0;
        float yc    = ((float(rand())/float(RAND_MAX))*(4));
        float radi  = ((float(rand())/float(RAND_MAX))*(0.3)) + 0.1;
        float speed = ((float(rand())/float(RAND_MAX))*(0.04)) + 0.01;
        float rot   = ((float(rand())/float(RAND_MAX))*(90)) + 45;

        int temp     = rand()%5+1;
        color_t col;
        if (temp == 1)
            col = COLOR_GREEN;
        else if (temp == 2)
            col = COLOR_BLUE;
        else if (temp == 3)
            col = COLOR_BROWN;
        else if (temp == 4)
            col = COLOR_SKYBLUE;
        else
            col = COLOR_YELLOW;

        pearr[i] = Plankenemy(xc, yc, col, radi, speed, rot);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 800;
    int height = 1000;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {


        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_input(window);
            if (pause_flag)
                continue;

            tick_elements();

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision_enemy(Enemy a) {
    return sqrt((ball1.position.x - a.position.x)*(ball1.position.x - a.position.x) + (ball1.position.y - a.position.y)*((ball1.position.y - a.position.y))) <= (ball1.radius + a.radius);
}

bool detect_collision_tramp() {
    return (ball1.position.y<=-0.35 && ball1.speedy<0 && ball1.position.x>1.9 && ball1.position.x<3.2);
}

bool detect_collision_plankenemy(Plankenemy a) {
    return ((ball1.position.x - a.position.x)*(ball1.position.x - a.position.x) + (ball1.position.y - a.position.y)*((ball1.position.y - a.position.y))) <= (ball1.radius + a.radius);
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
