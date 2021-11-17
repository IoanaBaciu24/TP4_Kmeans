//
// Created by Baciu Ioana on 08.11.2021.
//

#import "kmeans_utils.h"


int random_number_generator(int upper, int lower){
    return (rand() % (upper - lower + 1)) + lower;
}


clusters_t *random_initialization_rgb(int k){

    clusters_t *cluster_boysss = malloc(k* sizeof(clusters_t));
    for(int i=0;i<k;i++)
    {
        cluster_boysss[i].r = random_number_generator(255,0);
        cluster_boysss[i].g = random_number_generator(255,0);
        cluster_boysss[i].b = random_number_generator(255,0);
        cluster_boysss[i].size = 0;

    }
    return cluster_boysss;
}


image_structure_rgb_t *build_solution(clusters_t *clusters, int k, image_structure_rgb_t *img)
{
    image_structure_rgb_t *new_image = malloc(sizeof(image_structure_rgb_t));
    unsigned char *r = (unsigned char*) malloc(img->cols* img->rows*sizeof (unsigned char));
    unsigned char *g = (unsigned char*) malloc(img->cols* img->rows*sizeof (unsigned char));
    unsigned char *b = (unsigned char*) malloc(img->cols* img->rows*sizeof (unsigned char));
    for(int i=0;i<k;i++)
    {
//        printf("cluster size: %d, %d\n", clusters[0].size, clusters[1].size);
        for(int j=0;j<clusters[i].size;j++)
        {
            r[clusters[i].points[j].x * img->cols + clusters[i].points[j].y] = clusters[i].r;
            g[clusters[i].points[j].x * img->cols + clusters[i].points[j].y] = clusters[i].g;
            b[clusters[i].points[j].x * img->cols + clusters[i].points[j].x] = clusters[i].b;
        }
    }

    new_image->maxval = img->maxval;
    new_image->rows = img->rows;
    new_image->cols = img->cols;
    new_image->red = r;
    new_image->green = g;
    new_image->blue = b;

    return new_image;
}


int norm_thing(image_structure_rgb_t *img, int i, int j, int r, int g, int b)
{
    return (img->red[i*img->cols+j] - r)*(img->red[i*img->cols+j] - r) +
            (img->green[i*img->cols+j] - g)*(img->green[i*img->cols+j] - g) +
            (img->blue[i*img->cols+j] - b)*(img->blue[i*img->cols+j] - b) ;
}

void initialize_thing(clusters_t *clusters, int k)
{
    for(int i=0;i<k;i++)
    {
        clusters[i].points = malloc(1000000*sizeof(point_t));
        clusters[i].size= 0;
    }
}

void reinitialize_clusters(clusters_t *clusters, int k, image_structure_rgb_t *img)
{
    for(int i=0;i<k;i++)
    {
        int sum_r=0, sum_g = 0, sum_b = 0;
        for(int j=0;j<clusters[i].size;j++)
        {
            sum_r+= img->red[clusters[i].points[j].x*img->cols+clusters[i].points[j].y];
            sum_g+= img->green[clusters[i].points[j].x*img->cols+clusters[i].points[j].y];
            sum_b+= img->blue[clusters[i].points[j].x*img->cols+clusters[i].points[j].y];

        }
        clusters[i].r =(int)(sum_r/clusters[i].size);
        clusters[i].g =(int)(sum_g/clusters[i].size);
        clusters[i].b =(int)(sum_b/clusters[i].size);
        clusters[i].size=0;

    }

}

void add_centroids(clusters_t *clusters, int k, image_structure_rgb_t *img)
{
    int distances[k];
    initialize_thing(clusters, k);
    point_t p;

    for(int i=0;i<img->rows;i++){
        for(int j=0;j<img->cols;j++){
            for(int kk =0;kk<k;kk++)
            {
                distances[kk] = norm_thing(img, i,j, (int)clusters[kk].r, (int)clusters[kk].g, (int)clusters[kk].b);
            }
            int min = distances[0];
            int min_idx = 0;
            for(int kk=1;kk<k;kk++)
            {
                if(distances[kk] < min)
                {
                    min = distances[kk];
                    min_idx = kk;
                }
            }
            p.x = i;
            p.y = j;
            clusters[min_idx].points[clusters[min_idx].size] = p;
            clusters[min_idx].size++;

        }

    }



}

image_structure_rgb_t *k_means_yay(image_structure_rgb_t *img, int k)
{
        clusters_t *clusters = random_initialization_rgb(k);
        printf("done init clusters\n");
        for(int i=0; i<50;i++)
        {
            add_centroids(clusters, k, img);
            reinitialize_clusters(clusters, k, img);
            printf("iteration %d\n", i);

        }
        add_centroids(clusters, k, img);
        printf("building\n");
    for(int i=0;i<k;i++)
    {
        printf("red: %d, green: %d, blue %d\n", clusters[i].r, clusters[i].g, clusters[i].b);
    }
    image_structure_rgb_t *r = build_solution( clusters,  k, img);
    return r;
}





