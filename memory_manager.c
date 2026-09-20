/*
 * Memory Manager Assignment
 * Computer Science XII - Computer Systems
 */

#include <stdio.h>
#include <stdlib.h>

void create_inventory() {
    printf("\n=== PART 1: CREATE INVENTORY ===\n");

    int inventory_size = 5;
    int *item_ids = (int*)malloc(inventory_size * sizeof(int));
    int *quantities = NULL;

    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }

    quantities = (int*)malloc(inventory_size * sizeof(int));
    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        item_ids = NULL;
        return;
    }

    printf("Starting inventory:\n");
    for (int i = 0; i < inventory_size; i++) {
        item_ids[i] = 100 + i;
        quantities[i] = (i + 1) * 10;
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }

    free(item_ids);
    item_ids = NULL;
    free(quantities);
    quantities = NULL;

    printf("Memory freed successfully.\n");
}

void expand_inventory() {
    printf("\n=== PART 2: EXPAND INVENTORY ===\n");

    int initial_size = 3;
    int expanded_size = 6;
    int *item_ids = (int*)malloc(initial_size * sizeof(int));
    int *quantities = NULL;

    if (item_ids == NULL) {
        printf("Failed to allocate item_ids\n");
        return;
    }

    quantities = (int*)malloc(initial_size * sizeof(int));
    if (quantities == NULL) {
        printf("Failed to allocate quantities\n");
        free(item_ids);
        item_ids = NULL;
        return;
    }

    printf("Initial inventory (size %d):\n", initial_size);
    for (int i = 0; i < initial_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }

    printf("\nPlayer acquires more items! Expanding inventory...\n");

    int *new_item_ids = (int*)realloc(item_ids, expanded_size * sizeof(int));
    if (new_item_ids == NULL) {
        printf("Failed to expand item_ids\n");
        free(item_ids);
        free(quantities);
        return;
    }
    item_ids = new_item_ids;

    int *new_quantities = (int*)realloc(quantities, expanded_size * sizeof(int));
    if (new_quantities == NULL) {
        printf("Failed to expand quantities\n");
        free(item_ids);
        free(quantities);
        return;
    }
    quantities = new_quantities;

    for (int i = initial_size; i < expanded_size; i++) {
        item_ids[i] = 200 + i;
        quantities[i] = 5 * (i + 1);
    }

    printf("Expanded inventory (size %d):\n", expanded_size);
    for (int i = 0; i < expanded_size; i++) {
        printf("  Item %d: quantity %d\n", item_ids[i], quantities[i]);
    }

    free(item_ids);
    item_ids = NULL;
    free(quantities);
    quantities = NULL;

    printf("Memory freed successfully.\n");
}

void memory_leak_demo() {
    printf("\n=== PART 3A: MEMORY LEAK DEMONSTRATION ===\n");
    printf("Allocating memory in a loop WITHOUT freeing...\n");

    for (int i = 0; i < 1000; i++) {
        int *temp_item = (int*)malloc(1000 * sizeof(int));

        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }

        temp_item[0] = 300 + i;

        /*
         * Intentional demonstration only: this block is not freed here so the
         * program can show the leak that Part 3B fixes.
         */
    }

    printf("Loop complete. Leaked approximately %zu KB of memory.\n",
           (1000 * 1000 * sizeof(int)) / 1024);
    printf("This memory cannot be reused until the program ends.\n");
}

void memory_leak_fixed() {
    printf("\n=== PART 3B: FIXED VERSION - NO MEMORY LEAK ===\n");
    printf("Allocating memory in a loop WITH proper freeing...\n");

    for (int i = 0; i < 1000; i++) {
        int *temp_item = (int*)malloc(1000 * sizeof(int));

        if (temp_item == NULL) {
            printf("Allocation failed at iteration %d!\n", i);
            return;
        }

        temp_item[0] = 300 + i;
        free(temp_item);
        temp_item = NULL;
    }

    printf("Loop complete. Memory properly freed after each use.\n");
    printf("Total memory allocated and freed: %zu KB\n",
           (1000 * 1000 * sizeof(int)) / 1024);
}

void safe_pointer_handling() {
    printf("\n=== PART 4: SAFE POINTER HANDLING ===\n");

    int *player_health = (int*)malloc(sizeof(int));

    if (player_health == NULL) {
        printf("Allocation failed!\n");
        return;
    }

    *player_health = 100;
    printf("Player health: %d\n", *player_health);

    free(player_health);
    player_health = NULL;
    printf("Health memory freed.\n");

    if (player_health != NULL) {
        printf("Player health: %d\n", *player_health);
    } else {
        printf("Health data not available\n");
    }

    printf("Safe pointer handling complete.\n");
}

int main() {
    printf("=============================================================\n");
    printf("      MEMORY MANAGER: Dynamic Inventory System\n");
    printf("=============================================================\n");

    create_inventory();
    expand_inventory();

    printf("\n--- First, observe the memory leak ---\n");
    memory_leak_demo();

    printf("\n--- Now, see the properly managed version ---\n");
    memory_leak_fixed();

    safe_pointer_handling();

    printf("\n=============================================================\n");
    printf("Memory management complete!\n");
    printf("Review your code for proper malloc/free pairing and NULL checks.\n");
    printf("=============================================================\n");

    return 0;
}
