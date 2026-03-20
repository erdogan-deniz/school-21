#include <gtest/gtest.h>

#include <QDebug>

#include "../Controller/controller.h"

TEST(LoadingModels, FullCube) {
  s21::Controller::GetInstance().ParseVertex_3D("../Unit-tests/OBJ/cube.obj");

  QVector<GLfloat> polygons_after_pars = {
      1,  1,  -1, 0.000245, 0.5,      0,  1,  0,
      -1, 1,  -1, 0.333089, 0.5,      0,  1,  0,
      -1, 1,  1,  0.333089, 0.999266, 0,  1,  0,
      1,  1,  -1, 0.000245, 0.5,      0,  1,  0,
      -1, 1,  1,  0.333089, 0.999266, 0,  1,  0,
      1,  1,  1,  0.000245, 0.999266, 0,  1,  0,
      1,  -1, 1,  0.666911, 0.499511, 0,  0,  1,
      1,  1,  1,  0.666911, 0.000245, 0,  0,  1,
      -1, 1,  1,  0.999755, 0.000245, 0,  0,  1,
      1,  -1, 1,  0.666911, 0.499511, 0,  0,  1,
      -1, 1,  1,  0.999755, 0.000245, 0,  0,  1,
      -1, -1, 1,  0.999756, 0.499511, 0,  0,  1,
      -1, -1, 1,  0.666422, 0.5,      -1, 0,  0,
      -1, 1,  1,  0.666422, 0.999266, -1, 0,  0,
      -1, 1,  -1, 0.333578, 0.999266, -1, 0,  0,
      -1, -1, 1,  0.666422, 0.5,      -1, 0,  0,
      -1, 1,  -1, 0.333578, 0.999266, -1, 0,  0,
      -1, -1, -1, 0.333578, 0.5,      -1, 0,  0,
      -1, -1, -1, 0.000245, 0.000245, 0,  -1, 0,
      1,  -1, -1, 0.333089, 0.000245, 0,  -1, 0,
      1,  -1, 1,  0.333089, 0.499511, 0,  -1, 0,
      -1, -1, -1, 0.000245, 0.000245, 0,  -1, 0,
      1,  -1, 1,  0.333089, 0.499511, 0,  -1, 0,
      -1, -1, 1,  0.000245, 0.499511, 0,  -1, 0,
      1,  -1, -1, 0.666911, 0.999266, 1,  0,  0,
      1,  1,  -1, 0.666911, 0.5,      1,  0,  0,
      1,  1,  1,  0.999755, 0.5,      1,  0,  0,
      1,  -1, -1, 0.666911, 0.999266, 1,  0,  0,
      1,  1,  1,  0.999755, 0.5,      1,  0,  0,
      1,  -1, 1,  0.999756, 0.999266, 1,  0,  0,
      -1, -1, -1, 0.666422, 0.000245, 0,  0,  -1,
      -1, 1,  -1, 0.666422, 0.499511, 0,  0,  -1,
      1,  1,  -1, 0.333578, 0.499511, 0,  0,  -1,
      -1, -1, -1, 0.666422, 0.000245, 0,  0,  -1,
      1,  1,  -1, 0.333578, 0.499511, 0,  0,  -1,
      1,  -1, -1, 0.333578, 0.000245, 0,  0,  -1};
  EXPECT_EQ(s21::Controller::GetInstance().GetPolygonsArray().size(),
            polygons_after_pars.size());
  for (auto it = 0;
       it < s21::Controller::GetInstance().GetPolygonsArray().size(); ++it)
    EXPECT_NEAR(s21::Controller::GetInstance().GetPolygonsArray()[it],
                polygons_after_pars[it], 1e-4);

  QVector<GLuint> indices = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                             12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                             24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  EXPECT_EQ(s21::Controller::GetInstance().GetIndices().size(), indices.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetIndices().size();
       ++it)
    EXPECT_EQ(s21::Controller::GetInstance().GetIndices()[it], indices[it]);

  QVector<QVector3D> vertices = {
      QVector3D(0, 0, 0),    QVector3D(1, 1, -1), QVector3D(1, -1, -1),
      QVector3D(1, 1, 1),    QVector3D(1, -1, 1), QVector3D(-1, 1, -1),
      QVector3D(-1, -1, -1), QVector3D(-1, 1, 1), QVector3D(-1, -1, 1)};
  EXPECT_EQ(s21::Controller::GetInstance().GetVertices().size(),
            vertices.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetVertices().size();
       ++it) {
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].x(),
                vertices[it].x(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].y(),
                vertices[it].y(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].z(),
                vertices[it].z(), 1e-4);
  }

  QVector<QVector2D> uv_map = {QVector2D(0, 0),
                               QVector2D(0.000245, 0.5),
                               QVector2D(0.333089, 0.5),
                               QVector2D(0.333089, 0.999266),
                               QVector2D(0.000245, 0.999266),
                               QVector2D(0.666911, 0.499511),
                               QVector2D(0.666911, 0.000245),
                               QVector2D(0.999755, 0.000245),
                               QVector2D(0.999756, 0.499511),
                               QVector2D(0.666422, 0.5),
                               QVector2D(0.666422, 0.999266),
                               QVector2D(0.333578, 0.999266),
                               QVector2D(0.333578, 0.5),
                               QVector2D(0.000245, 0.000245),
                               QVector2D(0.333089, 0.000245),
                               QVector2D(0.333089, 0.499511),
                               QVector2D(0.000245, 0.499511),
                               QVector2D(0.666911, 0.999266),
                               QVector2D(0.666911, 0.5),
                               QVector2D(0.999755, 0.5),
                               QVector2D(0.999756, 0.999266),
                               QVector2D(0.666422, 0.000245),
                               QVector2D(0.666422, 0.499511),
                               QVector2D(0.333578, 0.499511),
                               QVector2D(0.333578, 0.000245)};
  EXPECT_EQ(s21::Controller::GetInstance().GetUV().size(), uv_map.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetUV().size(); ++it) {
    EXPECT_NEAR(s21::Controller::GetInstance().GetUV()[it].x(), uv_map[it].x(),
                1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetUV()[it].y(), uv_map[it].y(),
                1e-4);
  }

  QVector<QVector3D> normals = {QVector3D(0, 0, 0),  QVector3D(0, 1, 0),
                                QVector3D(0, 0, 1),  QVector3D(-1, 0, 0),
                                QVector3D(0, -1, 0), QVector3D(1, 0, 0),
                                QVector3D(0, 0, -1)};
  EXPECT_EQ(s21::Controller::GetInstance().GetNormals().size(), normals.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetNormals().size();
       ++it) {
    EXPECT_NEAR(s21::Controller::GetInstance().GetNormals()[it].x(),
                normals[it].x(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetNormals()[it].y(),
                normals[it].y(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetNormals()[it].z(),
                normals[it].z(), 1e-4);
  }

  EXPECT_EQ(s21::Controller::GetInstance().NormalsUsage(), true);
  EXPECT_EQ(s21::Controller::GetInstance().TextureUsage(), true);

  s21::Controller::GetInstance().clearArrays();
  EXPECT_EQ(s21::Controller::GetInstance().GetPolygonsArray().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetIndices().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetVertices().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetUV().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetNormals().isEmpty(), true);

  EXPECT_EQ(s21::Controller::GetInstance().NormalsUsage(), false);
  EXPECT_EQ(s21::Controller::GetInstance().TextureUsage(), false);
}

TEST(LoadingModels, CubeNoLight) {
  s21::Controller::GetInstance().ParseVertex_3D(
      "../Unit-tests/OBJ/cube_no_light.obj");

  QVector<GLfloat> polygons_after_pars = {
      1,  1,  -1, 0.000245, 0.5,      0, 0, 0,
      -1, 1,  -1, 0.333089, 0.5,      0, 0, 0,
      -1, 1,  1,  0.333089, 0.999266, 0, 0, 0,
      1,  1,  -1, 0.000245, 0.5,      0, 0, 0,
      -1, 1,  1,  0.333089, 0.999266, 0, 0, 0,
      1,  1,  1,  0.000245, 0.999266, 0, 0, 0,
      1,  -1, 1,  0.666911, 0.499511, 0, 0, 0,
      1,  1,  1,  0.666911, 0.000245, 0, 0, 0,
      -1, 1,  1,  0.999755, 0.000245, 0, 0, 0,
      1,  -1, 1,  0.666911, 0.499511, 0, 0, 0,
      -1, 1,  1,  0.999755, 0.000245, 0, 0, 0,
      -1, -1, 1,  0.999756, 0.499511, 0, 0, 0,
      -1, -1, 1,  0.666422, 0.5,      0, 0, 0,
      -1, 1,  1,  0.666422, 0.999266, 0, 0, 0,
      -1, 1,  -1, 0.333578, 0.999266, 0, 0, 0,
      -1, -1, 1,  0.666422, 0.5,      0, 0, 0,
      -1, 1,  -1, 0.333578, 0.999266, 0, 0, 0,
      -1, -1, -1, 0.333578, 0.5,      0, 0, 0,
      -1, -1, -1, 0.000245, 0.000245, 0, 0, 0,
      1,  -1, -1, 0.333089, 0.000245, 0, 0, 0,
      1,  -1, 1,  0.333089, 0.499511, 0, 0, 0,
      -1, -1, -1, 0.000245, 0.000245, 0, 0, 0,
      1,  -1, 1,  0.333089, 0.499511, 0, 0, 0,
      -1, -1, 1,  0.000245, 0.499511, 0, 0, 0,
      1,  -1, -1, 0.666911, 0.999266, 0, 0, 0,
      1,  1,  -1, 0.666911, 0.5,      0, 0, 0,
      1,  1,  1,  0.999755, 0.5,      0, 0, 0,
      1,  -1, -1, 0.666911, 0.999266, 0, 0, 0,
      1,  1,  1,  0.999755, 0.5,      0, 0, 0,
      1,  -1, 1,  0.999756, 0.999266, 0, 0, 0,
      -1, -1, -1, 0.666422, 0.000245, 0, 0, 0,
      -1, 1,  -1, 0.666422, 0.499511, 0, 0, 0,
      1,  1,  -1, 0.333578, 0.499511, 0, 0, 0,
      -1, -1, -1, 0.666422, 0.000245, 0, 0, 0,
      1,  1,  -1, 0.333578, 0.499511, 0, 0, 0,
      1,  -1, -1, 0.333578, 0.000245, 0, 0, 0};
  EXPECT_EQ(s21::Controller::GetInstance().GetPolygonsArray().size(),
            polygons_after_pars.size());
  for (auto it = 0;
       it < s21::Controller::GetInstance().GetPolygonsArray().size(); ++it)
    EXPECT_NEAR(s21::Controller::GetInstance().GetPolygonsArray()[it],
                polygons_after_pars[it], 1e-4);

  QVector<GLuint> indices = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                             12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                             24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  EXPECT_EQ(s21::Controller::GetInstance().GetIndices().size(), indices.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetIndices().size();
       ++it)
    EXPECT_EQ(s21::Controller::GetInstance().GetIndices()[it], indices[it]);

  QVector<QVector3D> vertices = {
      QVector3D(0, 0, 0),    QVector3D(1, 1, -1), QVector3D(1, -1, -1),
      QVector3D(1, 1, 1),    QVector3D(1, -1, 1), QVector3D(-1, 1, -1),
      QVector3D(-1, -1, -1), QVector3D(-1, 1, 1), QVector3D(-1, -1, 1)};
  EXPECT_EQ(s21::Controller::GetInstance().GetVertices().size(),
            vertices.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetVertices().size();
       ++it) {
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].x(),
                vertices[it].x(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].y(),
                vertices[it].y(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].z(),
                vertices[it].z(), 1e-4);
  }

  QVector<QVector2D> uv_map = {QVector2D(0, 0),
                               QVector2D(0.000245, 0.5),
                               QVector2D(0.333089, 0.5),
                               QVector2D(0.333089, 0.999266),
                               QVector2D(0.000245, 0.999266),
                               QVector2D(0.666911, 0.499511),
                               QVector2D(0.666911, 0.000245),
                               QVector2D(0.999755, 0.000245),
                               QVector2D(0.999756, 0.499511),
                               QVector2D(0.666422, 0.5),
                               QVector2D(0.666422, 0.999266),
                               QVector2D(0.333578, 0.999266),
                               QVector2D(0.333578, 0.5),
                               QVector2D(0.000245, 0.000245),
                               QVector2D(0.333089, 0.000245),
                               QVector2D(0.333089, 0.499511),
                               QVector2D(0.000245, 0.499511),
                               QVector2D(0.666911, 0.999266),
                               QVector2D(0.666911, 0.5),
                               QVector2D(0.999755, 0.5),
                               QVector2D(0.999756, 0.999266),
                               QVector2D(0.666422, 0.000245),
                               QVector2D(0.666422, 0.499511),
                               QVector2D(0.333578, 0.499511),
                               QVector2D(0.333578, 0.000245)};
  EXPECT_EQ(s21::Controller::GetInstance().GetUV().size(), uv_map.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetUV().size(); ++it) {
    EXPECT_NEAR(s21::Controller::GetInstance().GetUV()[it].x(), uv_map[it].x(),
                1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetUV()[it].y(), uv_map[it].y(),
                1e-4);
  }

  EXPECT_EQ(s21::Controller::GetInstance().GetNormals().size(), 1);
  EXPECT_EQ(
      s21::Controller::GetInstance().GetNormals()[0] == QVector3D(0, 0, 0),
      true);

  EXPECT_EQ(s21::Controller::GetInstance().NormalsUsage(), false);
  EXPECT_EQ(s21::Controller::GetInstance().TextureUsage(), true);

  s21::Controller::GetInstance().clearArrays();
  EXPECT_EQ(s21::Controller::GetInstance().GetPolygonsArray().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetIndices().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetVertices().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetUV().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetNormals().isEmpty(), true);

  EXPECT_EQ(s21::Controller::GetInstance().NormalsUsage(), false);
  EXPECT_EQ(s21::Controller::GetInstance().TextureUsage(), false);
}

