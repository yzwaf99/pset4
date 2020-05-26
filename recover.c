//Made by Ahmed Fawzy (YZWAF99) Edited by AhmedSafe

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
   
    int countername = 0;

    typedef uint8_t  BYTE;
    FILE *file = fopen(argv[1], "r");

    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    int ifnew = 1;
    char image[12];
    FILE *img = NULL; 
  
    while (true)
    {
        fread(buffer, 512, 1, file);
        if (feof(file))
        {
            break;
        }
        
        // check if it's the header of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //when you find jpeg header , create an image
            if (ifnew == 1)
            {
               
                sprintf(image, "%03i.jpg", countername);
                img = fopen(image, "w"); 
                ifnew = 0;
            
            }
            // when you find a header for the start of the next jpeg, close the previous image and create a new one
            else
            {
                fclose(img);
                countername++;
                sprintf(image, "%03i.jpg", countername);
                img = fopen(image, "w"); 
                //stop the previous jpeg and start new one
                
                
            } 
         
        }
        
        // start writing in the iamge if you found its header
        if (ifnew == 0) 
        {
            
        
            fwrite(buffer, sizeof(BYTE), 512, img);
          
        }
        
        
    }


    fclose(img);
    fclose(file);
    free(buffer);
}
