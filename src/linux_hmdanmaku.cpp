/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Jack Riales $
   $Notice: (C) Copyright 2016 by Jack Riales, Inc. All Rights Reserved. $
   ======================================================================== */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global for now...
static char *windowHeader = "Handmade Danmaku v. 0.0.0";
static Display *display = NULL;
static Window rootWindow;
static Window window;
static XVisualInfo *pVisualInfo = NULL;
static Colormap cmap;
static XWindowAttributes winAtb;
static XSetWindowAttributes setWinAtb;
static XEvent event;
static GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
static GLXContext glContext;


// Test GL function
void DrawQuad() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1., 1., -1., 1., 1., 20.);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0., 0., 10., 0., 0., 0., 0., 1., 0.);

    glBegin(GL_QUADS);
    glColor3f(1., 0., 0.); glVertex3f(-.75, -.75, 0.);
    glColor3f(0., 1., 0.); glVertex3f( .75, -.75, 0.);
    glColor3f(0., 0., 1.); glVertex3f( .75,  .75, 0.);

    glColor3f(1., 1., 0.); glVertex3f(-.75,  .75, 0.);
    glEnd();
}

int main(int argc, char **argv) {    

    // Open display
    display = XOpenDisplay(0);
    if (display == NULL) {
        fprintf(stderr, "Cannot open X11 display.\n");
        return(1);
    }

    // Initialization
    rootWindow = DefaultRootWindow(display);
    pVisualInfo = glXChooseVisual(display, 0, att);
    if (pVisualInfo == NULL) {
        fprintf(stderr, "No appropriate visual found.\n");
        return(1);
    }

    cmap = XCreateColormap(display, rootWindow, pVisualInfo->visual, AllocNone);

    setWinAtb.colormap = cmap;
    setWinAtb.event_mask = ExposureMask | KeyPressMask;

    window = XCreateWindow(display, rootWindow,
                           0, 0, 600, 600, 0,
                           pVisualInfo->depth,
                           InputOutput,
                           pVisualInfo->visual,
                           CWColormap | CWEventMask,
                           &setWinAtb);
    XMapWindow(display, window);
    XStoreName(display, window, windowHeader);

    glContext = glXCreateContext(display, pVisualInfo, NULL, GL_TRUE);
    glXMakeCurrent(display, window, glContext);
    glEnable(GL_DEPTH_TEST);
    
    // Main loop
    while(1) {
        XNextEvent(display, &event);

        if (event.type == Expose) {
            XGetWindowAttributes(display, window, &winAtb);
            glViewport(0, 0, winAtb.width, winAtb.height);
            DrawQuad();
            glXSwapBuffers(display, window);
        }
        if (event.type == KeyPress) {
            // Exit on key press
            break;
        }
        
    }

    // Cleanup
    glXMakeCurrent(display, None, NULL);
    glXDestroyContext(display, glContext);
    XDestroyWindow(display, window);
    XCloseDisplay(display);    
    return(0);
}
