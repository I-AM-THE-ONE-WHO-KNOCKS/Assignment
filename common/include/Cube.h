
#ifndef CUBE_H_
#define CUBE_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>


class Cube {
public:
    int posLoc;
    int colorLoc;
    int offsetloc;
    int flag;
    Cube();
	virtual ~Cube();

        void drawCubeVBO(int flag_draw, glm::vec4 color);
        void getattib(GLint id);
};

#endif /* CUBE_H_ */
