#include<iostream>
#include<windows.h>
#include<GL/glut.h>

#include<math.h>
using namespace std;

//# define PI           3.1415926535   8979323846


GLfloat position = 0.0f,position2=0, pos=.1,pos2=.1,pos3=.1,PI=3.1416;

GLfloat cx,cy,x1,y11,x2,y2,x3,y3,x4,y4,radiusCannon,radiusBall,angleCannon=0,dif=-.8,r=0,xBall=0,yBall=0,rad=.3;
GLfloat x5,y5,x6,y6,x7,y7,x8,y8,x9,y9,x10,y10,x11,y111,x12,y12,x13,y13,x14,y14,x15,y15,x16,y16,x17,y17,x18,y18,x19,y19;
double oldx=rad*cos((angleCannon/180)*PI);
double    oldy=rad*sin((angleCannon/180)*PI);
int score=0;
//diff is the difference between the original center of cannon and the translated center
//r is for shooting the ball

GLfloat canonLeverx1,canonLevery1,canonLeverx2,canonLevery2,canonLeverx3,canonLevery3,canonLeverx4,canonLevery4,radiusCannonLever,cannonCenterX,cannonCenterY;
GLfloat line,fire=1001;
int valueC=1,value1=1,value2=1,i=0,value3=1,value4=1,value5=1,value6=1;
int running=1;
GLfloat speed = 0.0f,speed2=0;


double newx,newy;

void timer();
void sound();
void Idle(){


glutPostRedisplay();


}



bool onSegment(GLfloat x,GLfloat y,GLfloat x2,GLfloat y2,GLfloat ctx,GLfloat cty,GLfloat len){


GLfloat distX=x-ctx;
GLfloat distY=y-cty;
GLfloat dist1=sqrt( (distX*distX) + (distY*distY) );

 distX=x2-ctx;
 distY=y2-cty;
GLfloat dist2=sqrt( (distX*distX) + (distY*distY) );

if(dist1+dist2<=len+.01 && dist1+dist2>=len-.01 )
    return true;
    else return false;

}

int collisionDetection(GLfloat x,GLfloat y,GLfloat x2,GLfloat y2,GLfloat cx1,GLfloat cy1){


 GLfloat distX = x - x2;
    GLfloat distY = y - y2;
    GLfloat len = sqrt( (distX*distX) + (distY*distY) );//length of line


    float dot = ( ((cx1-x)*(x2-x)) + ((cy1-y)*(y2-y)) ) / pow(len,2);


    float closestX = x + (dot * (x2-x));
    float closestY = y + (dot * (y2-y));

    bool result=onSegment(x,y,x2,y2,closestX,closestY,len);//clossest point on line
float distance;
    if(result){


        distX = closestX - cx1;
        distY = closestY - cy1;
 distance = sqrt( (distX*distX) + (distY*distY) );
        if (distance <= radiusBall)
            return 0;
        else return 1;
    }
return 1;
}

void update(int value) {
//if ball makes contact with any plane
    if(!value1||!value2||!value3||!value4||!value5||!value6)
        valueC=0;

    if((position+xBall+dif >1)||((position2+yBall+dif >1))){
        //if ball runs into wall
        position = 0;
        position2 = 0;
        r=0;
      //  rad=0;

     //   newx=xBall;
     //   newy=yBall;
    }

   // if(position+xBall+dif <-1.7 ){
//to make ball stop moving
    if(!valueC){
        position=0;
        position2=0;
        r=0;
        valueC=1;

    }

    if (pos<-1.7)
        pos=1;
    else if (value1==0 || value2==0){
             pos=1;
             score+=2;
             //if there is collision with ball
    }

    if (pos2<-1.7)
        pos2=1;
    else if (value3==0 || value4==0){
             pos2=1;
             score+=5;
             //if there is collision with ball
    }
     if (pos3<-1.7)
        pos3=1;
     else if (value5==0 || value6==0){
             pos3=1;
             score+=10;
             //if there is collision with ball
     }
        // pos used for plane
        //Plane goes to initial position after collision
   if(r){
    //rad+=.01;
    //moveX and Y are the points after increasing by something


    newx=.1*cos((angleCannon/180)*PI)+oldx;
    newy=.1*sin((angleCannon/180)*PI)+oldy;

   position+=newx-oldx;
   position2+=newy-oldy;
   oldx=newx;
   oldy=newy;

    }
    pos2-=.1;
    pos-=.05;
    pos3-=.075;
	glutPostRedisplay();

	glutTimerFunc(50, update, 0);
}


