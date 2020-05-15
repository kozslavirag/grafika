#include "scene.h"
#include "callbacks.h"
#include <GL/glut.h>

#include <load.h>
#include <draw.h>

int fogsets = 0;

struct {
    int x ;
    int y ;
	int z ;
} cat_position;

unsigned int SkyTexture;

void init_scene(Scene* scene)
{
    load_model(&(scene->cat), "models/cat.obj");
    scene->texture_id = load_texture("textures/cat.jpg");
	
	load_model(&(scene->stone), "models/stone.obj");
    scene->stonetexture_id = load_texture("textures/stone.jpg");
	
	SkyTexture = load_texture ("textures/skybox.jpg");
	scene->helptexture_id = load_texture("textures/help.png");
	
	set_lighting(scene);
	
    
	scene->material.ambient.red = 1.0;
    scene->material.ambient.green = 1.0;
    scene->material.ambient.blue = 1.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 10.0;
}

void set_lighting()
{
  float ambient_light[] = { 0.8f, 0.8f, 0.8f, 0.8f };
  float diffuse_light[] = { 0.9f, 0.9f, 0.9f, 0.9f };
  float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}



void DrawSky()
{
	GLUquadric* pSphereQuadric = gluNewQuadric();
	gluQuadricDrawStyle( pSphereQuadric, GLU_FILL );
	gluQuadricOrientation( pSphereQuadric, GLU_INSIDE );
	gluQuadricTexture( pSphereQuadric, GL_TRUE );
	gluQuadricNormals( pSphereQuadric, GLU_SMOOTH );
	gluSphere( pSphereQuadric, 100.0, 360, 360 );
	gluDeleteQuadric( pSphereQuadric );	
}

void draw_scene(const Scene* scene)
{
	double forward = calc_test();
	static int last_frame_time = 0;
        int current_time;
        double elapsed_time;
	int BlendType = 0;
        set_material(&(scene->material));
        draw_origin();
	
	current_time = glutGet(GLUT_ELAPSED_TIME);
        elapsed_time = (double)(current_time - last_frame_time) / 1000;
        last_frame_time = current_time;
 
        forward = forward * elapsed_time;
	
	glPushMatrix();
	glTranslatef(-forward ,0, -8);
	glBindTexture(GL_TEXTURE_2D, scene->texture_id);
	draw_model(&(scene->cat));
	glPopMatrix();
	
	
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_BLEND);
	glDisable(GL_CULL_FACE);
    if(BlendType == 0)
	{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
	else if(BlendType == 1)
	{ 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	}
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, scene->stonetexture_id);
	glTranslatef(25, 0, -5);
	draw_model(&(scene->stone));
	glTranslatef(0, 1, 1);
	draw_model(&(scene->stone));
	glTranslatef(0, 3, -1);
	draw_model(&(scene->stone));
	glPopMatrix();
	
	glPushMatrix();
	glBindTexture( GL_TEXTURE_2D, SkyTexture);
	DrawSky();
	glPopMatrix();
	
	glBindTexture( GL_TEXTURE_2D, scene->helptexture_id);
	
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void fog()
{
    float fogColor[] = {0.5, 0.5, 0.5};
	if (0 < fogsets)
	{
		glEnable(GL_FOG);

		glHint(GL_FOG_HINT, GL_NICEST);
		if (1 == fogsets)
		{
			glFogf(GL_FOG_DENSITY, 0.01);
			glFogi(GL_FOG_MODE, GL_EXP);
		}
		if (2 == fogsets)
		{
			glFogf(GL_FOG_DENSITY, 0.04);
			glFogi(GL_FOG_MODE, GL_EXP);
		}
		if (3 == fogsets)
		{
			glFogf(GL_FOG_DENSITY, 0.07);
			glFogi(GL_FOG_MODE, GL_EXP);
		}
		if (4 == fogsets)
		{
		    glFogf(GL_FOG_DENSITY, 0.1);
			glFogi(GL_FOG_MODE, GL_EXP);	
		}
		glFogf(GL_FOG_START, 1);
		glFogf(GL_FOG_END, 1000.0);
		glFogfv(GL_FOG_COLOR, fogColor);
	}
	else
	{
		glDisable(GL_FOG);
	}
}




