#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    if(head == NULL){
        return 0;
    }
    node *ptr1 = head, *ptr2 = head->next;
    while(ptr1 != NULL && ptr2 != NULL){
        if(ptr1 == ptr2){
            return 1;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
        if(ptr2 == NULL){
            break;
        }
        ptr2 = ptr2->next;
    }
    return 0;
}