#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {

    if(argc != 4) {
        printf("Usage: %s <VAS_MB> <PageSize_KB> <VirtualAddress>\n", argv[0]);
        return 1;
    }

    int vas_mb = atoi(argv[1]);
    int page_kb = atoi(argv[2]);
    int virtual_address = atoi(argv[3]);

    // Convert to bytes
    int vas_bytes = vas_mb * 1024 * 1024;
    int page_bytes = page_kb * 1024;

    // Number of pages
    int num_pages = vas_bytes / page_bytes;

    // Page table (simple simulation)
    int page_table[num_pages];

    // Initialize page table (example mapping: page i → frame i+1)
    for(int i = 0; i < num_pages; i++) {
        page_table[i] = i + 1;
    }

    // Calculate page number and offset
    int page_number = virtual_address / page_bytes;
    int offset = virtual_address % page_bytes;

    // Check for page table miss
    if(page_number >= num_pages) {
        printf("Page Table Miss!\n");
        return 0;
    }

    int frame_number = page_table[page_number];

    printf("Virtual Address: %d\n", virtual_address);
    printf("Page Number: %d\n", page_number);
    printf("Offset: %d\n", offset);
    printf("Physical Address: <%d, %d>\n", frame_number, offset);

    return 0;
}