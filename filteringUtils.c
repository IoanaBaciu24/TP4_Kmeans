//
// Created by Baciu Ioana on 04.10.2021.
//

//#include "ioUtils.h"
#include "filteringUtils.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int get_dot_prod(image_structure_t *img, int *matrix,  int start_i, int start_j, int end_i, int end_j, int pos_i, int pos_j)
{
    int sum = 0;
    int count = 0;
    int weight = 0;
    int val = 0, val_i, val_j;
    for(int i = start_i; i<=end_i;i++){
        for(int j=start_j;j<=end_j;j++)
        {
           if(i<0 || i>img->rows || j<0 || j>img->cols)
           {
                val_i = pos_i - i;
                val_j = pos_j - j;
                val = img->image_matrix[(pos_i+val_i)*img->cols+(pos_j+val_j)];
           }
           else{
               val = (int)img->image_matrix[i*img->cols+j];
           }
            sum+=val*matrix[count];
            weight+=matrix[count];
            count+=1;}
        }
    return (int)sum/weight;

    }

int get_dot_prod_gradient(image_structure_t *img, int *matrix,  int start_i, int start_j, int end_i, int end_j, int pos_i, int pos_j)
{
    int sum = 0;
    int count = 0;
    int val = 0, val_i, val_j;
    for(int i = start_i; i<=end_i;i++){
        for(int j=start_j;j<=end_j;j++)
        {
            if(i<0 || i>img->rows || j<0 || j>img->cols)
            {
                val_i = pos_i - i;
                val_j = pos_j - j;
                val = img->image_matrix[(pos_i+val_i)*img->cols+(pos_j+val_j)];
            }
            else{
                val = (int)img->image_matrix[i*img->cols+j];
            }
            sum+=val*matrix[count];
            count+=1;}
    }
    sum = abs(sum);
    return (int)sum/16;

}

int cmpfunc (const void * a, const void * b) {
    return ( *(int*)a - *(int*)b );
}

    int get_median_value(image_structure_t *img, int window,  int start_i, int start_j, int end_i, int end_j, int pos_i, int pos_j)
    {
        int values_in_window[window*window];
        int count = 0;
        int val = 0, val_i, val_j;
        for(int i = start_i; i<=end_i;i++){
            for(int j=start_j;j<=end_j;j++)
            {
                if(i<0 || i>img->rows || j<0 || j>img->cols)
                {
                    val_i = pos_i - i;
                    val_j = pos_j - j;
                    val = img->image_matrix[(pos_i+val_i)*img->cols+(pos_j+val_j)];
                }
                else{
                    val = (int)img->image_matrix[i*img->cols+j];
                }
                values_in_window[count++] = val;
                }
        }
        qsort(values_in_window, count, sizeof(int), cmpfunc);
        return values_in_window[(int)count/2+1];
    }

image_structure_t *smooth_image_median_filter(image_structure_t *img, int size_of_kernel)
{
    int start_i,start_j, end_i, end_j, pos_i, pos_j;
    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(img->rows*img->cols* sizeof(unsigned char));

    for(int i=0;i<img->rows;i++){
        for(int j=0;j<img->cols;j++){
            pos_i = i;
            pos_j = j;
            start_i = i-(int)size_of_kernel/2;
            end_i= i+(int)size_of_kernel/2;

            start_j = j-(int)size_of_kernel/2;
            end_j= j+(int)size_of_kernel/2;

            new_img_matrix[i*img->cols+j] = (char)get_median_value(img, size_of_kernel, start_i, start_j, end_i, end_j, pos_i, pos_j);

        }
    }

    new_image->maxval = 255;
    new_image->cols = img->cols;
    new_image->rows = img->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;
}



image_structure_t *smooth_image(image_structure_t *img, int size_of_kernel)
{
    int *kernel;
    int kernel_3[] = {1,2,1,2,4,2,1,2,1};
    int kernel_5[] = {1,4,6,4,1,4,16,24,16,4,6,24,36,24,6,4,16,24,16,4,1,4,6,4,1};
    if(size_of_kernel == 3)
        kernel = kernel_3;
    else
        kernel = kernel_5;
    int start_i,start_j, end_i, end_j, pos_i, pos_j;


    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(img->rows*img->cols* sizeof(unsigned char));


    for(int i=0;i<img->rows;i++){
        for(int j=0;j<img->cols;j++){
           pos_i = i;
           pos_j = j;
           start_i = i-(int)size_of_kernel/2;
           end_i= i+(int)size_of_kernel/2;

           start_j = j-(int)size_of_kernel/2;
           end_j= j+(int)size_of_kernel/2;

           new_img_matrix[i*img->cols+j] = (char)get_dot_prod(img, kernel, start_i, start_j, end_i, end_j, pos_i, pos_j);

        }
    }

    new_image->maxval = 255;
    new_image->cols = img->cols;
    new_image->rows = img->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;


}

