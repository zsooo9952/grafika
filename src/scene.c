#include "scene.h"
#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

double marsmove;
double marsx;
double marsy;
double fgd;

unsigned int SkyTexture;

void init_fog()
{
  glEnable(GL_FOG);
  GLfloat fogDensity = fgd;
  GLfloat fogColor[4] = { 0.0f, 1.0f, 1.0f, 1 };
  glFogi( GL_FOG_MODE, GL_EXP2 );
  glFogfv( GL_FOG_COLOR, fogColor );
  glFogf( GL_FOG_DENSITY, fogDensity );
  glHint( GL_FOG_HINT, GL_NICEST );
  glFogf( GL_FOG_START, 1.0f );
  glFogf( GL_FOG_END, 40.0f );
}

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "models/mars.obj");
    scene->texture_id = load_texture("textures/mars.jpg"); 
	scene->help_id = load_texture("ujhelp.png");
	load_model(&(scene->sun), "models/sun2.obj");
    scene->suntex = load_texture("textures/suntexture.jpg");
	
	SkyTexture=load_texture("textures/skybox.png");
	
	set_lighting(scene);
	init_fog();
	
  scene->material.ambient.red = 0.2;
  scene->material.ambient.green = 0.2;
  scene->material.ambient.blue = 0.2;

  scene->material.diffuse.red = 1;
  scene->material.diffuse.green = 1;
  scene->material.diffuse.blue = 1;

  scene->material.specular.red = 0.3;
  scene->material.specular.green = 0.3;
  scene->material.specular.blue = 0.3;

  scene->material.shininess = 50.0;

	}

void set_lighting()
{
  float ambient_light[] = { 0.8f, 0.8f, 0.8f, 0.8f };
  float diffuse_light[] = { 0.9f, 0.9f, 0.9f, 0.9f };
  float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  float position[] = { 1.0f, 1.0f, 1.0f, 0.0f };

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
    
    
	glBindTexture( GL_TEXTURE_2D, SkyTexture);
	DrawSky();
	init_fog();
	
	glPushMatrix();
	glTranslatef(20+marsx, -10+marsy, 0.42);
	glRotatef(0+marsmove, 0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D,scene->texture_id);
	draw_model(&(scene->cube));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(20, 10, 0.42);
		glBindTexture(GL_TEXTURE_2D,scene->suntex);
		draw_model(&(scene->sun));
	glPopMatrix();
	
	
	//help menü
	glBindTexture(GL_TEXTURE_2D,scene->help_id);
}
void marsmoves(double time) { 
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;
	marsx-=time/10;
	marsy+=time/10;
	marsmove+=time*5;
	fgd=elapsed_time/2;
	}