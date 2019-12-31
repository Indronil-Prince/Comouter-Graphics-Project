#include <windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include<bits/stdc++.h>
#include <stdlib.h>
#include<math.h>
#include "RGBpixmap.cpp"

float erer; // Spotlight cone half-angle.
static float xMove = 0.0, zMove = 0.0; // Movement components.
static float spotExponent = 2.0;
static int WindowSizX=1260, WindowSizY=680;
float flag=0,spotAngle = 3.0, degree=0, deg=0,theta=0,uu=25,s=200,s1=40, s2=100,s3=0,de=0,limp=0,limy=0,limr=0,x=0,i=0,ra=20,degree1=0, degree2=0,l=-3,r=-1,f=-19, sc=0.5,eyex=0,eyey=0,eyez=0,centerx=0,centery=0,centerz=-14,upx=0,upy=1,upz=0;
RGBpixmap pix[8];
/* GLUT callback Handlers */
const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { -3.0f, 15.0f, 0.0f, 0.0f };

const GLfloat light_ambient1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_diffuse1[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position1[] = { 15.0f, 15.0f, 15.0f, 1.0f };

const GLfloat mat_ambient[]    = { 1.0f, 0.0f, 0.0f, 0.0f };
const GLfloat mat_diffuse[]    = { 1.0f, 0.0f, 0.0f, 0.0f };
const GLfloat mat_specular[]   = { 1.0f, 0.0f, 0.0f, 0.0f };
const GLfloat high_shininess[] = { s };

const GLfloat mat_ambient1[]    = { 0.0f, 0.60f, 0.6f, 1.0f };
const GLfloat mat_diffuse1[]    = { 0.0f, .50f, 0.0f, 1.0f };
const GLfloat mat_specular1[]   = { 0.80f, .50f, 1.0f, 1.0f };
float high_shininess1[] = { s1 , 0};

const GLfloat mat_ambient2[]    = { 1.0f, .0f, 1.0f, 1.0f };
const GLfloat mat_diffuse2[]    = { .0f, 1.0f, 0.0f, 1.0f };
const GLfloat mat_specular2[]   = { 0.80f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess2[] = { s2 };

const GLfloat mat_ambient3[]    = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat mat_diffuse3[]    = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat mat_specular3[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess3[] = { s3 };

float ligdir[3] = { -1, -1, -2};;


  static inline void set_material(GLfloat c[], GLfloat s[], GLfloat sh[]){
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
    glMaterialfv(GL_FRONT, GL_SPECULAR, s);
    glMaterialfv(GL_FRONT, GL_SHININESS, sh);

}
static GLfloat carpet_bg_mat_color[] = { 0, 0, 0, 1 };
static GLfloat carpet_bg_mat_spec[] = { 0, 0, 0, 1 };
static GLfloat carpet_bg_mat_shininess[] = { 180 };

static GLfloat carpet_mat_color[] = { 1, 1, 1, 1 };
static GLfloat carpet_mat_spec[] = { 1, 1, 1, 1 };
static GLfloat carpet_mat_shininess[] = { 180 };

static void _carpet_recursive(int level, GLdouble t, GLdouble b, GLdouble l, GLdouble r){
    if (level <= 0)
    {
        glVertex3d(l, t, 0.01);
        glVertex3d(l, b, 0.01);
        glVertex3d(r, b, 0.01);
        glVertex3d(r, t, 0.01);
        return;
    }

    GLdouble frstX = l + (r-l)*1/3.0;
    GLdouble frstY = t + (b-t)*1/3.0;
    GLdouble secX = l + (r-l)*2/3.0;
    GLdouble secY = t + (b-t)*2/3.0;

    GLdouble x[4] = {l, frstX, secX, r};
    GLdouble y[4] = {t, frstY, secY, b};

    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            if (i==1 && j==1) continue;
            _carpet_recursive(level-1, y[i], y[i+1], x[j], x[j+1]);
        }
    }
}
static void carpet(int level){
    set_material(carpet_bg_mat_color, carpet_bg_mat_spec, carpet_bg_mat_shininess);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        glVertex3f(-0.5, -0.5, 0);
        glVertex3f(0.5, -0.5, 0);
        glVertex3f(0.5, 0.5, 0);
        glVertex3f(-0.5, 0.5, 0);
    glEnd();

    set_material(carpet_mat_color, carpet_mat_spec, carpet_mat_shininess);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);
        _carpet_recursive(level, 0.4, -0.4, -0.4, 0.4);
    glEnd();
}
static void resize(int width, int height){
    const float ar = (float) width / (float) height;

    glViewport(0,0, width-10, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}
void sphere(){
      glPushMatrix();
//    glViewport(0,0,width/2,height/2);
    glTranslated(0,0,0);
    glutSolidSphere(.6,16,16);
    glPopMatrix();
}
void OwnScalef(GLfloat x, GLfloat y, GLfloat z){
    GLfloat m[16];
    m[0]=x;
    m[1]=0;
    m[2]=0;
    m[3]=0;
    m[4]=0;
    m[5]=y;
    m[6]=0;
    m[7]=0;
    m[8]=0;
    m[9]=0;
    m[10]=z;
    m[11]=0;
    m[12]=0;
    m[13]=0;
    m[14]=0;
    m[15]=1;
    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);
}
void halfcircle(){
    glBegin(GL_POLYGON);

    double r=.5,h=1;

    for(float x=-r; x<r; x+=0.010)
    {
        glVertex3f(x,0,sqrt(r*r-x*x));
    }
    for(float x=r; x>-r; x-=0.010)
    {
        glVertex3f(x,0,sqrt(r*r-x*x));
    }

    glVertex3f(-r,0,0);
    glEnd();

}
void cylinder(){
    glBegin(GL_QUADS);
    int limit = 360;

    double x,r=.5,h=1;


    for(int i=limit; i>0;)
    {
        x = i*3.1416/180;
        glVertex3f(r*cos(x),h,r*sin(x));
        glVertex3f(r*cos(x),0,r*sin(x));
        i-=10;
        x = i*3.1416/180;
        glVertex3f(r*cos(x),0,r*sin(x));
        glVertex3f(r*cos(x),h,r*sin(x));
    }

    glEnd();
}
void cube(){
	glBegin(GL_QUADS);
	// top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	// front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);

	glEnd();

	glBegin(GL_QUADS);
	// right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	// left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	// bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);

	glEnd();

	glBegin(GL_QUADS);
	// back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);

	glEnd();
}
void roll(){
    glPushMatrix();
    /*glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular3);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess3);
*/
   glTranslated(0,0,0);


    OwnScalef(.8,3,.8);
    cylinder();
    glPopMatrix();
    glPushMatrix();
       glTranslated(0,-2,0);

    OwnScalef(.7,.8,.8);
    sphere();
    glPopMatrix();

     glPushMatrix();
       glTranslated(0,-4.6,0);

    OwnScalef(.7,.8,.8);
   sphere();
    glPopMatrix();
}
void jow(){
    glPushMatrix();
    glTranslated(17,-1,4);
    glRotated(45,0,0,1);
    glRotated(-20,1,0,0);
    glScalef(1,1.5,1);
    roll();
    glPopMatrix();
    glPushMatrix();
    glTranslated(14,-1,4);
     glRotated(20,0,1,0);
    glRotated(45,0,0,-1);
     glScalef(1,1.5,1);
     roll();
    glPopMatrix();
        glPushMatrix();
    glTranslated(16,-1,1.8);
     glRotated(-20,0,1,0);
    glRotated(45,1,0,0);
     glScalef(1,1.5,1);
     roll();
    glPopMatrix();

     glPushMatrix();
     glTranslated(15.5,-7,3.3);
     OwnScalef(1.5,1.5,1.5);
     sphere();


     glPopMatrix();

}
void ellipse(){
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular2);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess2);

    glPushMatrix();
    glScalef(.8,5,.8);
    glutSolidSphere(1,16,16);

    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
    glMaterialf(GL_FRONT, GL_SHININESS, s3);

    glPushMatrix();
    glTranslatef(0,4.5,0);
    glutSolidSphere(.6,16,16);

    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-4.5,0);
    glutSolidSphere(.6,16,16);

    glPopMatrix();
}
void jack(){


    glPushMatrix();
    glTranslatef(15.5,-.8,4.4);
    glRotated(45,1,0,0);
//    glRotated(65,0,1,0);
    glScalef(.8,.8,.8);
    ellipse();
    glPopMatrix();


    glPushMatrix();
   glTranslatef(15.5,-.8,4.4);
     glRotated(120,0,1,0);
    glRotated(45,1,0,0);


    glScalef(.8,.8,.8);
    ellipse();
    glPopMatrix();

     glPushMatrix();
   glTranslatef(15.5,-.8,4.4);
   glRotated(240,0,1,0);
    glRotated(45,1,0,0);


    glScalef(.8,.8,.8);
    ellipse();
    glPopMatrix();
}
void jack_place(){
    glPushMatrix();
    glTranslatef(8,.5,2);
    glScaled(.5,.5,.5);
    jack();
    glPopMatrix();
}
void table(){
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTranslated(-2,-2.3,-2);
    OwnScalef(21,1,8);
    glRotated(90,1,0,0);
    glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
    //stand
    glPushMatrix();
    glTranslated(-2,-2,-2);
    OwnScalef(1,-6,1);
    glBindTexture(GL_TEXTURE_2D,3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
	glTranslated(-2,-2,5);
    OwnScalef(1,-6,1);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslated(18,-2,-2);
    OwnScalef(1,-6,1);
    glBindTexture(GL_TEXTURE_2D,3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslated(18,-2,5);
    OwnScalef(1,-6,1);
    glBindTexture(GL_TEXTURE_2D,3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
void house(){

    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,4);
	glTranslated(-10,-8,-8);
    OwnScalef(40,.5,18);
    glRotated(90,1,0,0);
	glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    glPushMatrix();
    glTranslated(-10,-8,-8);
    OwnScalef(40,20,.5);
    glBindTexture(GL_TEXTURE_2D,2);
    glEnable(GL_TEXTURE_2D);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-10,-8,-8);
    OwnScalef(.5,20,18);
    glBindTexture(GL_TEXTURE_2D,2);
    glEnable(GL_TEXTURE_2D);
    glRotated(-90,0,1,0);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,5);
	glEnable(GL_TEXTURE_2D);
	glTranslated(5,3,-7.5);
    OwnScalef(5,5,1);
    cube();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D,6);
	glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslated(4.5,3,-7.5);
    OwnScalef(0.5,5,1);
    cube();
    glPopMatrix();
    glPushMatrix();
    glTranslated(10,3,-7.5);
    OwnScalef(0.5,5,1);
    cube();
    glPopMatrix();
    glPushMatrix();
    glTranslated(4.5,2.5,-7.5);
    OwnScalef(6,0.5,1);
    cube();
    glPopMatrix();
    glPushMatrix();
    glTranslated(4.5,8,-7.5);
    OwnScalef(6,0.5,1);
    cube();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void wings(){
    //wings
    glPushMatrix();
    glTranslated(2.8,5.5,1.5);
    OwnScalef(4,0.01,.8);
    //glcolor3f(0.0,0,0.0);
    cube();

    glPopMatrix();
    glPushMatrix();
    glTranslated(4.5,5.5,-.2);
    OwnScalef(0.8,0.01,4);
    //glcolor3f(0.0,0,0.0);
    cube();
    glPopMatrix();
    //halfcircle in wings
    glPushMatrix();
    glTranslated(4.9,5.5,-.2);
    glScaled(0.8,0.01,-.8);
    //glcolor3f(.8,1,.8);
    halfcircle();
    glPopMatrix();
    glPushMatrix();
    glTranslated(4.9,5.5,3.79);
    glScaled(0.8,0.01,.8);
    //glcolor3f(0.8,.8,.8);
    halfcircle();
    glPopMatrix();
    glPushMatrix();
    glTranslated(2.8,5.5,1.9);
    glRotated(90,0,0,1);
    glRotated(90,0,1,0);
    glRotated(90,1,0,0);
    glScaled(0.8,0.01,-.8);
    //glcolor3f(0.8,1,0.8);
    halfcircle();
    glPopMatrix();
    glPushMatrix();
    glTranslated(6.8,5.5,1.9);
    glRotated(90,0,0,1);
    glRotated(90,0,1,0);
    glRotated(90,1,0,0);
    glScaled(0.8,0.01,.8);
    //glcolor3f(0.8,1,0.8);
    halfcircle();
    glPopMatrix();
}
void helicopter(const double a){

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular3);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess3);

    glBindTexture(GL_TEXTURE_2D,8);
	glEnable(GL_TEXTURE_2D);

    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,1.0,0.0);
    glVertex3f(4.0,4.0,0.0);
    glVertex3f(6.0,4.0,0.0);
    glVertex3f(6.0,0.0,0.0);
    glEnd();
    glBegin(GL_POLYGON);

    //glcolor3f(1,0,1);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(6.0,0.0,0.0);
    glVertex3f(6.0,4.0,0.0);
    glVertex3f(4.0,4.0,0.0);
    glVertex3f(0.0,1.0,0.0);


    glEnd();
    glBegin(GL_POLYGON);
    //glcolor3f(1,0,1);
    glVertex3f(0.0,0.0,4.0);
    glVertex3f(6.0,0.0,4.0);
    glVertex3f(6.0,4.0,4.0);
    glVertex3f(4.0,4.0,4.0);
    glVertex3f(0.0,1.0,4.0);

    glEnd();
    glBegin(GL_POLYGON);
    //glcolor3f(1,0,1);
    glVertex3f(0.0,0.0,4.0);
    glVertex3f(0.0,1.0,4.0);
    glVertex3f(4.0,4.0,4.0);
    glVertex3f(6.0,4.0,4.0);
    glVertex3f(6.0,0.0,4.0);

    glEnd();


    glPushMatrix();
    glTranslated(1,-1.21,0.0);
    glScaled(4,0.4,1);
    //glcolor3f(1,0,0);
    cube();
    glPopMatrix();
    //stand
    glPushMatrix();
    glTranslated(2.5,-1.2,.25);
    glScaled(1.2,1.201,.25);
    //glcolor3f(1,0,1);
    cube();
    glPopMatrix();
