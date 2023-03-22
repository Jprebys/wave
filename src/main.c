#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "wave.h"


#define X_EMOJI "\u274C\uFE0F"
#define CHECK_EMOJI "\u2705\uFE0F"

void test_fail(const char *func_name, const int n)
{
    printf(X_EMOJI" %s test %d failed...\n", func_name, n);
    exit(EXIT_FAILURE);
}


int main(void)
{

    uint32_t values2d_1[] = {1, 2,
                             1, 2};

    Pattern pattern2d_1 = { .values = values2d_1 };
    uint32_t values2d_2[] = {2, 0,
                             2, 3};
    Pattern pattern2d_2 = { .values = values2d_2 };
    uint32_t values2d_3[] = {1, 2,
                             0, 0};
    Pattern pattern2d_3 = { .values = values2d_3 };
    uint32_t values3d_1[] = {3, 2, 2,
                             1, 2, 2,
                             1, 1, 0};
    Pattern pattern3d_1 = { .values = values3d_1 };
    uint32_t values3d_2[] = {3, 0, 3,
                             1, 3, 1,
                             2, 1, 1};
    Pattern pattern3d_2 = { .values = values3d_2 };
    uint32_t values3d_3[] = {1, 2, 3,
                             0, 0, 1,
                             3, 2, 2};
    Pattern pattern3d_3 = { .values = values3d_3 };


    {    
        printf("Testing pattern_equals...\n");
        if (!pattern_equals(pattern3d_1, pattern3d_1, 3)) 
            test_fail("pattern_equals", 1);
        if (!pattern_equals(pattern2d_1, pattern2d_1, 2))
            test_fail("pattern_equals", 2);
        if (pattern_equals(pattern2d_3, pattern2d_2, 2)) 
            test_fail("pattern_equals", 3);
        if (pattern_equals(pattern3d_1, pattern3d_2, 3)) 
            test_fail("pattern_equals", 4);

        printf(CHECK_EMOJI " pattern_equals tests succeeded!\n");
    }

    {
        printf("Testing pattern_in_list...\n");
        Pattern list2d[] = { pattern2d_1, pattern2d_2 };
        Pattern list3d[] = { pattern3d_1, pattern3d_2 };

        if (pattern_in_list(&pattern2d_3, list2d, 2, 2))
            test_fail("pattern_in_list", 1);
        if (pattern_in_list(&pattern3d_3, list3d, 2, 3))
            test_fail("pattern_in_list", 2);
        if (!pattern_in_list(&pattern2d_1, list2d, 2, 2))
            test_fail("pattern_in_list", 3);
        if (!pattern_in_list(&pattern3d_2, list3d, 2, 3)) 
            test_fail("pattern_in_list", 4);

        printf(CHECK_EMOJI " pattern_in_list tests succeeded!\n");
    }

    {
        char test_name[] = "pattern_copy";
        printf("Testing %s...\n", test_name);

        uint32_t new_values[4];
        Pattern new = { .values = new_values, .count = 2 };
        pattern_copy(&new, &pattern2d_1, 2);

        if (!(new.values[0] == 1 && new.values[1] == 2 && new.values[2] == 1 && new.values[3] == 2 && new.count == 0))
            test_fail(test_name, 1);

        uint32_t new_values3[9];
        Pattern new3 = { .values = new_values3, .count = 2};
        pattern_copy(&new3, &pattern3d_1, 3);

        if (!(new3.values[0] == 3 && new3.values[1] == 2 && new3.values[2] == 2 && 
              new3.values[3] == 1 && new3.values[4] == 2 && new3.values[5] == 2 && 
              new3.values[6] == 1 && new3.values[7] == 1 && new3.values[8] == 0 && 
              new3.count == 0))
            test_fail(test_name, 2);

        printf(CHECK_EMOJI " %s tests succeeded!\n", test_name);

    }


    {
        char test_name[] = "generate_patterns";
        printf("Testing %s...\n", test_name);

        uint32_t grid_cells[] = {1, 2,
                                 1, 3};
        CellGrid grid = { .cells = grid_cells, .rows = 2, .cols = 2 };

        Pattern *patterns;
        int n_patterns = generate_patterns(&grid, 4, 2, &patterns);

        if (n_patterns != 4)
            test_fail(test_name, 1);

        Pattern p0 = patterns[0];
        if (p0.values[0] != 1 || p0.values[1] != 2 || p0.values[2] != 1 || p0.values[3] != 3)
            test_fail(test_name, 1);
        
        Pattern p1 = patterns[1];
        if (p1.values[0] != 2 || p1.values[1] != 3 || p1.values[2] != 1 || p1.values[3] != 1)
            test_fail(test_name, 2);


        printf(CHECK_EMOJI " %s tests succeeded!\n", test_name);
    }


    // return 0;



    srand(time(NULL));
    printf("\n\nRunning wave...\n");
    uint32_t cells[] = {
4, 3, 1, 0, 3, 0, 3, 1, 0, 2, 
4, 3, 0, 4, 1, 3, 1, 0, 1, 4, 
4, 4, 3, 3, 4, 3, 2, 3, 0, 2, 
2, 0, 3, 1, 4, 4, 0, 1, 0, 2, 
3, 2, 3, 3, 1, 3, 4, 3, 2, 3, 
1, 1, 4, 2, 3, 1, 4, 2, 2, 2, 
1, 4, 3, 1, 2, 1, 0, 2, 1, 3, 
2, 4, 2, 1, 0, 2, 0, 2, 3, 0, 
4, 0, 3, 4, 0, 1, 1, 3, 4, 2, 
2, 2, 4, 0, 4, 0, 1, 0, 3, 4,
// 1, 0, 1,
// 0, 1, 2,
// 1, 0, 1
    };
    int rows = 10, cols = 10, p_size = 2;
    CellGrid cell_grid = { .cells = cells, .rows = rows, .cols = cols, .changed = false };
    run_wfc_algo(&cell_grid, p_size, 8, 10);


    return 0;
    // srand(time(NULL));

    // uint32_t cells2[] = {
    //     1, 0, 1, 0, 1,
    //     0, 2, 0, 2, 3,
    //     1, 0, 1, 1, 1
    // };
    // int rows = 3, cols = 5, p_size = 2, width = 20, height = 20;
    // CellGrid cell_grid2 = { .cells = cells2, .rows = rows, .cols = cols };

    // // int tries = 1;
    // // while(!run_wfc_algo(&cell_grid2, p_size, width, height))
    // // {
    // //     tries++;
    // // }
    // int tries = 1;
    // run_wfc_algo(&cell_grid2, p_size, width, height);

    // printf("Finished running wave, took %d tries\n", tries);

    return 0;
}