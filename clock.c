#include <GL/glut.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


//extra 
int revolution;
int ringflag;
float rev[][3] = {{4,0,0}, {0,4.5,0}, {-2.8868,2.8868,2.8868}, {3.1755,3.1755,3.1755}, {6,0,0}, {0,6.5,0}, {-4.0415,4.0415,4.0415}, {4.3301,4.3301,4.3301}};
float rottor[][3] = {{1,0,0}, {0,1,0}, {-1,1,0}, {1,1,0}, {1,0,0}, {0,1,0}, {-1,1,0}, {1,1,0}};
float torsize[] = {4, 4.5, 5, 5.5, 6, 6.5, 7, 7.5};
GLfloat color[][3]={{0.0,0.5,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,0.0,1.0},{0.5,0.0,1.0},{0.0,1.0,1.0}};
int objrev=1;
int m=2;
int flag=0;
int sub1,sub2,sub3;

//extra

// define glu objects
int about_int=0;

GLUquadricObj *Cylinder;
GLUquadricObj *Disk;

struct tm *newtime;
time_t ltime;
int M_TWOPI=0;
GLfloat rx, ry, rz, angle;

// lighting
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition[]= { 5.0f, 25.0f, 15.0f, 1.0f };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static int light_state = 1; // light on = 1, light off = 0
static int view_state = 1; // Ortho view = 1, Perspective = 0

//extra 
void mouse(int btn,int state,int x,int y)
{
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN && flag==0)
		flag=1;
}
//extra

void Sprint( float x, float y, char *st)
{
	int l,i;

	l=strlen( st );
	glRasterPos3f( x, y, -1);
	for( i=0; i < l; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
	}

}

static void TimeEvent(int te)
{

	rx = 30 * cos( angle );
	ry = 30 * sin( angle );
	rz = 30 * cos( angle );
	angle += 0.01;
	if (angle > M_TWOPI) angle = 0;

	glutPostRedisplay();
	glutTimerFunc( 100, TimeEvent, 1);
}

//extra
void revobj(float rev[],int i)
{
	glColor3f(0.5,0.5,0.5);
	if(ringflag)
	{
		glPushMatrix();
		glRotatef(90,rottor[i][0],rottor[i][1],rottor[i][2]);
		glutSolidTorus(0.03,torsize[i] + 0.03,10,100);
		glPopMatrix();
	}
	glColor3fv(color[i]);
	glTranslatef(rev[0],rev[1],rev[2]);
	if(objrev==1)
		glutWireSphere(0.4,10,10);
	else if(objrev==2)
		glutWireCube(0.7);
	else if(objrev==3)
	{
		glScalef(0.5,0.5,0.5);
		glutWireOctahedron();
	}
}
//extra 

void init(void)
{


   	glClearColor (0.0, 0.0, 0.0, 0.0);
   	glShadeModel (GL_SMOOTH);
   	glEnable(GL_DEPTH_TEST);
   	// Lighting is added to scene
   	glLightfv(GL_LIGHT1 ,GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1 ,GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1 ,GL_POSITION, LightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);


	   Cylinder = gluNewQuadric();
	   gluQuadricDrawStyle( Cylinder, GLU_FILL);
	   gluQuadricNormals( Cylinder, GLU_SMOOTH);
	   gluQuadricOrientation( Cylinder, GLU_OUTSIDE);
	   gluQuadricTexture( Cylinder, GL_TRUE);

	   Disk = gluNewQuadric();
	   gluQuadricDrawStyle( Disk, GLU_FILL);
	   gluQuadricNormals( Disk, GLU_SMOOTH);
	   gluQuadricOrientation( Disk, GLU_OUTSIDE);
	   gluQuadricTexture( Disk, GL_TRUE);


}

