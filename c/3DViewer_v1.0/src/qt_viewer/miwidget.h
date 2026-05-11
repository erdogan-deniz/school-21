/**
 * @file miwidget.h
 * @brief `QOpenGLWidget` subclass — the OpenGL viewport for
 *        `3DViewer_v1.0`, bridging the Qt front end with the C core
 *        (@ref 3d_viewer.h).
 *
 * Uses the legacy fixed-function OpenGL pipeline (`glVertexPointer`,
 * `glDrawArrays`) rather than the modern shader pipeline used in
 * `cpp/3DViewer_v2.0` and later. The C core is included via
 * `extern "C"` since this is a C++ host.
 *
 * File-scope `static` globals (rotation accumulators, color knobs,
 * style strings) are an artefact of the original v1.0 design — kept
 * here verbatim. They are not thread-safe and are mutated from the
 * slot handlers in @ref MainWindow.
 */

#ifndef MIWIDGET_H
#define MIWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

// #include <QGLWidget>

#include <GL/gl.h>

#include <QDebug>
#include <QGLFramebufferObjectFormat>
#include <QVector3D>

extern "C" {
#include "../3d_viewer.h"
}

//?????????????????????//
static double rotate_y = 0;       ///< Accumulated Y-axis rotation.
static double rotate_x = 0;       ///< Accumulated X-axis rotation.
static double rotate_z = 0;       ///< Accumulated Z-axis rotation.
static double rotate_zoom = 0;    ///< Accumulated zoom factor.

// static    double ** matrix_vertexes;
static double *vert_parsed;       ///< Cached flat vertex buffer for OpenGL.

static obj_data polygons;         ///< Cached parsed model (single per-process). // mojno ubrat
static int flag_parsed_file = 0;  ///< Non-zero once a file has been parsed.
//?????????????????????//

static double min_x = 0;          ///< Bounding-box min along X.
static double min_y = 0;          ///< Bounding-box min along Y.
static double min_z = 0;          ///< Bounding-box min along Z.

static double max_x = 0;          ///< Bounding-box max along X.
static double max_y = 0;          ///< Bounding-box max along Y.
static double max_z = 0;          ///< Bounding-box max along Z.

static double BGcolor = 0;        ///< Background grey level (0..255).
static double lineColor = 100;    ///< Edge line grey level.
static double lineWidth = 1;      ///< Edge line width in pixels.
static double vertexWidth = 2;    ///< Vertex point size in pixels.

static QString lineType = "Solid lines";  ///< Edge style: "Solid lines" / "Dashed" / "None".
static QString vertexType = "Point";      ///< Vertex marker: "Point" / "Square" / "None".
static QString mode = "Edges";            ///< Render mode: "Edges" / "Faces" / etc.
static QString perspective = "Central";   ///< Projection: "Central" / "Parallel".

/**
 * @brief OpenGL viewport widget used by @ref MainWindow.
 *
 * Owns no model state of its own — all data lives in the file-scope
 * `static` globals above. Slot handlers update those globals and call
 * `update()` to trigger a repaint.
 */
class miwidget : public QOpenGLWidget {
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
  /** @brief Update @ref BGcolor and request a repaint. */
  void changeColor(double);
  /** @brief Update @ref lineColor and request a repaint. */
  void changeLineColor(double);
  /** @brief Update @ref lineType (string-keyed) and request a repaint. */
  void changeLines(const QString &);
  /** @brief Update @ref lineWidth. */
  void lineSize(double);
  /** @brief Update @ref vertexWidth. */
  void vertexSize(double);
  /** @brief Update @ref vertexType. */
  void changeVertex(const QString &);
  /** @brief Update @ref mode. */
  void editMode(const QString &);
  /** @brief Update @ref perspective. */
  void perspectiveMode(const QString &);

  /** @brief Accumulate rotation around axis @p coord by @p value. */
  void start_rotate(double value, char coord);
  void on_pushButton_clicked();
  /**
   * @brief Parse @p path via @ref start_parse_obj_file and cache the
   *        result in @ref polygons.
   * @return The parsed @ref obj_data (also broadcast via the parent's
   *         file-changed signal).
   */
  obj_data parse_file(const QString &);
  /** @brief Update @ref rotate_zoom by @p zoom and request a repaint. */
  void move_camera(int zoom);
};

#endif  // MIWIDGET_H
