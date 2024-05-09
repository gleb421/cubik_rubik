//
// Created by User on 07.05.2024.
//

#ifndef RUBE_CUB_WINDOW_H
#define RUBE_CUB_WINDOW_H

class GLFWwindow;

class Window {

public:
    static int width;
    static int height;
    static GLFWwindow* window;
    static int initialize(int width, int height, const char * title);
    static bool isShouldClose();
    static void swapBuffers();
    static void setCursorMode(int mode);
    static void setShouldClose(bool flag  );
    static void terminate();
};



#endif //RUBE_CUB_WINDOW_H