//lowerplane
    glPushMatrix();
    glTranslated(1,-1.21,3.25);
    glScaled(4,0.4,1);
    //glcolor3f(1,0,0);
    cube();
    glPopMatrix();
    //stand
    glPushMatrix();
    glTranslated(2.5,-1.2,3.75);
    glScaled(1.2,1.201,.25);
    //glcolor3f(1,0,1);
    cube();
    glPopMatrix();
   //front
    glPushMatrix();
    glTranslated(-.01,0.0,0.0);
    glScaled(0.1,1.0,4);
    //glcolor3f(1,0,1);
    cube();
    glPopMatrix();


    glPushMatrix();
    glTranslated(0.0,1.0,0);
    glRotated(36.0,0,0,1);
    glScaled(2.1,0.01,3.99);
    //glcolor3f(0,1,1);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.2,3.50,0);
    glRotated(25.0,0,0,1);
    glScaled(.98,0.01,3.99);
    //glcolor3f(0,1,1);
    cube();
    glPopMatrix();


    //top
    glPushMatrix();
    glTranslated(4.0,4.0,4.0);
    OwnScalef(2,0.01,-4);
    //glcolor3f(0.8,0,0.8);
    cube();
    glPopMatrix();
    //back
    glPushMatrix();
    glTranslated(6.0,0.0,0.0);
    OwnScalef(0.01,4,4);
    //glcolor3f(1,0,1);
    cube();
    glPopMatrix();
    //tail
    glPushMatrix();
    glTranslated(6.01,1.3,1.5);
    OwnScalef(3.9,1.2,1);
    //glcolor3f(0.5,0.5,0);
    cube();
    glPopMatrix();
    //tail verticalcube
    glPushMatrix();
    glTranslated(9.9,1.5,1.8);
    glRotated(43.0,0,0,1);
    OwnScalef(3.05,1,.5);
    //glcolor3f(0.5,0.5,0);
    cube();
    glPopMatrix();

    //floor
    glPushMatrix();
    glTranslated(0.0,0.0,0);
    OwnScalef(6,0.01,4.00);
    //glcolor3f(1,1,0);
    cube();
    glPopMatrix();

    //wings
    glPushMatrix();
    glTranslated(4.9,4,1.9);
    glRotated(a*15,0,1,0);
    glTranslated(-4.9,-4,-1.9);
    wings();
    glPopMatrix();

    //tailwings
    glPushMatrix();
    glScaled(.5,.5,.5);
    glTranslated(23.5,7.9,3.7);

    glRotated(90,1,0,0);
    glRotated(a*15,0,1,0);
    glTranslated(-4.9,-4,-1.8);

    wings();
    glPopMatrix();

