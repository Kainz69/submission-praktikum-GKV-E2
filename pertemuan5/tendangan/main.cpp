#include <math.h>  
#include <GL/glut.h> 
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>   
#define PI 3.14 
 
// Global variables
float angle = 0.0, deltaAngle = 0.0, ratio;  
float x = -5.0f, y = 12.0f, z = 40.0f; // initial camera position  
float lx = 0.0f, ly = 0.0f, lz = -1.0f;  
int deltaMove = 0, h, w;  
static int rotAngleX = 0, rotAngleY = 0, rotAngleZ = 0; 
float posXKaki = 10, posXBola = -10, posYKaki = 6, posYBola = -5; 
float rotKaki = 0.0; 
int kick = 0, roll = 0, touch = 0; 
float jarak = 1; 
 
GLUquadricObj *IDquadric; 

// Function prototypes
void init(void);
void Reshape(int w1, int h1);
void orientMe(float ang);
void moveMeFlat(int i);
void keyboard(unsigned char key, int x, int y);
void pressKey(int k, int x, int y);
void releaseKey(int key, int x, int y);
void Grid(void);
void Balok(float panjang, float lebar, float tinggi);
void pergerakanKaki(void);
void pergerakanBola(void);
void Object(void);
void display(void);

// Initialization function
void init(void)  
{  
    glEnable(GL_DEPTH_TEST);  
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  
    IDquadric = gluNewQuadric(); // Create A Pointer To The Quadric Object
    gluQuadricNormals(IDquadric, GLU_SMOOTH); // Create Smooth Normals
    gluQuadricTexture(IDquadric, GL_TRUE); // Create Texture Coords
    glClearColor(0.4f, 0.7f, 1.0f, 1.0f); // warna langit biru cerah
}  
 
// Reshape function
void Reshape(int w1, int h1)  
{  
    if(h1 == 0) h1 = 1;  
    w = w1;  
    h = h1;  
    ratio = 1.0f * w / h;  
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity();  
    glViewport(0, 0, w, h);  
    gluPerspective(45, ratio, 0.1, 1000);  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);  
}  
 
// Function to rotate camera direction
void orientMe(float ang)  
{ 
    lx = sin(ang/10);  
    lz = -cos(ang/10);   
    glLoadIdentity();  
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);  
}  
 
// Function to move camera forward/backward
void moveMeFlat(int i)  
{ 
    x = x + i * (lx) * 0.1;  
    z = z + i * (lz) * 0.1;  
    glLoadIdentity();   
    gluLookAt(x, y, z, x + lx, y + ly, z + lz, 0.0f, 1.0f, 0.0f);  
}  
 
// Grid lapangan (warna rumput hijau)
void Grid()  
{ 
    double i;  
    const float Z_MIN = -50, Z_MAX = 50;  
    const float X_MIN = -50, X_MAX = 50;  
    const float gap = 2;  
    glColor3f(0.2f, 0.6f, 0.2f); // hijau rumput
    glBegin(GL_LINES);  
    for(i = Z_MIN; i < Z_MAX; i += gap)  
    {  
        glVertex3f(i, 0, Z_MIN);  
        glVertex3f(i, 0, Z_MAX);   
    }  
    for(i = X_MIN; i < X_MAX; i += gap)  
    {  
        glVertex3f(X_MIN, 0, i);  
        glVertex3f(X_MAX, 0, i);  
    }  
    glEnd();  
}  

// Membuat balok (kaki)
void Balok(float panjang, float lebar, float tinggi) 
{ 
    glPushMatrix();  
    float p = panjang/2; 
    float l = lebar/2; 
    float t = tinggi/2;  
    glBegin(GL_QUADS); // semua sisi balok
        glVertex3f(-p, 0, l); glVertex3f(p, 0, l); glVertex3f(p, -t*2, l); glVertex3f(-p, -t*2, l); // depan
        glVertex3f(-p, 0, -l); glVertex3f(p, 0, -l); glVertex3f(p, -t*2, -l); glVertex3f(-p, -t*2, -l); // belakang
        glVertex3f(-p, 0, -l); glVertex3f(p, 0, -l); glVertex3f(p, 0, l); glVertex3f(-p, 0, l); // atas
        glVertex3f(-p, -t*2, -l); glVertex3f(p, -t*2, -l); glVertex3f(p, -t*2, l); glVertex3f(-p, -t*2, l); // bawah
        glVertex3f(-p, -t*2, -l); glVertex3f(-p, -t*2, l); glVertex3f(-p, 0, l); glVertex3f(-p, 0, -l); // kiri
        glVertex3f(p, -t*2, -l); glVertex3f(p, -t*2, l); glVertex3f(p, 0, l); glVertex3f(p, 0, -l); // kanan
    glEnd();  
    glPopMatrix();  
} 

