#include <stdio.h>
#include <string.h>
#include <conio.h> // Solo en Windows
#include "login.h"
#include <windows.h>

int gestionarUsuarios() {
	char usuario[MAX_USUARIO];
	char contrasena[MAX_CONTRASENA];
	const char *archivoUsuarios = "usuarios.txt";
	int opcion;
	
	
	do{
		printf("+------- SISTEMA DE USUARIOS -------+\n");
		printf("|1. Iniciar sesion                  |\n");
		printf("|2. Registrarse                     |\n");
		printf("|3. Salir                           |\n");
		printf("+-----------------------------------+\n");
		printf("Seleccione una opcion: ");
		scanf("%d", &opcion);
		getchar(); // Para limpiar salto de linea del buffer
		
		switch (opcion) {
		case 1: {
			system("cls");
			printf("\n=== INICIO DE SESION ===\n");
			printf("Usuario: ");
			fgets(usuario, sizeof(usuario), stdin);
			int len = strlen(usuario);
			if (len > 0 && usuario[len - 1] == '\n') {
				usuario[len - 1] = '\0';
			}
			printf("Contrasena: ");
			leer_contrasena(contrasena);
			printf("\n");
			
			int resultadoLogin = verificar_credenciales(usuario, contrasena, archivoUsuarios);
			switch (resultadoLogin) {
			case 1:
				printf("Acceso concedido\n");
				return 5;
				break;
			case 0:
				system("cls");
				printf("Usuario o contrasena incorrectos\n");
				break;
			case -1:
				system("cls");
				printf("Error al abrir el archivo de usuarios\n");
				break;
			}
			break;
		}
		
		case 2: {
			char verificarCedula[20];
			int val;
			system("cls");
			printf("\n=== REGISTRO DE USUARIO ===\n");
			
			do {
				val=1;
				printf("Ingrese el numero de cedula del nuevo usuario: ");
				fgets(verificarCedula, sizeof(verificarCedula), stdin);
				
				int len = strlen(verificarCedula);
				if (len > 0 && verificarCedula[len - 1] == '\n') {
					verificarCedula[len - 1] = '\0';
				}
				
				for (int i = 0; verificarCedula[i] != '\0'; i++) {
					if (isspace((unsigned char)verificarCedula[i])) {
						val = 0;
						printf("Error: No ingrese espacios o caracteres de espacio en blanco.\n");
						break;
					}
				}
				
				if (val!=0){
					if (strspn(verificarCedula, "0123456789") != strlen(verificarCedula)) {
						printf("Error: solo se permiten numeros.\n");
						val=0;
						
					}
					if (strlen(verificarCedula) != 10) {
						printf("Error: ingrese un numero de cedula valido.\n");
						val=0;
					}
				}
				
			} while ( val==0);
			
			strcpy(usuario, verificarCedula);
			
			printf("Nueva contrasena: ");
			leer_contrasena(contrasena);
			printf("\n");
			
			int resultadoRegistro = registrar_usuario(usuario, contrasena, archivoUsuarios);
			switch (resultadoRegistro) {
			case 1:
				system("cls");
				printf("Usuario registrado correctamente\n");
				return 5;
				break;
			case 0:
				system("cls");
				printf("El usuario ya existe\n");
				break;
			case -1:
				system("cls");
				printf("Error al registrar el usuario\n");
				break;
			}
			break;
		}
		case 3: printf("\nSaliendo...");
		break;
		
		default:
			system("cls");
			printf("Opcion no valida\n");
		}
		
		
	}while(opcion!=3);
	return 0;
}


int verificar_credenciales(const char *usuario, const char *contrasena, const char *archivoUsuarios) {
	char usuarioArchivo[MAX_USUARIO];
	char contrasenaArchivo[MAX_CONTRASENA];
	
	FILE *archivo = fopen(archivoUsuarios, "r");
	if (archivo == NULL) return -1;
	
	while (fscanf(archivo, "%s %s", usuarioArchivo, contrasenaArchivo) != EOF) {
		if (strcmp(usuario, usuarioArchivo) == 0 && strcmp(contrasena, contrasenaArchivo) == 0) {
			fclose(archivo);
			return 1;
		}
	}
	
	fclose(archivo);
	return 0;
}

int registrar_usuario(const char *usuario, const char *contrasena, const char *archivoUsuarios) {
	char usuarioArchivo[MAX_USUARIO];
	char contrasenaArchivo[MAX_CONTRASENA];
	
	FILE *archivo = fopen(archivoUsuarios, "r");
	if (archivo != NULL) {
		while (fscanf(archivo, "%s %s", usuarioArchivo, contrasenaArchivo) != EOF) {
			if (strcmp(usuario, usuarioArchivo) == 0) {
				fclose(archivo);
				return 0; // Ya existe
			}
		}
		fclose(archivo);
	}
	
	archivo = fopen(archivoUsuarios, "a");
	if (archivo == NULL) return -1;
	
	fprintf(archivo, "%s %s\n", usuario, contrasena);
	fclose(archivo);
	return 1;
}

void leer_contrasena(char *contrasena) {
	char c;
	int i = 0;
	
	while ((c = getch()) != '\r') { // Enter
		if (c == '\b' && i > 0) { // Retroceso
			printf("\b \b");
			i--;
		} else if (c != '\b' && i < MAX_CONTRASENA - 1) {
			contrasena[i++] = c;
			printf("*");
		}
	}
	contrasena[i] = '\0';
}
