#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 256
#define MAX_COMMANDS 100

static char *readLine(void)
{
    int ch;
    size_t length = 0;
    size_t capacity = SIZE;
    char *line = malloc(capacity);

    if (line == NULL) {
        fprintf(stderr, "Unable to allocate input buffer.\n");
        return NULL;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            if (capacity > (size_t)-1 / 2) {
                fprintf(stderr, "Input line is too long.\n");
                free(line);
                return NULL;
            }

            capacity *= 2;
            char *temp = realloc(line, capacity);
            if (temp == NULL) {
                fprintf(stderr, "Unable to grow input buffer.\n");
                free(line);
                return NULL;
            }
            line = temp;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(line);
        return NULL;
    }

    line[length] = '\0';
    return line;
}

static char *trim(char *text)
{
    while (isspace((unsigned char)*text)) {
        text++;
    }

    char *end = text + strlen(text);
    while (end > text && isspace((unsigned char)end[-1])) {
        *--end = '\0';
    }

    return text;
}

static int copyOperand(char destination[SIZE], const char *source)
{
    size_t length = strlen(source);

    if (length == 0 || length >= SIZE) {
        return 0;
    }

    for (size_t i = 0; i < length; i++) {
        if (isspace((unsigned char)source[i])) {
            return 0;
        }
    }

    memcpy(destination, source, length + 1);
    return 1;
}

/* Returns 1 for arithmetic, 2 for assignment, and 0 for invalid TAC. */
static int parseStatement(char *line, char result[SIZE],
                          char operand1[SIZE], char *operator,
                          char operand2[SIZE])
{
    char *equals = strchr(line, '=');
    if (equals == NULL || strchr(equals + 1, '=') != NULL) {
        return 0;
    }

    *equals = '\0';
    char *lhs = trim(line);
    char *rhs = trim(equals + 1);
    if (!copyOperand(result, lhs) || *rhs == '\0') {
        return 0;
    }

    char *operatorPosition = NULL;
    for (char *p = rhs + 1; *p != '\0'; p++) {
        if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
            if (operatorPosition != NULL) {
                return 0;
            }
            operatorPosition = p;
        }
    }

    if (operatorPosition == NULL) {
        return copyOperand(operand1, rhs) ? 2 : 0;
    }

    *operator = *operatorPosition;
    *operatorPosition = '\0';
    char *left = trim(rhs);
    char *right = trim(operatorPosition + 1);

    if (!copyOperand(operand1, left) || !copyOperand(operand2, right)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    char *line;
    char *commands[MAX_COMMANDS];
    int numberOfCommands = 0;
    char result[SIZE];
    char operand1[SIZE];
    char operand2[SIZE];
    char operator;

    printf("Enter TAC statements (type END to finish):\n");

    /* Read and store all commands before generating code. */
    while ((line = readLine()) != NULL) {
        if (strcmp(line, "END") == 0) {
            free(line);
            break;
        }

        if (numberOfCommands < MAX_COMMANDS) {
            commands[numberOfCommands++] = line;
        } else {
            fprintf(stderr, "Maximum %d commands allowed.\n", MAX_COMMANDS);
            free(line);
        }
    }

    printf("\n--- GENERATED 8086 CODE ---\n");
    printf("\nDATA SEGMENT\n");
    printf("DATA ENDS\n");
    printf("\nCODE SEGMENT\n");
    printf("START:\n");
    printf("    MOV AX, @DATA\n");
    printf("    MOV DS, AX\n");

    /* Process the stored commands. */
    for (int commandNumber = 0;
         commandNumber < numberOfCommands;
         commandNumber++) {
        line = commands[commandNumber];
        int statementType = parseStatement(
            line, result, operand1, &operator, operand2);

        if (statementType == 1) {
            printf("    MOV AX, %s\n", operand1);

            switch (operator) {
            case '+':
                printf("    ADD AX, %s\n", operand2);
                break;
            case '-':
                printf("    SUB AX, %s\n", operand2);
                break;
            case '*':
                printf("    MOV BX, %s\n", operand2);
                printf("    IMUL BX\n");
                break;
            case '/':
                printf("    CWD\n");
                printf("    MOV BX, %s\n", operand2);
                printf("    IDIV BX\n");
                break;
            }

            printf("    MOV %s, AX\n", result);
        } else if (statementType == 2) {
            printf("    MOV AX, %s\n", operand1);
            printf("    MOV %s, AX\n", result);
        } else {
            printf("; Invalid TAC statement: %s\n", line);
        }

        free(line);
    }

    printf("    MOV AH, 4CH\n");
    printf("    INT 21H\n");
    printf("CODE ENDS\n");
    printf("END START\n");

    return 0;
}
