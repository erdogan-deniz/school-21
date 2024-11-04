
#ifndef SRC_3D_VIEWER_H_
#define SRC_3D_VIEWER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct polygons {
  int sum_of_vertexes;
  int *polygon_vertex;

} polygons_t;

typedef struct matrix {
  int row;
  int column;
  double **matrix;
} matrix_t;

typedef struct obj_data {
  double *matrix_vertexes;
  int summ_of_vertexes;
  int *matrix_polygons;
  int summ_of_polygons;

  int count_of_vertexes;
  int count_of_facets;
  matrix_t matrix;
  polygons_t *polygons;
} obj_data;

void start_parse_obj_file(obj_data *data, char *path_to_obj_file);
double stod(char *string, char *point);
void free_mem(obj_data *data);
// void print_struct_parsed_data(obj_data data);

// vertexes
void parse_string(char *string_for_parse, matrix_t *matrix, int count);
void build_matrix_vertex(FILE *file, obj_data *data);

// converting to openglformat
void convert_to_opengl_vertexes(obj_data *data);
void convert_to_opengl_polygons(obj_data *data);

double maximum_difference(double diff_x, double diff_y, double diff_z);
void resize_matrix_on_screen(obj_data *data, double value);
void centred(obj_data *data);

// matrix_change
void matrix_rotate(obj_data *data, char coord, double angle);
void matrix_scale(obj_data *data, double scale);
void matrix_move(obj_data *data, char coord, double value);

double min_coord(obj_data *data, int xyz);
double max_coord(obj_data *data, int xyz);

// polygons
void build_polygons(FILE *file, obj_data *data);
int parse_num_poligons(char *string_for_parse);
void parse_string_for_poligon(char *string_for_parse, polygons_t *polygons);

#endif  //  SRC_3D_VIEWER_H
