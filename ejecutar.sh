#!/bin/bash

clear

echo "Compilando programa..."

g++ cliente.cpp -o cliente

if [ $? -ne 0 ]; then
    echo "Error de compilacion"
    exit 1
fi

echo "Ejecutando cliente..."

./cliente
