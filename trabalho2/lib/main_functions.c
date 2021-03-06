#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main_functions.h"
#include "file_manipulation.h"
#include "ilbp.h"
#include "glcm.h"

void ILBP_GLCM_vector(double *super_vector_asphalt, double* super_vector_grass, int photos){
  char file_asphalt[100], file_grass[100];
  int columns, lines;
  int **file_matrix;

  //Monta os caminhos dos arquivos de grama e asfalto
  file_path(file_asphalt, file_grass, photos);

  //ASFALTO
  //calcula linhas e colunas:
  columns = count_columns(file_asphalt);
  lines = count_lines(file_asphalt);

  //monta a matriz do arquivo
  file_matrix = build_matrix(file_asphalt, lines, columns);
  //Calcula o ILBP e GLCM
  ILBP(file_matrix, lines, columns, super_vector_asphalt);
  GLCM(file_matrix, lines, columns, super_vector_asphalt);
  vector_normalize(super_vector_asphalt);

  //GRAMA
  //calcula linhas e colunas:
  columns = count_columns(file_grass);
  lines = count_lines(file_grass);

  //monta a matriz do arquivo
  file_matrix = build_matrix(file_grass, lines, columns);
  //Calcula o ILBP e GLCM
  ILBP(file_matrix, lines, columns, super_vector_grass);
  GLCM(file_matrix, lines, columns, super_vector_grass);
  vector_normalize(super_vector_grass);

}

void vector_normalize(double *vector){
  double bigger = 0;
  double smaller = 127444;

  for (int j = 0; j < 537; j++) {
    if (vector[j]>bigger)
      bigger = vector[j];
  }
  for (int j = 0; j < 5; j++) {
    if (vector[j]<smaller)
      smaller = vector[j];
  }
  for (int k = 0; k < 537; k++) {
    vector[k] = (vector[k]-smaller)/(bigger-smaller);
  }
}

int vector_classification(double *vector, double *average_asphalt_vector, double *average_grass_vector){

  if (vector_distance(vector, average_asphalt_vector) < vector_distance(vector, average_grass_vector))
    return 1;
  else
    return 0;

}

double vector_distance(double *vector, double *average_vector){
  double distance = 0;

  for (int i = 0; i < 537; i++) {
    distance += pow((vector[i]-average_vector[i]), 2.0);
  }
  distance = pow(distance, 0.5);
  return distance;
}

double* vector_average(double** super_matrix){
  double*vector = (double*) calloc(537, sizeof(double));

  for (int i = 0; i < 25; i++) {
    for (int j = 0; j < 537; j++) {
      vector[j]+= super_matrix[i][j];
    }
  }

  for (int i = 0; i < 537; i++) {
    vector[i]=vector[i]/25;
  }
  return vector;
}
