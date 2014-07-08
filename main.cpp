//Brandon Hathaway, CSCI 405 Assignment 2
//565069747

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "colour.h"
#include "vector.h"
#include "ray.h"
#include "camera.h"
#include "light.h"
#include "plane.h"
#include "sphere.h"
#include "object.h"
#include "source.h"


using namespace std;


// Specify the window dimensions
#define SCREENWIDTH 512
#define SCREENHEIGHT 512
#define AMBIENTLIGHT 0.5


static CRGB gsPixelBuffer[SCREENWIDTH*SCREENHEIGHT];          


void ClearImage()
{
	for( int x = 0; x < SCREENWIDTH; x++ )
	{
		for( int y = 0; y < SCREENHEIGHT; y++ )
		{	
			int bufferInd = y*SCREENHEIGHT+x;
			gsPixelBuffer[ bufferInd ] = CRGB(0, 0, 0);
		}
	}
}

int closestIntersection(vector<float> object_intersections)
{
    int min=INT_MAX;
    int minIndex=-1;

    if (object_intersections.size() == 0)
    {
        return -1;
    }
    else if (object_intersections.size() == 1)
    {
        if (object_intersections.at(0) > 0)
        {
            return 0;
        }
        else {
            return -1;
        }
    }
    else {
        for (int i=0; i < object_intersections.size();i++)
        {
            if ((min > object_intersections.at(i)) and (object_intersections.at(i) >= 0))
            {
                min = object_intersections.at(i);
                minIndex = i;
            }
        }
        if (minIndex == -1) {
            return -1;
        }
        return minIndex;  
    }
      
}


CRGB getColorAt(vector3 isectPos, vector3 isectDir, vector<object*> scene_objects, int closestIntersectionIndex, vector<source*> light_sources) 
{
    CRGB isectColor = scene_objects.at(closestIntersectionIndex)->getColor();
    vector3 isectNormal = scene_objects.at(closestIntersectionIndex)->getNormalAt(isectPos);
    
    CRGB colorResult = isectColor*AMBIENTLIGHT;

    for (int i=0;i<light_sources.size();i++) {

        bool shadow = false;

        //create a ray from the surface of the object to the current light

        vector3 lightDir = light_sources.at(i)->getPos().add(isectPos.negative()).normalize();

        float cosine_angle = isectNormal.dot(lightDir)/(isectNormal.length()*lightDir.length());

        vector3 isectToLight = light_sources.at(i)->getPos().add(isectPos.negative()).normalize();
            
        ray shadowRay(isectPos, isectToLight);

        vector<float> shadow_isects;


        //now check to see if the ray from the surface of the object intersects
        //anything else, and if it doesnt, then add light.
        for (int j=0;(j<scene_objects.size()) and (shadow == false);j++)
        {
            shadow_isects.push_back(scene_objects.at(j)->rayISect(shadowRay));
        }
       
        for(int k=0; k<shadow_isects.size();k++)
        {
            if (shadow_isects.at(k) >= 0.01)
            {
                if (shadow_isects.at(k) <= isectToLight.length())
                {
                    shadow = true;
                }
            }
        }
        if (shadow == false) {
            //ammount of light gained is dependant on the angle between the normal
            //of the surface and the ray between the surface and the light.

            colorResult = colorResult+(isectColor)+(light_sources.at(i)->getColor()*(cosine_angle)); 
        }  
    }
    return colorResult;  
}

void RenderImage()
{
    cout << "rendering..." << endl;

    //calculate orthonormal vectors for camera, and set its position

    vector3 I(1,0,0);
    vector3 J(0,1,0);
    vector3 K(0,0,1);

    vector3 pos(6, 3, -10);

    vector3 at = pos.negative().normalize(); //unit vector from position towards origin
    vector3 right = J.cross(at).normalize(); 
    vector3 up = right.cross(at).normalize();; 

    // camera
    camera scene_cam(pos, at, right, up);
    
    // light sources

    vector3 light_position (-7,10,-10);
    light scene_light (light_position, CRGB(100,100,100));
    
    vector<source*> light_sources;

    light_sources.push_back(dynamic_cast<source*>(&scene_light));

    // scene objects
    sphere scene_sphere3(vector3(-3,4,30),5,CRGB(120,0,0));
    sphere scene_sphere2(vector3(-6,0,0),1,CRGB(40,0,30));
    sphere scene_sphere(vector3(0,0,0),1,CRGB(100,60,0));
    plane scene_plane(J, -1, CRGB(0,0,100));

    vector<object*> scene_objects;
    scene_objects.push_back(dynamic_cast<object*>(&scene_sphere3)); 
    scene_objects.push_back(dynamic_cast<object*>(&scene_sphere2));            
    scene_objects.push_back(dynamic_cast<object*>(&scene_sphere));
    scene_objects.push_back(dynamic_cast<object*>(&scene_plane)); 
 

    float relX, relY;

	for( int x = 0; x < SCREENWIDTH; x++ )
	{
		for( int y = 0; y < SCREENHEIGHT; y++ )
		{	
            relX = ((x+0.5)/SCREENWIDTH);
            relY = ((SCREENHEIGHT - y) + 0.5)/SCREENHEIGHT;
                    
            vector3 rayStart = scene_cam.getPos();
            vector3 rayDir = scene_cam.getAt().add(scene_cam.getRight().scalar(relX - 0.5)
                                              .add(scene_cam.getUp().scalar(relY - 0.5)))
                                              .normalize();

            ray pixelRay(rayStart, rayDir);

            vector<float> intersections;

            for (int k=0;k<scene_objects.size();k++)
            {
                intersections.push_back(scene_objects.at(k)->rayISect(pixelRay));
            }  

                 
            int closestIntersectionIndex = closestIntersection(intersections);



            int bufferInd = y*SCREENHEIGHT + x;
            if (closestIntersectionIndex >= 0)  
            {
                vector3 isectPos = pixelRay.getOrigin()
                                 .add(pixelRay.getDirection()
                                 .scalar(intersections.at(closestIntersectionIndex)));

                vector3 isectDir = pixelRay.getDirection();

                CRGB isectColor = getColorAt(isectPos, isectDir, scene_objects, closestIntersectionIndex, light_sources);

                gsPixelBuffer[bufferInd] = isectColor;

            }
            else {
                gsPixelBuffer[bufferInd] = CRGB(0,0,0);

            }
		}
	}
}

// GLUT callback to handle rendering the scene
void renderScene(void) 
{
	glDrawPixels( SCREENWIDTH, SCREENHEIGHT,  GL_RGB, GL_UNSIGNED_BYTE, gsPixelBuffer );
	
	glutSwapBuffers();
}
void keyboard(unsigned char key, int x, int y) 
{
	if( 'r' == key )
	{
		ClearImage();
		RenderImage();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH|GLUT_DOUBLE|GLUT_RGBA);

	glutInitWindowPosition(100,100);
	glutInitWindowSize( SCREENWIDTH, SCREENHEIGHT );
	glutCreateWindow("CSCI 405 Assignment 2");

	glViewport( 0, 0, SCREENWIDTH, SCREENHEIGHT );

	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);

	glutKeyboardFunc( keyboard );

	//  GLUT main loop
	glutMainLoop();

	return(0);
}