//halfcircle in tail

    glPushMatrix();
    glTranslated(11.8,3.92,1.8);
    glRotated(90,0,0,1);
    glRotated(45,0,0,1);
    glRotated(90,1,0,0);
    glRotated(180,0,1,0);
    glScaled(1,.9,-.8);
    //glcolor3f(.2,.2,0);
    halfcircle();
    glPopMatrix();

    glPushMatrix();
    glTranslated(11.8,3.92,2.2);
    glRotated(90,0,0,1);
    glRotated(45,0,0,1);
    glRotated(90,1,0,0);
    glRotated(180,0,1,0);
    glScaled(1,.9,-.8);
    //glcolor3f(.2,.2,0);
    halfcircle();
    glPopMatrix();
//cylinder in tail
    glPushMatrix();
    glTranslated(11.78,3.94,1.8);
    glRotated(90,1,0,0);
    glScaled(1,.5,.85);
    //glcolor3f(.2,.2,0);
    cylinder();
    glPopMatrix();
//cylinder in tail wings

    glPushMatrix();
    glTranslated(11.78,3.94,1.8);
    glRotated(90,1,0,0);
    glScaled(.25,.80,.25);
    //glcolor3f(.2,1,1);
    cylinder();
    glPopMatrix();


//cylinder
    glPushMatrix();
    glTranslated(4.9,4,1.9);
    glScaled(0.5,1.5,0.5);
    //glcolor3f(0.2,0.2,0.2);
    cylinder();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//table

    glDisable(GL_TEXTURE_2D);
    glPushMatrix();

    table();
    glPopMatrix();

