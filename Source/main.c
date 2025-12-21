#include "orderQueue.h"
#include "product.h"
#include "common.h"
#include "utils.h"

/*

Konstantinos Tampouris
AM: 2022202400200
dit24200@uop.gr

Orfeas Vasilis Mermigas
AM: 2022202400122
dit24122@uop.gr

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
        
        MenuParameters *par = malloc(sizeof(*par));
        if(!par){
            printf("Malloc failed for MenuParameters!\n");
            continue;
        }

        runMS(option, &inventory, ob, par); 
        free(par);

        if(option != 5) pause();
    } while(option != 5);

    // Free everything before exiting.
    freeInventory(inventory);
    freeOrderBucket(ob);

}
