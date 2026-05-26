#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char** lines;
    int AmountOfLines;
    int capacity;
} Text;
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
void AddText(Text* editor) {
    char buffer[256];
    printf("> Enter text to append:\n");

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = 0;
        int currentLine = editor->AmountOfLines - 1;
        int oldLen = strlen(editor->lines[currentLine]);
        int newLen = strlen(buffer);

        editor->lines[currentLine] = realloc(editor->lines[currentLine], (oldLen + newLen + 1) * sizeof(char));
        strcat(editor->lines[currentLine], buffer);
    }
}
void NewLine(Text* editor) {
    if (editor->AmountOfLines >= editor->capacity) {
        editor->capacity *= 2;
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

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        FILE* file = fopen(buffer, "w");

        if (file != NULL) {
            for (int i = 0; i < editor->AmountOfLines; i++) {
                fputs(editor->lines[i], file);
                if (i < editor->AmountOfLines - 1) {
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

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        FILE* file = fopen(buffer, "r");

        if (file == NULL) {
            printf("> Error opening file\n");
        }
        else {
            freeText(editor);
            initText(editor);

            char fileBuffer[256];
            bool isFirstLine = true;

            while (fgets(fileBuffer, sizeof(fileBuffer), file) != NULL) {
                fileBuffer[strcspn(fileBuffer, "\n")] = '\0';

                if (!isFirstLine) {
                    if (editor->AmountOfLines >= editor->capacity) {
                        editor->capacity *= 2;
                        editor->lines = realloc(editor->lines, editor->capacity * sizeof(char*));
                    }
                    editor->lines[editor->AmountOfLines] = malloc(1 * sizeof(char));
                    editor->lines[editor->AmountOfLines][0] = '\0';
                    editor->AmountOfLines++;
                }
                int currentLine = editor->AmountOfLines - 1;
                int oldLen = strlen(editor->lines[currentLine]);
                int newLen = strlen(fileBuffer);
                editor->lines[currentLine] = realloc(editor->lines[currentLine], (oldLen + newLen + 1) * sizeof(char));
                strcat(editor->lines[currentLine], fileBuffer);
                isFirstLine = false;
            }
            printf("> Text has been loaded successfully\n");
            fclose(file);
        }
    }
}
void PrintText(Text* editor) {
    for (int i = 0; i < editor->AmountOfLines; i++) {
        printf("%s\n", editor->lines[i]);
    }
}
int main() {
    int command;
    Text editor;

    initText(&editor);

    while (true) {
        printf("\n> Choose the command:\n1. Add text\n2. New line\n3. Save to file\n4. Load from file\n5. Print all text\n6. Exit\n");

        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

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
            printf("> Exiting the program. Goodbye!\n");
            freeText(&editor);
            return 0;
        default:
            printf("> The command is not implemented\n");
            break;
        }
    }
    return 0;
}