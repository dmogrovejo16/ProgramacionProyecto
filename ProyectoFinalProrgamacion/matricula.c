#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "matricula.h"



float calcularMatricula (char placa[], float avaluo, int anio, int edad, int revisiones, int tipo) {
	int total, mesCorrespondiente, contador;
	float tasaFija, impuesto = avaluo * 0.0015, totalMatricula, valor, cilindraje, impuestoCilindraje,  impuestoAvaluo, impuestoMes, impuestoRevisiones, descuentoEdad;
	int anioActual = 2025, antiguedad = anioActual - anio;
	char placaMulta[100][10], verificarCilindraje[5];
	
	
	time_t t = time(NULL);     //Guardamos el mes actual
	struct tm* fecha = localtime(&t);  
	int mes=fecha->tm_mon + 1;
	
	// Descuento por antigüedad
	if (antiguedad > 20) {
		impuesto *= 0.7;  // 30% de descuento
	}
	
	
	FILE* archivo = fopen("multas.txt", "r"); //Abrimos archivo de las placas ocn multas
	 if (archivo!=NULL){ //Verificamos que se haya podido abi=rir
		fscanf(archivo, "%d", &total);
		 for (int i = 0; i<total; i++){
			fscanf(archivo, "%s", placaMulta[i]);
		 }
	 }else{
		 printf("ERROR: Archivo de base de multas no se puedo abrir. \n");
	 }
	fclose(archivo);
	 for (int i = 0; i<total; i++){ //Comparar si la placa ingresada esta en el archivo
		 if (strcmp(placa,placaMulta[i])==0){
			 printf("ALERTA: El vehiculo no se puede matriculas porque cuenta con multas sin pagar. \n");
			 totalMatricula=0;
			 return 0;
		 }
	 } 
	 
	 do {
		 printf("Ingrese el cilindraje del vehiculo: "); //Solicitamos cilindraje con validaciones
		 scanf("%s", verificarCilindraje);
		 
		 if (strspn(verificarCilindraje, "0123456789.,") != strlen(verificarCilindraje)) {
			 printf("Error: solo se permiten números.\n");
		 }
		 
	 } while (strspn(verificarCilindraje, "0123456789") != strlen(verificarCilindraje));	
	 cilindraje = atof(verificarCilindraje);
	
	 if (cilindraje <=1.5){ //Calculamos impuesto por cilindraje
		 impuestoCilindraje=0;
	 }else if(cilindraje >1.5 && cilindraje<=2){
		 impuestoCilindraje=55;
	 }else if (cilindraje >2 && cilindraje<=3){
		 impuestoCilindraje=175;
	 }else if(cilindraje >3 && cilindraje<=4){
		 impuestoCilindraje=450;
	 }else{
		 impuestoCilindraje=700;
	 }
	 
	 
	 if (avaluo <=4000){ //Calculamos impuesto por avaluo
		 impuestoAvaluo=20;
	 }else if(cilindraje >4000&& cilindraje<=8000){
		 impuestoAvaluo=60;
	 }else if (cilindraje >8000 && cilindraje<=12000){
		 impuestoAvaluo=140;
	 }else if(cilindraje >12000 && cilindraje<=16000){
		 impuestoAvaluo=260;
	 }else{
		 impuestoAvaluo=420;
	 }
	 
	 
	 if(placa[strlen(placa)-1]=='1' ){ //Definimos el mes correspondiente para la matricula
		 mesCorrespondiente = 2;
	 }else if(placa[strlen(placa)-1]=='2' ){
		 mesCorrespondiente = 3;
	 }else if(placa[strlen(placa)-1]=='3' ){
		 mesCorrespondiente = 4;
	 }else if(placa[strlen(placa)-1]=='4' ){
		 mesCorrespondiente = 5;
	 }else if(placa[strlen(placa)-1]=='5' ){
		 mesCorrespondiente = 6;
	 }else if(placa[strlen(placa)-1]=='6' ){
		 mesCorrespondiente = 7;
	 }else if(placa[strlen(placa)-1]=='7' ){
		 mesCorrespondiente = 8;
	 }else if(placa[strlen(placa)-1]=='8' ){
		 mesCorrespondiente = 9;
	 }else if(placa[strlen(placa)-1]=='9'){
		 mesCorrespondiente = 10;
	 }else if(placa[strlen(placa)-1]=='0'){
		 mesCorrespondiente = 11;
	 }else{
		 mesCorrespondiente = 0;
	 }
	 
	 switch(tipo){
	 case 1:
		 tasaFija=25;
		 break;
	 case 2:
		 tasaFija=18;
		 break;
	 case 3:
		 tasaFija=41;
		 break;
	 case 4:
		 tasaFija=35;
		 break;
	 case 5:
		 tasaFija=15;
		 break;
	 default:
		 printf("Error identificando el tipo de vehiculo.\n");
	 }
	 if(mes > mesCorrespondiente){ //Verificamos que no haya pasado la fecha
		 
		 for(int i=1; i<=(mes - mesCorrespondiente); i++){
			 contador = i;
			 impuestoMes+=25; //Se le agrega la multa al valor final
		 }
		 printf("Ha pasado la fecha de su matricula, se le aplicara un adicional de $%d \n", contador*25);
	 }
	 
	 if (edad>75){//Vemos si es mayor de edad
		descuentoEdad = 1; //Se verifica que es mayor de edad en una variable para poder comparar
		 printf("El propietario es mayor de edad, se le aplicara un descuento del 50% \n");
	 }
	 
	 if (revisiones<3){//Vemos si cumplio todas las revisiones
		 impuestoRevisiones = 50; //Se le agrega la multa al valor final
		 printf("NO cumple las revisiones tecnicas necesarias, se le aplicara una multa de $50 \n");
	 }
	 
	 totalMatricula = tasaFija+impuesto+impuestoAvaluo+impuestoCilindraje+impuestoMes+impuestoRevisiones;
	 if (descuentoEdad ==1){
		 totalMatricula*=0.5;
	 };
	 
	return totalMatricula;
} 

