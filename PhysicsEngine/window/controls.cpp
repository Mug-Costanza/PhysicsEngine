//Project files
#include "controls.hpp"
#include "window.hpp"
#include "keyCode.h"
#include "../object.hpp"
#include "../player.hpp"

extern Window window;
extern Player player;
extern glm::mat4 projectionMat;
extern glm::mat4 viewMat;

float verticalAngle = 0.0f, horizontalAngle = 3.14;

bool mouseEnable = false;

float mouseSpeed = 0.05f;

float deltaTime;

glm::vec3 direction, right, up;

void ComputeControls()
{
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    deltaTime = float(currentTime - lastTime); // Prevents movement from running at different speeds on different PCs.

    double xPos, yPos;

    player.speed = 15.0f;

    glfwGetCursorPos(window.getWindow(), &xPos, &yPos);

    int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

    // Check if controller is present.
    //std::cout << "Joystick Connected : " << present << std::endl;

    //  CONTROLER CONFIG
    //  
    //  axes[0] = Left Stick X
    //  axes[1] = Left Stick Y
    //  axes[2] = Right Stick X
    //  axes[3] = Right Stick Y
    //  axes[4] = Left Trigger
    //  axes[5] = Right Trigger
    //  button[0] = A
    //  button[1] = B
    // 
    // I'll figure out the rest later.
    //  

    if (!mouseEnable)
    {
        glfwSetCursorPos(window.getWindow(), window.getWidth() / 2, window.getHeight() / 2); // Place mouse at the center of the window.
        glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    // Toggle mouse when Tab is pressed.
    if (glfwGetKey(window.getWindow(), Tab) == Press)
    {
        mouseEnable ? mouseEnable = false : mouseEnable = true;
    }

    if (!mouseEnable)
    {
        horizontalAngle -= mouseSpeed * float((float)window.getWidth() / 2 - xPos) * -(deltaTime) * 2;
        verticalAngle -= mouseSpeed * float((float)window.getHeight() / 2 - yPos) * -(deltaTime) * 2;

        // Controller controls
        if (present == 1)
        {
            int axesCount;
            const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
            //std::cout << "Axes Avalible : " << axesCount << std::endl;
            //std::cout << "Left Stick X Axis : " << axes[0] << std::endl;
            //std::cout << "Left Stick Y Axis : " << axes[1] << std::endl;
            //std::cout << "Right Stick X Axis : " << axes[2] << std::endl;
            //std::cout << "Right Stick Y Axis : " << axes[3] << std::endl;
            //std::cout << "Left Trigger : " << axes[4] << std::endl;
            //std::cout << "Right Trigger : " << axes[5] << std::endl;

            if ((axes[2] > 0.15f || axes[2] < -0.15f) && axes[4] != 1)
            {
                horizontalAngle -= axes[2] * mouseSpeed * (deltaTime) * 50;
            }
            else if ((axes[2] > 0.15f || axes[2] < -0.15f) && axes[4] == 1)
            {
                horizontalAngle -= axes[2] * mouseSpeed * (deltaTime) * 60;
            }

            if ((axes[3] > 0.15f || axes[3] < -0.15f) && axes[4] != 1)
            {
                verticalAngle -= axes[3] * mouseSpeed * (deltaTime) * 100;
            }
            else if ((axes[3] > 0.15f || axes[3] < -0.15f) && axes[4] == 1)
            {
                verticalAngle -= axes[3] * mouseSpeed * (deltaTime) * 50;
            }

            int buttonCount;
            const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

            if (axes[1] < -0.15f)
            {
                player.Position.x += direction.x * deltaTime * player.speed;
                player.Position.z += direction.z * deltaTime * player.speed;
            }

            if (axes[1] > 0.15f)
            {
                player.Position.x -= direction.x * deltaTime * player.speed;
                player.Position.z -= direction.z * deltaTime * player.speed;
            }

            if (axes[0] < -0.15f)
            {
                player.Position -= right * deltaTime * player.speed;
            }

            if (axes[0] > 0.15f)
            {
                player.Position += right * deltaTime * player.speed;
            }

            if (GLFW_PRESS == buttons[0])
            {
                player.Position.y -= 0.25f;
            }


            if (GLFW_PRESS == buttons[1])
            {
                player.Position.y += 0.25f;
            }
        }

        // Camera clamping
        if (verticalAngle < -1.5f)
        {
            verticalAngle = -1.5f;
        }

        if (verticalAngle > 1.5f)
        {
            verticalAngle = 1.5f;
        }

        // Forces cursor at the center of the screen.
        glfwSetCursorPos(window.getWindow(), (float)window.getWidth() / 2, (float)window.getHeight() / 2);

        // Which direction is the camera facing?
        direction = glm::vec3((cos(verticalAngle) * sin(horizontalAngle)), sin(verticalAngle), (cos(verticalAngle) * cos(horizontalAngle)));

        // Which direction is right?
        right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));

        // Which direction is up?
        up = glm::cross(right, direction);

        projectionMat = glm::perspective(glm::radians(90.0f), float(window.getWidth() / window.getHeight()), 0.1f, 300.0f);

        viewMat = glm::lookAt(player.Position, player.Position + direction, up);

        // For player collisions.
        glm::vec3 oldPos = player.Position;

        if ((glfwGetKey(window.getWindow(), W) || glfwGetKey(window.getWindow(), Up)))
        {
            player.Position.x += direction.x * deltaTime * player.speed;
            player.Position.z += direction.z * deltaTime * player.speed;
            //player.Position.y = oldPos.y;
        }

        if ((glfwGetKey(window.getWindow(), S) || glfwGetKey(window.getWindow(), Down)))
        {
            player.Position.x -= direction.x * deltaTime * player.speed;
            player.Position.z -= direction.z * deltaTime * player.speed;
            //player.Position.y = oldPos.y;
        }

        if (glfwGetKey(window.getWindow(), A))
        {
            player.Position -= right * deltaTime * player.speed;
            //player.Position.y = oldPos.y;
        }

        if (glfwGetKey(window.getWindow(), D))
        {
            player.Position += right * deltaTime * player.speed;
            //player.Position.y = oldPos.y;
        }

        if (glfwGetKey(window.getWindow(), Left))
        {
            player.Position -= right * deltaTime * player.speed;
            //player.Position.y = oldPos.y;
            //direction.x -= 0.5f;
        }

        if (glfwGetKey(window.getWindow(), Right))
        {
            player.Position += right * deltaTime * player.speed;
            //player.Position.y = oldPos.y;
            //direction.x += 0.5f;
        }

        if (glfwGetKey(window.getWindow(), Space))
        {
            player.Position.y += 0.6 * player.speed * deltaTime;
        }

        if (glfwGetKey(window.getWindow(), lShift))
        {
            player.Position.y -= 0.6 * player.speed * deltaTime;
        }
    }

    lastTime = currentTime;
}
