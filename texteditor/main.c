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

void InsertWithReplacement(Text* editor) {
    int line_id;
    int symbol_id;
    char buffer[256];
    printf("Choose line and symbol ");
    if (scanf("%d %d", &line_id, &symbol_id) != 2) {
        printf("Invalid line or symbol index\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    if (line_id < 0 || line_id >= editor->AmountOfLines) {
        printf("> Wrong line index\n");
        return; 
    }
    printf("Enter text to insert.");
    if (fgets(buffer, 256, stdin) != NULL) {
        int i = 0;
        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                buffer[i] = '\0';
                break;
            }
            i++;
        }
        if (line_id >= 0 && line_id < editor->AmountOfLines) {
            int old_len = 0;
            char* line = editor->lines[line_id];
            while (line[old_len] != '\0') {
                old_len++;
            }

            int insert_len = 0;
            while (buffer[insert_len] != '\0') {
                insert_len++;
            }
            if (symbol_id < 0 || symbol_id > old_len) {
                printf("Incorrect symbol id.\n");
                return;
            }
            if (symbol_id + insert_len > old_len) {
                int new_len = symbol_id + insert_len;
                editor->lines[line_id] = realloc(editor->lines[line_id], (new_len + 1) * sizeof(char));
                line = editor->lines[line_id];
                line[new_len] = '\0';
            }
            for (int i = 0; i < insert_len; i++) {
                line[symbol_id + i] = buffer[i];
            }
        }
    }
}
typedef struct TextCopy {
    char** lines;
    int AmountOfLines;
}Copy;

void MakeCopy(Text* editor, Copy* undo_stack, int* undo_count) {
    int target_index;
    if (*undo_count < 3) {
        target_index = *undo_count;
        (*undo_count)++;
    }
    else {
        for (int i = 0; i < undo_stack[0].AmountOfLines; i++) {
            free(undo_stack[0].lines[i]);
        }
        free(undo_stack[0].lines);

        for (int i = 0; i < 2; i++) {
            undo_stack[i] = undo_stack[i + 1];
        }
        target_index = 2;
            
    }
    undo_stack[target_index].lines = malloc(editor->AmountOfLines * sizeof(char*));
    undo_stack[target_index].AmountOfLines = editor->AmountOfLines;

    for (int i = 0; i < editor->AmountOfLines; i++) {
        int len = getStringLength(editor->lines[i]);
        undo_stack[target_index].lines[i] = malloc((len + 1) * sizeof(char));
        int j = 0;
        while (editor->lines[i][j] != '\0') {
            undo_stack[target_index].lines[i][j] = editor->lines[i][j];

            j++;
        }
        undo_stack[target_index].lines[i][j] = '\0';
    }
}

void Undo(Text* editor, Copy* undo_stack, int* undo_count, Copy* redo_stack, int* redo_count) {
    if (*undo_count == 0) {
        printf("Nothing to undo\n");
        return;
    }
    MakeCopy(editor, redo_stack, redo_count);
    int last_index = *undo_count - 1;
    freeText(editor);
    editor->AmountOfLines = undo_stack[last_index].AmountOfLines;
    editor->lines = undo_stack[last_index].lines;
    editor->capacity = undo_stack[last_index].AmountOfLines;;
    (*undo_count)--;
    printf("successfully\n");
}

void Redo(Text* editor, Copy* undo_stack, int* undo_count, Copy* redo_stack, int* redo_count) {
    if (*redo_count == 0) {
        printf("Nothing to redo\n");
        return;
    }
    MakeCopy(editor, undo_stack, undo_count);
    int last_redo_index = *redo_count - 1;
    freeText(editor);
    editor->AmountOfLines = redo_stack[last_redo_index].AmountOfLines;
    editor->lines = redo_stack[last_redo_index].lines;
    editor->capacity = redo_stack[last_redo_index].AmountOfLines;
    (*redo_count)--;
    printf("successfully\n");
}

