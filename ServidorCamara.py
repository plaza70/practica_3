import socket
import struct

HOST = '0.0.0.0'
PORT = 12345

data_array = [i % 256 for i in range(768)]

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:

    server_socket.bind((HOST, PORT))

    server_socket.listen()

    print(f'Servidor escuchando en {HOST}:{PORT}')

    conn, addr = server_socket.accept()

    with conn:

        print('Conexion aceptada desde:', addr)

        data_bytes = struct.pack('768B', *data_array)

        conn.sendall(data_bytes)

        print('Datos enviados correctamente')
