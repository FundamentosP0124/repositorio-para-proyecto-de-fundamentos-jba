#include <iostream>
#include <fstream>  // Libreria utilizada para la creacion de archivos 
using namespace std;

char tablero[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char MA; // Marcador Actual
int JA;  // Jugador Actual
string NombreJ1, NombreJ2;  // Variables encargadas de guardar a los participantes a inscribirse 
const int maxGanadores = 200;         // Constante que define el número máximo de jugadores ganadores
string registroGanador[maxGanadores]; // Arreglo para guardar los ganadores
int numGanadores = 0;  // Contador encargado del numero actual de los ganadores registrados 
int victorias[maxGanadores] = {0}; // Arreglo para contar las victorias
const int capacidadInicial = 400;  // Constante que define el numero maximo de participantes
int capacidad = capacidadInicial;  // Gestiona la dinamica de los participantes del juego 
string participantes[capacidadInicial]; // Arreglo encargado de guardar a los participantes 
int numParticipantes = 0;  // Contador encargado del numero actual de participantes registrados 

// Función para dibujar el tablero de juego
void mostrarTablero()
{
    cout << "-------------\n";
    cout << "| " << tablero[0][0] << " | " << tablero[0][1] << " | " << tablero[0][2] << " | " << "\n";
    cout << "|---|---|---|\n";
    cout << "| " << tablero[1][0] << " | " << tablero[1][1] << " | " << tablero[1][2] << " | " << "\n";
    cout << "|---|---|---|\n";
    cout << "| " << tablero[2][0] << " | " << tablero[2][1] << " | " << tablero[2][2] << " | " << "\n";
    cout << "-------------\n";
}

// Función para reiniciar el tablero
void reiniciarTablero()
{
    int contador = 1;   // Variable asignada como contador 
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tablero[i][j] = '0' + contador;
            contador++;
        }
    }
}

// Función para colocar el marcador en el tablero
bool colocarMarcador(int casilla)
{
    int fila = (casilla - 1) / 3;
    int columna = (casilla - 1) % 3;

    if (tablero[fila][columna] != 'X' && tablero[fila][columna] != 'O')
    {
        tablero[fila][columna] = MA;
        return true;
    }
    else
    {
        return false;
    }
}

// Función para determinar el ganador
int ganadorJuego()
{
    for (int i = 0; i < 3; i++)
    {
        // Revisar filas
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2])
        {
            return JA;
        }
        // Revisar columnas
        if (tablero[0][i] == tablero[1][i] && tablero[1][i] == tablero[2][i])
        {
            return JA;
        }
    }
    // Revisar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2])
    {
        return JA;
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0])
    {
        return JA;
    }
    return 0;
}