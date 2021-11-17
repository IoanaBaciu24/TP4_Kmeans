//
// Created by Baciu Ioana on 04.10.2021.
//

#ifndef VISUALCOMPUTING_TP2_FILTERINGUTILS_H
#define VISUALCOMPUTING_TP2_FILTERINGUTILS_H

#endif //VISUALCOMPUTING_TP2_FILTERINGUTILS_H

#include "ioUtils.h"


image_structure_t *smooth_image(image_structure_t *img, int size_of_kernel);
image_structure_t *smooth_image_n_times(image_structure_t *img, int size_of_kernel, int smooth_intensity);
image_structure_t *smooth_image_n_times_median_filter(image_structure_t *img, int window_size, int smooth_intensity);

image_structure_t *obtain_gradient(image_structure_t *img, int axis);
image_structure_t *obtain_magnitude(image_structure_t *grad_x, image_structure_t *grad_y);
image_structure_t *canny_detector(image_structure_t *img);
image_structure_t *treshold_magnitude(image_structure_t *img, int threshold);