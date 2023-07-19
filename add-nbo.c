#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint32_t read_uint32(FILE* file) {
    uint8_t data[4];
    size_t bytesRead = fread(data, 1, 4, file);
    if (bytesRead != 4) {
        if (feof(file))
            fprintf(stderr, "Error: Unexpected end of file.\n");
        else if (ferror(file))
            fprintf(stderr, "Error: File read error.\n");
        exit(1);
    }
    return ((uint32_t)data[0] << 24) | ((uint32_t)data[1] << 16) |
           ((uint32_t)data[2] << 8) | (uint32_t)data[3];
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("syntax : add-nbo <file1> <file2>\n");
        printf("sample : add-nbo a.bin b.bin\n");
        return 0;
    }

    FILE* file1 = fopen(argv[1], "rb");
    if (file1 == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }

    FILE* file2 = fopen(argv[2], "rb");
    if (file2 == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[2]);
        fclose(file1);
        return 1;
    }

    uint32_t num1 = read_uint32(file1);
    uint32_t num2 = read_uint32(file2);
    uint32_t sum_result = num1 + num2;

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum_result, sum_result);

    fclose(file1);
    fclose(file2);

    return 0;
}

