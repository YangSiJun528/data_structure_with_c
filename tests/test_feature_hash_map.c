#include <stdio.h>
#include <stdlib.h>
#include "hash_map.h"

// Function to print all entries in the hash map
void print_entries(HashMap *hash_map) {
    Entry *entries = hash_map_entries(hash_map);
    for (int i = 0; i < hash_map_size(hash_map); i++) {
        printf("Key: %d, Value: %d\n", entries[i].key, entries[i].value->data);
    }
    free(entries);
}

int main() {
    // Initialize the hash map
    HashMap *hash_map = hash_map_init();

    // Create some data to insert
    Data data1 = {10};
    Data data2 = {20};
    Data data3 = {30};
    Data data4 = {40};
    Data data5 = {50};

    // Test adding elements to the hash map
    hash_map_put(hash_map, 1, &data1);
    hash_map_put(hash_map, 2, &data2);
    hash_map_put(hash_map, 3, &data3);
    hash_map_put(hash_map, 4, &data4);
    hash_map_put(hash_map, 5, &data5);

    // Print the entries in the hash map
    printf("Hash map after adding elements:\n");
    print_entries(hash_map);

    // Test getting elements from the hash map
    Data *value = hash_map_get(hash_map, 3);
    if (value != NULL) {
        printf("Value for key 3: %d\n", value->data);
    } else {
        printf("Value for key 3 not found.\n");
    }

    // Test checking if the hash map contains certain keys
    printf("Hash map contains key 2? %s\n", hash_map_contains(hash_map, 2) ? "Yes" : "No");
    printf("Hash map contains key 6? %s\n", hash_map_contains(hash_map, 6) ? "Yes" : "No");

    // Test removing an element from the hash map
    hash_map_remove(hash_map, 2);
    printf("Hash map after removing key 2:\n");
    print_entries(hash_map);

    // Test the size of the hash map
    printf("Size of the hash map: %d\n", hash_map_size(hash_map));

    // Free the hash map
    hash_map_free(hash_map);

    return 0;
}
