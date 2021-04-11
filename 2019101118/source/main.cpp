#include "main.h"
#include "timer.h"
#include "ball.h"

using namespace std;

GLMatrices Matrices;
GLuint programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball1;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
glm::vec3 eye(0.0f, 0.0f, 5.0f);
glm::vec3 target;
glm::vec3 up(0.0f, 1.0f, 0.0f); 
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f);
glm::vec3 cameraRight(glm::normalize(glm::cross(up, cameraFront)));
glm::vec3 cameraUp(glm::cross(cameraFront, cameraRight)), axis;
bool camera_rotate = false;
int object_number;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw()
{
    // clear the color and depth in the frame buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);
    // glm::vec3 cameraFront = glm::normalize(eye - target);
    Matrices.view = glm::lookAt(eye, cameraFront+eye, up); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP; // MVP = Projection * View * Model

    // Scene render
    ball1.draw(VP);
}

void toggle_object_rotate() {
    ball1.rotate = !ball1.rotate;
}


void recompute_axis(glm::vec3 position) {
    cameraFront = glm::normalize(position - eye);
    cameraRight = glm::normalize(glm::cross(cameraFront, up));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}


void camera_tick() {
    if (!camera_rotate)
        return;
    glm::vec3 resultant = eye;
    glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f), axis);
    glm::mat4 trans = glm::translate(ball1.position);
    glm::mat4 trans_neg = glm::translate(-ball1.position);
    glm::vec4 result = trans * rot * trans_neg * glm::vec4(resultant, 1.0f);
    eye = glm::vec3(result);
    recompute_axis(ball1.position);
}

void call_always() {
    target = ball1.position;
    recompute_axis(target);
    axis = cameraUp;
}

void spin() {
    camera_rotate = !camera_rotate;
    if (camera_rotate == true) {
        call_always();
    }
}

void tick_input(GLFWwindow *window)
{
    const float cameraSpeed = 0.2f, ballspeed = 0.2f;
    glm::vec3 cameraFront = glm::normalize(target - eye);
    glm::vec3 cameraRight = glm::normalize(glm::cross(cameraFront, up));
    glm::vec3 cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
    int ball_left = glfwGetKey(window, GLFW_KEY_A);
    int ball_right = glfwGetKey(window, GLFW_KEY_D);
    int ball_up = glfwGetKey(window, GLFW_KEY_W);
    int ball_down = glfwGetKey(window, GLFW_KEY_S);
    int ball_zoom_in = glfwGetKey(window, GLFW_KEY_F);
    int ball_zoom_out = glfwGetKey(window, GLFW_KEY_G);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        eye += cameraSpeed * cameraUp;
        if (camera_rotate == true)
            call_always();
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        eye -= cameraSpeed * cameraUp;
        if (camera_rotate == true)
            call_always();
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        eye -= cameraRight * cameraSpeed;
        if (camera_rotate == true)
            call_always();
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        eye += cameraRight * cameraSpeed;
        if (camera_rotate == true)
            call_always();
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        eye -= cameraFront * cameraSpeed;
        if (camera_rotate == true)
            call_always();
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        eye += cameraFront * cameraSpeed;
        if (camera_rotate == true)
            call_always();
        
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        ball1.set_position(ball1.position.x-ballspeed, ball1.position.y, ball1.position.z);
        if(camera_rotate == true) {call_always();}
    } else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        ball1.set_position(ball1.position.x+ballspeed, ball1.position.y, ball1.position.z);
        if(camera_rotate == true) {call_always();}
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        ball1.set_position(ball1.position.x, ball1.position.y+ballspeed, ball1.position.z);
        if(camera_rotate == true) {call_always();}
    } else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        ball1.set_position(ball1.position.x, ball1.position.y-ballspeed, ball1.position.z);
        if(camera_rotate == true) {call_always();}
    } else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        ball1.set_position(ball1.position.x, ball1.position.y, ball1.position.z+ballspeed);
        if(camera_rotate == true) {call_always();}
    } else if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        ball1.set_position(ball1.position.x, ball1.position.y, ball1.position.z-ballspeed);
        if(camera_rotate == true) {call_always();}
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        eye = glm::vec3(ball1.position.x, ball1.position.y - 5.0f, ball1.position.z + 5.0f);
        recompute_axis(ball1.position);
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        eye = glm::vec3(ball1.position.x, ball1.position.y + 5.0f, ball1.position.z + 5.0f);
        recompute_axis(ball1.position);
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        eye = glm::vec3(ball1.position.x, ball1.position.y, ball1.position.z - 5.0f);
        recompute_axis(ball1.position);
    }
}

void tick_elements()
{
    ball1.tick();
    camera_rotation_angle += 1;
    camera_tick();
    // eye_position_x += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    ball1 = Ball(0, 0, 0, object_number);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("../source/shaders/shader.vert", "../source/shaders/shader.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");

    reshapeWindow(window, width, height);

    // Background color of the scene
    glClearColor(COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth(1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main(int argc, char **argv)
{
    srand(time(0));
    int width = 600;
    int height = 600;

    cout<< "1: Elongated square dipyramid\n2: Hexagonal dipiramid\n3: Undecagonal pyramid\nInput the object number: ";
    cin>>object_number;

    window = initGLFW(width, height);

    initGL(window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window))
    {
        // Process timers

        if (t60.processTick())
        {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_input(window);
            tick_elements();
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b)
{
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen()
{
    float top = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left = screen_center_x - 4 / screen_zoom;
    float right = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 500.0f);
}