void handleKeyPress(unsigned char v,int x,int y){

switch(v){

//right
case 'l':
    if(angleCannon>0)
    angleCannon+=-5;

    break;
//left
case 'j':
    if(angleCannon<90)
    angleCannon+=5;

    break;
//fire
case 'r':
    sound();



    r=1;
    fire=1;
    speed=.1;
    speed2=.1;
    break;
}
glutPostRedisplay();




}

void display(){
    //So that cannon does not move with ball
glClearColor(1,1,1,1);
glClear(GL_COLOR_BUFFER_BIT);


glColor3ub(228, 234, 245);
//SKY
glBegin(GL_POLYGON);

glVertex2f(-1,-.6);
glVertex2f(-1,-.8);
glVertex2f(1,-.8);
glVertex2f(1,-.6);
glEnd();

glBegin(GL_POLYGON);
glColor3ub(202, 213, 235);
glVertex2f(-1,-.4);
glVertex2f(-1,-.6);
glVertex2f(1,-.6);
glVertex2f(1,-.4);
glEnd();

glBegin(GL_POLYGON);
glColor3ub(181, 197, 230);
glVertex2f(-1,-.2);
glVertex2f(-1,-.4);
glVertex2f(1,-.4);
glVertex2f(1,-.2);
glEnd();

glBegin(GL_POLYGON);
glColor3ub(153, 182, 247);
glVertex2f(-1,0);
glVertex2f(-1,-.2);
glVertex2f(1,-.2);
glVertex2f(1,0);
glEnd();


glBegin(GL_POLYGON);
glColor3ub(122, 163, 255);
glVertex2f(-1,.2);
glVertex2f(-1,0);
glVertex2f(1,0);
glVertex2f(1,.2);
glEnd();

glBegin(GL_POLYGON);
glColor3ub(109, 147, 232);
glVertex2f(-1,.4);
glVertex2f(-1,.2);
glVertex2f(1,.2);
glVertex2f(1,.4);
glEnd();

glBegin(GL_POLYGON);
glColor3ub(83, 131, 237);
glVertex2f(-1,1);
glVertex2f(-1,.4);
glVertex2f(1,.4);
glVertex2f(1,1);
glEnd();

glBegin(GL_POINTS);
glColor3ub(255,255,255);
glVertex2f(-.9,.8);
glVertex2f(-.8,.6);
glVertex2f(.9,.7);
glVertex2f(.6,.9);

glVertex2f(-.7,.5);
glVertex2f(-.8,.5);
glVertex2f(.5,.7);
glVertex2f(.7,.8);
glEnd();



GLfloat cx,cy;
int i;
	GLfloat  x=0,  y=0; radiusCannon =.12f;radiusBall=.05;
	int triangleAmount = 20; //# of triangles used to draw circle


	GLfloat twicePi =  PI;



	canonLeverx1=x;canonLevery1=y+radiusCannon;
	canonLeverx2=x;canonLevery2=y-radiusCannon;
	canonLeverx3=x+.3;canonLevery3=y-radiusBall-.02;
	canonLeverx4=x+.3;canonLevery4=y+radiusBall+.02;


//ball

//dif =extra distance between lever and ball

    twicePi=2*PI;
    xBall=canonLeverx4;
//diff is used to fix the ball in front of the cannon
//if there is no pushmatrix for each rotate the program misbehaves
    yBall=(canonLevery4+canonLevery3)/2.0;
   // if(r){
    //r is used for moving ball
    glTranslatef(position,position2,0);
    glPushMatrix();
   // }

    glTranslatef(dif,dif,0);
    glPushMatrix();
//creating a center in the cannons center for rotation


    glRotatef(angleCannon,0,0,1);

	glBegin(GL_TRIANGLE_FAN);
        glColor3ub(18, 17, 17);
		glVertex2f(xBall,yBall ); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            xBall +(radiusBall * cos(i *  twicePi / triangleAmount)),
			    yBall +(radiusBall * sin(i * twicePi / triangleAmount))
			);
		}

	glEnd();

    glLoadIdentity();
    glPopMatrix();
    glLoadIdentity();














