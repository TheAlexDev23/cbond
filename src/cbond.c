#include <math.h> // abs
#include <cwalk.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <libperiodic-c/periodic.h>
#include <pttui/easy.h>

char* db_loc = NULL;
#define PATH_MAX 200

int parse_input(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Wrong input. Specify project folder location");
        return -1;
    }

    db_loc = malloc(PATH_MAX);
    cwk_path_join(argv[1], "/lib/pttui/lib/libperiodic-c/Periodic-Table-JSON/PeriodicTableJSON.json", db_loc, PATH_MAX);

    return 0;
}

int pick_element(periodic_element_t** element)
{
    printf("Pick element\n");
    sleep(1);
    *element = pttui_easy_get_element(db_loc);
    if (*element == NULL)
    {
        fprintf(stderr, "pttui returned null element. Quitting...");
        return -1;
    }

    printf("Element chosen %s\n", (*element)->symbol);

    return 0;
}

int metals[] = { 3, 4, 11, 12, 13, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116 };
int nonmetals[] = { 1, 2, 6, 7, 8, 9, 10, 15, 16, 17, 18, 34, 35, 36, 53, 54, 85, 86, 117, 118 };

bool is_metal(periodic_element_t* element)
{
    for (int i = 0; i < 20; i++)
    {
        if (element->number == nonmetals[i])
            return false;
    }

    return true;
}

void calc_bond(periodic_element_t* element1, periodic_element_t* element2)
{
    bool m1 = is_metal(element1);
    bool m2 = is_metal(element2);

    int l1 = element1->conf.shells[element1->conf.shells_amnt - 1];
    int l2 = element2->conf.shells[element2->conf.shells_amnt - 1];

    /* Ionic */
    if ((m1 || m2) && !(m1 && m2))
    {
        if (l1 + l2 == 8 || l1 + l2 == 2)
        {
            if (element1->conf.shells_amnt > 1)
            {
                printf("%s will give %s %i electrons\n", element1->name, element2->name, l1);
            }
            else if (element2->conf.shells_amnt > 1 && 
                    element2->conf.shells[element2->conf.shells_amnt - 2])
            {
                printf("%s will give %s %i electrons\n", element2->name, element1->name, l1);
            }
            else
            {
                printf("No bonding\n");
                return;
            }
        }
        printf("Ionic bonding\n");
    }

    /* Covalent */
    if (!m1 && !m2)
    {
        // Amount of shared electrons
        int join1, join2;
        join1 = join2 = 0;

        if (l1 < 2)
        {
            // l2 has enough electrons to share with element1
            if (2 - l1 <= l2)
            {
                join2 = 2 - l1;
            }
            else
            {
                printf("Cannot join\n");
                return;
            }
        }
        else if (l1 < 8)
        {
            // l2 has enough electrons to share with element1
            if (8 - l1 <= l2)
            {
                join2 = 8 - l1;
            }
            else
            {
                printf("Cannot join\n");
                return;
            }
        }

        if (l2 < 2)
        {
            // l1 has enough electrons to share with element1
            if (2 - l2 <= l1)
            {
                join1 = 2 - l1;
            }
            else
            {
                printf("Cannot join\n");
                return;
            }
        }
        else if (l2 < 8)
        {
            // l1 has enough electrons to share with element1
            if (8 - l2 <= l1)
            {
                join1 = 8 - l1;
            }
            else
            {
                printf("Cannot join\n");
                return;
            }
        }

        printf("%s (1) will share %i electrons with %s (2)\n", element1->name, join1, element2->name);
        printf("%s (2) will share %i electrons with %s (1)\n", element2->name, join2, element1->name);

        printf("Covalent bonding\n");
    }
}

int main(int argc, char* argv[])
{
    if (parse_input(argc, argv))
        return -1;

    periodic_element_t* element1; 
    periodic_element_t* element2;
    element1 = element2 = NULL;

    if (pick_element(&element1) || pick_element(&element2))
        return -1;

    calc_bond(element1, element2);

    periodic_free_element(element1);
    periodic_free_element(element2);

    return 0;
}