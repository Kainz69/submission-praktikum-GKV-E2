#include <iostream>
#include <stdlib.h>

#ifdef APPLE
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h> [cite: 40]
#endif

#include "imageloader.h"
#include "imageloader.cpp"

using namespace std;

const float BOX_SIZE = 7.0f; //Panjang tiap sisi kubus [cite: 40]

float _angle = 0; //Rotasi terhadap box [cite: 40]
GLuint _textureIds[6]; // ID OpenGL untuk tekstur, satu untuk setiap sisi

void handleKeypress(unsigned char key, int x, int y) { [cite: 41]
    switch (key) {
        case 27: //Tekan Escape untuk EXIT [cite: 41]
            exit(0);
    }
}

//Membuat gambar menjadi tekstur kemudian berikan ID pada tekstur
GLuint loadTexture(Image* image) { [cite: 41]
    GLuint textureId;
    glGenTextures(1, &textureId); [cite: 42]
    glBindTexture(GL_TEXTURE_2D, textureId); [cite: 42]
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels); [cite: 42]
    return textureId; [cite: 43]
}

void initRendering() { [cite: 43]
    glEnable(GL_DEPTH_TEST); [cite: 43]
    glEnable(GL_LIGHTING); [cite: 43]
    glEnable(GL_LIGHT0); [cite: 43]
    glEnable(GL_NORMALIZE); [cite: 43]
    glEnable(GL_COLOR_MATERIAL); [cite: 44]

    // Load each image for each face
    Image* image1 = loadBMP("bg.bmp"); // Ganti dengan nama file gambar Anda
    _textureIds[0] = loadTexture(image1);
    delete image1;

    Image* image2 = loadBMP("image2.bmp"); // Ganti dengan nama file gambar Anda
    _textureIds[1] = loadTexture(image2);
    delete image2;
    
    Image* image3 = loadBMP("image3.bmp"); // Ganti dengan nama file gambar Anda
    _textureIds[2] = loadTexture(image3);
    delete image3;

    Image* image4 = loadBMP("image4.bmp"); // Ganti dengan nama file gambar Anda
    _textureIds[3] = loadTexture(image4);
    delete image4;

    Image* image5 = loadBMP("image5.bmp"); // Ganti dengan nama file gambar Anda
    _textureIds[4] = loadTexture(image5);
    delete image5;

    Image* image6 = loadBMP("IMG_0771.bmp"); // Gambar yang Anda berikan
    _textureIds[5] = loadTexture(image6);
    delete image6;
}

void handleResize(int w, int h) { [cite: 45]
    glViewport(0, 0, w, h); [cite: 45]
    glMatrixMode(GL_PROJECTION); [cite: 45]
    glLoadIdentity(); [cite: 45]
    gluPerspective(45.0, (float)w / (float)h, 1.0, 200.0); [cite: 46]
}

void drawScene() { [cite: 46]
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); [cite: 46]
    glMatrixMode(GL_MODELVIEW); [cite: 47]
    glLoadIdentity(); [cite: 47]
    glTranslatef(0.0f, 0.0f, -20.0f); [cite: 47]

    GLfloat ambientLight[] = {0.3f, 0.3f, 0.3f, 1.0f}; [cite: 48]
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight); [cite: 48]

    GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f}; [cite: 49]
    GLfloat lightPos[] = {-2 * BOX_SIZE, BOX_SIZE, 1.0f}; [cite: 49]
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor); [cite: 49]
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos); [cite: 49]

    glRotatef(-_angle, 1.0f, 1.0f, 0.0f); [cite: 50]

    glEnable(GL_TEXTURE_2D); [cite: 59]

    // Sisi Depan
    glBindTexture(GL_TEXTURE_2D, _textureIds[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); [cite: 59]
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); [cite: 59]
    glColor3f(1.0f, 1.0f, 1.0f); [cite: 60]
    glBegin(GL_QUADS); [cite: 60]
    glNormal3f(0.0, 0.0f, 1.0f); [cite: 60]
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2); [cite: 61]
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2); [cite: 61]
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2); [cite: 62]
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2); [cite: 63]
    glEnd();

    // Sisi Belakang
    glBindTexture(GL_TEXTURE_2D, _textureIds[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    // Sisi Kiri
    glBindTexture(GL_TEXTURE_2D, _textureIds[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(-1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    // Sisi Kanan
    glBindTexture(GL_TEXTURE_2D, _textureIds[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(1.0, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    // Sisi Atas
    glBindTexture(GL_TEXTURE_2D, _textureIds[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, BOX_SIZE / 2, -BOX_SIZE / 2);
    glEnd();

    // Sisi Bawah
    glBindTexture(GL_TEXTURE_2D, _textureIds[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glNormal3f(0.0, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-BOX_SIZE / 2, -BOX_SIZE / 2, BOX_SIZE / 2);
    glEnd();

    glDisable(GL_TEXTURE_2D); [cite: 66]

    glutSwapBuffers(); [cite: 66]
}

//Panggil setiap 25ms
void update(int value) { [cite: 67]
    _angle += 1.0f; [cite: 67]
    if (_angle > 360) { [cite: 67]
        _angle -= 360; [cite: 67]
    }
    glutPostRedisplay(); [cite: 67]
    glutTimerFunc(25, update, 0); [cite: 68]
}

int main(int argc, char** argv) { [cite: 68]
    glutInit(&argc, argv); [cite: 68]
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); [cite: 69]
    glutInitWindowSize(400, 400); [cite: 69]
    glutCreateWindow("Texture With Image"); [cite: 69]

    initRendering(); [cite: 69]

    glutDisplayFunc(drawScene); [cite: 69]
    glutKeyboardFunc(handleKeypress); [cite: 69]
    glutReshapeFunc(handleResize); [cite: 69]
    glutTimerFunc(25, update, 0); [cite: 69]

    glutMainLoop(); [cite: 69]
    return 0; [cite: 69]
}
