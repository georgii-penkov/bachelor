#version 330 core
    layout (location = 0) in vec3 aPos;
    out vec3 vertexColor;
    uniform mat4 transform;
    void main()
    {
       gl_Position = transform*vec4(aPos.x, aPos.y, aPos.z, 1.0);
       vertexColor = aPos;
    };