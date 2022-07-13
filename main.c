#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//---DEFINICION ESTRUCTURAS Y VECTORES GLOBALES---

struct Equipo{//Estructura equipos
    int nro;
    char nombre[15];
};

struct Equipo equipos[32];//Vector estructura equipos. Por cada posición del vector se almacena un "Equipo"

struct Grupo{//estructura grupos
    int nroEquipo;
    int grupo;
};

struct EquiposGrupo{//Cada posicion del vector almacena un grupo
    struct Grupo equiposGrupo[4];
};

struct EquiposGrupo grupos[8];//Vector estructura grupos. Cada posicion del vector almacena un grupo

struct Partido{//Estructura partidos de fase de grupos
    int nroPartido;
    int nroEquipo1;
    int nroEquipo2;
    int golesEquipo1;
    int golesEquipo2;
};

struct Partido partidos[48];//Vector estructura partidos. Cada posicion del vector almacena datos de un partido

struct ResultadoEquipo{//Estructuras de los resultados del grupo
    int nroEquipo;
    int puntos;
    int difGoles;
};

struct ResultadoEquipo puntosEquipos[32];//vector que almacena los resultados de un grupo

struct Posicion{//estructura de cada equipo
    int nroEquipo;
    int puntos;
    int difGoles;
};

struct PosicionGrupo{// estructura que almacena el grupo posicionado por puntos
    struct Posicion posicionEquipo[4];
};

struct PosicionGrupo posicionesGrupos[8];//Vector que almacena los grupos posicionados por puntos

//---PROTOTIPOS DE FUNCIONES---
void mostrarMenu();
void leerEquipos();
void mostrarEquipos();
void sortearGrupos();
void guardarGrupos();
void leerGrupos();
void mostrarGrupos();
void calcularPartidos();
void partidosDeUnGrupo(int grupo);
void guardarPartidos();
void leerPartidos();
void mostrarPartidos();
void resetearPartidos();
void cargarResultados();
void guardarResultados();
void leerResultados();
void resetearPuntos();
void calcularPuntos();
void guardarPuntos();
void leerPuntos();
void armarGrupos();
void posicionarGrupos();
void mostrarPosicionesPrimeraFase();
void modificarBanderaPartidosJugados(int estado);
bool leerBanderaPartidosJugados();

int main()//---INICIO PROGRAMA---
{
    int opcionMenu; //Variable que lee la opcion ingresada por el usuario respecto al menú

    leerEquipos(); //Cargo los equipos. Debe estar el vector "equipos" lleno(con los 32 equipos del archivo) antes de entrar al programa

    do
    {
        mostrarMenu();

        scanf("%d", &opcionMenu);
        fflush(stdin);

        switch (opcionMenu)
        {
            case 1: system("cls"); mostrarEquipos(); break;
            case 2: system("cls"); sortearGrupos();guardarGrupos();resetearPartidos();calcularPartidos();guardarPartidos();
                    printf(" ======================================================================================\n");
                    printf("|                                                                                      |\n");
                    printf("|                      *SORTEO REALIZADO EXITOSAMENTE - QATAR 2022*                    |\n");
                    printf("|                                                                                      |\n");
                    printf(" ======================================================================================\n\n");system("pause"); break;
            case 3: system("cls");leerGrupos();mostrarGrupos();system("pause"); break;
            case 4: system("cls");leerPartidos();mostrarPartidos();system("pause");break;
            case 5: system("cls");leerPartidos();cargarResultados();system("pause"); break;
            case 6: system("cls");leerGrupos();leerPuntos();armarGrupos();posicionarGrupos();mostrarPosicionesPrimeraFase();system("pause"); break;
            case 7: printf(" ==========================================================================================\n");
                    printf("|                                                                                          |\n");
                    printf("|                       *EL FIXTURE SE CERRO CORRECTAMENTE - QATAR 2022*                   |\n");
                    printf("|                                                                                          |\n");
                    printf(" ==========================================================================================\n\n");exit(1);
        }
    } while (opcionMenu != 7);

    return 0;
}

