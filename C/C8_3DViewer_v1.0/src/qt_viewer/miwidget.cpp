#include "miwidget.h"

miwidget::miwidget(QWidget *parent):QOpenGLWidget(parent){
//miwidget();
}

void miwidget::initializeGL(){

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

//    bgColor.setRgb(27, 39, 50);
}

void miwidget::resizeGL(int w, int h) {
        glViewport(0, 0, w, h);
}

//---------------------------

void miwidget::changeColor(double value) {
    BGcolor = value;
}

void miwidget::changeLineColor(double value) {
    lineColor = value;
}

void miwidget::changeLines(const QString& str) {
    lineType = str;

}

void miwidget::lineSize(double value) {
    lineWidth = value;
}

void miwidget::changeVertex(const QString& str) {
    vertexType = str;
    // ne rabotaet
}

void miwidget::vertexSize(double value) {
    vertexWidth = value;
    // не работает
}

void miwidget::editMode(const QString& str) {
    mode = str;
}

void miwidget::perspectiveMode(const QString& str) {
    perspective = str;
}

void miwidget::paintGL(){
    if (flag_parsed_file) {
        glClearColor(BGcolor, BGcolor / 10.0, BGcolor / 100.0, 1.0f);
        glColor3f(lineColor, lineColor / 10.0, lineColor / 100.0);

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);

        if (lineType == "Solid lines") {
            glDisable(GL_LINE_STIPPLE);
            glEnable(GL_LINE_SMOOTH);
        } else {
            glEnable(GL_LINE_STIPPLE);
            glLineStipple(2, 666);
        }
        glLineWidth(lineWidth);
        glShadeModel(GL_SMOOTH);
        glLoadIdentity();
        if (perspective == "Parallel") {
            glFrustum(-1, 1, -1, 1, 1, 50);
            glTranslated(0, 0, -6);
        }

        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_DOUBLE, 0, polygons.matrix_vertexes);
        if (mode == "Edges" && vertexType == "Point") {
            glDrawElements(GL_LINES, polygons.summ_of_polygons, GL_UNSIGNED_INT, polygons.matrix_polygons);
        } else if (mode == "Vertexes" && vertexType == "Point") {
            glDrawElements(GL_POINTS, polygons.summ_of_polygons, GL_UNSIGNED_INT, polygons.matrix_polygons);
        }
        if (vertexType == "Vertex") {
            glEnable(GL_POINT_SMOOTH);
        } else if (vertexType == "Circle") {
            glDrawElements(GL_CIRCULAR_TANGENT_ARC_TO_NV, polygons.summ_of_polygons, GL_UNSIGNED_INT, polygons.matrix_polygons);
        } else if (vertexType == "Square") {
            glDrawElements(GL_QUADS, polygons.summ_of_polygons, GL_UNSIGNED_INT, polygons.matrix_polygons);
        }
    }
        glDisableClientState(GL_VERTEX_ARRAY);

        glPointSize(vertexWidth);
update();
}


void miwidget::start_rotate(double value, char coord)
{
    // число 0.2 может быть переменной в шаге прокрутки
    // если по заданию надо менять шаг то туда можно отправлять данные из слайдера
    // приходящее значение из слайдера value
    // от знака зависит направление вращения

    if (flag_parsed_file){
        if (coord == 'x') {
            matrix_rotate(&polygons, 'x', 0.2);
        }
        else if (coord == 'y') {
            matrix_rotate(&polygons, 'y', 0.2);
        }
        else if (coord == 'z') {
            matrix_rotate(&polygons, 'z', 0.2);
        }
        //scale - изменение масштаба

        else if (coord == 's') {
            matrix_scale(&polygons, value);
            centred(&polygons);
//            resize_matrix_on_screen(&polygons, 0.8);1
        }

        //scale - сдвинуть модельку
        else if (coord == 'u') {
            matrix_move(&polygons, 'y', value);
        }
        else if (coord == 'd') {
            matrix_move(&polygons, 'y', value);
        }
        else if (coord == 'l') {
            matrix_move(&polygons, 'x', value);
        }
        else if (coord == 'r') {
            matrix_move(&polygons, 'x', value);
        }
    }
}

void miwidget::move_camera(int zoom){

    glTranslatef(0,0,-zoom);
    initializeGL();
    paintGL();
}

obj_data miwidget::parse_file(const QString& path)
{
    char* path_to_obj = path.toUtf8().data();
    start_parse_obj_file(&polygons, path_to_obj);
    flag_parsed_file = 1;


    //0.7 это масштаб от экрана - 1 - это 100% масштаб
    resize_matrix_on_screen(&polygons, 0.6);
    centred(&polygons);
    return polygons;
}

