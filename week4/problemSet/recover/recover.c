#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    if (card == NULL)
    {
        return 1;
    }

    uint8_t buffer[512];

    int count_files = 0;
    FILE *current_jpeg = NULL;

    while(fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (current_jpeg != NULL)
            {
                fclose(current_jpeg);
            }

            char *filename = malloc(8);
            sprintf(filename, "%03i.jpg", count_files);
            if (filename == NULL)
            {
                printf("Error - not possible to create new jpeg");
                return 1;
            }

            current_jpeg = fopen(filename, "w");
            count_files++;

            fwrite(buffer, 1, 512, current_jpeg);
            free(filename);
        }
        else
        {
            if (current_jpeg != NULL)
            {
                fwrite(buffer, 1, 512, current_jpeg);
            }
        }
    }

    if (current_jpeg != NULL)
    {
        fclose(current_jpeg);
    }

    fclose(card);
}
