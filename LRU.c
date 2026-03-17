#include <stdio.h>

int main() {
    int frames[3] = {-1, -1, -1}; // 3 frames
    int time[3] = {0};           // To track least recently used
    int pages[] = {2, 5, 1, 2, 3, 5, 4, 2, 3, 1, 5, 2};
    int n = 12;
    int faults = 0, t = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in frames (HIT)
        for (int j = 0; j < 3; j++) {
            if (frames[j] == page) {
                t++;
                time[j] = t; // update usage time
                found = 1;
                printf("Page %d: HIT\n", page);
                break;
            }
        }

        // If not found → FAULT
        if (!found) {
            int lru = 0;

            // Find least recently used frame
            for (int j = 1; j < 3; j++) {
                if (time[j] < time[lru]) {
                    lru = j;
                }
            }

            t++;
            frames[lru] = page;
            time[lru] = t;
            faults++;

            printf("Page %d: FAULT\n", page);
        }

        // Print frame status
        printf("Frames: ");
        for (int j = 0; j < 3; j++) {
            if (frames[j] != -1)
                printf("%d ", frames[j]);
            else
                printf("- ");
        }
        printf("\n\n");
    }

    printf("Total Page Faults = %d\n", faults);

    return 0;
}
