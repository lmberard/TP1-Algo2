_________________________________________________________________
-----------------------------------------------------------------
		Universidad de Buenos Aires
		Facultad de Ingeniería

		Algoritmos y Programacion II
		Trabajo Practico Nro 0

Integrantes:
Berard, Lucia Magdalena		101213  lberard@fi.uba.ar
Guglieri, Mariano Federico    	99573	mguglieri@fi.uba.ar
Rubin, Ivan Eric		100577  irubin@fi.uba.ar
Sandoval, Diego Ariel		101639	dsandoval@fi.uba.ar
_________________________________________________________________
-----------------------------------------------------------------

--------------------------Codigos--------------------------------
-> bignum.cpp / bignum.h: Declaracion e implementacion de la clase
-> cmdline.cpp / cmdline.h: Para el uso de la línea de comando.
-> tp0.cpp: Main principal
-> Makefile: Archivo Makefile utilizado en el proceso de compilacion
-> cuentas.txt: Archivo de prueba 

-----------------------Compilacion-------------------------------
Abrir terminal de Linux y utilizar el comando "make". 
Otros comandos utiles:
-make clean: borra todos los archivos .o generados.
-make valgrind: para debuggear con gdb
-make gdb: ejecuta el programa con valgrind para verificar que 
no haya fallas de memoria

-------------------Ejecución del programa------------------------
Ejemplos:
echo "-1 - 5" | ./tp0 -p 2
echo -189*50 | ./tp0 -p 6

Con archivos de entrada(i) y salida(o):
./tp0 -p 2 -i cuentas.txt
./tp0 -p 2 -o resultados.txt

Help:
./tp0 -hcmdline -p precision [-i file] [-o file]