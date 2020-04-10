/*
 * main.c
 *
 *  Created on: 28 feb. 2019
 *      Author: utnso
 */

#include "tp0.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	log_info(logger,"soy un logger");


	config = leer_config();
	ip=config_get_string_value(config,"IP");
	puerto=config_get_string_value(config,"PUERTO");
	log_info(logger,ip);
	log_info(logger,puerto);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/


	conexion=crear_conexion(ip,puerto);

	if(conexion<0){
		printf("No se pudo conectar\n");
		return -1;
	}

	char* str=malloc(50);
	printf("\nIngrese el mensaje : ");
	scanf("%s",str);
	enviar_mensaje(str,conexion);

	char* mensaje=recibir_mensaje(conexion);

	log_info(logger,mensaje);

	terminar_programa(conexion, logger, config);

	return 0;
}

//TODO
t_log* iniciar_logger(void)
{
	return log_create("tp0.log","Game-watch-client",true,0);

}

//TODO
t_config* leer_config(void)
{

return config_create("/home/utnso/Game-watch-client/tp0.config");
}

//TODO
void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
