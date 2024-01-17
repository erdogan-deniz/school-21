#include "3d_viewer.h"

double stod(char *string, char *point) {
  // printf("\nSTRING _%s_", string);

  // printf("\nPOINT _%s_", point);
  int flag_dot_in_line = 0;
  int count_exp = 0;

  long double temp = 0;
  int flag_unar_minus = 0;

  if (*string == '-') {
    flag_unar_minus = 1;
  }

  for (; string != point; string++) {
    // printf("\nstart ccccc = %c ", *string);
    if (*string == ' ') {
      continue;
    }
    if (*string == '.') {
      flag_dot_in_line = 1;
      count_exp = 0;
    }

    if (*string >= 48 && *string <= 57) {
      if (flag_dot_in_line) {
        count_exp++;
      }
      // int cast_to_int = *string;
      temp = (temp * 10) + ((int)*string - 48);
    }
  }

  // printf("_%d_", fabsl(temp) == 1e-7);
  // printf("!%d! ", count_exp);

  if (count_exp) {
    // printf("%f", pow(10, count_exp));
    temp = temp / pow(10, count_exp);
  }

  if (flag_unar_minus) {
    temp *= -1;
  }

  // printf("!!!!%Lf\n - ", temp);
  return temp;
}

void parse_string(char *string_for_parse, matrix_t *matrix, int count) {
  char *string = string_for_parse;
  char *point = string;

  int counter_for_data = 0;

  // int flag = 1;
  do {
    if (*point == ' ' || *point == '\0' || *point == '(' || *point == ')') {
      for (; string != point; string++) {
        if (*string == ' ') {
          continue;
        }

        if ((*string >= 48 && *string <= 57) || *string == '-') {
          matrix->matrix[count][counter_for_data] = stod(string, point);
          counter_for_data += 1;
          string = point;
          break;
        }
      }
    }
    point++;
  } while (*string);
}

void parse_string_for_poligon(char *string_for_parse, polygons_t *polygons) {
  char *string = string_for_parse;
  char *point = string;

  int counter_for_data = 0;

  int flag_space = 0;

  do {
    if (*point == ' ' || *point == '\0' || *point == '/') {
      // 677/1/1 678/2/2 679/3/3 680/4/4

      if (*point == '/' && flag_space == 1) {
        point++;
        continue;
      }

      else if ((*point == ' ') && flag_space == 1) {
        string = point;
        point++;
        flag_space = 0;
        continue;
      }

      if (*point == '\0' && flag_space == 1) {
        // string = point;
        // point++;
        // flag_space = 0;
        break;
      }

      if (*point == '/') {
        flag_space = 1;
      };

      for (; string != point; string++) {
        if (*string == ' ') {
          continue;
        }

        if ((*string >= 48 && *string <= 57) || *string == '-') {
          polygons->polygon_vertex[counter_for_data] = (int)stod(string, point);
          string = point;
          counter_for_data += 1;
          break;
        }
      }
    }
    if (*point == '\0') {
      break;
    }

    point++;

  } while (*string);
}

int parse_num_poligons(char *string_for_parse) {
  char *string = string_for_parse;

  int count = 0;
  do {
    if (*string == ' ' || *string == '\0') {
      count++;
    }

    string++;
  } while (*string);

  // double * return_arr = return_data;
  return count;
}

void build_polygons(FILE *file, obj_data *data) {
  polygons_t *polygons =
      (polygons_t *)calloc(data->count_of_facets + 1, sizeof(polygons_t));

  if (polygons == NULL) {
    exit(0);
  }

  char str_v[255] = {0};

  int num_of_line = 0;

  while (fgets(str_v, sizeof(str_v), file) != NULL) {
    if (!strncmp(str_v, "f ", 2)) {
      char *string_for_poligon_parse = str_v;
      // int alloc_num = parse_num_poligons(string_for_poligon_parse);
      polygons[num_of_line].sum_of_vertexes =
          parse_num_poligons(string_for_poligon_parse);

      // polygons[num_of_line].polygon_vertex = NULL;
      polygons[num_of_line].polygon_vertex =
          (int *)calloc(polygons[num_of_line].sum_of_vertexes, sizeof(int));

      parse_string_for_poligon(string_for_poligon_parse,
                               &polygons[num_of_line]);

      num_of_line += 1;
    }
  }

  data->polygons = polygons;
  // exit(0);
  // free(polygons[num_of_line].polygon_vertex);
  // free(polygons);
}

