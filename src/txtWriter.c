#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to write evidence to a file
void write_moves(char *string)
{
    FILE *fp;
    time_t current_time;
    char *c_time_string;

    // Get current time
    current_time = time(NULL);
    c_time_string = ctime(&current_time);

    // Open file for writing
    fp = fopen("./log/log.txt", "a");

    // Write evidence to file with timestamp
    fprintf(fp, "%s       [time]:  %s", string, c_time_string);

    // Close file
    fclose(fp);
}