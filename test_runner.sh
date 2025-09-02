#!/bin/bash
echo "¡Hola $(whoami)!"

if [[ -z "$1" ]]; then
 	echo "Uso: $0 [0|1] [nombre_fichero (opcional)]"
	echo "0 --> compila y ejecuta"
	echo "1 --> compila y ejecuta con valgrind"
  	exit 0
fi

if [[ "$1" != "0" && "$1" != "1" ]]; then
  	echo "El primer argumento debe ser 0 (ejecutar) o 1 (valgrind)"
  	exit 0
fi

if [[ ! -e "src/$2" ]]; then
	echo "Error: El fichero fuente '$2' no existe en este directorio."
  	exit 0
fi

modo=$1
test=$2

f_base="${test%.*}"
make compile_test FICHERO_FUENTE=src/$2 FICHERO_OBJETO=obj/$f_base.o
make $f_base

if [[ "$modo" == 0 ]]; then
	./$f_base
	exit 1
fi

if [["$modo" == 1]]; then
	echo "Ejecutando $f_base con Valgrind..."
	valgrind --leak-check=full --track-origins=yes ./$f_base
	exit 1
fi
