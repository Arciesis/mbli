#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char** argv) {
    if (argc != 2) {
        exit(EXIT_FAILURE);
    }

    size_t input_len = strlen(argv[1]);
    char prog_name[input_len];
    strcpy(prog_name, argv[1]);


    const char* extension = ".lua";
    const char* result = strtok(prog_name, extension);

    if (NULL == result) {
        exit(EXIT_FAILURE);
    }

    printf("result: %s", result);

    return 0;
}
