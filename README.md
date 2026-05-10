# Practica 3 - Comunicación Cliente Servidor TCP/IP

## Descripción
Programa cliente-servidor desarrollado en C++ y Python utilizando sockets TCP/IP para simular la recepción de datos de una cámara térmica industrial.

## Archivos incluidos

- cliente.cpp
- ServidorCamara.py
- ejecutar.sh
- datos_recibidos.txt

## Requisitos

- g++
- Python3
- Linux / WSL Ubuntu

## Ejecución

### 1. Ejecutar el servidor

```bash
python3 ServidorCamara.py
```

### 2. Ejecutar el cliente

```bash
chmod +x ejecutar.sh
sh ejecutar.sh
```

## Funcionamiento

El servidor envía 768 datos al cliente mediante sockets TCP/IP. El cliente recibe los datos usando recv(), los almacena en un vector dinámico y posteriormente los guarda en un archivo de texto.

## Resultado esperado

- Conexión correcta con el servidor
- Recepción de 768 datos
- Generación del archivo datos_recibidos.txt
