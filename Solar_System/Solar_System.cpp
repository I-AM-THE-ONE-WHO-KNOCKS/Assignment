#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Shader.h"
#include <stdio.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <Cube.h>

Shader* shader;
GLint programID = -1;
Cube* mCube;


GLint positionLocation;
GLint colorLocation;
GLint modelMatrixLocation;
GLint projectionMatrixLocation;
GLint viewMatrixLocation;

float zPos = 0.0;

int width = 0;
int height = 0;


void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    shader = new Shader();
    programID = shader->init("shader_solar.vert",
                             "shader_solar.frag");
    printf("program id = %d", programID);

    //load the program object to the GPU
    glUseProgram(programID);


    modelMatrixLocation =
            glGetUniformLocation(programID, "u_ModelMatrix");

    projectionMatrixLocation =
            glGetUniformLocation(programID, "u_ProjectionMatrix");

    viewMatrixLocation =
            glGetUniformLocation(programID, "u_ViewMatrix");

    glm::mat4 projMatrix = glm::mat4(1.0);
    projMatrix = glm::perspective(90.0, 1.0, 0.1, 100.0);

    glUniformMatrix4fv(projectionMatrixLocation,
                       1,
                       false,
                       &projMatrix[0][0]);


    mCube = new Cube();
    mCube->getattib(programID);
}

float angle = 0.0;
static glm::vec4 color_inc =  glm::vec4(0.0, 0.0, 0.0, 0.0);

void drawScene() {
    glm::vec4 color;
    angle += 1.0;
    if( angle >= 360.0) angle = 0.0;

    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0, 0.0, 1.0),  //pos
                                       glm::vec3(0.0, 0.0, 0.0),  //looking at
                                       glm::vec3(0.0, 1.0, 0.0)); //up vector
    viewMatrix = glm::mat4(1.0);
    glUniformMatrix4fv(viewMatrixLocation, 1, false, &viewMatrix[0][0]);


    glm::mat4 modelMatrix = glm::mat4(1.0);
            modelMatrix = glm::translate(glm::vec3(0, 0.0, -1.0));
            modelMatrix = glm::rotate(modelMatrix, glm::radians(angle),
                                      glm::vec3(0.0, 0.0, 1.0));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));

    glUniformMatrix4fv(modelMatrixLocation,
                       1,
                       false,
                       &modelMatrix[0][0]);


    color = glm::vec4(1.0, 1.0, 1.0, 1.0)+ color_inc;
    //draw instanced cube stars
    mCube->drawCubeVBO(1, color);


    modelMatrix = glm::mat4(1.0);

    modelMatrix =
            glm::translate(glm::vec3(0, 0.0, -1.0));
    modelMatrix = glm::rotate(modelMatrix, glm::radians(angle),
                              glm::vec3(0.0, 1.0, 0.0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(20.0, 20.0, 20.0));

    glUniformMatrix4fv(modelMatrixLocation,
                       1,
                       false,
                       &modelMatrix[0][0]);

    //draw the sun
    color = glm::vec4(1.0, 1.0, 0.0, 1.0)+ color_inc;
    mCube->drawCubeVBO(0, color);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(2.0, 0.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix,
                              glm::radians(angle+30), glm::vec3(0.0, 1.0, 0.0));

    modelMatrix = glm::scale(modelMatrix, glm::vec3(15.5, 15.5, 15.5));
    glUniformMatrix4fv(modelMatrixLocation,
                       1,
                       false,
                       &modelMatrix[0][0]);

    //draw the earth
    color = glm::vec4(0.0, 1.0, 0.0, 1.0) + color_inc;
    mCube->drawCubeVBO(0, color);

    modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.0, 0.0, 0.0));
    modelMatrix = glm::rotate(modelMatrix,
                              glm::radians(angle+100), glm::vec3(0.0, 1.0, 0.0));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(5.5, 5.5, 5.5));
    glUniformMatrix4fv(modelMatrixLocation,
                       1,
                       false,
                       &modelMatrix[0][0]);


    //draw the moon
    color = glm::vec4(0.0, 0.0, 1.0, 1.0) + color_inc;
    mCube->drawCubeVBO(0, color);


    //make color to black eventually
    color_inc -= glm::vec4(0.005, 0.005, 0.005, 0.005);

}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawScene();

    glutSwapBuffers();
}

void timer(int val) {
    draw();
    glutTimerFunc(50, timer, 0);
}

void resize(int w, int h) {
    printf("resize");

    glViewport(0, 0, w, h);
    glm::mat4 projMatrix = glm::mat4(1.0);
    projMatrix =
          glm::perspective(90.0, 1.0, 0.1, 100.0);
    glUniformMatrix4fv(projectionMatrixLocation, 1,
                       false, &projMatrix[0][0]);
}

int main(int argc, char** argv)
{
    //initialize the glut library
    glutInit(&argc, argv);

    //set the appropriate display mode
    //this configures the frame buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    //define the size of the window
    glutInitWindowSize(800, 720);

    glutCreateWindow("Solar System");

     //initialize the glew library
    glewInit();

    //start making opengl calls
    init();

    glutDisplayFunc(draw);
    glutReshapeFunc(resize);

    glutTimerFunc(50, timer, 0);
    //start the glut event loop
    glutMainLoop();


    return 0;
}
