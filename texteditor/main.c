#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct TextEditor {
    char** lines;
    int AmountOfLines;
    int capacity;
}Text;
void initText(Text* t) {
    t->AmountOfLines = 1;
    t->capacity = 5;
    t->lines = malloc(t->capacity * sizeof(char*));
    t->lines[0] = malloc(1 * sizeof(char));
    t->lines[0][0] = '\0';
}
void freeText(Text* t) {
    for (int i = 0; i < t->AmountOfLines; i++) {
        free(t->lines[i]);
    }
    free(t->lines);
}
int getStringLength(char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}
void AddText(Text* editor) {
    char buffer[256];
    printf("> Enter text to append:\n");
    if (fgets(buffer, 256, stdin) != NULL) {
        int i = 0;
        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
            i++;
        }
        int currentLine = editor->AmountOfLines - 1;
        int oldLen = getStringLength(editor->lines[currentLine]);
        int newLen = getStringLength(buffer);
        editor->lines[currentLine] = realloc(editor->lines[currentLine], (oldLen + newLen + 1) * sizeof(char));
        int j = 0;
        while (buffer[j] != '\0') {
            editor->lines[currentLine][oldLen + j] = buffer[j];
            j++;
        }
        editor->lines[currentLine][oldLen + j] = '\0';
    }
}
void NewLine(Text* editor) {
    if (editor->AmountOfLines >= editor->capacity) {
        editor->capacity = editor->capacity * 2;
        editor->lines = realloc(editor->lines, editor->capacity * sizeof(char*));
    }
    editor->lines[editor->AmountOfLines] = malloc(1 * sizeof(char));
    editor->lines[editor->AmountOfLines][0] = '\0';
    editor->AmountOfLines++;
    printf("> New line started\n");
}
void SaveToFile(Text* editor) {
    char buffer[256];
    printf("> Enter the file name for saving: ");
    if (fgets(buffer, 256, stdin) != NULL) {
        int i = 0;
        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
            i++;
        }
        FILE* file = fopen(buffer, "w");
        if (file != NULL) {
            int j;
            for (j = 0; j < editor->AmountOfLines; j++) {
                fputs(editor->lines[j], file);
                if (j < editor->AmountOfLines - 1) {
                    fputs("\n", file);
                }
            }
            printf("> Text has been saved successfully\n");
            fclose(file);
        }
        else {
            printf("> Error opening file for saving\n");
        }
    }
}
void LoadFile(Text* editor) {
    char buffer[256];
    printf("> Enter the file name for loading: ");
    if (fgets(buffer, 256, stdin) != NULL) {
        int i = 0;
        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
            i++;
        }
        FILE* file = fopen(buffer, "r");
        if (file == NULL) {
            printf("> Error opening file\n");
        }
        else {
            freeText(editor);
            initText(editor);
            char fileBuffer[256];
            int isFirstLine = 1;
            while (fgets(fileBuffer, 256, file) != NULL) {
                int k = 0;
                while (fileBuffer[k] != '\0') {
                    if (fileBuffer[k] == '\n') {
                        fileBuffer[k] = '\0';
                        break;
                    }
                    k++;
                }
                if (isFirstLine == 0) {
                    if (editor->AmountOfLines >= editor->capacity) {
                        editor->capacity = editor->capacity * 2;
                        editor->lines = realloc(editor->lines, editor->capacity * sizeof(char*));
                    }
                    editor->lines[editor->AmountOfLines] = malloc(1 * sizeof(char));
                    editor->lines[editor->AmountOfLines][0] = '\0';
                    editor->AmountOfLines++;
                }
                int currentLine = editor->AmountOfLines - 1;
                int oldLen = getStringLength(editor->lines[currentLine]);
                int newLen = getStringLength(fileBuffer);
                editor->lines[currentLine] = realloc(editor->lines[currentLine], (oldLen + newLen + 1) * sizeof(char));
                int m = 0;
                while (fileBuffer[m] != '\0') {
                    editor->lines[currentLine][oldLen + m] = fileBuffer[m];
                    m++;
                }
                editor->lines[currentLine][oldLen + m] = '\0';
                isFirstLine = 0;
            }
            printf("> Text has been loaded successfully\n");
            fclose(file);
        }
    }
}
void PrintText(Text * editor) 
    {
       int i;
        for (i = 0; i < editor->AmountOfLines; i++) {
            printf("%s\n", editor->lines[i]);
        }
    }
