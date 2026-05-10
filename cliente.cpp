#include <iostream>
#include <vector>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include <cstring>

using namespace std;

// Crear socket TCP/IP
int crearSocket()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd == -1)
    {
        cerr << "Error al crear el socket" << endl;
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

// Configurar servidor
sockaddr_in configurarServidor(const string &ip, int puerto)
{
    sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(puerto);

    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0)
    {
        cerr << "Direccion IP invalida" << endl;
        exit(EXIT_FAILURE);
    }

    return serv_addr;
}

// Conectar con el servidor
void conectarServidor(int sockfd, sockaddr_in &serv_addr)
{
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        cerr << "Error al conectar con el servidor" << endl;
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    cout << "Conexion establecida correctamente" << endl;
}

// Recibir datos
vector<unsigned char> recibirDatos(int sockfd)
{
    vector<unsigned char> datos;

    unsigned char buffer[256];

    ssize_t bytes_recibidos;

    while ((bytes_recibidos = recv(sockfd, buffer, sizeof(buffer), 0)) > 0)
    {
        for (int i = 0; i < bytes_recibidos; i++)
        {
            datos.push_back(buffer[i]);
        }
    }

    if (bytes_recibidos < 0)
    {
        cerr << "Error al recibir datos" << endl;
    }

    return datos;
}

// Guardar archivo
void guardarArchivo(const vector<unsigned char> &datos, const string &nombreArchivo)
{
    ofstream archivo(nombreArchivo);

    if (!archivo)
    {
        cerr << "Error al crear el archivo" << endl;
        return;
    }

    for (size_t i = 0; i < datos.size(); i++)
    {
        archivo << (int)datos[i] << endl;
    }

    archivo.close();

    cout << "Datos guardados en: " << nombreArchivo << endl;
}

// Imprimir datos
void imprimirDatos(const vector<unsigned char> &datos)
{
    cout << "Datos recibidos:" << endl;

    for (size_t i = 0; i < datos.size(); i++)
    {
        cout << (int)datos[i] << " ";

        if ((i + 1) % 16 == 0)
        {
            cout << endl;
        }
    }

    cout << endl;
    cout << "Cantidad total de datos recibidos: " << datos.size() << endl;
}

// Main
int main()
{
    string ipServidor = "127.0.0.1";
    int puerto = 12345;

    // Crear socket
    int sockfd = crearSocket();

    // Configurar servidor
    sockaddr_in servidor = configurarServidor(ipServidor, puerto);

    // Conectar
    conectarServidor(sockfd, servidor);

    // Recibir datos
    vector<unsigned char> datos = recibirDatos(sockfd);

    // Mostrar datos
    imprimirDatos(datos);

    // Guardar datos
    guardarArchivo(datos, "datos_recibidos.txt");

    // Cerrar socket
    close(sockfd);

    cout << "Socket cerrado correctamente" << endl;

    return 0;
}