void build_matrix_vertex(FILE *file, obj_data *data) {
  matrix_t matrix_vertexes = {0};

  matrix_vertexes.row = data->count_of_vertexes;
  matrix_vertexes.column = 3;

  matrix_vertexes.matrix =
      (double **)calloc(matrix_vertexes.row, sizeof(double *));

  if (matrix_vertexes.matrix == NULL) {
    exit(0);
  }

  for (int i = 0; i < matrix_vertexes.row; i++) {
    matrix_vertexes.matrix[i] =
        (double *)calloc(matrix_vertexes.column, sizeof(double));
  }

  matrix_vertexes.matrix[0][0] = 0;
  matrix_vertexes.matrix[0][1] = 0;
  matrix_vertexes.matrix[0][2] = 0;

  char str_v[255] = {0};

  int num_of_line = 0;

  while (fgets(str_v, sizeof(str_v), file) != NULL) {
    if (!strncmp(str_v, "v ", 2)) {
      num_of_line += 1;

      char *string_for_vertexes_parse = str_v;
      parse_string(string_for_vertexes_parse, &matrix_vertexes, num_of_line);
    }
  }

  data->matrix = matrix_vertexes;
}

// void print_struct_parsed_data(obj_data data) {
//   // print_vertexes
//   for (int i = 0; i < data.matrix.row; i++) {
//     printf("v ");
//     for (int j = 0; j < data.matrix.column; j++) {
//       printf("%f ", data.matrix.matrix[i][j]);
//     }
//     printf("\n");
//   }

//   // print_polygons
//   for (int i = 0; i < data.count_of_facets; i++) {
//     printf("f ");
//     for (int j = 0; j < data.polygons[i].sum_of_vertexes; j++) {
//       printf("%d ", data.polygons[i].polygon_vertex[j]);
//     }
//     printf("\n");
//   }

//   for (int i = 0; i < data.summ_of_polygons; i++) {
//     printf(" %d ", data.matrix_polygons[i]);
//   }
// }

void free_mem(obj_data *data) {
  // free vertexes mem
  for (int i = 0; i < data->count_of_vertexes; i++) {
    free(data->matrix.matrix[i]);
  }
  free(data->matrix.matrix);
  data->matrix.matrix = NULL;
  data->matrix.row = 0;
  data->matrix.column = 0;

  // free polygons mem
  for (int i = 0; i <= data->count_of_facets; i++) {
    free(data->polygons[i].polygon_vertex);
  }
  free(data->polygons);

  free(data->matrix_polygons);
  free(data->matrix_vertexes);
}

void convert_to_opengl_vertexes(obj_data *data) {
  if (data->matrix_vertexes != NULL) {
    free(data->matrix_vertexes);
  }

  int summ_of_vertexes = data->count_of_vertexes * 3;

  double *arr_vert_ogl = (double *)calloc(summ_of_vertexes, sizeof(double));

  if (arr_vert_ogl == NULL) {
    printf("\n\n EXIT");
    exit(0);
  }

  int count = 0;

  for (int i = 0; i < data->count_of_vertexes; i++) {
    for (int j = 0; j < 3; j++) {
      arr_vert_ogl[count] = data->matrix.matrix[i][j];
      count++;
    }
  }

  data->summ_of_vertexes = summ_of_vertexes;
  data->matrix_vertexes = arr_vert_ogl;
}