void InsertText(struct TextEditor* editor) {
    int targetLine, targetIndex;
    printf("> Choose line and index: ");
    if (scanf("%d %d", &targetLine, &targetIndex) == 2) {
        while (getchar() != '\n') {
        }
        if (targetLine < 0 || targetLine >= editor->AmountOfLines) {
            printf("> Wrong line\n");
            return;
        }
        int oldLen = getStringLength(editor->lines[targetLine]);
        if (targetIndex < 0 || targetIndex > oldLen) {
            printf("> Wrong index\n");
            return;
        }
        char buffer[256];
        printf("> Enter text to insert: ");
        if (fgets(buffer, 256, stdin) != NULL) {
            int i = 0;
            while (buffer[i] != '\0') {
                if (buffer[i] == '\n') {
                    buffer[i] = '\0';
                    break;
                }
                i++;
            }
            int insertLen = getStringLength(buffer);
            if (insertLen > 0) {
                editor->lines[targetLine] = realloc(editor->lines[targetLine], (oldLen + insertLen + 1) * sizeof(char));
                int j;
                for (j = oldLen; j >= targetIndex; j--) {
                    editor->lines[targetLine][j + insertLen] = editor->lines[targetLine][j];
                }
                int k;
                for (k = 0; k < insertLen; k++) {
                    editor->lines[targetLine][targetIndex + k] = buffer[k];
                }
            }
        }
    }
    else {
        while (getchar() != '\n') {
        }
    }
}
void DeleteText(Text* editor) {
    int line_id;
    int start_char_id;
    int num_of_symbols;
    int len = 0;
    printf("Choose line index and number of symbols: ");
    if (scanf("%d %d %d", &line_id, &start_char_id, &num_of_symbols) != 3) {
        printf("Invalid input\n");
        return;
    }
    if (line_id >= 0 && line_id < editor->AmountOfLines) {
        char* line = editor->lines[line_id];
        while (line[len] != '\0') {
            len++;
        }
        if (start_char_id < 0 || start_char_id >= len) {
            printf("index is too big or too low\n");
            return;
        }
        if (start_char_id + num_of_symbols > len) {
            num_of_symbols = len - start_char_id;
        }
        for (int i = start_char_id;i <= len - num_of_symbols;i++) {
            line[i] = line[i + num_of_symbols];
        }
        int new_len = len - num_of_symbols;
        editor->lines[line_id] = realloc(editor->lines[line_id], (new_len + 1) * sizeof(char));
    }
    else {
        printf("> Wrong line index\n");
    }
}




        int main() {
            int command;
            Text editor;
            initText(&editor);
            while (1) {
                printf("\n> Choose the command:\n1. Add text\n2. New line\n3. Save to file\n4. Load from file\n5. Print all text\n6.InsertText\n7.Delete text\n8.Exit.\n");
                if (scanf("%d", &command) != 1) {
                    while (getchar() != '\n') {
                    }
                    continue;
                }
                while (getchar() != '\n') {
                }
                switch (command) {
                case 1:
                    AddText(&editor);
                    break;
                case 2:
                    NewLine(&editor);
                    break;
                case 3:
                    SaveToFile(&editor);
                    break;
                case 4:
                    LoadFile(&editor);
                    break;
                case 5:
                    PrintText(&editor);
                    break;
                case 6:
                    InsertText(&editor); 
                    break;
                case 7:
                    DeleteText(&editor);
                    break;
                case 8:
                    printf("> Exiting the program. Goodbye!\n");
                    freeText(&editor);
                    return 0;
                default:
                    printf("> The command is not implemented\n");
                }
            }
            return 0;
        }