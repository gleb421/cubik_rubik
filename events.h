//
// Created by User on 07.05.2024.
//

#ifndef RUBE_CUB_EVENTS_H
#define RUBE_CUB_EVENTS_H


#include "window.h"

typedef unsigned int uint;

class Events {
public:
    static bool* _keys;
    static uint* _frames;
    static uint _current;
    static float deltaX;
    static float deltaY;
    static float x;
    static float y;
    static bool _cursor_locked;
    static bool _cursor_started;

    static int initialize();
    static void pullEvents();

    static bool pressed(int keycode);
    static bool jpressed(int keycode);

    static bool clicked(int button);
    static bool jclicked(int button);
    static void toogleCursor();
};


#endif //RUBE_CUB_EVENTS_H
