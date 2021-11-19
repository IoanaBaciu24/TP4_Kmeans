//
// Created by Baciu Ioana on 04.10.2021.
//
#include <stdlib.h>
#include <stdio.h>
//#include "ioUtils.h"
#include "filteringUtils.h"
#include "kmeans_utils.h"
#include <time.h>
//#include "histogramUtils.h"

int main(int argc, char *argv[])
{
    FILE *input_file_descriptor, *output_file_descriptor;
    srand(time(0));

    if(argc<4)
    {
        printf("Please give all the args\n");
        exit(1);
    }

    char *input_file_name = argv[1];
    char *output_file_name = argv[2];


    input_file_descriptor = fopen(input_file_name,"r");
    if (input_file_descriptor == NULL) {
        printf("error in opening file %s\n", input_file_name);
        exit(1);
    }


    output_file_descriptor = fopen(output_file_name,"w");
    if (output_file_descriptor == NULL) {
        printf("error in opening file %s\n", output_file_name);
        exit(1);
    }

    int smoothening_intensity = atoi(argv[3]);
    if(smoothening_intensity<=0)
    {
        printf("bad value for intensity. shame.");
        exit(1);

    }

    image_structure_rgb_t *img = read_rgb_image(input_file_descriptor);
//    image_structure_t *new_img = smooth_image_n_times_median_filter(img, 3, smoothening_intensity);
//    int *histogram = compute_histogram(img);
//
//    int min=0, max=0;
//    for(int i=0;i<=255;i++)
//    {
//        if(histogram[i]!=0)
//        {
//            min = i;
//            break;
//        }
//    }
//
//    for(int i=255;i>=0;i--)
//    {
//        if(histogram[i]!=0)
//        {
//            max = i;
//            break;
//        }
//    }
//    image_structure_t *new_img = histogram_stretching(img, min, max);
//    image_structure_t *new_img =treshold_magnitude(img, 70);
//            write_image_to_file(new_img,output_file_descriptor);
//         img = k_means_yay(img,  5);
    image_structure_rgb_t *new_img =k_means_yay(img, 20);
    write_image_to_file_rgb(new_img, output_file_descriptor);


}

