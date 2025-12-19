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

// REMEMBER TO FREE ALL MEMORY

int main(void){

    int option;
    Product *inventory = NULL;
    do {
        mainMenu(&option);
        runMS(option, &inventory);
        if(option != 5) pause();
    } while(option != 5);
}