void mostrarMenu()//funcion del menu principal al que se llama siempre que terminamos alguna tarea.
{
    system("cls");
    printf("\n  =================================== MENU PRINCIPAL ======================================\n");
    printf(" |  1- Mostrar equipos participantes.                                                      |\n");
    printf(" |  2- Realizar sorteo.                                                                    |\n");
    printf(" |  3- Mostrar grupos.                                                                     |\n");
    printf(" |  4- Mostrar partidos fase de grupos.                                                    |\n");
    printf(" |  5- Cargar resultados fase de grupos.                                                   |\n");
    printf(" |  6- Mostrar posiciones primera fase.                                                    |\n");
    printf(" |  7- Salir.                                                                              |\n");
    printf("  =========================================================================================\n");
    printf("\n\n  Opcion: ");
}

void leerEquipos()//Función que lee los equipos del archivo equipos.txt y guarda en el vector estructura de nombre "equipos".
{
    FILE*archivo;
    archivo = fopen("equipos.txt", "r");
    int i=0;
    while(!feof(archivo))//lee el archivo hasta el final
    {
        fscanf(archivo,"%d", &equipos[i].nro);//lee el nro de equipo
        fflush(stdin);
        fgets(equipos[i].nombre,15,archivo);//lee el nombre del equipo
        i++;
    };
    fclose(archivo);

}


void mostrarEquipos()//función que imprime los equipos participantes en pantalla.
{
        printf(" ======================================================================================\n");
        printf("|                                                                                      |\n");
        printf("|                          *SELECCIONES MUNDIAL - QATAR 2022*                          |\n");
        printf("|                                                                                      |\n");
        printf(" ======================================================================================\n\n");
            printf("Nro -  EQUIPOS:\n\n");
        for(int i=0 ;i<32;i++)
        {
            printf(" %d -   %s\n",equipos[i].nro ,equipos[i].nombre);

        }
        system("pause");
}


int repetidos[32];
bool nroRepetido(int indice)//funcion para controlar que no se repitan los numeros del sorteo.
{
    if (repetidos[indice])
        return true;
    else
    {
        repetidos[indice] = 1;
        return false;
    }
}

void sortearGrupos()//funcion que realiza el sorteo de forma aleatoria segun el reloj de nuestra pc.
{
    for (int z=0; z<32;z++)
        repetidos[z] = 0;

    int numRandom, base = 0;//base es la variable que vamos a usar para cambiar de bombo en el sorteo
    srand(time(0));
    for(int i=0;i<8;i++)//bucle que itera los grupos
    {
        for(int j=0;j<4;j++)//bucle que itera los equipos para un grupo
        {
            numRandom = rand() %8 + base;
            if(nroRepetido(numRandom))//si un quipo esta repetido, restarle uno a j y hacer un continue
            {
                j--;
                continue;
            }
            else
                {
                    grupos[i].equiposGrupo[j].nroEquipo = equipos[numRandom].nro;
                    grupos[i].equiposGrupo[j].grupo = i;
                }
                base +=8;
        }
        base = 0;
    }
}

void guardarGrupos()//funcion que guarda los grupos armados en el archivo grupos.txt despues del sorteo.
{
    FILE*archivo;
    archivo = fopen("grupos.txt","w");
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<4;j++)
        {
            fprintf(archivo,"%d %d\n",grupos[i].equiposGrupo[j].nroEquipo, grupos[i].equiposGrupo[j].grupo);
        }
    }
    fclose(archivo);
}

void leerGrupos()//funcion que lee los datos guardado en el archivo grupos.txt
{
    FILE*archivo;
    archivo = fopen("grupos.txt", "r");
    int residual;
    for (int i=0;i<8;i++)
    {
        for (int j=0;j<4;j++)
        {
            fscanf(archivo,"%d %d",&grupos[i].equiposGrupo[j].nroEquipo,&residual );
            fflush(stdin);
        }
    }
    fclose(archivo);
}

void mostrarGrupos()//funcion que imprime los grupos en pantalla.
{

    int j=0,i=0;
    char A=65;
    printf(" ======================================================================================\n");
    printf("|                                                                                      |\n");
    printf("|                       *COMPOSICION DE LOS GRUPOS - QATAR 2022*                       |\n");
    printf("|                                                                                      |\n");
    printf(" ======================================================================================\n\n");

     for(i=0;i<8;i++)
    {
        printf("GRUPO %c:\n",A);
        A=A+1;

        for(j=0;j<4;j++)
        {
            printf("    %s\n",equipos[(grupos[i].equiposGrupo[j].nroEquipo)-1].nombre);
        }
    }
}

