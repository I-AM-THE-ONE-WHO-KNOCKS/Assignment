#include "include/Shader.h"
#
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>

using namespace std;
#define _CRT_SECURE_NO_WARNINGS

static char* textFileRead(const char *fileName) {
	char* text = NULL;

	if (fileName != NULL) {
		FILE *file = fopen(fileName, "rt");

		if (file != NULL) {
			fseek(file, 0, SEEK_END);
			int count = ftell(file);
			rewind(file);

			if (count > 0) {
				text = (char*)malloc(sizeof(char) * (count + 1));
				count = fread(text, sizeof(char), count, file);
				text[count] = '\0';
			}
			fclose(file);
		}
	}
	return text;
}

GLuint  Shader::init(const char* csFile) {
	shader_cp = glCreateShader(GL_COMPUTE_SHADER);
	const char* csText = textFileRead(csFile);
	if (csText == NULL) {
		cerr << "Compute shader file not found." << endl;
		return -1;
	}

	glShaderSource(shader_cp, 1, &csText, 0);
	glCompileShader(shader_cp);

	GLint success;
	glGetShaderiv(shader_cp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_cp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_cp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}


	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_cp);

	//link the program object
	glLinkProgram(shader_id);

	glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
	if (success) {
		printf("Shader link successful\n");
		return shader_id;
	}
	else {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetProgramInfoLog(shader_id, length, &length, log);
		printf("Compiler link failed\n%s", log);
		return -1;
	}

	return shader_id;






}


GLuint Shader::init(const char *vsFile, const char *fsFile) {
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vsText = textFileRead(vsFile);
	const char* fsText = textFileRead(fsFile);

	if (vsText == NULL || fsText == NULL) {
		cerr << "Either vertex shader or fragment shader file not found." << endl;
		return -1;
	}

	glShaderSource(shader_vp, 1, &vsText, 0);
	glCompileShader(shader_vp);

	GLint success;
	glGetShaderiv(shader_vp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_vp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_vp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}

	glShaderSource(shader_fp, 1, &fsText, 0);
	glCompileShader(shader_fp);

	glGetShaderiv(shader_fp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_fp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_fp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}

	
	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_vp);
	glAttachShader(shader_id, shader_fp);

	//link the program object
	glLinkProgram(shader_id);
	
	glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
	if (success) {
		printf("Shader link successful\n");
		return shader_id;
	}
	else {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetProgramInfoLog(shader_id, length, &length, log);
		printf("Compiler link failed\n%s", log);
		return -1;
	}

	return shader_id;
}

GLuint Shader::init(const char *vsFile, const char *fsFile, const char* gsFile) {
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
	shader_gp = glCreateShader(GL_GEOMETRY_SHADER);

	const char* vsText = textFileRead(vsFile);
	const char* fsText = textFileRead(fsFile);
	const char* gsText = textFileRead(gsFile);


	if (vsText == NULL || fsText == NULL || gsText == NULL) {
		cerr << "Either vertex shader or fragment or geometry shader file not found." << endl;
		return -1;
	}

	glShaderSource(shader_vp, 1, &vsText, 0);
	glCompileShader(shader_vp);

	GLint success;
	glGetShaderiv(shader_vp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_vp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_vp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}

	glShaderSource(shader_fp, 1, &fsText, 0);
	glCompileShader(shader_fp);

	glGetShaderiv(shader_fp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_fp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_fp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}


	glShaderSource(shader_gp, 1, &gsText, 0);
	glCompileShader(shader_gp);

	glGetShaderiv(shader_gp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_gp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_gp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}



	shader_id = glCreateProgram();

	glAttachShader(shader_id, shader_vp);
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_gp);
 
	//link the program object
	glLinkProgram(shader_id);

	glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
	if (success) {
		printf("Shader link successful\n");
		return shader_id;
	}
	else {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetProgramInfoLog(shader_id, length, &length, log);
		printf("Compiler link failed\n%s", log);
		return -1;
	}

	return shader_id;
}


GLuint Shader::init(const char *vsFile, const char *fsFile, const char* tcs, const char* tes) {
	shader_vp = glCreateShader(GL_VERTEX_SHADER);
	shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
	shader_tcsp = glCreateShader(GL_TESS_CONTROL_SHADER);
	shader_tesp = glCreateShader(GL_TESS_EVALUATION_SHADER);

	const char* vsText = textFileRead(vsFile);
	const char* fsText = textFileRead(fsFile);
	const char* tcsText = textFileRead(tcs);
	const char* tesText = textFileRead(tes);


	if (vsText == NULL || fsText == NULL || tcsText == NULL || tesText == NULL) {
		cerr << "Either vertex shader or fragment or geometry or shader file not found." << endl;
		return -1;
	}

	glShaderSource(shader_vp, 1, &vsText, 0);
	glCompileShader(shader_vp);

	GLint success;
	glGetShaderiv(shader_vp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_vp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_vp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}

	glShaderSource(shader_fp, 1, &fsText, 0);
	glCompileShader(shader_fp);

	glGetShaderiv(shader_fp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_fp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_fp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}


	glShaderSource(shader_tcsp, 1, &tcsText, 0);
	glCompileShader(shader_tcsp);

	glGetShaderiv(shader_tcsp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_tcsp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_tcsp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}



	glShaderSource(shader_tesp, 1, &tesText, 0);
	glCompileShader(shader_tesp);

	glGetShaderiv(shader_tesp, GL_COMPILE_STATUS, &success);
	if (!success) {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetShaderiv(shader_tesp, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetShaderInfoLog(shader_tesp, length, &length, log);
		printf("Compiler failed\n%s", log);
		return -1;
	}
	else {
		printf("shader success\n");
	}


	shader_id = glCreateProgram();
	glAttachShader(shader_id, shader_vp);
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_tcsp);
	glAttachShader(shader_id, shader_tesp);



	//link the program object
	glLinkProgram(shader_id);

	glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
	if (success) {
		printf("Shader link successful\n");
		return shader_id;
	}
	else {
		//get the length of the shader compile error log
		GLint length = 0;
		glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &length);
		char* log = (char*)malloc(length);
		glGetProgramInfoLog(shader_id, length, &length, log);
		printf("Compiler link failed\n%s", log);
		return -1;
	}

	return shader_id;
}
Shader::Shader()
{
}

Shader::~Shader() {
	glDetachShader(shader_id, shader_fp);
	glDetachShader(shader_id, shader_vp);

	glDeleteShader(shader_fp);
	glDeleteShader(shader_vp);
	glDeleteProgram(shader_id);
}

unsigned int Shader::id() {
	return shader_id;
}

void Shader::bind() {
	glUseProgram(shader_id);
}

void Shader::unbind() {
	glUseProgram(0);
}
void Shader::setInt(const std::string &name, int value)
{
    glUniform1i(glGetUniformLocation(shader_id, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat)
{
    glUniformMatrix4fv(glGetUniformLocation(shader_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
void Shader::setVec3(const std::string &name, const glm::vec3 &value)
{
     glUniform3fv(glGetUniformLocation(shader_id, name.c_str()), 1, &value[0]);
}
void Shader::setFloat(const std::string &name, float value)
{
    glUniform1f(glGetUniformLocation(shader_id, name.c_str()), value);
}