//jack
    glPushMatrix();
//ellipse();
    jack_place();
   // jow();

    glPopMatrix();

    glPushMatrix();
    house();
    glPopMatrix();

}
void table_n(){

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glPushMatrix();
    glTranslated(-2,-2.3,-2);
    OwnScalef(21,1,8);
    cube();

    glPopMatrix();
    //stand
    glPushMatrix();
    glTranslated(-2,-2,-2);
    OwnScalef(1,-6,1);
    cube();
    glPopMatrix();

    glPushMatrix();
	glTranslated(-2,-2,5);
    OwnScalef(1,-6,1);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(18,-2,-2);
    OwnScalef(1,-6,1);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(18,-2,5);
    OwnScalef(1,-6,1);
    cube();
    glPopMatrix();
}
void house_n(){

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient1);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse1);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular1);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess1);

	glTranslated(-10,-8,-8);
    OwnScalef(40,.5,18);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-10,-8,-8);
    OwnScalef(40,20,.5);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(-10,-8,-8);
    OwnScalef(.5,20,18);
    cube();
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular3);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess3);
    glPushMatrix();
	glTranslated(5,3,-7.5);
    OwnScalef(5,5,1);
    cube();
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glPushMatrix();
    glTranslated(4.5,3,-7.5);
    OwnScalef(0.5,5,1);
    cube();
    glPopMatrix();
    glPushMatrix();
    glTranslated(10,3,-7.5);
    OwnScalef(0.5,5,1);
    cube();
    glPopMatrix();
    glPushMatrix();
    glTranslated(4.5,2.5,-7.5);
    OwnScalef(6,0.5,1);
    cube();
    glPopMatrix();
    glPushMatrix();
    glTranslated(4.5,8,-7.5);
    OwnScalef(6,0.5,1);
    cube();
    glPopMatrix();
}
void helicopter_n(const double a){

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient3);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse3);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular3);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess3);
    glBegin(GL_POLYGON);

    //glcolor3f(1,0.0,1);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(0.0,1.0,0.0);
    glVertex3f(4.0,4.0,0.0);
    glVertex3f(6.0,4.0,0.0);
    glVertex3f(6.0,0.0,0.0);
    glEnd();
    glBegin(GL_POLYGON);

    //glcolor3f(1,0,1);
    glVertex3f(0.0,0.0,0.0);
    glVertex3f(6.0,0.0,0.0);
    glVertex3f(6.0,4.0,0.0);
    glVertex3f(4.0,4.0,0.0);
    glVertex3f(0.0,1.0,0.0);



    glEnd();
    glBegin(GL_POLYGON);
    //glcolor3f(1,0,1);
    glVertex3f(0.0,0.0,4.0);
    glVertex3f(6.0,0.0,4.0);
    glVertex3f(6.0,4.0,4.0);
    glVertex3f(4.0,4.0,4.0);
    glVertex3f(0.0,1.0,4.0);

    glEnd();
    glBegin(GL_POLYGON);
    //glcolor3f(1,0,1);
    glVertex3f(0.0,0.0,4.0);
    glVertex3f(0.0,1.0,4.0);
    glVertex3f(4.0,4.0,4.0);
    glVertex3f(6.0,4.0,4.0);
    glVertex3f(6.0,0.0,4.0);



    glEnd();


    glPushMatrix();
    glTranslated(1,-1.21,0.0);
    glScaled(4,0.4,1);
    //glcolor3f(1,0,0);
    cube();
    glPopMatrix();
    //stand
    glPushMatrix();
    glTranslated(2.5,-1.2,.25);
    glScaled(1.2,1.201,.25);
    //glcolor3f(1,0,1);
    cube();
    glPopMatrix();