int contadorPartido = 0;//variable global usada para el numero de partido en partidosDeUnGrupo()

void calcularPartidos()//funcion que calcula los partidos de los grupos.
{
    contadorPartido = 0;
    for (int i=0; i<8;i++)//for para iterar los grupos
    {
        partidosDeUnGrupo(i);
    }
}

void partidosDeUnGrupo(int grupo)//funcion que calcula los partidos de los grupos.
{
    //partido 1 del grupo, 1vs2
    partidos[contadorPartido].nroPartido = contadorPartido +1;
    partidos[contadorPartido].nroEquipo1 = grupos[grupo].equiposGrupo[0].nroEquipo;
    partidos[contadorPartido].nroEquipo2 = grupos[grupo].equiposGrupo[1].nroEquipo;
    contadorPartido++;
    //partido 2 del grupo, 3vs4
    partidos[contadorPartido].nroPartido = contadorPartido +1;
    partidos[contadorPartido].nroEquipo1 = grupos[grupo].equiposGrupo[2].nroEquipo;
    partidos[contadorPartido].nroEquipo2 = grupos[grupo].equiposGrupo[3].nroEquipo;
    contadorPartido++;
    //partido 3 del grupo, 1vs3
    partidos[contadorPartido].nroPartido = contadorPartido +1;
    partidos[contadorPartido].nroEquipo1 = grupos[grupo].equiposGrupo[0].nroEquipo;
    partidos[contadorPartido].nroEquipo2 = grupos[grupo].equiposGrupo[2].nroEquipo;
    contadorPartido++;
    //partido 4 del grupo, 2vs4
    partidos[contadorPartido].nroPartido = contadorPartido +1;
    partidos[contadorPartido].nroEquipo1 = grupos[grupo].equiposGrupo[1].nroEquipo;
    partidos[contadorPartido].nroEquipo2 = grupos[grupo].equiposGrupo[3].nroEquipo;
    contadorPartido++;
    //partido 5 del grupo, 1vs4
    partidos[contadorPartido].nroPartido = contadorPartido +1;
    partidos[contadorPartido].nroEquipo1 = grupos[grupo].equiposGrupo[0].nroEquipo;
    partidos[contadorPartido].nroEquipo2 = grupos[grupo].equiposGrupo[3].nroEquipo;
    contadorPartido++;
    //partido 6 del grupo, 2vs3
    partidos[contadorPartido].nroPartido = contadorPartido +1;
    partidos[contadorPartido].nroEquipo1 = grupos[grupo].equiposGrupo[1].nroEquipo;
    partidos[contadorPartido].nroEquipo2 = grupos[grupo].equiposGrupo[2].nroEquipo;
    contadorPartido++;
}

void guardarPartidos()//funcion que guarda los calcula los 48 partidos, en un archivo partidos.txt.
{
    FILE*archivo;
    archivo = fopen("partidos.txt", "w");
    for (int i=0; i<48; i++)
    {
        fprintf(archivo,"%d %d %d\n",partidos[i].nroPartido, partidos[i].nroEquipo1, partidos[i].nroEquipo2);
    }
    fclose(archivo);
}

void leerPartidos()//funcion que lee los partidos guardado en el archivo partidos.txt.
{

    FILE*archivo;
    archivo = fopen("partidos.txt", "r");
    for (int i=0;i<48;i++)//lee el archivo hasta el final
    {
        fscanf(archivo,"%d %d %d",&partidos[i].nroPartido,&partidos[i].nroEquipo1,&partidos[i].nroEquipo2);
        fflush(stdin);
    }
    fclose(archivo);
}


