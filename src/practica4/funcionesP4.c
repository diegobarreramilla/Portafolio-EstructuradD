#include "funcionesP4.h"


unsigned char ** crear_laberinto(void)
{
    int i,j;
    char *tmp =
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
xAx*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x**************x\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

    unsigned char **lab;
    lab = (unsigned char**) malloc(sizeof(unsigned char *)*REN);
    
    for(i=0;i<REN;i++)
        lab[i] = (unsigned char*) malloc(sizeof(unsigned char)*COL);
    
    for(i=0;i<REN;i++)
        for(j=0;j<COL;j++)
            lab[i][j] = tmp[(i*COL)+j];

    return lab;
}

void imprimirLab(unsigned char **lab)
{
    int i,j;
    for(i=0;i<REN;i++)
    {
        printf("\n\r");
        for(j=0;j<COL;j++)
        {
            if(lab[i][j]=='*') printf("  ");
            else printf("%c ",lab[i][j]);
        }   
    }
}


Coordenada* crearCoordenada(int x,int y)
{
    Coordenada *nueva = malloc(sizeof(Coordenada));
    nueva->x=x;
    nueva->y=y;
    return nueva;
}

void imprimirCoordenada(void *dato)
{
    Coordenada *a = dato;
    printf("[%-2d,%-2d]", a->x,a->y);
}

int compararCoordenada(void *a,void *b)
{
    Coordenada *aa=a,*bb=b;
    if(aa->x==bb->x && aa->y==bb->y)
        return 1;
    return 0;
}

// alternaivas
unsigned char alternativas(unsigned char **lab,Coordenada *coordenada)
{		
    unsigned char caracter;
    unsigned char banderas = 0;	

    // arriba
    caracter = lab[coordenada->x-1][coordenada->y];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        banderas |= ARRIBA;

    // Aabjo
    caracter = lab[coordenada->x+1][coordenada->y];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        banderas |= ABAJO;

    // DErecha
    caracter = lab[coordenada->x][coordenada->y+1];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        banderas |= DERECHA;

    // izquierad
    caracter = lab[coordenada->x][coordenada->y-1];
    if(caracter!='x' && caracter!='.' && caracter!='o' && caracter!='A')
        banderas |= IZQUIERDA;

    return banderas;	
}

void imprimirPosibles(unsigned char caminos)
{
    if(caminos&ARRIBA)    printf("\n ARRIBA");
    if(caminos&ABAJO)     printf("\n ABAJO");
    if(caminos&IZQUIERDA) printf("\n IZQUIERDA");
    if(caminos&DERECHA)   printf("\n DERECHA");
}

// pila
Pila* crearPila()
{
    Pila *pila = malloc(sizeof(Pila));
    pila->cima = NULL;
    return pila;
}

void push(Pila *pila, Coordenada *coord)
{
    Nodo *nuevo = malloc(sizeof(Nodo));
    nuevo->coord = coord;
    nuevo->sig = pila->cima;
    pila->cima = nuevo;
}

Coordenada* pop(Pila *pila)
{
    if(pila->cima==NULL) return NULL;
    Nodo *tmp = pila->cima;
    Coordenada *dato = tmp->coord;
    pila->cima = tmp->sig;
    free(tmp);
    return dato;
}

Coordenada* peek(Pila *pila)
{
    if(pila->cima==NULL) return NULL;
    return pila->cima->coord;
}

int pilaVacia(Pila *pila)
{
    return pila->cima==NULL;
}

////////////////////////////////////////////////////
void resolver(unsigned char **lab)
{
    int i,j;
    Coordenada *actual=NULL;
    unsigned char movs;

    // Buscar inicio A
    int ax=-1, ay=-1;
    for(i=0;i<REN;i++)
        for(j=0;j<COL;j++)
            if(lab[i][j]=='A'){
                 ax=i; ay=j; 
            }

    Pila *pila = crearPila();
    push(pila, crearCoordenada(ax,ay));

    while(!pilaVacia(pila))
    {
        actual = peek(pila);
        if(lab[actual->x][actual->y]=='B'){
            printf("\n\nsolucion: \n\n");
            break;
        }

        movs = alternativas(lab,actual);

        ///camino sin salida
        if(movs==0){ // Sin caminos
            lab[actual->x][actual->y] = 'o'; //regresar
            pop(pila);
            continue;
        }

        // mover
        if((movs&DERECHA) != 0 ){
            lab[actual->x][actual->y] = '.';
            push(pila, crearCoordenada(actual->x,actual->y+1));
        }
        else if((movs&IZQUIERDA) !=0 ){
            lab[actual->x][actual->y] = '.';
            push(pila, crearCoordenada(actual->x,actual->y-1));
        }
        else if((movs&ABAJO) !=0 ){
            lab[actual->x][actual->y] = '.';
            push(pila, crearCoordenada(actual->x+1,actual->y));
        }
        else if((movs&ARRIBA) != 0){
            lab[actual->x][actual->y] = '.';
            push(pila, crearCoordenada(actual->x-1,actual->y));
        }
    }

    
}
