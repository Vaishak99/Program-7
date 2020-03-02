#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LINE_SIZE 250

//Time to days convert

int top = -1, i = 0;
long int array[1000];
long int stack[1000];


void print_dates(long long int dates)
{
    time_t rawtime = dates;
    struct tm  ts;
    char buf[80];
    ts = *localtime(&rawtime);
    strftime(buf, sizeof(buf), "%Y-%m-%d", &ts);
    printf("%s\n", buf);
}

void empty_stack()
{
    while(top)
    {
        top -= 1;
    }
    top -= 1;
}
                


//Main function.
int main(int argc, char *argv[]) {

    //logic for date to time conversion.
    FILE *fd;
    char *filename = argv[1];
    char line[MAX_LINE_SIZE];
    char *datestr;
    struct tm tm;
    time_t epoch;
    if (argc != 2) {
        printf("Enter file name in the command line arguments \n");
        exit(1);
    }

    if ((fd = fopen(filename, "r")) == NULL) {
        printf("Error in opening file %s\n", filename);
        exit(1);
    }
    while (fgets(line, MAX_LINE_SIZE, fd) != NULL) {
        line[strnlen(line, MAX_LINE_SIZE) - 1] = '\0';
        if (strptime(line, "%Y-%m-%d", &tm) != NULL) {
            epoch = mktime(&tm);
            array[i] = epoch;
            i += 1;
        } else {
            printf("Invalid date %s in input", line);
        }

    }
    int j;
    for(j = 0; j < i; j++) {
        for(int k = 0; k < i; k++) {
            if(array[j] > array[k])
            {
                long long int temp = array[k];
                array[k] = array[j];
                array[j] = temp;
            }
        }
    }
    long int min = 9999999;
    printf("\n");
    for(j = 0; j < i - 1; j++) {
        if(min == labs(array[j]-array[j+1])) {
            stack[++top] = array[j];
            stack[++top] = array[j+1];
        } 
        else if(min > labs(array[j]-array[j+1]))
        {
            min = labs(array[j]-array[j+1]);
            empty_stack();
            stack[++top] = array[j];
            stack[++top] = array[j+1];
        }
    }
    printf("The dates are - \n");
    for(j = 0; j <= top; j++) {
        print_dates(stack[j]);
    }
    return 0;
}
