/*
Grupo: SO-010
Membros:
Francisco Teixeira | FC56305
Andre Alves        | FC56349
Rodrigo Antunes    | FC56321
*/
#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "main.h"
#include "client.h"

int execute_client(int client_id, struct communication_buffers* buffers, struct main_data* data){
    int ops = 0;
    int* ptr = &ops;
    int terminate_flag = *(data->terminate);
    struct operation* op = create_dynamic_memory(sizeof (struct operation));
    while (1){
        terminate_flag = *(data->terminate);
        if(terminate_flag == 1) {
            destroy_dynamic_memory(op);
            return *ptr;
        }
        else{
            memset(op,0,sizeof (struct operation));
            op->id=-1;
            client_get_operation(op, client_id, buffers, data);

            if(op->id != -1){
                client_process_operation(op, client_id, data, ptr);
            }
        }
    }
}


void client_get_operation(struct operation* op, int client_id, struct communication_buffers* buffers, struct main_data* data){
    int terminate_flag = *(data->terminate);
    if(terminate_flag == 1)
        return;
    else{
        read_driver_client_buffer(buffers->driv_cli, client_id, data->buffers_size, op);

    }
}

void client_process_operation(struct operation* op, int client_id, struct main_data* data, int* counter){
    printf("O cliente recebeu o pedido!\n");
    op->receiving_client = client_id;
    op->status = 'C';
    (*counter)++;
    data->results[op->id] = *op;
}