void mostrarPartidos()//funcion que imprime en pantalla los partidos en fase de grupos.
{
    int i=0;
    printf(" ======================================================================================\n");
    printf("|                                                                                      |\n");
    printf("|                       *PARTIDOS DE FASE DE GRUPOS - QATAR 2022*                      |\n");
    printf("|                                                                                      |\n");
    printf(" ======================================================================================\n\n");

    if (leerBanderaPartidosJugados())
    {
        leerResultados();
        for(i=0;i<48;i++)
            printf("Partido %d: %s %d vs %d       %s\n",partidos[i].nroPartido,equipos[(partidos[i].nroEquipo1)-1].nombre,partidos[i].golesEquipo1,partidos[i].golesEquipo2,equipos[(partidos[i].nroEquipo2)-1].nombre);
    }
    else
        for(i=0;i<48;i++)
        {
            printf("Partido %d: %s vs       %s\n",partidos[i].nroPartido,equipos[(partidos[i].nroEquipo1)-1].nombre,equipos[(partidos[i].nroEquipo2)-1].nombre);
        }
}
void resetearPartidos()
{
    for(int i=0;i<48;i++)
    {
        partidos[i].nroPartido = 0;
        partidos[i].nroEquipo1 = 0;
        partidos[i].nroEquipo2 = 0;
        partidos[i].golesEquipo1 = 0;
        partidos[i].golesEquipo2 = 0;
    }
    modificarBanderaPartidosJugados(0);

    guardarPartidos();
    guardarResultados();

    //resetea los puntos en el txt
    FILE*archivo;
    archivo = fopen("tablaPartidos.txt", "w");
    for (int i=0; i<32; i++)
    {
        fprintf(archivo,"%d %d %d\n",i+1,0,0);
    }
    fclose(archivo);
}

void moverCursor(int x,int y)//función de posicionamiento del cursor
{
	COORD p;// Definir la variable de estructura p
	HANDLE handle=GetStdHandle(STD_OUTPUT_HANDLE);// Obtener el identificador de función actual
	p.X=x;p.Y=y;// Transfiere la posición de movimiento objetivo del cursor a la estructura
	SetConsoleCursorPosition(handle,p);// Mueve el cursor
}

void cargarResultados()//funcion para ingresar por teclado los goles de los partidos.
{
    char condicion;
    int x=9;
    printf(" ======================================================================================\n");
    printf("|                                                                                      |\n");
    printf("|                      *CARGAR RESULTADOS PARTIDOS - QATAR 2022*                       |\n");
    printf("|                                                                                      |\n");
    printf(" ======================================================================================\n\n");

    printf("**SI LOS GOLES YA FUERON CARGADOS, LOS DATOS SE PERDERAN, DESEAS CONTINUAR???** (Y/N): ");
    scanf("%c", &condicion);
    fflush(stdin);
    switch (condicion)
        {
            case 'y':
                    for(int i=0;i<48;i++)
                    {
                        printf("\nPartido %d:   %s vs      %s",partidos[i].nroPartido,equipos[(partidos[i].nroEquipo1)-1].nombre,equipos[(partidos[i].nroEquipo2)-1].nombre);
                        printf("\nGOLES:          ");
                        scanf("%d",&partidos[i].golesEquipo1);
                        moverCursor(38,x);
                        scanf("%d",&partidos[i].golesEquipo2);
                        fflush(stdin);
                        x=x+3;
                    }
                    modificarBanderaPartidosJugados(1);
                    guardarResultados();leerResultados();resetearPuntos();calcularPuntos();guardarPuntos();
                    break;
            case 'Y':
                    for(int i=0;i<48;i++)
                    {
                        printf("\nPartido %d:   %s vs      %s",partidos[i].nroPartido,equipos[(partidos[i].nroEquipo1)-1].nombre,equipos[(partidos[i].nroEquipo2)-1].nombre);
                        printf("\nGOLES:          ");
                        scanf("%d",&partidos[i].golesEquipo1);
                        moverCursor(38,x);
                        scanf("%d",&partidos[i].golesEquipo2);
                        fflush(stdin);
                        x=x+3;
                    }
                    modificarBanderaPartidosJugados(1);
                    guardarResultados();leerResultados();resetearPuntos();calcularPuntos();guardarPuntos();
                    break;
            case 'n':
                    break;
            case 'N':
                    break;
            default:
                printf("\n*LA OPCION INGRESADA ES INCERRECTA*\n");;break;
        }
}

