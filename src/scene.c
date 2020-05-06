#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

double marsmove;

unsigned int SkyTexture;
void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "models/mars.obj");
    scene->texture_id = load_texture("textures/mars.jpg"); 

	SkyTexture=load_texture("textures/skybox.png");	

    scene->material.ambient.red = 0.0;
    scene->material.ambient.green = 0.0;
    scene->material.ambient.blue = 0.0;

    scene->material.diffuse.red = 1.0;
    scene->material.diffuse.green = 1.0;
    scene->material.diffuse.blue = 1.0;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 10.0;
	set_lighting(scene);
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
	glBindTexture( GL_TEXTURE_2D, SkyTexture);
	GLUquadric* pSphereQuadric = gluNewQuadric();
	gluQuadricDrawStyle( pSphereQuadric, GLU_FILL );
	gluQuadricOrientation( pSphereQuadric, GLU_INSIDE );
	gluQuadricTexture( pSphereQuadric, GL_TRUE );
	gluQuadricNormals( pSphereQuadric, GLU_SMOOTH );
	gluSphere( pSphereQuadric, 100.0, 360, 180 );
	gluDeleteQuadric( pSphereQuadric );	
}

void draw_scene(const Scene* scene)
{
    set_material(&(scene->material));
    
    draw_origin();
	glBindTexture( GL_TEXTURE_2D,scene->texture_id );
    draw_model(&(scene->cube));
	
	glBindTexture( GL_TEXTURE_2D, SkyTexture);
	DrawSky();
	
	glPushMatrix();
	glTranslatef(3, -7.3, 34.65);
	glRotatef(0+marsmove, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D,scene->texture_id);
	draw_model(&(scene->cube));
	glPopMatrix();
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
void marsrotate(double time) {
	marsmove+=time*5;
}