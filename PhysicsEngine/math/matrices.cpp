#include "matrices.hpp"

extern float deltaTime;
extern float gravity;

// Translation function
glm::mat4 Translate(glm::vec3 transCoords)
{
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, transCoords);
    //object.vertices = trans * object.vertices;
    return trans;
}

// Rotation function
glm::mat4 Rotate(glm::vec3 rotCoords)
{
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 transX = glm::mat4(1.0f);
    glm::mat4 transY = glm::mat4(1.0f);
    glm::mat4 transZ = glm::mat4(1.0f);
    
    transX = glm::rotate(trans, glm::radians(rotCoords.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transY = glm::rotate(trans, glm::radians(rotCoords.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transZ = glm::rotate(trans, glm::radians(rotCoords.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    trans = transX * transY * transZ;
    
    return trans;
}

// Scaling function
glm::mat4 Scale(glm::vec3 scaleCoords)
{
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::scale(trans, scaleCoords);
    return trans;
}

// Return the value to the model matrix
glm::mat4 CheckMatrices(Object &object)
{
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 transT = glm::mat4(1.0f);
    glm::mat4 transRx = glm::mat4(1.0f);
    glm::mat4 transRy = glm::mat4(1.0f);
    glm::mat4 transRz = glm::mat4(1.0f);
    glm::mat4 transR = glm::mat4(1.0f);
    glm::mat4 transS = glm::mat4(1.0f);
    
    //Translate
    transT = glm::translate(transT,object.Position);
    
    //Rotation
    transRx = glm::rotate(transRx, glm::radians(object.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transRy = glm::rotate(transRy, glm::radians(object.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transRz = glm::rotate(transRz, glm::radians(object.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    transR = transRx * transRy * transRz;

    transR = glm::mat4_cast(object.Orientation);
    
    //Scale
    transS = glm::scale(transS, object.Scale);
    
    trans = transT * transR * transS;

    //Update collider orientation
    //object.collider.Position = object.Position;
    //object.collider.Rotation = object.Rotation;
    //object.collider.Scale = object.Scale;
  
    return trans;
}

// Return the value to the model matrix
glm::mat4 CheckMatrices_Collider(Collider &collider)
{    
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 transT = glm::mat4(1.0f);
    glm::mat4 transRx = glm::mat4(1.0f);
    glm::mat4 transRy = glm::mat4(1.0f);
    glm::mat4 transRz = glm::mat4(1.0f);
    glm::mat4 transR = glm::mat4(1.0f);
    glm::mat4 transS = glm::mat4(1.0f);
    
    //Translate
    transT = glm::translate(transT, collider.Position);
    
    //Rotation
    transRx = glm::rotate(transRx, glm::radians(collider.Rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transRy = glm::rotate(transRy, glm::radians(collider.Rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transRz = glm::rotate(transRz, glm::radians(collider.Rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    transR = transRx * transRy * transRz;

    transR = glm::mat4_cast(collider.Orientation);
    
    //Scale
    transS = glm::scale(transS, collider.Scale);
    
    trans = transT * transR * transS;
    
    return trans;
}