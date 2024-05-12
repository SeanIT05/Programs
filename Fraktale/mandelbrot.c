#include <stdio.h>
#include <stdlib.h>

int main(){

    int height = 4000, width = 8000;
    int halfHeight = height/2, halfWidth = width/2;
    //2d array mit malloc (ram management in C)
    int (*image)[width] = malloc(sizeof(int[height][width]));

    //adjust how big the fractal will appear, the smaller the value the larger it will be
    float fractalScalar = .0007;

    /*
     * The two dimensional array 'image' is treated such that the
     * x axis is the real numberline and the y axis is the complex
     * numberline, to produce the fractal the center of the 'image'
     * must be treated as (0,0), to achive this the 'image' array is
     * traversed starting at -1/2 of the x or y and ending at +1/2 x or y
     */
    for(int x = -halfWidth; x < halfWidth; x++){
        for(int y = -halfHeight; y < halfHeight; y++){

            //a & b are set to x and y respecitvely as they represet a complex# a + bi
            float a = (float)x*fractalScalar;
            float b = (float)y*fractalScalar; //cast x & y to floats

            int count = 0;
            /*
             * iteresting things happen when you adjust 'totalIterations' totalIterations
             * deteremines how confident we are that a+b will not go to - or + infinity, it almost
             * acts as 'resolution'
             */
            int totalIterations = 50;
            while(count < totalIterations){
                //(a+bi)^2 = (a^2 - b^2) + 2abi
                float realTerm = a*a - b*b; //real component
                float complexTerm = 2 * a * b; //complex component 'coeffiecnt'

                //add the original values and iterate the process
                a = realTerm + (float)x*fractalScalar;
                b = complexTerm + (float)y*fractalScalar;

                //check for unbounded cases where a+b become - or + infinite
                //the mandelbrot values always lay between -2 & 2
                if(a+b > 2.0 || a+b < -2.0 ){ //alternatively real term + complex term
                    break;
                }
                count++;
            }

            //in the case that a+b did not become - or + infinite change pixel color
            if(count == totalIterations){
                image[y+halfHeight][x+halfWidth] = 200;
            }
        }
    }

    /*
     * Write to the image file:
     * file pointer 'pgmimg' opens "mandelbrot.pgm" for "writing"
     * print "P2" to the file via the 'pgmimg' file pointer to
       denote it is a portable graymap image file
     * via the same process print the width and height
     * then denote the max grey value '255'
     */
    FILE* pgmimg = fopen("mandelbrot.pgm", "w");
    fprintf(pgmimg, "P2\n");
    fprintf(pgmimg, "%d %d\n", width, height);
    fprintf(pgmimg, "255\n");
    //now traverse the image array and write the int values to .pgm file
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int temp = image[i][j];
            fprintf(pgmimg, "%d ", temp);
        }
        fprintf(pgmimg, "\n");
    }
    fclose(pgmimg); //schließt die pgm Datei
    free(image); //leert die bilder array
}