void Draw_gear( void )
{

	int i;
	glPushMatrix();
	gluCylinder(Cylinder, 2.5, 2.5, 1, 16, 16);
	gluDisk(Disk, 0, 2.5, 32, 16);
	glTranslatef(0,0,1);
    	gluDisk(Disk, 0, 2.5, 32, 16);
	glPopMatrix();
    	for( i = 0; i < 8; i++)
	{
	    	glPushMatrix();
		glTranslatef( 0.0, 0.0, 0.50);
		glRotatef( (360/8) * i, 0.0, 0.0, 1.0);
		glTranslatef( 3.0, 0.0, 0.0);
		glutSolidCube( 1.0 );
		glPopMatrix();
	}


}

void Draw_clock( GLfloat cx, GLfloat cy, GLfloat cz )
{

	  int hour_ticks , sec_ticks;
	  glPushMatrix();
	  glTranslatef(cx,cy,cz);
	  glRotatef( 180, 1.0, 0.0, 0.0);

	  glPushMatrix(); // Draw large wire cube (outside of disk clock)
	  glColor3f(1.0, 1.0, 1.0);
	  glTranslatef( 0.0, 0.0, 6.0);
	  glutWireCube(14.0);
	  glPopMatrix();

	  glPushMatrix(); // Draw clock face
	  glTranslatef( 0, 0, 1.0);
	  gluDisk(Disk, 0, 6.75, 32, 16);
	  glColor3f(0.7176470588,0.431372549,0.4745098039);
	  glPopMatrix();

	  glPushMatrix();// Draw hour hand
	  glColor3f(0.8980392157,0.8941176471,0.8862745098);
	  glTranslatef( 0, 0, 0.0);
	  glRotatef( (360/12) * newtime->tm_hour  + (360/60) * (60 / (newtime->tm_min+1)), 0.0, 0.0, 1.0);
	  glPushMatrix();
	  glTranslatef(0.0, 0.0, 2.0);
	  Draw_gear();
	  glPopMatrix();
	  glRotatef( 90, 1.0, 0.0, 0.0);
	  gluCylinder(Cylinder, 0.75, 0, 4, 16, 16);
	  glPopMatrix();

	  glPushMatrix();// Draw minute hand
	  glColor3f(0.831372549,0.6862745098,0.2156862745);
	  glTranslatef( 0, 0, 0.0);
	  glRotatef( (360/60) * newtime->tm_min, 0.0, 0.0, 1.0);
	  glPushMatrix();
	  glTranslatef(0.0, 0.0, 3.0);
	  glScalef(0.5, 0.5, 1.0);
	  Draw_gear();
	  glPopMatrix();
	  glRotatef( 90, 1.0, 0.0, 0.0);
	  gluCylinder(Cylinder, 0.5, 0, 6, 16, 16);
	  glPopMatrix();

	  glPushMatrix();// Draw second hand
	  glColor3f(1.5, 3.0, 1.5);
	  glTranslatef( 0, 0, -0.0);
	  glRotatef( (360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
	  glPushMatrix();
	  glTranslatef(0.0, 0.0, 4.0);
	  glScalef(0.25, 0.25, 1.0);
	  Draw_gear();
	  glPopMatrix();
	  glRotatef( 90, 1.0, 0.0, 0.0);
	  gluCylinder(Cylinder, 0.25, 0, 6, 16, 16);
	  glPopMatrix();


	  for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
		  {
		  glPushMatrix();// Draw next arm axis.
	      glColor3f(0.0, 1.0, 1.0); // give it a color
		  glTranslatef(0.0, 0.0, 0.0);
		  glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);
	      glTranslatef( 6.0, 0.0, 0.0);
		  glutSolidCube(1.0);

	      glPopMatrix();
	  }
	  
	  for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
		 {
	   	glPushMatrix();
		glTranslatef(0.0, 0.0, 0.0);
		glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
		glTranslatef(6.0, 0.0, 0.0);
		glutSolidCube(0.25);
		glPopMatrix();
		}


	  glPopMatrix();

}

void num()
{
    if(view_state == 1)
	{
	glColor3f( 0.0, 0.0, 1.0);
	Sprint(-6.2,-0.2,"9"); //counting from center
	Sprint(-0.2,-6.2,"6"); 
	Sprint(-0.4,5.7,"12");
	Sprint(5.8,-0.2,"3");
	}
}

void about()
{
    //glClear(GL_COLOR_BUFFER_BIT);
	glColor3f( 1.0, 1.0, 1.0);
    Sprint(-5,-2,"This project implements the clock");
	Sprint(-5,-2.8,"   Both Wall clock and digit clock");
	Sprint(-5,-3.6,"               is displayed");
    Sprint(-5,-4.4,"   Clock shows the local time");
	Sprint(-5,-5.2,"    fetching from computer");
	//glFlush(); 
}

void display_clock()
{
		time(&ltime); // Get time
	  newtime = localtime(&ltime); // Convert to local time

	  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  // easy way to put text on the screen.
	  glMatrixMode (GL_PROJECTION);
	  glLoadIdentity();
	  glOrtho(-8.0, 8.0, -8.0, 8.0, 1.0, 60.0);
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  glDisable(GL_LIGHTING);
	  glDisable(GL_COLOR_MATERIAL);

	  // Put view state on screen
	  glColor3f( 1.0, 1.0, 1.0);
	  if (view_state == 0 && about_int==0)
		  {
		  Sprint(-3, -4, "Perspective view");
		  }
	  else if (view_state != 0 && about_int==0)
	  {
		  Sprint(-2, -4, "Ortho view");
	  }
	  else 
	  {
		  about();
	  }


	      Sprint(-4,-7.7, asctime(newtime));

	  // Turn Perspective mode on/off
	  if (view_state == 0)
	     {
	     glMatrixMode (GL_PROJECTION);
	     glLoadIdentity();

	     gluPerspective(60.0, 1, 1.0, 60.0);
	     glMatrixMode(GL_MODELVIEW);
	     glLoadIdentity();
	     gluLookAt( rx, 0.0, rz, 0.0, 0.0, -14.0, 0, 1, 0);
		 }

		if (light_state == 1)
		  {
		   glEnable(GL_LIGHTING);
		   glEnable(GL_COLOR_MATERIAL);  // Enable for lighing
	      }else
		  {
		  glDisable(GL_LIGHTING);
		  glDisable(GL_COLOR_MATERIAL);  // Disable for no lighing
	  }

	Draw_clock( 0.0, 0.0, -14.0);
	num();
	glutSwapBuffers();
}
//extra


void strokeString(float x,float y,float sx,float sy,char *string,int width)
{
	char *c;
	glLineWidth(width);
	glPushMatrix();
	glTranslatef(x,y,0);
	glScalef(sx,sy,0);
	for (c=string; *c != '\0'; c++) 
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

void display3()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glClearColor(0.439216,0.858824,0.576471,1.0);
	glColor3f(0.6,0.6,0);
	strokeString(270,870,0.18,0.18,"BANGALORE INSTITUTE OF TECHNOLOGY",2);
	glColor3f(1,0,0);
	strokeString(130,750,0.3,0.3,"DEPARTMENT OF COMPUTER SCIENCE",4);
	strokeString(330,670,0.3,0.3,"AND ENGINEERING",4);
	strokeString(200,500,0.3,0.3,"AN OPENGL MINI PROJECT ON",2);
	glColor3f(0,0.5,1);
	strokeString(50,420,0.43,0.4,"Designer Clock",6);
	
	glColor3f(0,0.5,0);
	strokeString(150,280,0.23,0.23,"Press (Left Click and Maximize the window) to",2);
	strokeString(350,240,0.23,0.23,"start the simulation",2);
	glColor3f(0,0.5,1);
	strokeString(50,120,0.18,0.18,"Sharath R ",2);
	strokeString(50,80,0.18,0.18,"1BI15CS199",2);
	strokeString(750,120,0.2,0.2,"Prof. Thanuja N",2);
	strokeString(750,80,0.2,0.2,"Prof. Pooja. R",2);
	
	glColor3f(1,0,0);
	strokeString(50,160,0.15,0.15,"By:",2);
	strokeString(750,160,0.15,0.15,"Under the guidance of ",2);
	glPopMatrix();	
	glutSwapBuffers();
}

void display2()
{
	if(flag==0)
		display3();
	else if(flag==1)
	{
		display();
		glEnable(GL_DEPTH_TEST);
	}
	glutPostRedisplay();
}
//extra

void display(void)
{
   glClear(GL_COLOR_BUFFER_BIT);
	 display_clock();
	 glFlush();
}

void reshape (int w, int h)
{
	   //extra
	   glClearColor(0.0,0.0,0.0,1.0);
	   
	   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	   glMatrixMode (GL_PROJECTION);
	   glLoadIdentity();
		//extra	
		if(flag==0)
			glOrtho(0,1000,0,1000,-1,1);
		else
		{
			if(w<=h)
				glOrtho(-8.0,8.0,-8.0*(GLfloat)h/(GLfloat)w,8.0*(GLfloat)h/(GLfloat)w,-8.0,16.0);
			else
				glOrtho(-8.0*(GLfloat)w/(GLfloat)h,8.0*(GLfloat)w/(GLfloat)h,-8.0,8.0,-8.0,16.0);
		}
		glMatrixMode(GL_MODELVIEW);
		//extra
	   
}

//extra
void sub_menu1(int id)					//Sub Menu definition.
{
	glutDisplayFunc(display);
	switch(id)
	{
		case 1: m=1;
			break;
		case 2: m=2;
			break;
		case 3: m=3;
			break;
		case 4: m=4;
			break;
		case 5: m=5;
			break;
		case 6: m=6;
			break;
		case 7: m=7;
			break;
		case 8: m=8;
			break;
	}
}
void sub_menu2(int id)					//Sub Menu definition.
{
	switch(id)
	{
		case 1:revolution=1;
			glutIdleFunc(display);
			break;
		case 2:revolution=0;
			glutIdleFunc(display);
			break;
	}
}

void sub_menu3(int id)					//Sub Menu definition.
{
	glutDisplayFunc(display);
	switch(id)
	{
		case 1: ringflag=1;
			break;
		case 2: ringflag=0;
			break;
	}
}

//extra 

void options(int id)
{
	 switch(id)
	 {
	  
	  case 1:
		  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		about_int= abs(about_int - 1);
		  break;
	  case 2:
		  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		  view_state = abs(view_state - 1);
		  break;
	  case 3:
		  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		   light_state = abs(light_state - 1);
	      break;
	  case 4 :
		  exit(0);
	 }
 }

int main(int argc, char** argv)
{
	   glutInit(&argc, argv);
	   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	   glutInitWindowSize (500, 500);
	   glutInitWindowPosition (50, 50);
	   glutCreateWindow (argv[0]);
	   glutSetWindowTitle("Clock");
	   init ();
	   glutCreateMenu(options);
	   glutAddMenuEntry("About the Project",1);
	   glutAddMenuEntry("Toggle Ortho/Perspective view",2);
	   glutAddMenuEntry("Light on/off",3);
	   glutAddSubMenu("Revolution",sub1);
	 	glutAddSubMenu("Rings of Revolution",sub2);
	 	glutAddSubMenu("No. of Revolving Objects",sub3);
	   glutAddMenuEntry("Quit",4);

	   //extra
	   sub1=glutCreateMenu(sub_menu1);

		glutAddMenuEntry("One",1);
		glutAddMenuEntry("Two",2);
		glutAddMenuEntry("Three",3);
		glutAddMenuEntry("Four",4);
		glutAddMenuEntry("Five",5);
		glutAddMenuEntry("Six",6);
		glutAddMenuEntry("Seven",7);
		glutAddMenuEntry("Eight",8);




	   sub2=glutCreateMenu(sub_menu2);

		glutAddMenuEntry("Yes",1);
		glutAddMenuEntry("No",2);

	   sub3=glutCreateMenu(sub_menu3);

		glutAddMenuEntry("On",1);
		glutAddMenuEntry("Off",2);
	//extra

	   glutAttachMenu(GLUT_RIGHT_BUTTON);
	   glutDisplayFunc(display2);
	   //extra
	   glutMouseFunc(mouse);

	   glutReshapeFunc(reshape);
	   glutTimerFunc( 10, TimeEvent, 1);
	   glutMainLoop();
	   return 0;
}

