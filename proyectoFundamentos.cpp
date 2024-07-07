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
