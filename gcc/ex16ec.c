#include <stdio.h>
// Extra credit - passing structs normaly, not as pointers and not using malloc

struct Flower {
    char *name;
    int power;
    int smell_rating;
};

// let's use look-up table
const char *smell_rating_names[10] = { 
    "abysmal", "disgusting", "awful", "bad", "bland", 
    "adequate", "good", "wonderful", "gorgeous", "heavenly"  
};

struct Flower Flower_create(char *name, int power, unsigned int smell_rating)
{
    if (smell_rating < 1) {
        printf("WARNING: Smell rating cannot be bellow 1. %s gets 1 instead.\n", name);
        smell_rating = 1;
    }
    
    if (smell_rating > 10) {
        printf("WARNING: Smell rating cannot be above 10. %s gets 10 instead.\n", name);
    }

    struct Flower flower = { .name = name, .power = power, .smell_rating = smell_rating };
    return flower;
}

const char *Flower_get_rating_name(struct Flower flower)
{
    return smell_rating_names[flower.smell_rating-1];
}

void Flower_print(struct Flower flower)
{
    printf("Flower: %s has %d power and smells %d/10 - which is %s.\n",
            flower.name, flower.power, flower.smell_rating, Flower_get_rating_name(flower));
}

void Flower_print_all(struct Flower flowers[], const size_t flower_count)
{
    for (int i = 0; i < flower_count; i++) {
        Flower_print(flowers[i]);
    }
}

// let's implement simple sorting (bubble sort)
void Flower_sort_all(struct Flower flowers[], const size_t flower_count)
{
    for (int i = 0; i < flower_count; i++) {
        for (int j = 1; j < flower_count; j++) {
            if (flowers[j-1].smell_rating > flowers[j].smell_rating) {
                struct Flower swap = flowers[j-1];
                flowers[j-1] = flowers[j];
                flowers[j] = swap;
            }
        }
    }
}


int main(int argc, char *argv[])
{
    struct Flower rose = Flower_create("Rose", 9000, 10);
    struct Flower carrion_flower = Flower_create("Carrion flower", 1234, 1);
    struct Flower orange_blossom = Flower_create("Orange blossom", 7890, 9);
    struct Flower lilly_of_the_valey = Flower_create("Lily of the valley", 123, 5);
    struct Flower geranium = Flower_create("geranium", 4567, 8);
    struct Flower eastern_skunk_cabbage = Flower_create("Eastern Skunk Cabbage", 8765, 2);
    struct Flower jasmine = Flower_create("Jasmine", 7777, 7);
    struct Flower carob_tree_flower = Flower_create("Carob tree", 666, 3);

    struct Flower flowers[] = { 
        rose, carrion_flower, orange_blossom, lilly_of_the_valey,
        geranium, eastern_skunk_cabbage, jasmine, carob_tree_flower
    };
    const size_t flower_count = sizeof(flowers) / sizeof(struct Flower);

    Flower_print_all(flowers, flower_count);

    printf("\nFlowers sorted by rating (form worst to best):\n");
    Flower_sort_all(flowers, flower_count);
    Flower_print_all(flowers, flower_count);

    return 0;
}