
#include "Cube.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


float vertices[] = {
    // positions
    // front
    -0.01, 0.01, 0.01,   0.01, 0.01, 0.01,   0.01,-0.01, 0.01,  -0.01,-0.01, 0.01,

    // back
     0.01, 0.01,-0.01,  -0.01, 0.01,-0.01,  -0.01,-0.01,-0.01,   0.01,-0.01,-0.01,

    // top
    -0.01, 0.01,-0.01,   0.01, 0.01,-0.01,   0.01, 0.01, 0.01,  -0.01, 0.01, 0.01,

    // bottom
    -0.01,-0.01, 0.01,   0.01,-0.01, 0.01,   0.01,-0.01,-0.01,  -0.01,-0.01,-0.01,

    // right
     0.01, 0.01, 0.01,   0.01, 0.01,-0.01,   0.01,-0.01,-0.01,   0.01,-0.01, 0.01,

    // left
    -0.01, 0.01,-0.01, -0.01, 0.01, 0.01,  -0.01,-0.01, 0.01,  -0.01,-0.01,-0.01,
    };

GLubyte indices[] = {
	    //front
	    0,1,2, 2,3,0,
	    //back
	    4,5,6, 6,7,4,
	    // top
	    8,9,10, 10,11,8,
	    // bottom
	    12,13,14,  14,15,12,
	    //right
	    16,17,18,  18,19,16,
	    //left
	    20,21,22,  22,23,20,
    };

Cube::Cube() {

}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}
glm::vec2 translations[100];

void Cube::getattib(GLint id)
{
    // TODO Auto-generated constructor stub
    posLoc = glGetAttribLocation(id, "a_Position");
    colorLoc = glGetUniformLocation(id, "a_Color");
    offsetloc = glGetAttribLocation(id, "aOffset");
    flag = glGetUniformLocation(id, "flag");


    int index = 0;
    float offset = 0.1f;
    if(!(index >= 100)){
    for (int y = -10; y < 10; y += 2.0)
    {
        for (int x = -10; x < 10; x += 2.0)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            translations[index++] = translation;
            printf("%f ,  %f\n", translation.x, translation.y);
        }
    }
    }
}

void Cube::drawCubeVBO(int flag_draw, glm::vec4 color)
{
    unsigned int instanceVBO;
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    glEnableVertexAttribArray(offsetloc);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(offsetloc, 1);

    glUniform4f(colorLoc, color.x, color.y, color.z, color.w);

    glBindVertexArray(quadVAO);

    if(flag_draw == 1){
        glUniform1i(flag, 1);
        glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices, 100);
    }
    else
    {
        glUniform1i(flag, 0);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, indices);
    }
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
}
