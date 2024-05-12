#include <stdio.h>
#include <stdlib.h>

int main(){

    int height = 4000, width = 8000;
    int halfHeight = height/2, halfWidth = width/2;
    //2d array mit malloc (ram management in C)
    int (*image)[width] = malloc(sizeof(int[height][width]));

    //Größe des Fraktals
    float fractalScalar = .0007;

    /* Das zweidimensionale Array 'image' wird so behandelt, dass die x-Achse 
     * der reelle Zahlenstrahl und die y-Achse der komplexe, 
     * um das Fraktal als Mittelpunkt des "Bildes" zu erzeugen muss als (0,0) 
     * behandelt werden, um dies zu erreichen, ist das 'image'-Array durchlaufen von -1/2 x oder y bis +1/2 x oder y
     */
    for(int x = -halfWidth; x < halfWidth; x++){
        for(int y = -halfHeight; y < halfHeight; y++){

            //A & B werden auf x bzw. y gesetzt, da sie einen Komplexe Zahl darstellen  --> a + bi
            float a = (float)x*fractalScalar;
            float b = (float)y*fractalScalar; //cast x & y to floats

            int count = 0;
            /*
             * Hier werden die insgesamten Wiederholungen gegeben
             * Interessante Dinge passieren, wenn man diese ändert
             */
            int totalIterations = 50;
            while(count < totalIterations){
                //(a+bi)^2 = (a^2 - b^2) + 2abi
                float realTerm = a*a - b*b; //Realteil
                float complexTerm = 2 * a * b; //Komplexer Komponent

                //Originalwerte hinzufügen und es wiederholen
                a = realTerm + (float)x*fractalScalar;
                b = complexTerm + (float)y*fractalScalar;
                
                //nach Fällen suchen, in denen A+B - oder + unendlich werden
                //Mandelbrotwerte liegen immer zwischen -2 & 2
                if(a+b > 2.0 || a+b < -2.0 ){
                    break;
                }
                count++;
            }
            
            if(count == totalIterations){
                image[y+halfHeight][x+halfWidth] = 200;
            }
        }
    }

    //Erstellt eine PGM Datei in welcher es als eine Greymap mit einem maximalem
    //"grezvalue" von 255 dargestellt wird
    FILE* pgmimg = fopen("mandelbrot.pgm", "w");
    fprintf(pgmimg, "P2\n");
    fprintf(pgmimg, "%d %d\n", width, height);
    fprintf(pgmimg, "255\n");
    //Durchläuft das Image-Array und schreibt die INT-Werte in die PGM-Datei
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