void convert_to_opengl_polygons(obj_data *data) {
  if (data->matrix_polygons != NULL) {
    // printf("!!!!!!__ %d \n", *data->matrix_polygons);
    free(data->matrix_polygons);
  }

  data->summ_of_polygons = 0;

  for (int i = 0; i < data->count_of_facets; i++) {
    data->summ_of_polygons += data->polygons[i].sum_of_vertexes * 2;
  }

  // printf("---------%d\n", data->summ_of_polygons);

  int *polygons = (int *)calloc(data->summ_of_polygons, sizeof(int));
  if (polygons == NULL) {
    exit(0);
  }

  int count = 0;

  for (int i = 0; i < data->count_of_facets; i++) {
    for (int j = 0; j < data->polygons[i].sum_of_vertexes; j++) {
      // [1][2][3][3];

      if (j == 0 || j == 1) {
        polygons[count] = data->polygons[i].polygon_vertex[j];
        count++;
      }

      if (j == data->polygons[i].sum_of_vertexes - 1) {
        polygons[count] = data->polygons[i].polygon_vertex[j - 1];
        count++;
        polygons[count] = data->polygons[i].polygon_vertex[j];
        count++;

        polygons[count] = data->polygons[i].polygon_vertex[j];
        count++;
        polygons[count] = data->polygons[i].polygon_vertex[0];
        count++;
        break;
      }

      if (j > 1) {
        polygons[count] = data->polygons[i].polygon_vertex[j - 1];
        count++;
        polygons[count] = data->polygons[i].polygon_vertex[j];
        count++;
      }
    }
  }
  data->matrix_polygons = polygons;

  // for (int i = 0; i<data->summ_of_polygons;i++){
  // printf("__%d-(%d)__", data->matrix_polygons[i], i);
  // }
  // printf("\n");
}

double min_coord(obj_data *data, int xyz) {
  double min = 1000000;

  for (int i = 1; i < data->count_of_vertexes; i++) {
    if (data->matrix.matrix[i][xyz] < min) {
      min = data->matrix.matrix[i][xyz];
    }
  }
  return min;
}

double max_coord(obj_data *data, int xyz) {
  double max = -1000000;

  for (int i = 0; i < data->count_of_vertexes; i++) {
    if (data->matrix.matrix[i][xyz] > max) {
      max = data->matrix.matrix[i][xyz];
    }
  }
  return max;
}

void centred(obj_data *data) {
  double min_x = min_coord(data, 0);
  double min_y = min_coord(data, 1);
  double min_z = min_coord(data, 2);

  double max_x = max_coord(data, 0);
  double max_y = max_coord(data, 1);
  double max_z = max_coord(data, 2);

  double diff_x = (min_x + (max_x - min_x) / 2);
  double diff_y = (min_y + (max_y - min_y) / 2);
  double diff_z = (min_z + (max_z - min_z) / 2);

  for (int i = 1; i < data->count_of_vertexes; i++) {
    data->matrix.matrix[i][0] -= diff_x;
    data->matrix.matrix[i][1] -= diff_y;
    data->matrix.matrix[i][2] -= diff_z;
  }
  convert_to_opengl_vertexes(data);

  // int j = 0;
  // while(j < data->vertex_array.coords_number) {
  //     data->vertex_array.coords_array[j] -= diff_x;
  //     j++;
  //     data->vertex_array.coords_array[j] -= diff_y;
  //     j++;
  //     data->vertex_array.coords_array[j] -= diff_z;
  //     j++;
  // }
}

void resize_matrix_on_screen(obj_data *data, double value) {
  double max_x = max_coord(data, 0);
  double max_y = max_coord(data, 1);
  double max_z = max_coord(data, 2);

  double min_x = min_coord(data, 0);
  double min_y = min_coord(data, 1);
  double min_z = min_coord(data, 2);

  double diff_x = max_x - min_x;
  double diff_y = max_y - min_y;
  double diff_z = max_z - min_z;

  double diff_max = maximum_difference(diff_x, diff_y, diff_z);
  double scale_value = (value - (value * (-1))) / diff_max;

  matrix_scale(data, scale_value);
}

double maximum_difference(double diff_x, double diff_y, double diff_z) {
  double max;
  if (diff_x > diff_y)
    max = diff_x;
  else
    max = diff_y;
  if (diff_z > max) max = diff_z;
  return max;
}

void matrix_scale(obj_data *data, double scale) {
  if (scale != 0) {
    for (int i = 0; i < data->count_of_vertexes; i++) {
      for (int j = 0; j < 3; j++) {
        data->matrix.matrix[i][j] *= scale;
      }
    }

    convert_to_opengl_vertexes(data);
  }
}

void matrix_move(obj_data *data, char coord, double value) {
  int index;
  if (coord == 'x') {
    index = 0;
  } else if (coord == 'y') {
    index = 1;
  } else if (coord == 'z') {
    index = 2;
  }
  for (int i = 1; i < data->count_of_vertexes; i++) {
    data->matrix.matrix[i][index] += value;
  }
  convert_to_opengl_vertexes(data);
}

