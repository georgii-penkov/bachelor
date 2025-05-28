#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <glm/glm.hpp> //TODO add the other glm headers for matrices and vectors
  
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
  

class Shader
{
public:
    // the program ID
    unsigned int ID;
  
    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // destructor?
    //no need. cant see use case of stopping needing a shader. 
    //when program ends everything cleared anyway
    // use/activate the shader
    void Use();
    // utility uniform functions
    void SetBool(const std::string &name, bool value) const;  
    void SetInt(const std::string &name, int value) const;   
    void SetFloat(const std::string &name, float value) const;

    //TODO more setters for matrices and vectors.
};
  
#endif