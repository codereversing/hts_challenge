#include <stdio.h>

#define CHARS_TO_READ 5

int main(int argc, char* argv[])
{
    unsigned char dst[16] = { 0 };
    unsigned char enc_char;
    int input_char = 0;
    int input_sum = 0;
    int xor_sum = 0;
    int index = 0;
    printf("Please enter the password:\n");
    while (input_char != 0xA && input_char != EOF)
    {
        input_char = fgetchar();
        input_sum += input_char;
    }
    FILE* enc_file = fopen("encrypted.enc", "rb");
    if (enc_file)
    {
        while (index < CHARS_TO_READ)
        {
            if (fread(&enc_char, sizeof(unsigned char), 1, enc_file) != 1)
            {
                printf("An error occured.\n");
                return 0;
            }
            xor_sum += (input_sum ^ enc_char);
            dst[index] = (input_sum ^ enc_char);
            for (int i = 0; i < input_sum; ++i)
            {
                if (dst[index] & 1)
                    dst[index] = ((dst[index] >> 1) | 0x80);
                else
                    dst[index] = (dst[index] >> 1);
            }
            dst[index] += 3;
            index++;
        }
        if (xor_sum == 0xDCA)
            printf("Congratulations, the password is %s\n", dst);
        else
            printf("Invalid password.\n");
    }
    else
        printf("Failed to open encrypted.enc\n");
    return 0;
}