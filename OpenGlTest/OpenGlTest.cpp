#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath> // cos, sin 함수 사용을 위해 추가

static int Day = 0, Time = 0;

void SetLighting() {
    GLfloat light_position[] = { 0.0, 1.5, 1.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void SetMaterialColor(GLfloat r, GLfloat g, GLfloat b) {
    GLfloat mat_diffuse[] = { r, g, b, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
}

void DrawOrbit() {
    glDisable(GL_LIGHTING); // 궤도는 조명 없이 그립니다
    glColor3f(0.6, 0.6, 0.6); // 궤도는 회색으로 표현
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        GLfloat theta = (GLfloat)(i * 3.14159 / 180.0); // GLfloat로 변환
        glVertex3f(0.7 * cos(theta), 0.0, 0.7 * sin(theta)); // 세 번째 인수 추가
    }
    glEnd();
    glEnable(GL_LIGHTING); // 조명 다시 활성화
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);

    SetLighting();

    // 태양을 빨간색으로 표현
    SetMaterialColor(1.0, 0.0, 0.0);
    glutSolidSphere(0.2, 20, 16); // 태양 그리기

    DrawOrbit();

    glPushMatrix();
    glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
    glTranslatef(0.7, 0.0, 0.0);

    // 지구를 파란색으로 표현
    SetMaterialColor(0.0, 0.0, 1.0);
    glutSolidSphere(0.1, 10, 8); // 지구 그리기

    glPushMatrix();
    glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
    glTranslatef(0.2, 0.0, 0.0);

    // 달을 노란색으로 표현
    SetMaterialColor(1.0, 1.0, 0.0);
    glutSolidSphere(0.04, 10, 8); // 달 그리기

    glPopMatrix();
    glPopMatrix();

    glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'd':
        Day = (Day + 10) % 360;
        glutPostRedisplay();
        break;
    case 't':
        Time = (Time + 5) % 360;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Sample Drawing with Lighting and Orbit");

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 3.0);

    glutDisplayFunc(MyDisplay);
    glutKeyboardFunc(MyKeyboard);
    glutMainLoop();
    return 0;
}