//lowerplane
    glPushMatrix();
    glTranslated(1,-1.21,3.25);
    glScaled(4,0.4,1);
    //glcolor3f(1,0,0);
    cube();
    glPopMatrix();
    //stand
    glPushMatrix();
    glTranslated(2.5,-1.2,3.75);
    glScaled(1.2,1.201,.25);
    //glcolor3f(1,0,1);
    cube();
    glPopMatrix();
//front curve
//    glPushMatrix();
//    glTranslated(2.05,2.38,4.0);
//    glRotatef(38,0,0,1);
//    glRotatef(-90,1,0,0);
//
//    glScaled(5,1.0,1);
//    //glcolor3f(1,0,1);
//    halfcircle();
//    glPopMatrix();
//
//    glPushMatrix();
//    glTranslated(2.05,2.38,0);
//    glRotatef(38,0,0,1);
//    glRotatef(-90,1,0,0);
//
//    glScaled(5,1.0,1);
//    //glcolor3f(1,0,1);
//    halfcircle();
//    glPopMatrix();

//    glPushMatrix();
//    glTranslated(.88,1.55,3.99);
//    glRotatef(38,0,0,1);
//    glRotatef(-90,1,0,0);
//
//    glScalef(2.2,4.0,.5);
//    //glcolor3f(0,1,1);
//    cylinder();
//    glPopMatrix();
//front
    glPushMatrix();
    glTranslated(-.01,0.0,0.0);
    glScaled(0.1,1.0,4);
    //glcolor3f(1,0,1);
    cube();
    glPopMatrix();


    glPushMatrix();
    glTranslated(0.0,1.0,0);
    glRotated(36.0,0,0,1);
    glScaled(2.1,0.01,3.99);
    //glcolor3f(0,1,1);
    cube();
    glPopMatrix();

    glPushMatrix();
    glTranslated(3.2,3.50,0);
    glRotated(25.0,0,0,1);
    glScaled(.98,0.01,3.99);
    //glcolor3f(0,1,1);
    cube();
    glPopMatrix();


    //top
    glPushMatrix();
    glTranslated(4.0,4.0,4.0);
    OwnScalef(2,0.01,-4);
    //glcolor3f(0.8,0,0.8);
    cube();
    glPopMatrix();
    //back
    glPushMatrix();
    glTranslated(6.0,0.0,0.0);
    OwnScalef(0.01,4,4);
    //glcolor3f(1,0,1);
    cube();
    glPopMatrix();
    //tail
    glPushMatrix();
    glTranslated(6.01,1.3,1.5);
    OwnScalef(3.9,1.2,1);
    //glcolor3f(0.5,0.5,0);
    cube();
    glPopMatrix();
    //tail verticalcube
    glPushMatrix();
    glTranslated(9.9,1.5,1.8);
    glRotated(43.0,0,0,1);
    OwnScalef(3.05,1,.5);
    //glcolor3f(0.5,0.5,0);
    cube();
    glPopMatrix();

    //floor
    glPushMatrix();
    glTranslated(0.0,0.0,0);
    OwnScalef(6,0.01,4.00);
    //glcolor3f(1,1,0);
    cube();
    glPopMatrix();

    //wings
    glPushMatrix();
    glTranslated(4.9,4,1.9);
    glRotated(a*15,0,1,0);
    glTranslated(-4.9,-4,-1.9);
    wings();
    glPopMatrix();

    //tailwings
    glPushMatrix();
    glScaled(.5,.5,.5);
    glTranslated(23.5,7.9,3.7);

    glRotated(90,1,0,0);
    glRotated(a*15,0,1,0);
    glTranslated(-4.9,-4,-1.8);

    wings();
    glPopMatrix();


