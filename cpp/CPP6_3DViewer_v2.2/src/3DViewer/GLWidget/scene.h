/**
 * @file scene.h
 * @brief `QOpenGLWidget` + `QOpenGLFunctions` subclass that renders the
 *        scene with modern shader-based OpenGL.
 *
 * Distinct from `3DViewer_v2.0`'s legacy GL pipeline: here we own
 * `QOpenGLShaderProgram`, VAO/VBO/EBO, a quaternion camera and an
 * optional texture. Public fields are UI knobs the parent `viewer`
 * writes before triggering a repaint.
 */

#ifndef SCENE_H
#define SCENE_H

#define GL_SILENCE_DEPRECATION

#include <QtOpenGLWidgets/qopenglwidget.h>

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLTexture>
#include <QOpenGLVertexArrayObject>
#include <QSettings>
#include <QTimer>
#include <QWidget>

/**
 * @brief 3D scene renderer with shader-based OpenGL pipeline.
 *
 * Holds shader programs (main + light), VAO/VBO/EBO buffers, a
 * quaternion-based orbit camera, and Phong-style light parameters.
 * Persists UI knob state to @ref settings between launches.
 */
class scene : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 public:
  scene(QWidget *parent = nullptr);
  ~scene();

  /** @brief Wireframe vs flat / smooth toggle hotkey handler. */
  void keyPressEvent(QKeyEvent *) override;
  /**
   * @brief Upload parsed geometry into the VBO / EBO.
   * @param vertices Flat (x, y, z, …) buffer from @ref s21::Parse.
   * @param indices Index buffer for `glDrawElements`.
   */
  void InitModel(QVector<GLfloat> &vertices, QVector<GLuint> &indices);
  /** @brief Rebuild @ref view / @ref projection from current camera params. */
  void CalculateCamera();
  /** @brief Apply incremental Euler rotation deltas to the model. */
  void RotateModel(float x, float y, float z);
  /** @brief Scan the framebuffer @p map and return all visible edge lines
   *         (used by the GIF / image export path). */
  QList<QLine> GetLines(QPixmap map);

  QVector3D light_pos, light_color, move_object;             ///< Phong light + model translation.
  QColor background, vertices_color, lines_color;            ///< Rendering palette.
  unsigned line_width, vertex_size;                          ///< Edge / point sizes.
  bool circle_square, dashed_solid, is_none;                 ///< Vertex / line style flags.

  float scale_factor;                                        ///< Uniform model scale.
  float r_x, r_y, r_z;                                       ///< Accumulated Euler rotation.

  bool projection_type, wireframe, flat_shading;             ///< Perspective vs ortho; render-mode flags.
  bool has_texture, has_normals, is_light_enabled;           ///< Per-frame feature toggles.

  QSettings *settings;  ///< Borrowed settings store (lifetime owned by viewer).

  QOpenGLShaderProgram program, light;                       ///< Main + light-volume shaders.
  QOpenGLVertexArrayObject vao, vao_light;                   ///< VAOs for model and light.
  QOpenGLBuffer vbo, ebo;                                    ///< Vertex / element buffers.
  QOpenGLTexture *texture;                                   ///< Optional model texture.
  QMatrix4x4 view, projection;                               ///< Cached camera matrices.

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  void wheelEvent(QWheelEvent *) override;

 private:
  void LightInit_();
  void CheckDisplayType_();
  void StartDraw_();
  void DrawLight_();

  void SaveSettings_();
  void LoadSettings_();

  float x_rot_, y_rot_, start_y_, start_x_;
  bool moving_;

  QVector3D camera_target_, camera_pos_, camera_up_;
  QQuaternion rotation_;
};

#endif  // SCENE_H