// Animasi kaki
void pergerakanKaki()
{ 
    if (kick == 1) {
        if (rotKaki <= 45) rotKaki += 1.03;
        if (rotKaki > 44.9) kick = 2;
    }
    if (posXBola > -2.9) touch = 1;
    else if (posXBola < -12) touch = 0;

    if (kick == 2) {
        if (rotKaki >= -90) {
            rotKaki -= 1.2;
            if (rotKaki < 1 && touch == 1) roll = 1;
        }
        if (rotKaki < -90) kick = 3;
    }

    if (kick == 3) {
        if (rotKaki <= 0) rotKaki += 1.05;
        if (rotKaki > -1) kick = 0;
    }
} 

// Animasi bola
void pergerakanBola()
{ 
    if (roll == 1) {
        if (jarak > 0) {
            posXBola -= 0.33;
            jarak -= 0.01;
        }
        if (jarak < 0) {
            roll = 0;
            jarak = 1;
        }
    }
} 

// Menggambar objek kaki dan bola
void Object() 
{ 
    glPushMatrix(); 
        glTranslatef(posXKaki, posYKaki, 0); 
        glPushMatrix(); 
            pergerakanKaki(); 
            glRotatef(rotKaki, 0, 0, 1); 
            glColor3f(0.2, 0.4, 0.6); // warna kaki
            Balok(2, 3, 6); 
        glPopMatrix(); 

        glPushMatrix(); 
            pergerakanBola(); 
            glColor3f(1.0, 1.0, 1.0); // bola warna putih
            glTranslatef(posXBola, posYBola, 0); 
            glutSolidSphere(1, 20, 20); 
        glPopMatrix(); 
    glPopMatrix(); 
    glFlush(); 
}     

// Display
void display()
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    if (deltaMove) moveMeFlat(deltaMove);  
    if (deltaAngle) { angle += deltaAngle; orientMe(angle); }  
    glPushMatrix(); 
        glRotated(rotAngleX, 1, 0, 0);   
        glRotated(rotAngleY, 0, 1, 0); 
        glRotated(rotAngleZ, 0, 0, 1); 
        Grid();  
        Object();  
    glPopMatrix();  
    glFlush();  
    glutSwapBuffers(); 
}   

// Input keyboard
void keyboard(unsigned char key, int x, int y)  
{ 
    switch (key) 
    { 
        case 'w': rotAngleX += 2; break;
        case 's': rotAngleX -= 2; break;
        case 'a': rotAngleY += 2; break;
        case 'd': rotAngleY -= 2; break;
        case 'q': rotAngleZ += 2; break;
        case 'e': rotAngleZ -= 2; break;
        case 'o': posXKaki -= 1; if (posXBola < -2.9) posXBola += 1; break;
        case 'p': posXKaki += 1; posXBola -= 1; break;
        case 'k': kick = 1; break;  
        case 32: // spasi
            rotAngleX = rotAngleY = rotAngleZ = 0; 
            posXKaki = 10, posXBola = -10, posYKaki = 6, posYBola = -5; 
            rotKaki = kick = roll = 0; 
            break; 
        case 27: // ESC 
            exit(0);  
    } 
    glutPostRedisplay(); 
}  

// Tombol panah
void pressKey(int k, int x, int y)  
{ 
    switch (k)  
    {  
        case GLUT_KEY_UP: deltaMove = 1; break;
        case GLUT_KEY_DOWN: deltaMove = -1; break;
        case GLUT_KEY_LEFT: deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT: deltaAngle = 0.01f; break;
    }  
}  

void releaseKey(int key, int x, int y)  
{ 
    switch (key)  
    {  
        case GLUT_KEY_UP: if (deltaMove > 0) deltaMove = 0; break;
        case GLUT_KEY_DOWN: if (deltaMove < 0) deltaMove = 0; break;
        case GLUT_KEY_LEFT: if (deltaAngle < 0.0f) deltaAngle = 0.0f; break;
        case GLUT_KEY_RIGHT: if (deltaAngle > 0.0f) deltaAngle = 0.0f; break;
    }  
}  

// Main
int main(int argc, char **argv)  
{  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);  
    glutInitWindowPosition(100, 100);  
    glutInitWindowSize(640, 480);  
    glutCreateWindow("tendangan");  
    glutSpecialFunc(pressKey); 
    glutSpecialUpFunc(releaseKey);  
    glutDisplayFunc(display);  
    glutKeyboardFunc(keyboard); 
    glutIdleFunc(display);  
    glutReshapeFunc(Reshape); 
    init(); 
    glutMainLoop(); 
    return(0); 
}

