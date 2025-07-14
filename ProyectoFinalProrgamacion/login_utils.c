#include <stdio.h>
#include <string.h>
#include <conio.h> // Solo en Windows
#include "procesos.h" 
#include "login.h"
#include <windows.h>

int gestionarUsuarios() {
	char usuario[MAX_USUARIO];
	char contrasena[MAX_CONTRASENA];
	const char *archivoUsuarios = "usuarios.txt";
	
	// Ingreso de usuario con validación
	int valido;
	do {
		valido = 1;
		printf("Ingrese su numero de cedula (10 digitos): ");
		fgets(usuario, sizeof(usuario), stdin);
		int len = strlen(usuario);
		if (len > 0 && usuario[len - 1] == '\n') {
			usuario[len - 1] = '\0';
		}
		
		if (strlen(usuario) != 10) {
			printf("Error: la cedula debe tener exactamente 10 digitos.\n");
			valido = 0;
			continue;
		}
		
		for (int i = 0; i < 10; i++) {
			if (!isdigit(usuario[i])) {
				printf("Error: solo se permiten numeros.\n");
				valido = 0;
				break;
			}
		}
	} while (!valido);
	
	// Ingreso de contraseña
	printf("Ingrese su contrasena: ");
	leer_contrasena(contrasena);
	printf("\n");
	
	// Verificación de credenciales
	int resultadoLogin = verificar_credenciales(usuario, contrasena, archivoUsuarios);
	switch (resultadoLogin) {
	case 1:
		printf("Acceso concedido\n");
		return 5;
	case 0:
		printf("Usuario o contrasena incorrectos\n");
		break;
	case -1:
		printf("Error al abrir el archivo de usuarios\n");
		log_error("Error al abrir 'usuarios.txt' en verificar_credenciales().");
		return 0;
	}
	
	// Preguntar si desea registrarse
	char respuesta[10];
	printf("Desea registrarse como nuevo usuario? (si/no): ");
	fgets(respuesta, sizeof(respuesta), stdin);
	
	// Eliminar el salto de línea
	respuesta[strcspn(respuesta, "\n")] = '\0';
	
	// Convertir a minúsculas para comparación
	for (int i = 0; respuesta[i]; i++) {
		respuesta[i] = tolower((unsigned char)respuesta[i]);
	}
	
	if (strcmp(respuesta, "si") == 0) {
		printf("Ingrese nueva contrasena: ");
		leer_contrasena(contrasena);
		printf("\n");
		
		int resultadoRegistro = registrar_usuario(usuario, contrasena, archivoUsuarios);
		switch (resultadoRegistro) {
		case 1:
			printf("Usuario registrado correctamente\n");
			return 5;
		case 0:
			printf("El usuario ya existe\n");
			break;
		case -1:
			printf("Error al registrar el usuario\n");
			log_error("Error al escribir en 'usuarios.txt' en registrarUsuario().");
			break;
		}
	}
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
