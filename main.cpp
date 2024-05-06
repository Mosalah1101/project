#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float rotationOne = 0, rotationTwo = 0;

void myinit()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-400.0, 400.0, -400.0, 400.0, -400.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST); // Enable depth testing
}

void drawOrbit(float radius)
{
    glBegin(GL_LINE_LOOP);
    for (float angle = 0; angle < 2 * M_PI; angle += 0.0009)
    {
        glVertex2f(radius * cos(angle), radius * sin(angle));
    }
    glEnd();
}

void drawDot(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    rotationOne += 0.01; // Decreased increment for Earth's rotation
    rotationTwo += .0001;   // Increased increment for Moon's rotation

    glPushMatrix();
    glColor3ub(255, 255, 0); // sun
    glRotated(rotationOne, 0, 0, 1);
    glutWireSphere(65.0, 16, 16);

    glPushMatrix();
    glColor3f(0.2, 0.2, 0.7); // earth
    glRotated(rotationOne, 1, 0, 0); // Earth rotates around x-axis
    glTranslatef(200, 0, 0);
    glScalef(.9, .9, .9); // Scale earth by 1.5
    glutWireSphere(45.0, 16, 16);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1); // moon
    glRotated(rotationTwo, 0, 1, 0); // Moon rotates around y-axis
    glTranslatef(200 + 70 * cos(rotationOne), 70 * sin(rotationOne), 0); // Moon's orbit around the Earth
    glScalef(0.6 ,0.6, 0.6); // Scale moon by 0.8
    glutWireSphere(10.0, 16, 16);
    glPopMatrix();

    glPopMatrix();

    glColor3f(0, 0, 1); // orbits
    drawOrbit(200);
    drawOrbit(300);

    glFlush();
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("planet");
    glutDisplayFunc(display);
    myinit();
    glutMainLoop();
    return 0;
}