//Cannon

    glTranslatef(dif,dif,0);
    glPushMatrix();
    glRotatef(angleCannon,0,0,1);
	glBegin(GL_TRIANGLE_FAN);
        glColor3ub(79, 75, 74);
		glVertex2f(x, y); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x -(radiusCannon * sin(i *  twicePi / triangleAmount)),
			    y -(radiusCannon * cos(i * twicePi / triangleAmount))
			);
		}
	glEnd();


	glBegin(GL_QUADS);
	glVertex2f(canonLeverx1,canonLevery1);
	glVertex2f(canonLeverx2,canonLevery2);
	glVertex2f(canonLeverx3,canonLevery3);
	glVertex2f(canonLeverx4,canonLevery4);

	glEnd();



//blast
    if(fire<700){
    glBegin(GL_POLYGON);

    glColor3ub(255, 0, 0);
	glVertex2f(canonLeverx3,canonLevery3);
	glVertex2f(canonLeverx3+.1,canonLevery3-.1);
	glVertex2f(canonLeverx3+.05,canonLevery3);
	glVertex2f(canonLeverx3+.125,canonLevery3-.05);
	glVertex2f(canonLeverx3+.112,canonLevery3+.02);
	glVertex2f(canonLeverx3+.175,canonLevery3+.045);
	glVertex2f(canonLeverx4,canonLevery4);
	glVertex2f(canonLeverx4+.1,canonLevery4+.1);
	glVertex2f(canonLeverx4+.05,canonLevery4);
	glVertex2f(canonLeverx4+.125,canonLevery4+.05);
	glVertex2f(canonLeverx4+.112,canonLevery4-.02);
	glVertex2f(canonLeverx4+.175,canonLevery4-.045);

	line=.01;
	glColor3ub(255, 255, 0);
	glVertex2f(canonLeverx3,canonLevery3-line);
	glVertex2f(canonLeverx3+.1,canonLevery3-.1-line);
	glVertex2f(canonLeverx3+.05,canonLevery3);
	glVertex2f(canonLeverx3+.125,canonLevery3-.05-line);
	glVertex2f(canonLeverx3+.112,canonLevery3+.02-line);
	glVertex2f(canonLeverx3+.175,canonLevery3+.045-line);
	glVertex2f(canonLeverx4,canonLevery4-line);
	glVertex2f(canonLeverx4+.1,canonLevery4+.1-line);
	glVertex2f(canonLeverx4+.05,canonLevery4-line);
	glVertex2f(canonLeverx4+.125,canonLevery4+.05-line);
	glVertex2f(canonLeverx4+.112,canonLevery4-.02-line);
	glVertex2f(canonLeverx4+.175,canonLevery4-.045-line);


    glEnd();
    fire++;
    }

    glPopMatrix();
    glLoadIdentity();


        cx=rad*cos((angleCannon/180)*PI)+dif+position;
        cy=rad*sin((angleCannon/180)*PI)+dif+position2;
        //position of te center of the moving ball
        //this is used for detecting collision
     x1=0;y11=0+.2;
     x2=-.1;y2=-.1+.2;
     x3=.4; y3=-.1+.2;
     x4=.4; y4=0+.2;
     x5=.4; y5=.08+.2;
     x6=.3;y6=0+.2;

     x7=.1;y7=-.1+.2;
     x8=.1;y8=-.05+.2;
     x9=.15;y9=-.05+.2;
     x10=.15; y10=-.1+.2;

     x11=.2; y111=-.03+.2;
     x12=.2; y12=-.06+.2;
     x13=.23;y13=-.06+.2;
     x14=.23;y14=-.03+.2;

	glColor3ub(0,0,0);
