#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <sched.h>


int rc,rc2;
int newprio = 10;
int newprio2 = 11;
pthread_attr_t attr,attr2;
struct sched_param param,param2;

// Compile with -pthread
// Create a mutex this ready to be locked!
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t n = PTHREAD_MUTEX_INITIALIZER;

int sum = 0;

void *countgold(void *param) {
    int i;
    
    //Same thread that locks the mutex must unlock it
    //Critical section is just 'sum += 1'
    //However locking and unlocking a million times
    //has significant overhead in this simple answer
    int in = (intptr_t)param;
    
    pthread_mutex_lock(&m);
    printf("LOCK\n");
    // Other threads that call lock will have to wait until we call unlock
    printf("%i \n ",in);
    int res = sum + in;
    if(in<0){
        //Es retiro
        
        if((res)<=0){
            //Retiro excede total de saldo disponible err
            printf("No se ha realizado el retiro!\n");
        }
        else{
            //Se realiza retiro.
            printf("Retiro realizado con exito!\n");
            sum = sum + in;
        }
    }
    else{
        //Es deposito
            printf("Deposito realizado con exito!\n");
            sum = sum + in;
    }
    pthread_mutex_unlock(&m);
    printf("UNLOCK \n");
    return NULL;
}

void clearScreen(){
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

int main() {
    pthread_t tid1, tid2;

    Inicio:
    printf("Ingrese deposito \n");
    int x = 0;
    scanf("%i",&x);

    printf("Ingrese retiro \n");
    int y = 0;
    scanf("%i",&y);
    y= y*-1;

    //Definir prioridades
    rc = pthread_attr_init(&attr);
    rc = pthread_attr_getschedparam(&attr,&param);
    rc = pthread_attr_setschedpolicy(&attr, SCHED_RR);
    rc = pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    param.sched_priority = newprio;
    rc = pthread_attr_setschedparam(&attr,&param);

    //Definir prioridades
    rc2 = pthread_attr_init(&attr2);
    rc2 = pthread_attr_getschedparam(&attr2,&param2);
    rc2 = pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    rc2 = pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    param2.sched_priority = newprio2;
    rc2 = pthread_attr_setschedparam(&attr2,&param2);

    pthread_create(&tid1, &attr2, countgold, (void *)(intptr_t)y);
    pthread_create(&tid2, &attr, countgold, (void *)(intptr_t)x);
    

    //Wait for both threads to finish:
    pthread_join(tid2, NULL);
    pthread_join(tid1, NULL);

    printf("Total de saldo es %d\n", sum);
    printf("%i %i\n",rc,rc2);
    preg:
    printf("Realizar nuevas transacciones S|N \n");
    char op = ' ';
    scanf("%c",&op);
    op = tolower(op);
    
    if((op == 's')){
        clearScreen();
        goto Inicio;
    }
    else if(op == 'n'){

    }
    else{
        goto preg;
    }
    return 0;
}