#include "common.h"
#include "order.h"
#include "orderQueue.h"
#include "product.h"
#include "utils.h"

/*

Konstantinos Tampouris
AM: 2022202400200
dit24200@uop.gr

*/

int main(void){

    int option;
    Product *inventory = NULL;

    // Initialize OrderBucket here.
    OrderBucket *ob = malloc(sizeof(*ob));
    if(!ob){
        printf("Malloc failed for OrderBucket!\n");
        return 1;
    }
    initializeOB(ob); 

    // Run the program.
    do {
        mainMenu(&option);
        runMS(option, &inventory, ob);
        if(option != 5) pause();
    } while(option != 5);

    // Free everything before exiting.
    freeInventory(inventory);
    freeOrderBucket(ob);

}
