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

// Función para cambiar de jugador y de marcador
void cambiarJugadorYMarcador()
{
    if (MA == 'X')
    {
        MA = 'O';
    }
    else
    {
        MA = 'X';
    }

    if (JA == 1)
    {
        JA = 2;
    }
    else
    {
        JA = 1;
    }
}

// Funcion encargada de guardar a los ganadores de cada partida 
void guardarGanador(string nombre)
{
    bool encontrado = false;
    for (int i = 0; i < numGanadores; i++)
    {
        if (registroGanador[i] == nombre)
        {
            victorias[i]++;
            encontrado = true;
            break;
        }
    }

    if (!encontrado && numGanadores < maxGanadores)
    {
        registroGanador[numGanadores] = nombre;
        victorias[numGanadores] = 1; // Inicia con una victoria
        numGanadores++;
    }

    // Guardar los nombres y las victorias en el archivo
    ofstream archivo("GANADORES.txt", ios::trunc); // Usa ios::trunc para reescribir el archivo
    if (archivo.is_open())
    {
        for (int i = 0; i < numGanadores; i++)
        {
            archivo << registroGanador[i] << " -Victorias: " << victorias[i] << endl;
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo de ganadores." << endl;
    }
}

// Funcion donde se crea el archivo donde iran los ganadores 
void mostrarGanadores()
{
    ifstream archivo("GANADORES.txt");
    if (archivo.is_open())
    {
        string nombre;
        cout << "LISTA DE GANADORES:" << endl;
        cout << "-------------------" << endl;
        while (getline(archivo, nombre))
        {
            cout << nombre << endl;
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo de ganadores." << endl;
    }

    cout << endl;
    system("pause"); // Pausa la ejecución del programa y espera a que el usuario presione una tecla para continuar.
    system("cls");  // Limpia la consola.
}

// Funcion encargada de guardar las inscripciones de los participantes en cada ronda  
void inscribirParticipante(string nombre)
{
    // Verifica si el participante ya está inscrito
    for (int i = 0; i < numParticipantes; i++)
    {
        if (participantes[i] == nombre)
        {
            cout << "El participante " << nombre << "ya esta inscrito.\n\n";
            return;
        }
    }

    // Añade el nuevo participante al array
    participantes[numParticipantes++] = nombre;

    // Guarda la lista de participantes en el archivo
    ofstream archivo("PARTICIPANTES.txt", ios::trunc); // Usa ios::trunc para reescribir el archivo
    if (archivo.is_open())
    {
        for (int i = 0; i < numParticipantes; i++)
        {
            archivo << "-" << participantes[i] << endl;
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo de participantes.\n";
    }
}

// Funcion encargada de crear el archivo donde iran los participantes
void mostrarParticipantes()
{
    ifstream archivo("PARTICIPANTES.txt");
    if (archivo.is_open())
    {
        string linea;
        cout << "LISTA DE PARTICIPANTES:\n";
        cout << "-----------------------\n";
        while (getline(archivo, linea))
        {
            cout << linea << endl;
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo de participantes.\n";
    }

    cout << endl;
    system("pause");
    system("cls");
}

// Función para repetir el juego
void repetirJuego()
{    
    static bool yaseJugo = false;  // Variable estática para rastrear si el juego ya se ha repetido

    if (yaseJugo)
    {
        cout << "El juego solo puede repetirse una vez para tener un desempate. \nVuelva al menu principal...\n";
        cout << endl;
        return;
    }

    reiniciarTablero();
    char MJ1;

    cout << NombreJ1 << "\nElige tu Marcador (X u O): ";
    cin >> MJ1;
    cout << endl;

    while (MJ1 != 'X' && MJ1 != 'O')
    {
        cout << "Marcador Invalido!" << endl;
        cout << "Por favor elige 'X' o 'O': ";
        cin >> MJ1;
        cout << endl
             << endl;
    }

    JA = 1;
    MA = MJ1;

    mostrarTablero();

    int JG = 0;  // Jugador ganador

    for (int i = 0; i < 9; i++)
    {
        int casilla;  // Variable que guarda el numero de la casilla a ingresar

        cout << "\nEs el Turno del Jugador " << JA << ". Ingresa el Numero de Casilla: ";
        cin >> casilla;
        cout << endl;

        if (casilla < 1 || casilla > 9)
        {
            cout << "Casilla Invalida! \nIntentalo Otra Vez.\n";
            i--;
            continue;
        }

        if (!colocarMarcador(casilla))
        {
            cout << "Casilla Ocupada! \nIntentalo Otra Vez.\n";
            i--;
            continue;
        }

        system("cls");
        mostrarTablero();

        JG = ganadorJuego();

        if (JG == 1)
        {
            cout << endl << "Felicitaciones! " << NombreJ1 << "Eres el Ganador.\n";
            guardarGanador(NombreJ1);
            break;
        }
        else if (JG == 2)
        {
            cout << endl << "Felicitaciones! " << NombreJ2 << " Eres el Ganador.\n";
            guardarGanador(NombreJ2);
            break;
        }

        cambiarJugadorYMarcador();
    }
    if (JG == 0)
    {
        cout << "El Juego ha Terminado en Empate.\n";
    }

    cout << endl;
    
    yaseJugo = true;  // Establece yaseJugo a true después de que el juego se haya repetido una vez
}

// Función encargada de mostrar el menú para repetir el juego 
void menuRepetir()
{
    int repetir; // Variable que guarda la funcion 

    do
    {
        system("pause");
        system("cls");

        cout << "REPETIR JUEGO" << endl;
        cout << "-------------" << endl;
        cout << "1. SI " << endl;
        cout << "2. NO " << endl;
        cout << "-------------" << endl
             << endl;
        cout << "Opcion a elegir: ";
        cin >> repetir;
        
        cout << endl;
        system("pause");
        system("cls");

        switch (repetir)
        {
        case 1:
            repetirJuego();
            break;
        case 2:
            cout << "SALIENDO AL MENU PRINCIPAL..." << endl
                 << endl;
            break;
        default:
            cout << "Opcion invalida! ";
            cout << endl 
                 << endl;
            break;
        }
    } while (repetir != 2);
}

// Función eccargada de otorgar una revancha en el juego
void revanchaJuego()
{
    reiniciarTablero();
    char MJ1; // Variable que guarda el marcador 

    cout << NombreJ1 << "\nElige tu Marcador (X u O): ";
    cin >> MJ1;
    cout << endl;

    while (MJ1 != 'X' && MJ1 != 'O')
    {
        cout << "Marcador Invalido!" << endl;
        cout << "Por favor elige 'X' o 'O': ";
        cin >> MJ1;
        cout << endl
             << endl;
    }

    JA = 1;
    MA = MJ1;

    mostrarTablero();

    int JG = 0;

    for (int i = 0; i < 9; i++)
    {
        int casilla;

        cout << "\nEs el Turno del Jugador " << JA << ". Ingresa el Numero de Casilla: ";
        cin >> casilla;
        cout << endl;

        if (casilla < 1 || casilla > 9)
        {
            cout << "Casilla Invalida! \nIntentalo Otra Vez.\n";
            i--;
            continue;
        }

        if (!colocarMarcador(casilla))
        {
            cout << "Casilla Ocupada! \nIntentalo Otra Vez.\n";
            i--;
            continue;
        }

        system("cls");
        mostrarTablero();

        JG = ganadorJuego();

        if (JG == 1)
        {
            cout << "\nJUGADOR@ " << NombreJ1 << "HA GANADO, FELICIDADES!\n\n ";
            guardarGanador(NombreJ1);
            break;
        }
        if (JG == 2)
        {
            cout << "\nJUGADOR@ " << NombreJ2 << " HA GANADO, FELICIDADES!\n\n ";
            guardarGanador(NombreJ2);
            break;
        }
        cambiarJugadorYMarcador();
    }

    if (JG == 0)
    {
        cout << "\nEs un empate!\n\n";
    }
}

// Función encargada de mostrar el menú de la revancha
void menuRevancha()
{
    int decision; // Variable que guarda la opcion 

    do
    {
        system("pause");
        system("cls");

        cout << "REVANCHA" << endl;
        cout << "-------------" << endl;
        cout << "1. SI " << endl;
        cout << "2. NO " << endl;
        cout << "-------------" << endl
             << endl;
        cout << "Opcion a elegir: ";
        cin >> decision;
        
        cout << endl;
        system("pause");
        system("cls");

        switch (decision)
        {
        case 1:
            revanchaJuego();
            break;
        case 2:
            cout << "SALIENDO AL MENU PRINCIPAL..." << endl
                 << endl;
            break;
        default:
            cout << "Opcion invalida! ";
            cout << endl
                 << endl;
            break;
        }
    } while (decision != 2);
}

// Función principal del juego general
void juego()
{
    char MJ1;

    cout << "Jugador 1, escribe un nombre y un apellido: ";
    cin.ignore();
    getline(cin, NombreJ1);
    inscribirParticipante(NombreJ1);

    cout << "Jugador 2, escribe un nombre y un apellido: ";
    getline(cin, NombreJ2);
    inscribirParticipante(NombreJ2);

    cout << endl;
    system("pause");
    system("cls");

    reiniciarTablero();

    cout << NombreJ1 << "\nElige tu Marcador (X u O): ";
    cin >> MJ1;
    cout << endl;

    while (MJ1 != 'X' && MJ1 != 'O')
    {
        cout << endl
             << "Marcador Invalido!" << endl;
        cout << "Por favor elige 'X' o 'O': ";
        cin >> MJ1;
        cout << endl
             << endl;
    }

    JA = 1;
    MA = MJ1;

    mostrarTablero();

    int JG = 0;

    for (int i = 0; i < 9; i++)
    {
        int casilla;

        cout << "\nEs el Turno del Jugador " << JA << ". Ingresa el Numero de Casilla: ";
        cin >> casilla;
        cout << endl;

        if (casilla < 1 || casilla > 9)
        {
            cout << "Casilla Invalida! \nIntentalo Otra Vez.\n";
            i--;
            continue;
        }

        if (!colocarMarcador(casilla))
        {
            cout << "Casilla Ocupada! \nIntentalo Otra Vez.\n";
            i--;
            continue;
        }
        
        system("cls");
        mostrarTablero();

        JG = ganadorJuego();

        if (JG == 1)
        {
            cout << "\nJUGADOR@ " << NombreJ1 << "HA GANADO, FELICIDADES!\n\n ";
            guardarGanador(NombreJ1);
            menuRevancha();
            break;
        }
        else if (JG == 2)
        {
            cout << "\nJUGADOR@ " << NombreJ2 << " HA GANADO, FELICIDADES!\n\n ";
            guardarGanador(NombreJ2);
            menuRevancha();
            break;
        }
        cambiarJugadorYMarcador();
    }

    if (JG == 0)
    {
        cout << "\nEs un empate!\n\n";
        menuRepetir();
    }
}

// Función que genera la prueba del juego en el submenu
void pruebaJuego()
{
    reiniciarTablero();

    cout << endl;
    cout << "Elige tu Marcador (X u O): ";
    char MJ1;
    cin >> MJ1;
    cout << endl;

    while (MJ1 != 'X' && MJ1 != 'O')
    {
        cout << endl
             << "Marcador Invalido!" << endl;
        cout << "Por favor elige 'X' o 'O': ";
        cin >> MJ1;
    }

    JA = 1;
    MA = MJ1;

    mostrarTablero();

    int JG = 0;

    for (int i = 0; i < 9; i++)
    {
        int casilla;

        cout << "\nEs el Turno del Jugador " << JA << ". Ingresa el Numero de Casilla: ";
        cin >> casilla;
        cout << endl;

        if (casilla < 1 || casilla > 9)
        {
            cout << "Casilla Invalida! \nIntentalo Otra Vez.\n";
            i--;
            continue;
        }

        if (!colocarMarcador(casilla))
        {
            cout << "Casilla Ocupada! \nIntentalo Otra Vez.\n";
            i--;
            continue;
        }
        
        system("cls");
        mostrarTablero();

        JG = ganadorJuego();

        if (JG == 1)
        {
            cout << "\nEL JUGADOR 1 HA GANADO, FELICIDADES!\n\n ";
            break;
        }
        if (JG == 2)
        {
            cout << "\nEL JUGADOR 2 HA GANADO, FELICIDADES!\n\n ";
            break;
        }
        cambiarJugadorYMarcador();
    }

    if (JG == 0)
    {
        cout << "\nEs un empate!\n\n";
    }
}

// Funcion encargada de proporcionar las opciones del menu de ayuda
void menuAyuda(){
    int OP; // Variable que guarda la opcion
    do
    {
        system("cls");
        cout << "MENU DE AYUDA" << endl;
        cout << "--------------------" << endl;
        cout << "1. Guia" << endl;
        cout << "2. Juego de Prueba" << endl;
        cout << "3. Salir del Menu" << endl;
        cout << "--------------------" << endl
             << endl;
        cout << "Ingresa el numero de opcion: ";
        cin >> OP;

        switch (OP)
        {
        case 1:
            system("cls");
            cout << endl
                 << "BIENVENIDO A LA GUIA" << endl;
            cout << "--------------------" << endl
                 << endl;
            cout << "PASO 1: Escribe un Nombre, Un Apellido y Tu Carnet" << endl
                 << endl;
            cout << "PASO 2: Escoge la Figura que Deseas Usar (X u O)\n Nota: Escribelas en Mayuscula" << endl
                 << endl;
            cout << "PASO 3: Marca el Numero de la casilla a elegir" << endl
                 << endl;

            mostrarTablero();
            cout << endl;

            cout << "El Ganador es el Primero en Alinear 3 de sus Figuras" << endl;
            cout << "Si Ninguno de los jugadores Alinea 3 de sus figuras, sera un Empate" << endl
                 << endl;
            cout << "El juego presenta dos opciones incluidas, una de revancha y la otra de repetir juego si se llega a dar un empate" << endl
                 << endl;
            system("pause");
            system("cls");
            break;

        case 2:
            system("cls");
            cout << "PRUEBA\n";
            cout << "------\n";
            pruebaJuego();
            system("pause");
            system("cls");
            break;

        case 3:
             system("cls");
            cout << "SALIENDO AL MENU PRINCIPAL..." << endl
                 << endl;
            system("pause");
            system("cls");
            break;

        default:
            system("cls");
            cout << endl
                 << "Opcion Erronea\nPor favor, Ingrese una Opcion Valida" << endl
                 << endl;
            system("pause");
            system("cls");
            break;    
        }
    } while (OP != 3);
    
}

int main(){
    int opcion; // Variable que guarda la opcion 

    do
    {
        cout << endl
             << "BIENVENIDOS AL JUEGO" << endl;
        cout << "       X|O|X" << endl;
        cout << "--------------------" << endl;
        cout << "1. Iniciar Partida" << endl;
        cout << "2. Ganadores" << endl;
        cout << "3. Inscripciones" << endl;
        cout << "4. Ayuda" << endl;
        cout << "5. Creditos" << endl;
        cout << "6. Salir del Juego" << endl;
        cout << "--------------------" << endl
             << endl;
        cout << "Ingresa el Numero de Opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            system("cls");
            juego();
            system("pause");
            system("cls");
            break;

        case 2:
            system("cls");
            mostrarGanadores();
            break;

        case 3:
            system("cls");
            mostrarParticipantes();
            break;

        case 4:
            menuAyuda();
            break;

        case 5:
            system("cls");
            cout << endl
                 << "INTEGRANTES DEL GRUPO" << endl;
            cout << "---------------------" << endl
                 << endl;
            cout << "Josue Rafael Carpio Oliva" << endl;
            cout << "00018023" << endl
                 << endl;
            cout << "Ana Cecilia Menjivar Menjivar" << endl;
            cout << "00176824" << endl
                 << endl;
            cout << "Byron Alexis Zepeda Ramirez" << endl;
            cout << "00020023" << endl;
            cout << "--------------------" << endl
                 << endl;
            system("pause");
            system("cls");
            break;

        case 6:
            system("cls");
            cout << "Gracias Por Jugar :)" << endl
                 << endl;
            system("pause");
            system("cls");
            break;

        default:
            system("cls");
            cout << endl
                 << "Opcion Erronea\nPor favor Ingrese una Opcion Valida" << endl
                 << endl;
            system("pause");
            system("cls");
            break;
        }

    }while(opcion != 6);
    
    return 0;
}