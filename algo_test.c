#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
} Rectangle;

typedef struct {
    Rectangle** results;
    int* sizes;
    int count;
    int capacity;
} ResultList;

void appendResult(ResultList* resultList, Rectangle* currentRectangles, int currentCount) {
    if (resultList->count >= resultList->capacity) {
        resultList->capacity *= 2;
        resultList->results = realloc(resultList->results, resultList->capacity * sizeof(Rectangle*));
        resultList->sizes = realloc(resultList->sizes, resultList->capacity * sizeof(int));
    }
    resultList->results[resultList->count] = malloc(currentCount * sizeof(Rectangle));
    for (int i = 0; i < currentCount; i++) {
        resultList->results[resultList->count][i] = currentRectangles[i];
    }
    resultList->sizes[resultList->count] = currentCount;
    resultList->count++;
}

void decomposeBlocks(int x, int y, int remainingCells, Rectangle* currentRectangles, int currentCount, ResultList* resultList) {
    if (remainingCells == 0) {
        appendResult(resultList, currentRectangles, currentCount);
        return;
    }

    for (int width = 1; width <= x; width++) {
        for (int height = 1; height <= y; height++) {
            if (width * height <= remainingCells) {
                int newRemainingCells = remainingCells - width * height;
                int newX = x - width;
                int newY = y;

                currentRectangles[currentCount].width = width;
                currentRectangles[currentCount].height = height;

                if (newX > 0) {
                    decomposeBlocks(newX, y, newRemainingCells, currentRectangles, currentCount + 1, resultList);
                }

                newX = x;
                newY = y - height;

                if (newY > 0) {
                    decomposeBlocks(x, newY, newRemainingCells, currentRectangles, currentCount + 1, resultList);
                }
            }
        }
    }
}

ResultList* rozklad_klockow(int n, int h) {
    ResultList* resultList = malloc(sizeof(ResultList));
    resultList->count = 0;
    resultList->capacity = 100; // Initial capacity
    resultList->results = malloc(resultList->capacity * sizeof(Rectangle*));
    resultList->sizes = malloc(resultList->capacity * sizeof(int));

    Rectangle* currentRectangles = malloc(n * h * sizeof(Rectangle));
    decomposeBlocks(n, h, n * h, currentRectangles, 0, resultList);

    free(currentRectangles);
    return resultList;
}

void printResults(ResultList* resultList) {
    for (int i = 0; i < resultList->count; i++) {
        printf("Option %d: ", i + 1);
        for (int j = 0; j < resultList->sizes[i]; j++) {
            Rectangle rect = resultList->results[i][j];
            printf("(%d, %d) ", rect.width, rect.height);
        }
        printf("\n");
    }
}

void freeResults(ResultList* resultList) {
    for (int i = 0; i < resultList->count; i++) {
        free(resultList->results[i]);
    }
    free(resultList->results);
    free(resultList->sizes);
    free(resultList);
}

int main() {
    int n = 3;
    int h = 3;

    ResultList* results = rozklad_klockow(n, h);
    printResults(results);

    freeResults(results);

    return 0;
}
