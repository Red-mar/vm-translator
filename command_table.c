#include "command_table.h"

hash_table* command_ht;

void init_cmd_ht() {
    hash_table* ht = new_hash_table(128);

    insert_ht_item(ht, "add" , "C_ARITHMETIC");
    insert_ht_item(ht, "sub" , "C_ARITHMETIC");
    insert_ht_item(ht, "neg" , "C_ARITHMETIC");
    insert_ht_item(ht, "and" , "C_ARITHMETIC");
    insert_ht_item(ht, "or" , "C_ARITHMETIC");
    insert_ht_item(ht, "not" , "C_ARITHMETIC");
    insert_ht_item(ht, "eq" , "C_ARITHMETIC");
    insert_ht_item(ht, "gt" , "C_ARITHMETIC");
    insert_ht_item(ht, "lt" , "C_ARITHMETIC");

    insert_ht_item(ht, "pop" , "C_POP");
    insert_ht_item(ht, "push" , "C_PUSH");

    insert_ht_item(ht, "label" , "C_LABEL");
    insert_ht_item(ht, "goto" , "C_GOTO");

    insert_ht_item(ht, "if-goto" , "C_IF");

    insert_ht_item(ht, "function" , "C_FUNCTION");
    insert_ht_item(ht, "return" , "C_RETURN");
    insert_ht_item(ht, "call" , "C_CALL");
    command_ht = ht;
}

void init_command_ht() {
    init_cmd_ht();
}


void free_command_ht() {
    free_ht(command_ht);
}
