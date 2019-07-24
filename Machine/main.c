#include <stdio.h>
#include "buffer.h"

int main(int argc, char const *argv[])
{
    FILE* source_file = fopen(argv[1], "r");

    buffer_t* current_token = buffer_new();

    char c;
    while ((c = fgetc(source_file)) != EOF)
    {
        buffer_append_n(current_token, &c, 1);
    }

    printf("%s", buffer_string(current_token));
        
    fclose(source_file);

    /* code */
    return 0;
}
