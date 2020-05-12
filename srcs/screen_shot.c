#include <stdio.h>
#include "raycasting.h"

#define	BYTES_PER_PIXEL 3
#define FILE_HEADER_SIZE 14
#define INFO_HEADER_SIZE 40

unsigned char* createBitmapFileHeader(int height, int width, int padding_size){
    int file_size;
    unsigned char *file_header;

	if (!(file_header = malloc(sizeof(unsigned char) * 16)))
		return (0);
	ft_memset(file_header, 0, 16);
	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (BYTES_PER_PIXEL*width+padding_size) * height;
    file_header[ 0] = (unsigned char)('B');
    file_header[ 1] = (unsigned char)('M');
    file_header[ 2] = (unsigned char)(file_size);
    file_header[ 3] = (unsigned char)(file_size >> 8);
    file_header[ 4] = (unsigned char)(file_size >> 16);
    file_header[ 5] = (unsigned char)(file_size >> 24);
    file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
    return file_header;
}

unsigned char* createBitmapInfoHeader(int height, int width){
    unsigned char *info_header;

	if (!(info_header = malloc(sizeof(unsigned char) * 40)))
		return (0);
	ft_memset(info_header, 0, 40);
    info_header[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    info_header[ 4] = (unsigned char)(width);
    info_header[ 5] = (unsigned char)(width >> 8);
    info_header[ 6] = (unsigned char)(width >> 16);
    info_header[ 7] = (unsigned char)(width >> 24);
    info_header[ 8] = (unsigned char)(height);
    info_header[ 9] = (unsigned char)(height >> 8);
    info_header[10] = (unsigned char)(height >> 16);
    info_header[11] = (unsigned char)(height >> 24);
    info_header[12] = (unsigned char)(1);
    info_header[14] = (unsigned char)(BYTES_PER_PIXEL * 8);
    return info_header;
}

void generateBitmapImage(unsigned char *image, int height, int width, char* imageFileName){

    unsigned char padding[3] = {0, 0, 0};
    int padding_size = (4 - (width * BYTES_PER_PIXEL) % 4) % 4;

    unsigned char *file_header = createBitmapFileHeader(height, width, padding_size);
    unsigned char *info_header = createBitmapInfoHeader(height, width);

    FILE* imageFile = fopen(imageFileName, "wb");

    fwrite(file_header, 1, FILE_HEADER_SIZE, imageFile);
    fwrite(info_header, 1, INFO_HEADER_SIZE, imageFile);

    int i;
    for(i=0; i<height; i++){
        fwrite(image+(i*width*BYTES_PER_PIXEL), BYTES_PER_PIXEL, width, imageFile);
        fwrite(padding, 1, padding_size, imageFile);
    }

    fclose(imageFile);
}

int screen_shot(t_scene *scene){
	int	color;
	int	r,g,b;
    int height = (int)scene->window.height;
    int width = (int)scene->window.width;
    unsigned char image[height][width][BYTES_PER_PIXEL];
    char* imageFileName = "bitmapImage.bmp";

    int i, j;
    for(i=0; i<height; i++){
        for(j=0; j<width; j++){
			color = scene->window.img_data[i * width + j];
			r = color >> 16;
			g = (color - (r << 16)) >> 8;
			b = (color - (r << 16) - (g << 8));
            image[i][j][2] = (unsigned char)r;
            image[i][j][1] = (unsigned char)g;
            image[i][j][0] = (unsigned char)b;
        }
    }

    generateBitmapImage((unsigned char *)image, height, width, imageFileName);
	return (0);
}