//plane1
	glPushMatrix();
glTranslatef(pos,0,0);
	//if(value1&&value2){


	glBegin(GL_POLYGON);
	glVertex2f(x1,y11);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);

	glEnd();
//wing
	glBegin(GL_POLYGON);
	glVertex2f(x4,y4);
	glVertex2f(x5,y5);
	glVertex2f(x6,y6);

	glEnd();
//door
    glColor3ub(255,255,255);
	glBegin(GL_LINES);
	glVertex2f(x7,y7);
	glVertex2f(x8,y8);
	glVertex2f(x8,y8);
	glVertex2f(x9,y9);
	glVertex2f(x9,y9);
	glVertex2f(x10,y10);

	glEnd();
//window1
	glColor3ub(255,255,255);
	glBegin(GL_POLYGON);
	glVertex2f(x11,y111);
	glVertex2f(x12,y12);
	glVertex2f(x13,y13);
	glVertex2f(x14,y14);
//window2
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(x11+.08,y111);
	glVertex2f(x12+.08,y12);
	glVertex2f(x13+.08,y13);
	glVertex2f(x14+.08,y14);

    glEnd();
//	}
//	glLoadIdentity();
	glPopMatrix();



    //for left edge
    value1 =collisionDetection(x1+pos,y11,x2+pos,y2,cx,cy);
    //for bottom edge
    value2=collisionDetection(x2+pos,y2,x3+pos,y3,cx,cy);


//plane2
    glColor3ub(0,0,0);
	glTranslatef(pos2,.2,0);
//	if(value3&&value4){
	glBegin(GL_POLYGON);
	glVertex2f(x1,y11);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);

	glEnd();
//wing
	glBegin(GL_POLYGON);
	glVertex2f(x4,y4);
	glVertex2f(x5,y5);
	glVertex2f(x6,y6);

	glEnd();
//door
    glColor3ub(255,255,255);
	glBegin(GL_LINES);
	glVertex2f(x7,y7);
	glVertex2f(x8,y8);
	glVertex2f(x8,y8);
	glVertex2f(x9,y9);
	glVertex2f(x9,y9);
	glVertex2f(x10,y10);

	glEnd();
//window1
	glColor3ub(255,255,255);
	glBegin(GL_POLYGON);
	glVertex2f(x11,y111);
	glVertex2f(x12,y12);
	glVertex2f(x13,y13);
	glVertex2f(x14,y14);
//window2
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(x11+.08,y111);
	glVertex2f(x12+.08,y12);
	glVertex2f(x13+.08,y13);
	glVertex2f(x14+.08,y14);

    glEnd();
//	}
	glLoadIdentity();
	glPopMatrix();
    glLoadIdentity();



    //for left edge
    value3 =collisionDetection(x1+pos2,y11+.2,x2+pos2,y2+.2,cx,cy);
    //for bottom edge
    value4 =collisionDetection(x2+pos2,y2+.2,x3+pos2,y3+.2,cx,cy);



//plane3
    glColor3ub(0,0,0);
	glTranslatef(pos3,.4,0);
//	if(value5&&value6){
	glBegin(GL_POLYGON);
	glVertex2f(x1,y11);
	glVertex2f(x2,y2);
	glVertex2f(x3,y3);
	glVertex2f(x4,y4);

	glEnd();
//wing
	glBegin(GL_POLYGON);
	glVertex2f(x4,y4);
	glVertex2f(x5,y5);
	glVertex2f(x6,y6);

	glEnd();
//door
    glColor3ub(255,255,255);
	glBegin(GL_LINES);
	glVertex2f(x7,y7);
	glVertex2f(x8,y8);
	glVertex2f(x8,y8);
	glVertex2f(x9,y9);
	glVertex2f(x9,y9);
	glVertex2f(x10,y10);

	glEnd();
