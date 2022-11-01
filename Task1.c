#include <stdio.h>
#include <string.h>

int shouldStop(int c, FILE* input, int encrypted){
    if(encrypted != 0)
        return feof(input);
    return c == '\n' || feof(input);
}

int handleChar(int dbug, int encrypted, int index, char* key, int c){
    int  a='a', z='z', modified=c;

    if (encrypted == 0 && c >= a && c <= z) {
        modified -= 32;
    }

    if(encrypted == 1){
        modified += key[index] - '0';
    }

    if(encrypted == -1){
        modified -= key[index] - '0';
    }

    if(dbug){
        fprintf(stderr, "%x %x\n", c, modified);
    }
    return modified % 128;
}

int main(int argc, char **argv){
    FILE* output = stdout;
    FILE * input = stdin;
    int c, index=0, ifile = 0,dbug=0, encrypted=0, keyLength=0;
    char* encryptionKey;

    //Handle program arguments
    for (int i = 0; i < argc; ++i) {
        if(strcmp(argv[i],"-D")==0){
            fprintf(output, "-D\n");
            dbug = 1;
        }
        if(argv[i][0] == '-' && argv[i][1] == 'i'){
            input = fopen(&argv[i][2], "r");
            if(input == NULL) {
                fprintf(stdout, "can't open input file\n");
                return 0;
            }
            ifile = 1;
            fprintf(stdout, "input file was open successfully\n");
        }
        if(argv[i][0] == '-' && argv[i][1] == 'o'){
            output = fopen(&argv[i][2], "w");
            if(output == NULL) {
                fprintf(stdout, "can't open output file\n");
                return 0;
            }
            fprintf(stdout, "output file was open successfully\n");
        }
        if(argv[i][1]=='e'){
            if(argv[i][0]=='+'){
                encrypted=1;
            }
            if(argv[i][0]=='-'){
                encrypted=-1;
            }
            encryptionKey = &argv[i][2];
            if((keyLength = strlen(argv[i])-2) == 0){
                fprintf(output, "No encryption key was given");
                return 0;
            }
        }
    }
    if(ifile == 0){
        fprintf(stdout, "insert your text here:\n");
    }
    while(1) {
        c = fgetc(input);
        if(shouldStop(c, input, encrypted)){
            break;
        }
        if(c == '\n'){
            fputc( (char)c, output);
            index = 0;
            continue;
        }
        c = handleChar(dbug, encrypted, index, encryptionKey, c);
        fputc( (char)c, output);
        if(keyLength != 0) {
            index = (index + 1) % keyLength;
        }
    }
    fprintf(stdout, "\nwe gracefully ended the program\n");
    fclose(input);
    fclose(output);
    return 0;
}