image_structure_t *smooth_image_n_times(image_structure_t *img, int size_of_kernel, int smooth_intensity)
{
    for(int i=0;i<smooth_intensity;i++)
    {
        img = smooth_image(img, size_of_kernel);
    }
    return img;
}

image_structure_t *smooth_image_n_times_median_filter(image_structure_t *img, int window_size, int smooth_intensity)
{
    for(int i=0;i<smooth_intensity;i++)
    {
        img = smooth_image_median_filter(img, window_size);
    }
    return img;
}

image_structure_t *obtain_gradient(image_structure_t *img, int axis)
{
    int *kernel;
    int kernel_x[10] = {(-1)*3, 0, 3, (-1)*10, 0, 10, (-1)*3, 0, 3};
    int kernel_y[10] = {(-1)*3, (-1)*10, (-1)*3, 0, 0, 0, 3, 10, 3};

    if(axis == 0)
        kernel = kernel_x;
    else
        kernel = kernel_y;
    int start_i,start_j, end_i, end_j, pos_i, pos_j;

    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(img->rows*img->cols* sizeof(unsigned char));


    for(int i=0;i<img->rows;i++){
        for(int j=0;j<img->cols;j++){
            pos_i = i;
            pos_j = j;
            start_i = i-1;
            end_i= i+1;

            start_j = j-1;
            end_j= j+1;

            new_img_matrix[i*img->cols+j] = (char)get_dot_prod_gradient(img, kernel, start_i, start_j, end_i, end_j, pos_i, pos_j);

        }


    }

    new_image->maxval = 255;
    new_image->cols = img->cols;
    new_image->rows = img->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;

}

image_structure_t *obtain_magnitude(image_structure_t *grad_x, image_structure_t *grad_y)
{
//    image_structure_t *grad_x = obtain_gradient(img, 0);
//    image_structure_t *grad_y = obtain_gradient(img, 1);

    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(grad_x->rows*grad_x->cols* sizeof(unsigned char));

    for(int i=0;i<grad_x->rows;i++){
        for(int j=0;j<grad_x->cols;j++){


            new_img_matrix[i*grad_x->cols+j] = (char)((int)sqrt(grad_x->image_matrix[i*grad_x->cols+j]*grad_x->image_matrix[i*grad_x->cols+j] + grad_y->image_matrix[i*grad_x->cols+j]*grad_y->image_matrix[i*grad_x->cols+j]));

        }}

        new_image->maxval = 255;
        new_image->cols = grad_x->cols;
        new_image->rows = grad_x->rows;

        new_image->image_matrix = new_img_matrix;

        return new_image;

}

image_structure_t *non_maximum_suppression(image_structure_t *magnitude, image_structure_t *grad_x, image_structure_t *grad_y){
    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = calloc(grad_x->rows*grad_x->cols,  sizeof(unsigned char));
    int intensity1, intensity2;
    double angle;
    for(int i=1;i<grad_x->rows-1;i++){
        for(int j=1;j<grad_x->cols-1;j++){

            intensity1 = 255;
            intensity2 = 255;
            angle = (double)(180. * atan((double )grad_y->image_matrix[i*grad_x->cols+j]/(double )grad_x->image_matrix[i*grad_x->cols+j]))/M_PI;
            if ((0 <= angle && angle < 22.5) || (157.5 <= angle && angle <= 180))
            {
                intensity1 = magnitude->image_matrix[i*grad_x->cols+j+1];
                intensity2 = magnitude->image_matrix[i*grad_x->cols+j-1];
            }

            else if (22.5 <= angle && angle < 67.5){
                intensity1 = magnitude->image_matrix[(i+1)*grad_x->cols+j-1];
                intensity2 = magnitude->image_matrix[(i-1)*grad_x->cols+j+1];
            }
            else if (67.5 <= angle && angle < 112.5){
                intensity1 = magnitude->image_matrix[(i+1)*grad_x->cols+j];
                intensity2 = magnitude->image_matrix[(i-1)*grad_x->cols+j];
            }

            else if (112.5 <= angle && angle < 157.5){
                intensity1 = magnitude->image_matrix[(i-1)*grad_x->cols+j-1];
                intensity2 = magnitude->image_matrix[(i+1)*grad_x->cols+j+1];
            }

            if ((magnitude->image_matrix[i*grad_x->cols+j] >= (char)((int)intensity1)) && (magnitude->image_matrix[i*grad_x->cols+j] >= (char)((int)intensity2))){
                new_img_matrix[i*grad_x->cols+j] = magnitude->image_matrix[i*grad_x->cols+j];
            }
            else{
                new_img_matrix[i*grad_x->cols+j] = 0;

            }

        }
    }

    new_image->maxval = 255;
    new_image->cols = grad_x->cols;
    new_image->rows = grad_x->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;
}

