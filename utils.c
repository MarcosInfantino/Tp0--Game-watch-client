/*
 * conexiones.c
 *
 *  Created on: 2 mar. 2019
 *      Author: utnso
 */

#include "utils.h"
//TODO


void* serializar_paquete(t_paquete* paquete, int bytes){
	void* a_enviar=malloc(bytes);
	int offset=0;
	memcpy(a_enviar+offset,&(paquete->codigo_operacion),sizeof(op_code));
	offset+=sizeof(op_code);

	memcpy(a_enviar+offset,&(paquete->buffer->size),sizeof(int));
	offset+=sizeof(int);

	memcpy(a_enviar+offset,(paquete->buffer->stream),paquete->buffer->size);

	return a_enviar;

}

int crear_conexion(char *ip, char* puerto)
{
	struct addrinfo hints;
	struct addrinfo *server_info;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &hints, &server_info);

	int socket_cliente = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);

	if(connect(socket_cliente, server_info->ai_addr, server_info->ai_addrlen) == -1)
		printf("error");

	freeaddrinfo(server_info);

	return socket_cliente;
}

//TODO

void enviar_mensaje(char* mensaje, int socket_cliente){
	t_buffer* buffer=malloc(sizeof(t_buffer));
	buffer->size=strlen(mensaje)+1;
	buffer->stream=malloc(buffer->size);
	memcpy(buffer->stream,mensaje,buffer->size);



	t_paquete* paquete=malloc(sizeof(t_paquete));
	paquete->codigo_operacion=MENSAJE;
	paquete->buffer=buffer;

	void* a_enviar=serializar_paquete(paquete,sizeof(op_code)+buffer->size+sizeof(buffer->size));

	send(socket_cliente,a_enviar,sizeof(op_code)+buffer->size+sizeof(buffer->size),0);

	free(buffer->stream);
	free(buffer);
	free(paquete);
	free(a_enviar);

}



char* deserializar_mensaje(t_buffer* buffer){
	return (char*) (buffer->stream);
}

//TODO


char* recibir_mensaje(int socket_cliente){
	int codigoOp;
	int size;
	recv(socket_cliente,&codigoOp,sizeof(int),0);
	recv(socket_cliente,&size,sizeof(int),0);
	void* stream=malloc(size);
	recv(socket_cliente,stream,size,0);
	t_buffer* buffer=malloc(sizeof(t_buffer));
	buffer->size=size;
	buffer->stream=stream;

	switch(codigoOp){
		case MENSAJE:

			return deserializar_mensaje(buffer);
			break;

		default:

			return '\0';
			break;
	}
}

void liberar_conexion(int socket_cliente)
{
	close(socket_cliente);
}