TEST(LoadingModels, CubeNoTexture) {
  s21::Controller::GetInstance().ParseVertex_3D(
      "../Unit-tests/OBJ/cube_no_texture.obj");

  QVector<GLfloat> polygons_after_pars = {
      1,  1,  -1, 0,  0,  0,  1,  0,  -1, 1,  -1, 0,  0,  0,  1,  0,  -1, 1,
      1,  0,  0,  0,  1,  0,  1,  1,  -1, 0,  0,  0,  1,  0,  -1, 1,  1,  0,
      0,  0,  1,  0,  1,  1,  1,  0,  0,  0,  1,  0,  1,  -1, 1,  0,  0,  0,
      0,  1,  1,  1,  1,  0,  0,  0,  0,  1,  -1, 1,  1,  0,  0,  0,  0,  1,
      1,  -1, 1,  0,  0,  0,  0,  1,  -1, 1,  1,  0,  0,  0,  0,  1,  -1, -1,
      1,  0,  0,  0,  0,  1,  -1, -1, 1,  0,  0,  -1, 0,  0,  -1, 1,  1,  0,
      0,  -1, 0,  0,  -1, 1,  -1, 0,  0,  -1, 0,  0,  -1, -1, 1,  0,  0,  -1,
      0,  0,  -1, 1,  -1, 0,  0,  -1, 0,  0,  -1, -1, -1, 0,  0,  -1, 0,  0,
      -1, -1, -1, 0,  0,  0,  -1, 0,  1,  -1, -1, 0,  0,  0,  -1, 0,  1,  -1,
      1,  0,  0,  0,  -1, 0,  -1, -1, -1, 0,  0,  0,  -1, 0,  1,  -1, 1,  0,
      0,  0,  -1, 0,  -1, -1, 1,  0,  0,  0,  -1, 0,  1,  -1, -1, 0,  0,  1,
      0,  0,  1,  1,  -1, 0,  0,  1,  0,  0,  1,  1,  1,  0,  0,  1,  0,  0,
      1,  -1, -1, 0,  0,  1,  0,  0,  1,  1,  1,  0,  0,  1,  0,  0,  1,  -1,
      1,  0,  0,  1,  0,  0,  -1, -1, -1, 0,  0,  0,  0,  -1, -1, 1,  -1, 0,
      0,  0,  0,  -1, 1,  1,  -1, 0,  0,  0,  0,  -1, -1, -1, -1, 0,  0,  0,
      0,  -1, 1,  1,  -1, 0,  0,  0,  0,  -1, 1,  -1, -1, 0,  0,  0,  0,  -1};
  EXPECT_EQ(s21::Controller::GetInstance().GetPolygonsArray().size(),
            polygons_after_pars.size());
  for (auto it = 0;
       it < s21::Controller::GetInstance().GetPolygonsArray().size(); ++it)
    EXPECT_NEAR(s21::Controller::GetInstance().GetPolygonsArray()[it],
                polygons_after_pars[it], 1e-4);

  QVector<GLuint> indices = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                             12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                             24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  EXPECT_EQ(s21::Controller::GetInstance().GetIndices().size(), indices.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetIndices().size();
       ++it)
    EXPECT_EQ(s21::Controller::GetInstance().GetIndices()[it], indices[it]);

  QVector<QVector3D> vertices = {
      QVector3D(0, 0, 0),    QVector3D(1, 1, -1), QVector3D(1, -1, -1),
      QVector3D(1, 1, 1),    QVector3D(1, -1, 1), QVector3D(-1, 1, -1),
      QVector3D(-1, -1, -1), QVector3D(-1, 1, 1), QVector3D(-1, -1, 1)};
  EXPECT_EQ(s21::Controller::GetInstance().GetVertices().size(),
            vertices.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetVertices().size();
       ++it) {
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].x(),
                vertices[it].x(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].y(),
                vertices[it].y(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].z(),
                vertices[it].z(), 1e-4);
  }

  EXPECT_EQ(s21::Controller::GetInstance().GetUV().size(), 1);
  EXPECT_EQ(s21::Controller::GetInstance().GetUV()[0] == QVector2D(0, 0), true);

  QVector<QVector3D> normals = {QVector3D(0, 0, 0),  QVector3D(0, 1, 0),
                                QVector3D(0, 0, 1),  QVector3D(-1, 0, 0),
                                QVector3D(0, -1, 0), QVector3D(1, 0, 0),
                                QVector3D(0, 0, -1)};
  EXPECT_EQ(s21::Controller::GetInstance().GetNormals().size(), normals.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetNormals().size();
       ++it) {
    EXPECT_NEAR(s21::Controller::GetInstance().GetNormals()[it].x(),
                normals[it].x(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetNormals()[it].y(),
                normals[it].y(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetNormals()[it].z(),
                normals[it].z(), 1e-4);
  }

  EXPECT_EQ(s21::Controller::GetInstance().NormalsUsage(), true);
  EXPECT_EQ(s21::Controller::GetInstance().TextureUsage(), false);

  s21::Controller::GetInstance().clearArrays();
  EXPECT_EQ(s21::Controller::GetInstance().GetPolygonsArray().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetIndices().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetVertices().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetUV().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetNormals().isEmpty(), true);

  EXPECT_EQ(s21::Controller::GetInstance().NormalsUsage(), false);
  EXPECT_EQ(s21::Controller::GetInstance().TextureUsage(), false);
}

TEST(LoadingModels, CubeNoTextureAndLight) {
  s21::Controller::GetInstance().ParseVertex_3D(
      "../Unit-tests/OBJ/cube_no_texture_and_light.obj");

  QVector<GLfloat> polygons_after_pars = {
      1,  1,  -1, 0, 0,  0,  0,  0, -1, 1,  -1, 0, 0,  0,  0,  0, -1, 1,  1,  0,
      0,  0,  0,  0, 1,  1,  -1, 0, 0,  0,  0,  0, -1, 1,  1,  0, 0,  0,  0,  0,
      1,  1,  1,  0, 0,  0,  0,  0, 1,  -1, 1,  0, 0,  0,  0,  0, 1,  1,  1,  0,
      0,  0,  0,  0, -1, 1,  1,  0, 0,  0,  0,  0, 1,  -1, 1,  0, 0,  0,  0,  0,
      -1, 1,  1,  0, 0,  0,  0,  0, -1, -1, 1,  0, 0,  0,  0,  0, -1, -1, 1,  0,
      0,  0,  0,  0, -1, 1,  1,  0, 0,  0,  0,  0, -1, 1,  -1, 0, 0,  0,  0,  0,
      -1, -1, 1,  0, 0,  0,  0,  0, -1, 1,  -1, 0, 0,  0,  0,  0, -1, -1, -1, 0,
      0,  0,  0,  0, -1, -1, -1, 0, 0,  0,  0,  0, 1,  -1, -1, 0, 0,  0,  0,  0,
      1,  -1, 1,  0, 0,  0,  0,  0, -1, -1, -1, 0, 0,  0,  0,  0, 1,  -1, 1,  0,
      0,  0,  0,  0, -1, -1, 1,  0, 0,  0,  0,  0, 1,  -1, -1, 0, 0,  0,  0,  0,
      1,  1,  -1, 0, 0,  0,  0,  0, 1,  1,  1,  0, 0,  0,  0,  0, 1,  -1, -1, 0,
      0,  0,  0,  0, 1,  1,  1,  0, 0,  0,  0,  0, 1,  -1, 1,  0, 0,  0,  0,  0,
      -1, -1, -1, 0, 0,  0,  0,  0, -1, 1,  -1, 0, 0,  0,  0,  0, 1,  1,  -1, 0,
      0,  0,  0,  0, -1, -1, -1, 0, 0,  0,  0,  0, 1,  1,  -1, 0, 0,  0,  0,  0,
      1,  -1, -1, 0, 0,  0,  0,  0};
  EXPECT_EQ(s21::Controller::GetInstance().GetPolygonsArray().size(),
            polygons_after_pars.size());
  for (auto it = 0;
       it < s21::Controller::GetInstance().GetPolygonsArray().size(); ++it)
    EXPECT_NEAR(s21::Controller::GetInstance().GetPolygonsArray()[it],
                polygons_after_pars[it], 1e-4);

  QVector<GLuint> indices = {0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11,
                             12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,
                             24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};
  EXPECT_EQ(s21::Controller::GetInstance().GetIndices().size(), indices.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetIndices().size();
       ++it)
    EXPECT_EQ(s21::Controller::GetInstance().GetIndices()[it], indices[it]);

  QVector<QVector3D> vertices = {
      QVector3D(0, 0, 0),    QVector3D(1, 1, -1), QVector3D(1, -1, -1),
      QVector3D(1, 1, 1),    QVector3D(1, -1, 1), QVector3D(-1, 1, -1),
      QVector3D(-1, -1, -1), QVector3D(-1, 1, 1), QVector3D(-1, -1, 1)};
  EXPECT_EQ(s21::Controller::GetInstance().GetVertices().size(),
            vertices.size());
  for (auto it = 0; it < s21::Controller::GetInstance().GetVertices().size();
       ++it) {
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].x(),
                vertices[it].x(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].y(),
                vertices[it].y(), 1e-4);
    EXPECT_NEAR(s21::Controller::GetInstance().GetVertices()[it].z(),
                vertices[it].z(), 1e-4);
  }

  EXPECT_EQ(s21::Controller::GetInstance().GetUV().size(), 1);
  EXPECT_EQ(s21::Controller::GetInstance().GetUV()[0] == QVector2D(0, 0), true);

  EXPECT_EQ(s21::Controller::GetInstance().GetNormals().size(), 1);
  EXPECT_EQ(
      s21::Controller::GetInstance().GetNormals()[0] == QVector3D(0, 0, 0),
      true);

  EXPECT_EQ(s21::Controller::GetInstance().NormalsUsage(), false);
  EXPECT_EQ(s21::Controller::GetInstance().TextureUsage(), false);

  s21::Controller::GetInstance().clearArrays();
  EXPECT_EQ(s21::Controller::GetInstance().GetPolygonsArray().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetIndices().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetVertices().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetUV().isEmpty(), true);
  EXPECT_EQ(s21::Controller::GetInstance().GetNormals().isEmpty(), true);

  EXPECT_EQ(s21::Controller::GetInstance().NormalsUsage(), false);
  EXPECT_EQ(s21::Controller::GetInstance().TextureUsage(), false);
}
