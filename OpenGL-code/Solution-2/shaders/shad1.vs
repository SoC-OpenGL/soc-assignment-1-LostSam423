
#version 400 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in float aCol;

out vec3 ourCol;

void main()
{
    gl_Position = vec4(aPos,0.0, 1.0);
    ourCol = vec3(aCol, aCol, aCol);

}