//window1
	glColor3ub(255,255,255);
	glBegin(GL_POLYGON);
	glVertex2f(x11,y111);
	glVertex2f(x12,y12);
	glVertex2f(x13,y13);
	glVertex2f(x14,y14);
//window2
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(x11+.08,y111);
	glVertex2f(x12+.08,y12);
	glVertex2f(x13+.08,y13);
	glVertex2f(x14+.08,y14);

    glEnd();
//	}
	glLoadIdentity();
	glPopMatrix();
    glLoadIdentity();



    //for left edge
    value5 =collisionDetection(x1+pos3,y11+.4,x2+pos3,y2+.4,cx,cy);
    //for bottom edge
    value6 =collisionDetection(x2+pos3,y2+.4,x3+pos3,y3+.4,cx,cy);




//Holder
    x9=-.75; y9=-.75;
    x10=-.85; y10=-.75;
    x11=-.85; y111=-1;
    x12=-.75; y12=-1;

//Standing bar
    glColor3ub(128, 90, 15);
    glBegin(GL_POLYGON);
	glVertex2f(x9,y9);
	glVertex2f(x10,y10);
	glVertex2f(x11,y111);
	glVertex2f(x12,y12);

    glEnd();


     x9=-1; y9=-.95;
    x10=-1; y10=-1;
    x11=-.6; y111=-1;
    x12=-.6; y12=-.95;
//Lowest Bar
 glBegin(GL_POLYGON);
	glVertex2f(x9,y9);
	glVertex2f(x10,y10);
	glVertex2f(x11,y111);
	glVertex2f(x12,y12);

    glEnd();


     x9=-.95; y9=-.9;
    x10=-.95; y10=-.95;
    x11=-.65; y111=-.95;
    x12=-.65; y12=-.9;
//@nd lowest bar
 glBegin(GL_POLYGON);
	glVertex2f(x9,y9);
	glVertex2f(x10,y10);
	glVertex2f(x11,y111);
	glVertex2f(x12,y12);

    glEnd();

//black bar inside yellow circle

    x10=.02; y10=.05;
    x11=-.02; y111=.05;
    x12=-.02; y12=-.05;
    x13=.02; y13=-.05;




    x9=0; y9=0;
    twicePi=2*PI;

    glTranslatef(dif,dif,0);
    glPushMatrix();
//Yellow circle
//creating a center in the cannons center for rotation


	glBegin(GL_TRIANGLE_FAN);
        glColor3ub(237, 222, 12);
		glVertex2f(x9,y9 ); // center of circle
		for(i = 0; i <= triangleAmount;i++) {
			glVertex2f(
		            x9 +(.05 * cos(i *  twicePi / triangleAmount)),
			    y9 +(.05 * sin(i * twicePi / triangleAmount))
			);
		}

	glEnd();
    glRotatef(angleCannon,0,0,1);

//black bar inside yellow circle
	glColor3ub(0,0,0);
    glBegin(GL_POLYGON);

	glVertex2f(x10,y10);
	glVertex2f(x11,y111);
	glVertex2f(x12,y12);
    glVertex2f(x13,y13);
    glEnd();

    glLoadIdentity();
    glPopMatrix();
     glLoadIdentity();






glFlush();
}

void timer(int x){

cout<<"Your Score: "<<score;
exit(0);
}
void sound()
{

    //PlaySound("a.wav", NULL, SND_ASYNC|SND_FILENAME);
    PlaySound("Cannon+2.wav", NULL,SND_ASYNC|SND_FILENAME);

}



int main(int argc,char** argv){

glutInitWindowSize(400,400);
glutInitWindowPosition(500, 200);
glutInit(&argc, argv);
glutCreateWindow("Port");
glutDisplayFunc(display);
glutKeyboardFunc(handleKeyPress);
   glutTimerFunc(100, update, 0);
    glutTimerFunc(1000*30, timer, 0);
   glutIdleFunc(Idle);

glutMainLoop();



return 0;


}