void CopyText(Text* editor, char** clipboard) {
    int line_id, start_char_id, num_of_symbols;
    printf("Choose line, start index and number of symbols to copy: ");
    if (scanf("%d %d %d", &line_id, &start_char_id, &num_of_symbols) != 3) {
        printf("> Invalid input\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (line_id < 0 || line_id >= editor->AmountOfLines) {
        printf("> Wrong index\n");
        return;
    }

    int len = getStringLength(editor->lines[line_id]);
    if (start_char_id < 0 || start_char_id >= len) {
        printf("> Wrong index\n");
        return;
    }
    if (start_char_id + num_of_symbols > len) {
        num_of_symbols = len - start_char_id; 
    }
    if (*clipboard != NULL) {
        free(*clipboard);
    }
    *clipboard = malloc((num_of_symbols + 1) * sizeof(char));
    for (int i = 0; i < num_of_symbols; i++) {
        (*clipboard)[i] = editor->lines[line_id][start_char_id + i];
    }
    (*clipboard)[num_of_symbols] = '\0';
    printf("> Text copied\n");
}

void PasteText(Text* editor, char* clipboard) {
    if (clipboard == NULL) {
        printf("> Clipboard is empty\n");
        return;
    }

    int line_id, start_char_id;
    printf("Choose line  and start index to paste: ");
    if (scanf("%d %d", &line_id, &start_char_id) != 2) {
        printf("> Invalid input\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (line_id < 0 || line_id >= editor->AmountOfLines) {
        printf("> Wrong index\n");
        return;
    }

    int old_len = getStringLength(editor->lines[line_id]);
    if (start_char_id < 0 || start_char_id > old_len) {
        printf("> Wrong index\n");
        return;
    }
    int clipboard_len = getStringLength(clipboard);
    editor->lines[line_id] = realloc(editor->lines[line_id], (old_len + clipboard_len + 1) * sizeof(char));
    for (int i = old_len; i >= start_char_id; i--) {
        editor->lines[line_id][i + clipboard_len] = editor->lines[line_id][i];
    }
    for (int i = 0; i < clipboard_len; i++) {
        editor->lines[line_id][start_char_id + i] = clipboard[i];
    }
    printf("> Text pasted\n");
}

void CutText(Text* editor, char** clipboard) {
    int line_id, start_char_id, num_of_symbols;
    printf("Choose line , start index and number of symbols to cut: ");
    if (scanf("%d %d %d", &line_id, &start_char_id, &num_of_symbols) != 3) {
        printf("> Invalid input\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    if (line_id < 0 || line_id >= editor->AmountOfLines) {
        printf("> Wrong index\n");
        return;
    }

    int len = getStringLength(editor->lines[line_id]);
    if (start_char_id < 0 || start_char_id >= len) {
        printf("> Wrong index\n");
        return;
    }
    if (start_char_id + num_of_symbols > len) {
        num_of_symbols = len - start_char_id;
    }
    if (*clipboard != NULL) {
        free(*clipboard);
    }
    *clipboard = malloc((num_of_symbols + 1) * sizeof(char));
    for (int i = 0; i < num_of_symbols; i++) {
        (*clipboard)[i] = editor->lines[line_id][start_char_id + i];
    }
    (*clipboard)[num_of_symbols] = '\0';
    for (int i = start_char_id; i <= len - num_of_symbols; i++) {
        editor->lines[line_id][i] = editor->lines[line_id][i + num_of_symbols];
    }
    int new_len = len - num_of_symbols;
    editor->lines[line_id] = realloc(editor->lines[line_id], (new_len + 1) * sizeof(char));
    printf("> Text cut\n");
}
int main() {
    int command;
    Text editor;
    initText(&editor);
    Copy undo_stack[3];
    int undo_count = 0;
    Copy redo_stack[3];
    int redo_count = 0;
    char* clipboard = NULL;
    while (1) {
        printf("\n> Choose the command:\n1. Add text\n2. New line\n3. Save to file\n4. Load from file\n5. Print all text\n6.InsertText\n7.Delete text\n8.Insert with replacement.\n9.Undo\n10.Redo\n11.Copy\n12.Paste\n13.Cut\n14.Exit\n");
        if (scanf("%d", &command) != 1) {
            while (getchar() != '\n') {
            }
            continue;
        }
        while (getchar() != '\n') {
        }
        switch (command) {
        case 1:
            redo_count = 0;
            MakeCopy(&editor, undo_stack, &undo_count);
            AddText(&editor);
            break;
        case 2:
            redo_count = 0;
            MakeCopy(&editor, undo_stack, &undo_count);
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
            redo_count = 0;
            MakeCopy(&editor, undo_stack, &undo_count);
            InsertText(&editor);
            break;
        case 7:
            redo_count = 0;
            MakeCopy(&editor, undo_stack, &undo_count);
            DeleteText(&editor);
            break;
        case 8:
            redo_count = 0;
            MakeCopy(&editor, undo_stack, &undo_count);
            InsertWithReplacement(&editor);
            break;
        case 9:
            Undo(&editor, undo_stack, &undo_count, redo_stack, &redo_count);
            break;
        case 10:
            Redo(&editor, undo_stack, &undo_count, redo_stack, &redo_count);
            break;
        case 11:
            CopyText(&editor, &clipboard);
            break;

        case 12:
            redo_count = 0;
            MakeCopy(&editor, undo_stack, &undo_count); 
            PasteText(&editor, clipboard);
            break;

        case 13:
            redo_count = 0;
            MakeCopy(&editor, undo_stack, &undo_count);
            CutText(&editor, &clipboard);
            break;

        case 14:
            printf("> Exiting the program. Goodbye!\n");
            if (clipboard != NULL) {
                free(clipboard);
            }
            return 0;
        default:
            printf("> The command is not implemented\n");
        }
    }
    if (clipboard != NULL) free(clipboard);
    return 0;
}