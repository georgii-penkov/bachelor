#version 330 core
   uniform vec4 color;
   in vec3 aColor;
   out vec4 FragColor;
   void main()
   {
      FragColor = vec4(aColor.x, aColor.y, aColor.z, 1.0f);
   };