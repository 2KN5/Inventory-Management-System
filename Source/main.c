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
    do {
        mainMenu(&option);
        runMS(option);
        if(option != 5) pause();
    } while(option != 5);
}
