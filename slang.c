//
// Created by stenh
//
#include "slang-lib.h"
//#define LIBRARY
#ifndef LIBRARY

int main(int argc, char **argv) {
    if(argc == 2) {
        char p[16384];
        char buff[2048];
        FILE *f = fopen(argv[1], "r");

        while(fgets(buff, 2048, f)) {
            strcat(p, buff);
        }
        printf("Read programm: %s\n", p);

        int length = 0;
        Token* tokens = tokenize(p, &length);
        //printTokens(tokens, length);


        printf("%d tokens!\n", length);
        SlangInterpreter* main_interpreter = createSlangInterpreter(tokens, length);
        interpret(main_interpreter);
        printAllFunctions(main_interpreter);
        printAllVariables(main_interpreter);
        free(main_interpreter); 
    }
    else if(argc == 1) {
        Token* tokens = malloc(sizeof(Token)*8192);
        SlangInterpreter* main_interpreter = createSlangInterpreter(tokens, 0);
        while(1) {
            char* buf = malloc(sizeof(4096));
            printf("slang> ");
            fgets (buf, 8192, stdin);
            int tokens_length = 0;
            Token* in_tokens = tokenize(buf, &tokens_length);
            addTokensToInterpreter(main_interpreter, in_tokens, tokens_length);
            interpret(main_interpreter);
            printAllFunctions(main_interpreter);
            printAllVariables(main_interpreter);
        }
    }
    else {
        printf("Wrong number of arguments!\nUsage: slang <file>\n");
    }
    
    
    return 0;
}
#endif
