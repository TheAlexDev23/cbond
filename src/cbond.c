#include <cwalk.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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

int main(int argc, char* argv[])
{
    if (parse_input(argc, argv))
        return -1;

    periodic_element_t* element1; 
    periodic_element_t* element2;
    element1 = element2 = NULL;

    if (pick_element(&element1) || pick_element(&element2))
        return -1;

    periodic_free_element(element1);
    periodic_free_element(element2);

    return 0;
}