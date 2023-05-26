#include <stdio.h>
#include <unistd.h>

#include <pttui/easy.h>

int main()
{
    printf("Welcome to cbond. Pick your first element.");
    sleep(1);
    periodic_element_t* element1 = pttui_easy_get_element("./lib/pttui/lib/libperiodic-c/Periodic-Table-JSON/PeriodicTableJSON.json");
    if (element1 == NULL)
    {
        fprintf(stderr, "Element cannot be null");
        return -1;
    }

    printf("Element 1: %s", element1->symbol);

    periodic_element_t* element2 = pttui_easy_get_element("./lib/pttui/lib/libperiodic-c/Periodic-Table-JSON/PeriodicTableJSON.json");
    if (element2 == NULL)
    {
        fprintf(stderr, "Element cannot be null");
        return -1;
    }

    printf("Element 2: %s", element2->symbol);

    return 0;
}