void matrix_rotate(obj_data *data, char coord, double angle) {
  if (coord == 'x') {
    for (int i = 0; i < data->count_of_vertexes; i++) {
      double temp_y = data->matrix.matrix[i][1];
      double temp_z = data->matrix.matrix[i][2];
      data->matrix.matrix[i][1] = cos(angle) * temp_y - sin(angle) * temp_z;
      data->matrix.matrix[i][2] = sin(angle) * temp_y + cos(angle) * temp_z;
    }

  } else if (coord == 'y') {
    for (int i = 0; i < data->count_of_vertexes; i++) {
      double temp_x = data->matrix.matrix[i][0];
      double temp_z = data->matrix.matrix[i][2];
      data->matrix.matrix[i][0] = cos(angle) * temp_x - sin(angle) * temp_z;
      data->matrix.matrix[i][2] = sin(angle) * temp_x + cos(angle) * temp_z;
    }
    // convert_to_opengl_vertexes(data);

  } else if (coord == 'z') {
    for (int i = 0; i < data->count_of_vertexes; i++) {
      double temp_x = data->matrix.matrix[i][0];
      double temp_y = data->matrix.matrix[i][1];
      data->matrix.matrix[i][0] = cos(angle) * temp_x - sin(angle) * temp_y;
      data->matrix.matrix[i][1] = sin(angle) * temp_x + cos(angle) * temp_y;
    }
    // convert_to_opengl_vertexes(data);
  }
  convert_to_opengl_vertexes(data);
}

void start_parse_obj_file(obj_data *data, char *path_to_obj_file) {
  data->count_of_facets += 0;

  FILE *file = fopen(path_to_obj_file, "r");
  if (!file) {
    exit(0);
  }
  // data = {0};
  char str[255] = {0};

  data->count_of_facets = 0;
  data->count_of_vertexes = 0;

  while (fgets(str, sizeof(str), file) != NULL) {
    if (!strncmp(str, "v ", 2)) {
      data->count_of_vertexes += 1;
      // printf("%d - vert \n", data->count_of_vertexes);
    }

    if (!strncmp(str, "f ", 2)) {
      data->count_of_facets += 1;
      // printf("%s", str);
      // printf("%d", data->count_of_facets);
    }
    memset(str, '\0', sizeof(str));
  }

  // data->matrix_vertexes = (double *) calloc(1, sizeof(double));
  // data->matrix_polygons = (int *) calloc(1, sizeof(int));

  data->matrix_vertexes = NULL;
  data->matrix_polygons = NULL;

  if (data->count_of_facets <= 0 || data->count_of_vertexes <= 0) {
    exit(0);
  }
  data->count_of_vertexes += 1;

  rewind(file);
  build_matrix_vertex(file, data);

  rewind(file);
  build_polygons(file, data);
  fclose(file);

  convert_to_opengl_vertexes(data);
  convert_to_opengl_polygons(data);

  // print_struct_parsed_data(*data);
}

// int main() {
//   obj_data address_of_parsed_struct = {0};
//   start_parse_obj_file(&address_of_parsed_struct, "cube_test.obj");

//   print_struct_parsed_data(address_of_parsed_struct);

//   printf("\n\n________ %d", address_of_parsed_struct.matrix_polygons[4]);
//   // printf("\n MAX X %f \n", max_coord(&address_of_parsed_struct,0));
//   // printf("\n MIN X %f \n", max_coord(&address_of_parsed_struct,0));

//   // address_of_parsed_struct
//   // matrix_scale(&address_of_parsed_struct, 2);
// // matrix_scale(&address_of_parsed_struct, 0.1);
//   // for (int i=0; i<address_of_parsed_struct.count_of_vertexes; i++){
//   //   for (int j=0; j<3; j++){
//   //     printf("% f ", address_of_parsed_struct.matrix.matrix[i][j]);
//   //   }
//   //   printf("\n");
//   // }

//   // for (int i=0; i<address_of_parsed_struct.summ_of_vertexes; i++){
//   //   printf("%f ", address_of_parsed_struct.matrix_vertexes[i]);
//   // }
//   // printf("\n");
//   // free(address_of_parsed_struct.matrix_vertexes);

//   free_mem(&address_of_parsed_struct);
//   // exit(0);
// }