image_structure_t *hysteria(image_structure_t *non_max, int t_low, int t_high)
{

    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(non_max->rows*non_max->cols* sizeof(unsigned char));

    for(int i=0;i<non_max->rows;i++){
        for(int j=0;j<non_max->cols;j++){

                if(non_max->image_matrix[i*non_max->cols+j] > t_high)
                    new_img_matrix[i*non_max->cols+j] = 255;
                else if(non_max->image_matrix[i*non_max->cols+j] < t_low)
                    new_img_matrix[i*non_max->cols+j] = 0;
                else{
                    if( non_max->image_matrix[(i-1)*non_max->cols+j-1] > t_high ||
                            non_max->image_matrix[(i+1)*non_max->cols+j-1] > t_high ||
                            non_max->image_matrix[(i+1)*non_max->cols+j] > t_high ||
                            non_max->image_matrix[(i+1)*non_max->cols+j+1] > t_high ||
                            non_max->image_matrix[i*non_max->cols+j-1] > t_high ||
                            non_max->image_matrix[i*non_max->cols+j+1] > t_high ||
                            non_max->image_matrix[(i-1)*non_max->cols+j] > t_high ||
                            non_max->image_matrix[(i-1)*non_max->cols+j+1] > t_high

                            )                     new_img_matrix[i*non_max->cols+j] = 255;
                    else
                        new_img_matrix[i*non_max->cols+j] = 0;


                }

        }}

    new_image->maxval = 255;
    new_image->cols = non_max->cols;
    new_image->rows = non_max->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;

}

image_structure_t *treshold_magnitude(image_structure_t *img, int threshold)
{
    image_structure_t *grad_x = obtain_gradient(img, 0);
    image_structure_t *grad_y = obtain_gradient(img, 1);

    // magnitude thing
    image_structure_t *magnitude = obtain_magnitude(grad_x, grad_y);


    image_structure_t *new_image = malloc(sizeof(image_structure_t));
    unsigned char *new_img_matrix = malloc(img->rows*img->cols* sizeof(unsigned char));

    for(int i=0;i<img->rows;i++){
        for(int j=0;j<img->cols;j++){


//            new_img_matrix[i*img->cols+j] = (char)((int)sqrt(grad_x->image_matrix[i*grad_x->cols+j]*grad_x->image_matrix[i*grad_x->cols+j] + grad_y->image_matrix[i*grad_x->cols+j]*grad_y->image_matrix[i*grad_x->cols+j]));
                if(magnitude->image_matrix[i*img->cols+j] > threshold)
                    new_img_matrix[i*img->cols+j] = magnitude->image_matrix[i*img->cols+j];
                else new_img_matrix[i*img->cols+j] = 0;
        }}

    new_image->maxval = 255;
    new_image->cols = img->cols;
    new_image->rows = img->rows;

    new_image->image_matrix = new_img_matrix;

    return new_image;
}


image_structure_t *canny_detector(image_structure_t *img)
{
    // gradient thing
    image_structure_t *grad_x = obtain_gradient(img, 0);
    image_structure_t *grad_y = obtain_gradient(img, 1);

    // magnitude thing
    image_structure_t *magnitude = obtain_magnitude(grad_x, grad_y);

    // non maximum thing
    image_structure_t *non_max = non_maximum_suppression(magnitude, grad_x, grad_y);
    image_structure_t *hyst = hysteria(non_max, 5, 40);
    return hyst;



}


