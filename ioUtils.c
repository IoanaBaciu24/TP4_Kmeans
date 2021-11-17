/* Some useful functions to read, write PBM, PGM, PPM files
**
**
** E.B.
*/

#include <stdio.h>
#include <stdlib.h>
#include "ioUtils.h"
//aaa

char pm_getc(FILE* file)
{
    int ich;
    char ch;

    ich = getc( file );
    if ( ich == EOF )
        pm_erreur("EOF / read error" );
    ch = (char) ich;

    if ( ch == '#' )
    {
        do
        {
            ich = getc( file );
            if ( ich == EOF )
                pm_erreur("EOF / read error" );
            ch = (char) ich;
        }
        while ( ch != '\n' && ch != '\r' );
    }

    return ch;
}


//bit pm_getbit(FILE* file)
//{
//    char ch;
//
//    do
//    {
//        ch = pm_getc( file );
//    }
//    while ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' );
//
//    if ( ch != '0' && ch != '1' )
//        pm_erreur("read error : != [0|1]" );
//
//    return ( ch == '1' ) ? 1 : 0;
//}


unsigned char pm_getrawbyte(FILE* file)
{
    int iby;

    iby = getc( file );
    if ( iby == EOF )
        pm_erreur("EOF / read error " );
    return (unsigned char) iby;
}

int pm_getint( FILE* file)
{
    char ch;
    int i;

    do
    {
        ch = pm_getc( file );
    }
    while ( ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' );

    if ( ch < '0' || ch > '9' )
        pm_erreur( "read error : != [0-9]" );

    i = 0;
    do
    {
        i = i * 10 + ch - '0';
        ch = pm_getc( file );
    }
    while ( ch >= '0' && ch <= '9' );

    return i;
}

void pm_erreur(char *texte)
{
    fprintf(stderr, "\n%s \n\n", texte);
    exit(1);
}


image_structure_t* read_image(FILE *file_descr){

    unsigned char *image_matrix;
    int ch1, ch2, rows, cols, maxval = 255;
    ch1 = getc(file_descr);
    if (ch1 == EOF)
    {
        pm_erreur("read error");
    }
    ch2 = getc(file_descr);
    if (ch2 == EOF)
    {
        pm_erreur("you thought you got away, huh?");
    }

    cols = pm_getint(file_descr);
    rows = pm_getint(file_descr);
    maxval = pm_getint(file_descr);

    image_matrix = (unsigned char*) malloc(cols*rows*sizeof (unsigned char));
    image_structure_t *image = malloc(sizeof(image_structure_t));
    for(int i=0; i < rows; i++)
    {for(int j=0; j < cols ; j++)
        {image_matrix[i * cols + j] = pm_getrawbyte(file_descr) ;}}

    image->maxval = maxval;
    image->rows = rows;
    image->cols = cols;
    image->image_matrix = image_matrix;

    return image;
}


image_structure_rgb_t* read_rgb_image(FILE *file_descr){

    unsigned char *r,*g,*b;
    int ch1, ch2, rows, cols, maxval = 255;
    ch1 = getc(file_descr);
    if (ch1 == EOF)
    {
        pm_erreur("read error");
    }
    ch2 = getc(file_descr);
    if (ch2 == EOF)
    {
        pm_erreur("you thought you got away, huh?");
    }

    cols = pm_getint(file_descr);
    rows = pm_getint(file_descr);
    maxval = pm_getint(file_descr);

    r = (unsigned char*) malloc(cols*rows*sizeof (unsigned char));
    g = (unsigned char*) malloc(cols*rows*sizeof (unsigned char));
    b = (unsigned char*) malloc(cols*rows*sizeof (unsigned char));

    image_structure_rgb_t *image = malloc(sizeof(image_structure_t));
    for(int i=0; i < rows; i++)
    {for(int j=0; j < cols ; j++)
        {
        r[i * cols + j] = pm_getrawbyte(file_descr);
        g[i * cols + j] = pm_getrawbyte(file_descr);
        b[i * cols + j] = pm_getrawbyte(file_descr);

        }
    }

    image->maxval = maxval;
    image->rows = rows;
    image->cols = cols;
    image->red = r;
    image->green = g;
    image->blue = b;

    return image;
}



void write_image_to_file(image_structure_t *img, FILE * fp)
{
//    FILE *fp = fopen(file_name, "w");
    fprintf(fp, "P5\n");

    fprintf(fp, "%d %d \n", img->cols, img->rows);
    fprintf(fp, "%d\n",img->maxval);

    for(int i=0; i < img->rows; i++)
        for(int j=0; j < img->cols ; j++)
            fprintf(fp,"%c",img->image_matrix[i * img->cols + j]);
    fclose(fp);
}

void write_image_to_file_rgb(image_structure_rgb_t *img, FILE * fp)
{
//    FILE *fp = fopen(file_name, "w");
    fprintf(fp, "P6\n");

    fprintf(fp, "%d %d \n", img->cols, img->rows);
    fprintf(fp, "%d\n",img->maxval);

    for(int i=0; i < img->rows; i++)
        for(int j=0; j < img->cols ; j++)
        {
            fprintf(fp,"%c",img->red[i * img->cols + j]);
            fprintf(fp,"%c",img->green[i * img->cols + j]);
            fprintf(fp,"%c",img->blue[i * img->cols + j]);


        }
    fclose(fp);
}
