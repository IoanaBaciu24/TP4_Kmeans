//
// Created by Baciu Ioana on 04.10.2021.
//

#ifndef VISUALCOMPUTING_TP2_IOUTILS_H
#define VISUALCOMPUTING_TP2_IOUTILS_H

#endif //VISUALCOMPUTING_TP2_IOUTILS_H

#include <stdio.h>
#include "image_structure.h"

//typedef struct ImageStructure{
//    int maxval, rows,cols;
//    unsigned char* image_matrix;
//} image_structure_t;


char pm_getc(FILE* file);
//bit pm_getbit(FILE* file);
unsigned char pm_getrawbyte(FILE* file);
int pm_getint( FILE* file);

void pm_erreur(char *);
image_structure_t * read_image(FILE *file_descr);
image_structure_rgb_t *read_rgb_image(FILE *file);
void write_image_to_file(image_structure_t *img, FILE *fp);
void write_image_to_file_rgb(image_structure_rgb_t *img, FILE *fp);