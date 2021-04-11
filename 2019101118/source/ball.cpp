#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y, float z, int number)
{
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->rotate = false;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    if (number == 1) {
        static const GLfloat vertex_buffer_data[] = {
            // elongated square dipyramid
            0.5f, 0.5f, 0.5f,
            -0.5f, 0.5f, 0.5f,
            -0.5f, -0.5f, 0.5f,
            0.5f, -0.5f, 0.5f,
            0.5f, 0.5f, -0.5f,
            -0.5f, 0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.0f, 1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
        };

        unsigned int indices[] {
            // elongated square dipyramid
            0, 1, 2,
            2, 3, 0,
            1, 5, 6,
            6, 2, 1,
            6, 5, 4,
            6, 7, 4,
            1, 0, 4,
            0, 1, 5,
            2, 6, 3,
            6, 7, 3,
            0, 3, 7,
            0, 4, 7,
            0, 8, 4,
            0, 8, 1,
            1, 5, 8,
            4, 5, 8,
            2, 3, 9,
            3, 7, 9,
            6, 7, 9,
            2, 6, 9,
        };

        static const GLfloat g_color_buffer_data[] = {
            // elongated square dipyramid
            0.583f, 0.771f, 0.014f,
            0.609f, 0.115f, 0.436f,
            0.327f, 0.483f, 0.844f,
            0.822f, 0.569f, 0.201f,
            0.982f, 0.099f, 0.879f,
            0.310f, 0.747f, 0.185f,
            0.302f, 0.455f, 0.848f,
            0.225f, 0.587f, 0.040f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f,
            // 0.320f, 0.383f, 0.371f,
            
        };
        int num_vertices = (sizeof(vertex_buffer_data)/sizeof(vertex_buffer_data[0]))/3;
        int num_indices = (sizeof(indices)/sizeof(indices[0]))/3;
        this->object = create3DObject(GL_TRIANGLES, num_vertices, num_indices, vertex_buffer_data, indices, g_color_buffer_data, GL_FILL);
    }
    else if(number == 2) {
        static const GLfloat vertex_buffer_data[] = {
            // hexagonal dipyramid
            cos(0*60.0f*M_PI/180.0f), 0, sin(0*60.0f*M_PI/180.0f),
            cos(1*60.0f*M_PI/180.0f), 0, sin(1*60.0f*M_PI/180.0f),
            cos(2*60.0f*M_PI/180.0f), 0, sin(2*60.0f*M_PI/180.0f),
            cos(3*60.0f*M_PI/180.0f), 0, sin(3*60.0f*M_PI/180.0f),
            cos(4*60.0f*M_PI/180.0f), 0, sin(4*60.0f*M_PI/180.0f),
            cos(5*60.0f*M_PI/180.0f), 0, sin(5*60.0f*M_PI/180.0f),
            0.0f, 1.0f, 0.0f,
            0.0f, -1.0f, 0.0f,
        };

        unsigned int indices[] {
            // hexagonal dipyramid
            0, 1, 6,
            1, 2, 6,
            2, 3, 6,
            3, 4, 6,
            4, 5, 6,
            5, 0, 6,
            0, 1, 7,
            1, 2, 7,
            2, 3, 7,
            3, 4, 7,
            4, 5, 7,
            5, 0, 7,
        };

        static const GLfloat g_color_buffer_data[] = {
            // hexagonal dipyramid
            0.597f, 0.770f, 0.761f,
            0.014f, 0.184f, 0.576f,
            0.771f, 0.328f, 0.970f,
            0.406f, 0.615f, 0.116f,
            0.971f, 0.572f, 0.833f,
            0.676f, 0.977f, 0.133f,
            0.140f, 0.616f, 0.489f,
            1.0f, 0.0f, 0.0f,
            // 0.997f, 0.513f, 0.064f,
        };
        int num_vertices = (sizeof(vertex_buffer_data)/sizeof(vertex_buffer_data[0]))/3;
        int num_indices = (sizeof(indices)/sizeof(indices[0]))/3;
        this->object = create3DObject(GL_TRIANGLES, num_vertices, num_indices, vertex_buffer_data, indices, g_color_buffer_data, GL_FILL);
    }
    else {
        static const GLfloat vertex_buffer_data[] = {
            // undecagonal pyramid
            cos(0*(360.0f/11)*M_PI/180.0f), 0, sin(0*(360.0f/11)*M_PI/180.0f),
            cos(1*(360.0f/11)*M_PI/180.0f), 0, sin(1*(360.0f/11)*M_PI/180.0f),
            cos(2*(360.0f/11)*M_PI/180.0f), 0, sin(2*(360.0f/11)*M_PI/180.0f),
            cos(3*(360.0f/11)*M_PI/180.0f), 0, sin(3*(360.0f/11)*M_PI/180.0f),
            cos(4*(360.0f/11)*M_PI/180.0f), 0, sin(4*(360.0f/11)*M_PI/180.0f),
            cos(5*(360.0f/11)*M_PI/180.0f), 0, sin(5*(360.0f/11)*M_PI/180.0f),
            cos(6*(360.0f/11)*M_PI/180.0f), 0, sin(6*(360.0f/11)*M_PI/180.0f),
            cos(7*(360.0f/11)*M_PI/180.0f), 0, sin(7*(360.0f/11)*M_PI/180.0f),
            cos(8*(360.0f/11)*M_PI/180.0f), 0, sin(8*(360.0f/11)*M_PI/180.0f),
            cos(9*(360.0f/11)*M_PI/180.0f), 0, sin(9*(360.0f/11)*M_PI/180.0f),
            cos(10*(360.0f/11)*M_PI/180.0f), 0, sin(10*(360.0f/11)*M_PI/180.0f),
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
        };

        unsigned int indices[] {
            // undecagonal pyramid
            0, 1, 11,
            1, 2, 11,
            2, 3, 11,
            3, 4, 11,
            4, 5, 11,
            5, 6, 11,
            6, 7, 11,
            7, 8, 11,
            8, 9, 11,
            9, 10, 11,
            10, 0, 11,
            0, 1, 12,
            1, 2, 12,
            2, 3, 12,
            3, 4, 12,
            4, 5, 12,
            5, 6, 12,
            6, 7, 12,
            7, 8, 12,
            8, 9, 12,
            9, 10, 12,
            10, 0, 12,
        };

        static const GLfloat g_color_buffer_data[] = {
            // undecagonal pyramid
            0.945f, 0.719f, 0.592f,
            0.543f, 0.021f, 0.978f,
            0.479f, 0.317f, 0.505f,
            0.667f, 0.620f, 0.077f,
            0.947f, 0.857f, 0.137f,
            0.055f, 0.953f, 0.042f,
            0.714f, 0.505f, 0.945f,
            0.783f, 0.290f, 0.734f,
            0.022f, 0.645f, 0.974f,
            0.053f, 0.959f, 0.120f,
            0.393f, 0.621f, 0.362f,
            0.673f, 0.211f, 0.457f,
            0.673f, 0.211f, 0.457f,

            // 0.302f, 0.455f, 0.848f,
            // 0.225f, 0.587f, 0.040f,
            // 0.517f, 0.713f, 0.338f,
            // 0.820f, 0.883f, 0.371f,
            // 0.982f, 0.099f, 0.879f
        };
        int num_vertices = (sizeof(vertex_buffer_data)/sizeof(vertex_buffer_data[0]))/3;
        int num_indices = (sizeof(indices)/sizeof(indices[0]))/3;
        this->object = create3DObject(GL_TRIANGLES, num_vertices, num_indices, vertex_buffer_data, indices, g_color_buffer_data, GL_FILL);
    }
}

void Ball::draw(glm::mat4 VP)
{
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate(this->position); // glTranslatef
    glm::mat4 rotate = glm::rotate((float)(this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y, float z)
{
    this->position = glm::vec3(x, y, z);
}

void Ball::tick()
{
    if (this->rotate == true)
        this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}