//halfcircle in tail

    glPushMatrix();
    glTranslated(11.8,3.92,1.8);
    glRotated(90,0,0,1);
    glRotated(45,0,0,1);
    glRotated(90,1,0,0);
    glRotated(180,0,1,0);
    glScaled(1,.9,-.8);
    //glcolor3f(.2,.2,0);
    halfcircle();
    glPopMatrix();

    glPushMatrix();
    glTranslated(11.8,3.92,2.2);
    glRotated(90,0,0,1);
    glRotated(45,0,0,1);
    glRotated(90,1,0,0);
    glRotated(180,0,1,0);
    glScaled(1,.9,-.8);
    //glcolor3f(.2,.2,0);
    halfcircle();
    glPopMatrix();
//cylinder in tail
    glPushMatrix();
    glTranslated(11.78,3.94,1.8);
    glRotated(90,1,0,0);
    glScaled(1,.5,.85);
    //glcolor3f(.2,.2,0);
    cylinder();
    glPopMatrix();
//cylinder in tail wings

    glPushMatrix();
    glTranslated(11.78,3.94,1.8);
    glRotated(90,1,0,0);
    glScaled(.25,.80,.25);
    //glcolor3f(.2,1,1);
    cylinder();
    glPopMatrix();


//cylinder
    glPushMatrix();
    glTranslated(4.9,4,1.9);
    glScaled(0.5,1.5,0.5);
    //glcolor3f(0.2,0.2,0.2);
    cylinder();
    glPopMatrix();

