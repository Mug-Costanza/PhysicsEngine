#include "objLoader.hpp"

bool LoadOBJ(const char* modelPath, std::vector <glm::vec3>& outVertices, std::vector <glm::vec2>& outTextureCoords, std::vector <glm::vec3>& outNormals)
{
    std::vector <unsigned int> vertexIndices, textIndices, normalIndices;
    std::vector <glm::vec3> vertices;
    std::vector <glm::vec2> textureCoords;
    std::vector <glm::vec3> normals;

    FILE* modelFile = fopen(modelPath, "r");

    if (modelFile == NULL)
    {
        std::cout << "Failed to load model : " << modelPath << std::endl;
        fclose(modelFile);
        return false;
    }

    while (modelFile)
    {
        char lineHeader[128];

        int res = fscanf(modelFile, "%s", lineHeader);

        if (res == EOF)
        {
            break;
        }

        if (strcmp(lineHeader, "v") == 0)
        {
            glm::vec3 vertex;
            fscanf(modelFile, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0)
        {
            glm::vec2 textCoord;
            fscanf(modelFile, "%f %f\n", &textCoord.x, &textCoord.y);
            textCoord.y = -textCoord.y;
            textureCoords.push_back(textCoord);
        }
        else if (strcmp(lineHeader, "vn") == 0)
        {
            glm::vec3 normal;
            fscanf(modelFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            normals.push_back(normal);
        }
        else if (strcmp(lineHeader, "f") == 0)
        {
            std::string vertex1, vertex2, vertex3;

            unsigned int vertexIndex[3], textIndex[3], normalIndex[3];

            int matches = fscanf(modelFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &textIndex[0], &normalIndex[0], &vertexIndex[1], &textIndex[1], &normalIndex[1], &vertexIndex[2], &textIndex[2], &normalIndex[2]);

            if (matches != 9)
            {
                std::cout << "The model file : " << modelPath << " cannot be read, please try exporting with different settings." << std::endl;

                fclose(modelFile);
                return true;
            }

            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            textIndices.push_back(textIndex[0]);
            textIndices.push_back(textIndex[1]);
            textIndices.push_back(textIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int textIndex = textIndices[i];
        unsigned int normalIndex = normalIndices[i];

        glm::vec3 vertex = vertices[vertexIndex - 1];
        glm::vec2 textureCoord = textureCoords[textIndex - 1];
        glm::vec3 normal = normals[normalIndex - 1];

        outVertices.push_back(vertex);
        outTextureCoords.push_back(textureCoord);
        outNormals.push_back(normal);
    }

    fclose(modelFile);
    return true;
}