void guardarResultados()//funcion para guardar los goles en el archivo partidosJugados.txt.
{
    FILE*archivo;
    archivo = fopen("partidosJugados.txt", "w");
    for (int i=0; i<48; i++)
    {
        fprintf(archivo,"%d %d %d %d %d\n",partidos[i].nroPartido, partidos[i].nroEquipo1, partidos[i].nroEquipo2,partidos[i].golesEquipo1,partidos[i].golesEquipo2);
    }
    fclose(archivo);
}

void leerResultados()//funcion para leer los goles guardados en el archivo partidosJugados.txt.
{

    FILE*archivo;
    archivo = fopen("partidosJugados.txt", "r");
    for (int i=0;i<48;i++)//lee el archivo hasta el final
    {
        fscanf(archivo,"%d %d %d %d %d",&partidos[i].nroPartido,&partidos[i].nroEquipo1,&partidos[i].nroEquipo2,&partidos[i].golesEquipo1,&partidos[i].golesEquipo2);
        fflush(stdin);
    }
    fclose(archivo);
}

void resetearPuntos()
{

    for (int i=0; i<48;i++)
    {
        puntosEquipos[(partidos[i].nroEquipo1)-1].puntos = 0;
        puntosEquipos[(partidos[i].nroEquipo2)-1].puntos = 0;
        puntosEquipos[(partidos[i].nroEquipo1)-1].difGoles = 0;
        puntosEquipos[(partidos[i].nroEquipo2)-1].difGoles = 0;
    }
}


void calcularPuntos()//funcion para calcular los puntos de cada equipo.
{
    for (int i=0; i<48; i++)
    {
       if (partidos[i].golesEquipo1 > partidos[i].golesEquipo2)
        {
            puntosEquipos[(partidos[i].nroEquipo1)-1].puntos +=3;  // indice
            puntosEquipos[(partidos[i].nroEquipo1)-1].difGoles += partidos[i].golesEquipo1 - partidos[i].golesEquipo2;
            puntosEquipos[(partidos[i].nroEquipo2)-1].difGoles += partidos[i].golesEquipo2 - partidos[i].golesEquipo1;
        }
       else
            if (partidos[i].golesEquipo1 < partidos[i].golesEquipo2)
            {
                puntosEquipos[(partidos[i].nroEquipo2)-1].puntos +=3;  // indice
                puntosEquipos[(partidos[i].nroEquipo2)-1].difGoles += partidos[i].golesEquipo2 - partidos[i].golesEquipo1;
                puntosEquipos[(partidos[i].nroEquipo1)-1].difGoles += partidos[i].golesEquipo1 - partidos[i].golesEquipo2;
            }
            else//empate
            {
                puntosEquipos[(partidos[i].nroEquipo1)-1].puntos +=1;
                puntosEquipos[(partidos[i].nroEquipo2)-1].puntos +=1;
            }
    }
}

void guardarPuntos()//funcion para guardar los puntos en el archivo tablaPartidos.txt.
{
    FILE*archivo;
    archivo = fopen("tablaPartidos.txt", "w");
    for (int i=0; i<32; i++)
    {
        fprintf(archivo,"%d %d %d\n",i+1,puntosEquipos[i].puntos,puntosEquipos[i].difGoles);
    }
    fclose(archivo);
}

void leerPuntos()//funcion para leer los puntos guardados en el archivo tablaPartidos.txt.
{
    FILE*archivo;
    archivo = fopen("tablaPartidos.txt", "r");
    for (int i=0;i<32;i++)//lee el archivo hasta el final
    {
        fscanf(archivo,"%d %d %d",&puntosEquipos[i].nroEquipo,&puntosEquipos[i].puntos,&puntosEquipos[i].difGoles);
        fflush(stdin);
    }
    fclose(archivo);
}

void armarGrupos()//funcion para armar los grupos con sus puntos y diferencias de goles.
{
    int nroEquipoTemp;
    for (int i=0; i<8;i++)
        for (int j=0; j<4;j++)
        {
            nroEquipoTemp = grupos[i].equiposGrupo[j].nroEquipo;
            posicionesGrupos[i].posicionEquipo[j].nroEquipo = nroEquipoTemp;
            posicionesGrupos[i].posicionEquipo[j].puntos = puntosEquipos[nroEquipoTemp-1].puntos;
            posicionesGrupos[i].posicionEquipo[j].difGoles = puntosEquipos[nroEquipoTemp-1].difGoles;
        }
}

