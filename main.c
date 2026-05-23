#include <stdio.h>
#include <stdbool.h>

struct masivi {
    char **lines;
    int AmountOfLines;
    int capacity;
};

int CommandMenu() {
    int command;
    int line;  
    int index; 

    printf("\n> Choose the command: ");
    scanf("%d", &command);

    switch (command)
    {
        case 1:
            printf("> Enter text to append:\n");        
            break;
        case 2:
            printf("> New line started\n");
            break; 
        case 3:
            printf("> Enter the file name for saving:\n");
            break;
        case 4:
            printf("> Enter the file name for loading: \n");
            break;
        case 5:
            printf("> Hello, text editor! \n");
            break;
        case 6:
            printf("> Choose line and index: ");
            scanf("%d %d", &line, &index);
            break;
        default:
            printf("> The command is not implemented\n"); 
            break;
    }
    return 0;
}

int main(void) {
    while (true) {
        CommandMenu();
    }

    return 0;
}