#ifndef LOGIN_H
#define LOGIN_H

#define MAX_USUARIO 50
#define MAX_CONTRASENA 50

int verificar_credenciales(const char *usuario, const char *contrasena, const char *archivoUsuarios);
int registrar_usuario(const char *usuario, const char *contrasena, const char *archivoUsuarios);
void leer_contrasena(char *contrasena);
int gestionarUsuarios();
#endif