void posicionarGrupos()//funcion para ordenar los grupos segun sus puntos y diferencias de goles.
{
    int aux1, aux2, aux3;
    for (int i=0; i<8;i++)
        for (int x=0; x<3;x++)
            for (int j=0; j<(3-x);j++)
            {
                if (posicionesGrupos[i].posicionEquipo[j].puntos < posicionesGrupos[i].posicionEquipo[j+1].puntos)
                {
                    aux1 = posicionesGrupos[i].posicionEquipo[j].nroEquipo;
                    aux2 = posicionesGrupos[i].posicionEquipo[j].puntos;
                    aux3 = posicionesGrupos[i].posicionEquipo[j].difGoles;
                    posicionesGrupos[i].posicionEquipo[j].nroEquipo = posicionesGrupos[i].posicionEquipo[j+1].nroEquipo;
                    posicionesGrupos[i].posicionEquipo[j].puntos = posicionesGrupos[i].posicionEquipo[j+1].puntos;
                    posicionesGrupos[i].posicionEquipo[j].difGoles = posicionesGrupos[i].posicionEquipo[j+1].difGoles;
                    posicionesGrupos[i].posicionEquipo[j+1].nroEquipo = aux1;
                    posicionesGrupos[i].posicionEquipo[j+1].puntos = aux2;
                    posicionesGrupos[i].posicionEquipo[j+1].difGoles = aux3;
                }
                else
                {
                    if (posicionesGrupos[i].posicionEquipo[j].puntos == posicionesGrupos[i].posicionEquipo[j+1].puntos)
                    {
                         if (posicionesGrupos[i].posicionEquipo[j].difGoles < posicionesGrupos[i].posicionEquipo[j+1].difGoles)
                            {
                                aux1 = posicionesGrupos[i].posicionEquipo[j].nroEquipo;
                                aux3 = posicionesGrupos[i].posicionEquipo[j].difGoles;
                                posicionesGrupos[i].posicionEquipo[j].nroEquipo = posicionesGrupos[i].posicionEquipo[j+1].nroEquipo;
                                posicionesGrupos[i].posicionEquipo[j].difGoles = posicionesGrupos[i].posicionEquipo[j+1].difGoles;
                                posicionesGrupos[i].posicionEquipo[j+1].nroEquipo = aux1;
                                posicionesGrupos[i].posicionEquipo[j+1].difGoles = aux3;
                            }
                    }
                }
            }
}

void mostrarPosicionesPrimeraFase()//funcion para imprimir en pantalla las posiciones de primera fase.
{
    int j=0,i=0;
    char A=65;
    printf(" ======================================================================================\n");
    printf("|                                                                                      |\n");
    printf("|                         *POSICIONES PRIMERA FASE - QATAR 2022*                       |\n");
    printf("|                                                                                      |\n");
    printf(" ======================================================================================\n\n");

    for(i=0;i<8;i++)
    {
        printf("\nPOSICION GRUPO %c\n",A);
        printf("   EQUIPO            PTS    DG \n");
        A=A+1;

        for(j=0;j<4;j++)
        {
            printf("%d- %s      %d    %d\n",j+1,equipos[(posicionesGrupos[i].posicionEquipo[j].nroEquipo)-1].nombre,
            posicionesGrupos[i].posicionEquipo[j].puntos,
            posicionesGrupos[i].posicionEquipo[j].difGoles);
        }
    }
}

void modificarBanderaPartidosJugados(estado) // funcion para guardar un estado si se cargaron o no los resultados para mostrarlos con o sin los goles
{
    FILE*archivo;
    archivo = fopen("banderaPartidosJugados.txt", "w");
    fprintf(archivo,"%d\n",estado);
    fclose(archivo);
}

bool leerBanderaPartidosJugados() //funcion que lee un estado si se cargaron o no los resultados
{
    int estado;
    FILE*archivo;
    archivo = fopen("banderaPartidosJugados.txt", "r");
    fscanf(archivo,"%d",&estado);
    fflush(stdin);
    fclose(archivo);

    if (estado)
        return true;
    else
        return false;
}
