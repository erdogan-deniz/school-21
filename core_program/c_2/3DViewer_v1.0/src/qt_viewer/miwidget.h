#ifndef MIWIDGET_H
#define MIWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

//#include <QGLWidget>

#include <QGLFramebufferObjectFormat>
#include <GL/gl.h>
#include <QDebug>
#include <QVector3D>

extern "C" {
    #include "../3d_viewer.h"
}


//?????????????????????//
static double rotate_y=0;
static double rotate_x=0;
static double rotate_z=0;
static double rotate_zoom=0;


//static    double ** matrix_vertexes;
static double * vert_parsed;

static obj_data polygons; //mojno ubrat
static int flag_parsed_file = 0;
//?????????????????????//

static double min_x=0;
static double min_y=0;
static double min_z=0;

static double max_x=0;
static double max_y=0;
static double max_z=0;

static double BGcolor = 0;
static double lineColor = 100;
static double lineWidth = 1;
static double vertexWidth = 2;

static QString lineType = "Solid lines";
static QString vertexType = "Point";
static QString mode = "Edges";
static QString perspective = "Central";

class miwidget:public QOpenGLWidget
{

public:
    explicit miwidget(QWidget *parent = 0);

public:
    void initializeGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;

//    float color = 0;
//    QPalette palette;
//    QVector3D lineColorV = {1, 1, 1};


public slots:
     void changeColor(double);
     void changeLineColor(double);
     void changeLines(const QString&);
     void lineSize(double);
     void vertexSize(double);
     void changeVertex(const QString&);
     void editMode(const QString&);
     void perspectiveMode(const QString&);

     void start_rotate(double value, char coord);
     void on_pushButton_clicked();
     obj_data parse_file(const QString&);
     void move_camera(int zoom);
};

#endif // MIWIDGET_H
