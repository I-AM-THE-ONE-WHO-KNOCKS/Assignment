#version 140
attribute vec3 a_Position;
uniform vec4 a_Color;
out vec4 v_Color;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
attribute vec2 aOffset;
uniform int flag;

void main(void)
{
    vec4 pos  = vec4(a_Position.xyz, 1.0);
    vec4 result =
                u_ProjectionMatrix *
                u_ViewMatrix *
                u_ModelMatrix *
                pos;
    if(flag == 1)
    {
        gl_Position = vec4(result.x + aOffset.x, result.y + aOffset.y, result.z , 1.0);
    }
    else
    {
        gl_Position = result;
    }
    v_Color = a_Color;
}
