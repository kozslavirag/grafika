#ifndef CALLBACKS_H
#define CALLBACKS_H

#include "camera.h"
#include "scene.h"

#include <GL/glut.h>

/**
 * Scene
 */
Scene scene;

/**
 * Camera
 */
Camera camera;

/**
 * Call when need to display the graphical content.
 */
void display();

/**
 * Call after windows resizing.
 */
void reshape(GLsizei width, GLsizei height);

/**
 * Call after mouse button event.
 */
void mouse(int button, int state, int x, int y);

/**
 * Call after mouse event.
 */
void motion(int x, int y);
/**
 *Increase lights
 */
void set_increase();
/**
 *Decrease lights
 */
 void set_decrease();

/**
 * Call after keyboard event.
 */
void keyboard(unsigned char key, int x, int y);

/**
 * Call after keyboard release event.
 */
void keyboard_up(unsigned char key, int x, int y);
/**
 *Help menu
 */
void special_key_handler(int key, int x, int y);

/**
 * Call when there is no other event.
 */

double calc_test(); 
 
void idle();

#endif /* CALLBACKS_H */
