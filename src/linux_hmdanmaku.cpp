/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Jack Riales $
   $Notice: (C) Copyright 2016 by Jack Riales, Inc. All Rights Reserved. $
   ======================================================================== */

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {    
    Display *display = NULL;
    Window window;
    XEvent event;
    char *message = "Hello World!";
    int screen;

    // Open display
    display = XOpenDisplay(0);
    if (display == NULL) {
        fprintf(stderr, "Cannot open X11 display.\n");
        return(1);
    }

    // Initialization
    screen = DefaultScreen(display);
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 100, 100, 1,
                                 BlackPixel(display, screen), WhitePixel(display, screen));
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    // Main loop
    while(1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Dummy operations
            XFillRectangle(display, window, DefaultGC(display, screen), 20, 20, 10, 10);
            XDrawString(display, window, DefaultGC(display, screen), 10, 50, message, strlen(message));
        }
        if (event.type == KeyPress) {
            // Exit on key press
            break;
        }
    }

    // Cleanup
    XCloseDisplay(display);    
    return(0);
}
