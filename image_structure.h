//
// Created by Baciu Ioana on 08.10.2021.
//

#ifndef VISUALCOMPUTING_TP2_IMAGE_STRUCTURE_H
#define VISUALCOMPUTING_TP2_IMAGE_STRUCTURE_H
typedef struct Point{
    int x,y;
}point_t;
typedef struct ImageStructureRGB{
    int maxval, rows,cols;
    unsigned char* red;
    unsigned char* green;
    unsigned char* blue;

} image_structure_rgb_t;
typedef struct ImageStructure{
    int maxval, rows,cols;
    unsigned char* image_matrix;

} image_structure_t;

typedef struct cluster{

    int r, g, b;
    point_t *points;
    int size;

}clusters_t;


typedef struct cluster2{
    int i,j;
    int r, g, b;
    point_t *points;
    int size;
}clusters2_t;

#endif //VISUALCOMPUTING_TP2_IMAGE_STRUCTURE_H

//typedef struct ImageStructure{
//    int maxval, rows,cols;
//    unsigned char* image_matrix;
//} image_structure_t;
