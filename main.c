#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"
 
/* it is going to making 5 items in this program */
#define NUM_ITEMS 5
 
/* This function fills in ONE item in the array.
   "index" tells it which spot in the array to fill in. */
void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index)
{
  /* price is just a number, so it can copy it directly */
  item_list[index].price = price;
 
  /* sku, category, and name are being
     allocate memory for this */

  item_list[index].sku = malloc(strlen(sku) + 1);
  strcpy(item_list[index].sku, sku);
 
  item_list[index].category = malloc(strlen(category) + 1);
  strcpy(item_list[index].category, category);
 
  item_list[index].name = malloc(strlen(name) + 1);
  strcpy(item_list[index].name, name);
}
 
/* This function frees all the memory it allocated.
   it have to free each string inside every item first,
   and then free the array itself. */
void free_items(Item *item_list, int size)
{
  int i;
 
  for (i = 0; i < size; i++)
  {
    free(item_list[i].sku);
    free(item_list[i].category);
    free(item_list[i].name);
  }
 
  /* now that every item's strings are freed, free the array */
  free(item_list);
}
 
/* This function adds up all the prices and divides by
   how many items there are, to get the average price. */
double average_price(Item *item_list, int size)
{
  double total = 0.0;
  int i;
 
  for (i = 0; i < size; i++)
  {
    total = total + item_list[i].price;
  }
 
  return total / size;
}
 
/* This function prints every item in the array to the screen. */
void print_items(Item *item_list, int size)
{
  int i;
 
  for (i = 0; i < size; i++)
  {
    printf("###############\n");
    printf("item name = %s\n", item_list[i].name);
    printf("item sku = %s\n", item_list[i].sku);
    printf("item category = %s\n", item_list[i].category);
    printf("item price = %.2f\n", item_list[i].price);
  }
}
 
int main(int argc, char *argv[])
{
  /* make space for 5 items, but don't fill them in yet */
  Item *item_list = malloc(NUM_ITEMS * sizeof(Item));
 
  /* make sure malloc worked */
  if (item_list == NULL)
  {
    printf("Something went wrong allocating memory.\n");
    return 1;
  }
 
  /* now fill in each item using add_item */
  add_item(item_list, 5.00, "19282", "breakfast", "reese's cereal", 0);
  add_item(item_list, 3.95, "79862", "dairy",     "milk",           1);
  add_item(item_list, 7.50, "14512", "dairy",     "eggs",           2);
  add_item(item_list, 9.25, "33021", "beverages", "coffee",         3);
  add_item(item_list, 5.70, "60417", "bakery",    "bread",          4);
 
  /* print all the items */
  print_items(item_list, NUM_ITEMS);
 
  /* print the average price */
  printf("###############\n");
  printf("average price of items = %.2f\n", average_price(item_list, NUM_ITEMS));
 
  /* if the user gave us a command line argument,
     treat it as a SKU and search for it. */
  if (argc >= 2)
  {
    char *sku_to_find = argv[1];
    int ct = 0;
    int found = 0; /* we will set this to 1 if we find the item */
 
    /* Keep looking as long as it still have items left to check (ct < NUM_ITEMS)
       and the current item's sku does not match what it would be looking for.*/

    while (ct < NUM_ITEMS && strcmp(item_list[ct].sku, sku_to_find) != 0)
    {
      ct = ct + 1;
    }
 
    if (ct < NUM_ITEMS)
    {
      found = 1;
    }
 
    printf("\nSearching for SKU %s...\n", sku_to_find);
 
    if (found == 1)
    {
      printf("###############\n");
      printf("item name = %s\n", item_list[ct].name);
      printf("item sku = %s\n", item_list[ct].sku);
      printf("item category = %s\n", item_list[ct].category);
      printf("item price = %.2f\n", item_list[ct].price);
    }
    else
    {
      printf("item not found\n");
    }
  }
 
  /*  free all the memory we allocated */
  free_items(item_list, NUM_ITEMS);
 
  return 0;
}
 
