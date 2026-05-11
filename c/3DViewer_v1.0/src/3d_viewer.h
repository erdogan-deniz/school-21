/**
 * @file 3d_viewer.h
 * @brief Pure-C 3D model parser + affine-transform back end for
 *        `3DViewer_v1.0`.
 *
 * This is the **C** core consumed by the Qt front end (see
 * `qt_viewer/`). It owns the Wavefront OBJ parser, the
 * polygon / vertex buffers, and the in-place rotate / scale / move
 * primitives. The C++ rewrite (`cpp/3DViewer_v2.0`) replaces this
 * module with `Object` + `ReadFile` + `Transform`.
 */

#ifndef SRC_3D_VIEWER_H_
#define SRC_3D_VIEWER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Single polygon — list of vertex indices that form one face.
 */
typedef struct polygons {
  int sum_of_vertexes;   ///< Number of vertices in this polygon.
  int *polygon_vertex;   ///< Index buffer (1-based, as in OBJ).

} polygons_t;

/**
 * @brief Dynamically allocated 2-D matrix (rows × columns).
 *        Used for vertex coordinates during transform.
 */
typedef struct matrix {
  int row;          ///< Number of rows.
  int column;       ///< Number of columns.
  double **matrix;  ///< Row-major matrix data.
} matrix_t;

/**
 * @brief Top-level container produced by @ref start_parse_obj_file.
 *
 * Holds both the OpenGL-friendly flat vertex / index buffers
 * (`matrix_vertexes` + `matrix_polygons`) and the structured
 * `matrix_t` + `polygons_t` views used by the affine-transform
 * routines. The two representations are kept in sync.
 */
typedef struct obj_data {
  double *matrix_vertexes;   ///< Flat (x, y, z, ...) buffer for OpenGL.
  int summ_of_vertexes;      ///< Number of floats in @ref matrix_vertexes.
  int *matrix_polygons;      ///< Flat index buffer for OpenGL.
  int summ_of_polygons;      ///< Number of ints in @ref matrix_polygons.

  int count_of_vertexes;     ///< Vertex count (rows of @ref matrix).
  int count_of_facets;       ///< Polygon-face count.
  matrix_t matrix;           ///< Vertex matrix (count_of_vertexes × 3).
  polygons_t *polygons;      ///< Per-face index lists.
} obj_data;

/**
 * @brief Parse a Wavefront OBJ file end-to-end into @p data.
 * @param data Output container — caller-owned, must be freed with
 *             @ref free_mem.
 * @param path_to_obj_file Path to the `.obj` file on disk.
 */
void start_parse_obj_file(obj_data *data, char *path_to_obj_file);
/**
 * @brief Locale-agnostic double parser.
 * @param string Source string starting with a numeric token.
 * @param point Decimal-point character (`.` or `,`).
 * @return Parsed value as `double`.
 */
double stod(char *string, char *point);
/** @brief Release every buffer allocated inside @p data. */
void free_mem(obj_data *data);
// void print_struct_parsed_data(obj_data data);

// vertexes
/** @brief Parse one `v ...` line into @p matrix at row @p count. */
void parse_string(char *string_for_parse, matrix_t *matrix, int count);
/** @brief First pass: count vertices and allocate the matrix. */
void build_matrix_vertex(FILE *file, obj_data *data);

// converting to openglformat
/** @brief Convert @ref obj_data::matrix into flat @ref matrix_vertexes. */
void convert_to_opengl_vertexes(obj_data *data);
/** @brief Convert @ref obj_data::polygons into flat @ref matrix_polygons. */
void convert_to_opengl_polygons(obj_data *data);

/** @brief Returns the largest of three diffs — used for normalisation. */
double maximum_difference(double diff_x, double diff_y, double diff_z);
/** @brief Scale every vertex so the model fits on screen with @p value
 *         margin. */
void resize_matrix_on_screen(obj_data *data, double value);
/** @brief Translate the model so its bounding box is centred on origin. */
void centred(obj_data *data);

// matrix_change
/**
 * @brief Rotate every vertex around axis @p coord by @p angle radians.
 * @param coord `'x'`, `'y'`, or `'z'`.
 */
void matrix_rotate(obj_data *data, char coord, double angle);
/** @brief Uniformly scale every vertex by @p scale (1.0 = identity). */
void matrix_scale(obj_data *data, double scale);
/**
 * @brief Translate every vertex along axis @p coord by @p value.
 * @param coord `'x'`, `'y'`, or `'z'`.
 */
void matrix_move(obj_data *data, char coord, double value);

/** @brief Minimum coordinate along axis @p xyz (0=x, 1=y, 2=z). */
double min_coord(obj_data *data, int xyz);
/** @brief Maximum coordinate along axis @p xyz (0=x, 1=y, 2=z). */
double max_coord(obj_data *data, int xyz);

// polygons
/** @brief Second pass: read every `f ...` line into @ref obj_data::polygons. */
void build_polygons(FILE *file, obj_data *data);
/** @brief Count vertex indices on one polygon line. */
int parse_num_poligons(char *string_for_parse);
/** @brief Parse one `f ...` line into a single @ref polygons_t. */
void parse_string_for_poligon(char *string_for_parse, polygons_t *polygons);

#endif  //  SRC_3D_VIEWER_H
