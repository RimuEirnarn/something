#include <stdio.h>
#include "stdrimu.h"
#include "stderr.h"

class AddressBook {
    String name;
    String phone_number;
} AddressBook;

class LinkedAddress {
    AddressBook value;
    struct LinkedAddress *prev;
    struct LinkedAddress *next;
} LinkedAddress;

LinkedAddress* init_la(AddressBook value) {
    LinkedAddress *content = malloc(sizeof(LinkedAddress));
    // LinkedAddress content = {
    //     value,
    //     NULL,
    //     NULL
    // };
    content->value = value;
    content->next = NULL;
    content->prev = NULL;
    return content;
}

void push_la(LinkedAddress *arr, AddressBook value) {
    LinkedAddress *curr = arr;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    LinkedAddress *content = init_la(value);
    content->prev = curr;
    content->next = NULL;
    curr->next = content;
}

LinkedAddress* pop_la(LinkedAddress *arr, AddressBook value) {
    LinkedAddress *curr = arr;
    while (curr != NULL) {
        if ((strcmp(curr->value.name.value, value.name.value) == 0) &&
            (strcmp(curr->value.phone_number.value, value.phone_number.value) == 0)) {
            LinkedAddress *prev = curr->prev;
            LinkedAddress *next = curr->next;
            prev->next = next;
            if (next != NULL) next->prev = prev;
            curr->prev = NULL;
            curr->next = NULL;
            // free(curr);
            return curr;
        }
        curr = curr->next;
    }
    String val = value.name;
    char fmt[1024];
    sprintf(fmt, "Cannot find %.*s", val.length, val.value);
    raise_from("ValueError", fmt);
}

LinkedAddress* find_la_by_name(LinkedAddress *arr, String name) {
    LinkedAddress *curr = arr;
    while (curr != NULL) {
        if (strcmp(curr->value.name.value, name.value) == 0) return curr;
        curr = curr->next;
    }

    String val = name;
    char fmt[1024];
    sprintf(fmt, "Cannot find %.*s", val.length, val.value);
    raise_from("ValueError", fmt);
}


void print(LinkedAddress *arr) {
    LinkedAddress *curr = arr;
    while (curr != NULL) {
        AddressBook a = curr->value;
        printf("Name  : " STR_FMT "\n", STR_ARGS(a.name));
        printf("Number: " STR_FMT "\n", STR_ARGS(a.phone_number));
        printf("---\n");
        // if (curr->next == NULL) break;
        curr = curr->next;
    }
}

int main() {
    AddressBook ad = {
        define_str("Agus Sentosa"),
        define_str("000-000-000")
    };
    AddressBook ad0 = {
        define_str("Agus Sentosa 2"),
        define_str("000-000-000")
    };
    LinkedAddress *la = init_la(ad);
    push_la(la, ad0);
    LinkedAddress *lb0 = find_la_by_name(la, define_str("Agus Sentosa 2"));
    lb0->value.name = define_str("Agus Sentosa 3");

    print(la);
    LinkedAddress *lb = pop_la(la, ad0);
    free(lb);
    print(la);
    return 0;
}