//table


    glPushMatrix();

    table_n();
    glPopMatrix();

//jack
    glPushMatrix();
//ellipse();
    jack_place();
   // jow();

    glPopMatrix();

    glPushMatrix();
    house_n();
    glPopMatrix();

}
static void display(void){
 const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glcolor3d(1,0,0);

 glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt( eyex, eyey, eyez, centerx, centery, centerz, upx, upy,upz);
//utiu
    glPushMatrix();
    glViewport(0,200,WindowSizX/2, WindowSizY/2);
    glTranslated(l,r,f);
    glRotated(degree,1,0,0);
    glRotated(degree1,0,1,0);
    glRotated(degree2,0,0,1);

    glScalef(sc,sc,sc);
    helicopter(a);
    glPushMatrix();
        glTranslated(-9.8, 2, 1.8);
        glRotated(90, 0, 1, 0);
        glScaled(16.5,20,32);
        carpet(3);
    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glViewport(WindowSizX/2,200,WindowSizX/2, WindowSizY/2);
    glTranslated(l,r,f);
    glRotated(degree,1,0,0);
    glRotated(degree1,0,1,0);
    glRotated(degree2,0,0,1);

    glScalef(sc,sc,sc);

    helicopter_n(a);

    glPopMatrix();
glutSwapBuffers();
}
static void key(unsigned char key, int x, int y){
    switch (key)
    {
    case 'q':
        exit(0);
        break;
    case 'a':
        degree+=2.5;
        break;
    case 'b':
        degree-=2.5;
        break;
    case 'c':
        degree1+=2.5;
        break;
    case 'd':
        degree1-=2.5;
        break;
    case 'D':
        deg+=30.0;
        break;
    case 'e':
        degree2+=2.5;
        break;
    case 'f':
        degree2-=2.5;
        break;

    case '+':
        sc+=.1;
        break;
    case '-':
        sc-=.1;
        break;

    case 'g':
        l+=.1;
        deg+=30;
        break;
    case 'i':
        r+=.1;
        break;
    case 'k':
        f+=.1;
        break;
    case 'h':
        l-=.1;
        deg+=30;
        break;
    case 'j':
        r-=.1;
        break;
    case 'l':
        f-=0.1;
        break;
    case 'm':
        eyex+=.1;
        break;
    case 'n':
        eyey+=.1;
        break;
    case 'o':
        eyez+=.1;
        break;
    case 'p':
        centerx+=.1;
        break;
    case 'r':
        centery+=.1;
        break;
    case 's':
        centerz+=.1;
        break;
    case 't':
        upx+=.1;
        break;
    case 'u':
        upy+=.1;
        break;
    case 'v':
        upz+=.1;
        break;

    case 'M':
        eyex-=.1;
        break;
    case 'N':
        eyey-=.1;
        break;
    case 'O':
        eyez-=.1;
        break;
    case 'P':
        centerx-=.1;
        break;
    case 'R':
        centery-=.1;
        break;
    case 'S':
        centerz-=.1;
        break;
    case 'T':
        upx-=.1;
        break;
    case 'U':
        upy-=.1;
        break;
    case 'V':
        upz-=.1;
        break;
    case 'B':
        limy+=5;
        theta=(3.1416*limy)/180;
        centerx=5*sin(theta);

       // upz=0;
        //eyex=0;
       // eyez=0;//centery=0;
        break;
    case 'C':
        limp+=5;
        theta=(3.1416*limp)/180;
        centery=5*sin(theta);
       // upz=0;
       // eyex=0;
       //eyez=0;
        //centerx=0;
        break;
    case 'E':
        limr+=5;theta=(3.1416*limr)/180;
        // upz=20*cos(theta);
        //centerx=0.1;
        //eyex=0;
       // eyez=0;

        upx=sin(theta);
        upy=cos(theta);

        break;
    case 'W':

        theta=(3.1416*i)/180;
        eyex=14*sin(theta);
        eyez=14*cos(theta)-14;
        i+=5;
        //deg+=30.0;
        upx=0;
        upy=1;
        upz=0;
       // std::cout<<centerx<<centery<<centerz;
        break;

    case 'F':
        glEnable(GL_LIGHT0);
        break;
   case 'G':
        glDisable(GL_LIGHT0);
        break;
    case 'H':
        s3++;
        break;
    case 'I':
        glEnable(GL_LIGHT2);
        break;
     case 'J':
        glDisable(GL_LIGHT2);
        break;

    }
    glutPostRedisplay();
}
static void idle(void){
    glutPostRedisplay();
}
void Init(){
    pix[0].makeCheckImage();
	pix[0].setTexture(1);

	pix[1].readBMPFile("C:\\Users\\INDRONIL\\Desktop\\11\\hw\\brick.bmp");
	pix[1].setTexture(2);

	pix[2].readBMPFile("C:\\Users\\INDRONIL\\Desktop\\11\\hw\\wood.bmp");
	pix[2].setTexture(3);

	pix[3].readBMPFile("C:\\Users\\INDRONIL\\Desktop\\11\\hw\\floor.bmp");
	pix[3].setTexture(4);

    pix[4].readBMPFile("C:\\Users\\INDRONIL\\Desktop\\11\\hw\\flower.bmp");;
	pix[4].setTexture(5);

    pix[5].readBMPFile("C:\\Users\\INDRONIL\\Desktop\\11\\hw\\wood (2).bmp");;
	pix[5].setTexture(6);

	pix[6].readBMPFile("C:\\Users\\INDRONIL\\Desktop\\11\\hw\\jake.bmp");;
	pix[6].setTexture(7);

	pix[6].readBMPFile("C:\\Users\\INDRONIL\\Desktop\\11\\hw\\heli.bmp");;
	pix[6].setTexture(8);
}
/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(WindowSizX, WindowSizY);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
//    glutSpecialFunc(processSpecialKeys);
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    glEnable(GL_NORMALIZE);
    //glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT2);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT2, GL_AMBIENT,  light_ambient1);
    glLightfv(GL_LIGHT2, GL_DIFFUSE,  light_diffuse1);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular1);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, ligdir);

    Init();
    glutMainLoop();

    return EXIT_SUCCESS;
}

