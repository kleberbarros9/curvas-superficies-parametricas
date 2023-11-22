/* 
       g++ main.cpp bezierCurve.cpp bezierSurface.cpp bezierMath.cpp -o prog -lGL -lGLU -lglut -Llib -lm -g && ./prog surfaceDemo
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include "bezier.h"
#include "bezierCurve.h"
#include "bezierSurface.h"
#include "bezierFile.h"
#include <GL/glut.h>

using namespace std;

#define PI 3.1415926535898

static int width = 600;
static int height = 600;
float camera_theta = PI/2.0;
float camera_phi = 0.0;
float camera_r = 30.0;

int precision = 5;
bool showControlPoints = true;
bezier * b;

void init(){
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  glClearColor(0.5, 0.5, 0.5, 1.0);
  glShadeModel(GL_FLAT);
  glDisable(GL_COLOR_MATERIAL);
}


void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(1, 1, width-2, height-2);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 50.0);
//  gluOrtho2D(0, width-2, height-2, 0);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  gluLookAt(camera_r*sin(camera_theta)*cos(camera_phi), camera_r*cos(camera_theta), camera_r*sin(camera_theta)*sin(camera_phi),
         0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
  
  b->draw();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y)
{
  switch (key) {
  case 'z':
         if(camera_r - 1.0/18.0 > 0)
                 camera_r -= 1.0;
         break;
  case 'x':
         camera_r += 1.0;
         break;
  case '1':
         b->setPrecisions(1);
         break;
  case '2':
         b->setPrecisions(2);
         break;
  case '3':
         b->setPrecisions(3);
         break;
  case '4':
         b->setPrecisions(4);
         break;
  case '5':
         b->setPrecisions(5);
         break;
  case '6':
         b->setPrecisions(6);
         break;
  case '7':
         b->setPrecisions(7);
         break;
  case '8':
         b->setPrecisions(8);
         break;
  case '9':
         b->setPrecisions(9);
         break;
  case 's':
	     showControlPoints = !showControlPoints;
         b->controlPoints(showControlPoints);
         break;
  }
  glutPostRedisplay();
}

void special(int key, int x, int y)
{
        switch(key) {
        case GLUT_KEY_LEFT:
                camera_theta -= PI/18.0;
                break;
        case GLUT_KEY_RIGHT:
                camera_theta += PI/18.0;
                break;
        case GLUT_KEY_UP:
                camera_phi += PI/18;
                break;
        case GLUT_KEY_DOWN:
                camera_phi -= PI/18;
                break;
        }
        glutPostRedisplay();
}

bezier *readBezierFile(char *filename){
    std::ifstream inputFile(filename);
    //std::ifstream inputFile("surfaceDemo");

    if (!inputFile.is_open()) {
        std::cout << "Unable to open file";
        //return 1;
    }

    int uPoints, vPoints;
    inputFile >> uPoints >> vPoints;

    int length = (uPoints + 1) * (vPoints + 1);
    float **points = new float*[length];
    //float* point = new float[3];

    for (int i = 0; i < length; i++) {
        float* point = new float[3];
        inputFile >> point[0] >> point[1] >> point[2];
        points[i] = point;
    }

    inputFile.close();
    		bezier *bc;
		if(vPoints == 0){
		//	uPoints = i-1;		
		//	std::cout<< "newLine" << endl;
			bc = new bezierCurve(uPoints, points);
		} else {
			float ***points2d;
			points2d = new float **[uPoints];
			for(int m = 0; m <= uPoints; m++){
				float **points1d = new float*[vPoints+1];
				int width = vPoints+1;
				for(int n = 0; n <= vPoints; n++){
					points1d[n] = points[m*width + n];
					std::cout<<points[m*width + n][0]<<','<<points[m*width + n][1]<<','<<points[m*width + n][2]<<endl;
				}
                std::cout << "===============" << std::endl;
				points2d[m] = points1d;

			}
            
			bc = new bezierSurface(uPoints, vPoints, points2d);
		}
        
        delete[] points;
        
		return bc;
}

int main(int argc, char * argv[])
{
        //don't forget to free
	    if (argc < 2) {
			 std::cout << "Usage is: <infile>\n";
			 exit(0);
		}
        b = readBezierFile(argv[1]);
		b->setPrecisions(5);
		b->controlPoints(showControlPoints);

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(100, 100);
        glutCreateWindow(argv[0]);
        init();

        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);
        glutSpecialFunc(special);
        glutMainLoop();
        return 0;
}
