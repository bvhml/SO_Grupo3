#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <sched.h>


int rc,rc2,rc3,rc4,rc5;
long newprio = 10;
long newprio2 = 20;
long newprio3 = 30;
long newprio4 = 40;
long newprio5 = 99;
pthread_attr_t attr,attr2,attr3,attr4,attr5;
struct sched_param param,param2,param3,param4,param5;
int sum = 0;

void *hello1(void *param) {
   
    printf("Hello from thread 1\n");
    
    return NULL;

}
void *hello2(void *param) {
   
    printf("Hello from thread 2\n");
   
    return NULL;
}
void *hello3(void *param) {
   
    printf("Hello from thread 3\n");
  
    return NULL;
}
void *hello4(void *param) {

    printf("Hello from thread 4\n");
   
    return NULL;
}
void *hello5(void *param) {
  
    printf("Hello from thread 5\n");
   
    return NULL;
}

void clearScreen(){
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

int main() {
    pthread_t tid1, tid2, tid3, tid4, tid5;

    //Definir prioridades
    rc = pthread_attr_init(&attr);
    rc = pthread_attr_getschedparam(&attr,&param);
    printf("Prioridad original: %i \n",param.sched_priority);
    param.sched_priority = newprio;
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    rc = pthread_attr_setschedpolicy(&attr, SCHED_RR);
    rc = pthread_attr_setschedparam(&attr,&param);

    rc = pthread_attr_getschedparam(&attr,&param);
    printf("Prioridad modificada: %i \n",param.sched_priority);
    
    //Definir prioridades
    rc2 = pthread_attr_init(&attr2);
    rc2 = pthread_attr_getschedparam(&attr2,&param2);
    param2.sched_priority = newprio2;
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);
    rc2 = pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    rc2 = pthread_attr_setschedparam(&attr2,&param2);

    //Definir prioridades
    rc3 = pthread_attr_init(&attr3);
    rc3 = pthread_attr_getschedparam(&attr3,&param3);
    param3.sched_priority = newprio3;
    pthread_attr_setinheritsched(&attr3, PTHREAD_EXPLICIT_SCHED);
    rc3 = pthread_attr_setschedpolicy(&attr3, SCHED_RR);
    rc3 = pthread_attr_setschedparam(&attr3,&param3);

    //Definir prioridades
    rc4 = pthread_attr_init(&attr4);
    rc4 = pthread_attr_getschedparam(&attr4,&param4);
    param4.sched_priority = newprio4;
    pthread_attr_setinheritsched(&attr4, PTHREAD_EXPLICIT_SCHED);
    rc4 = pthread_attr_setschedpolicy(&attr4, SCHED_RR);
    rc4 = pthread_attr_setschedparam(&attr4,&param4);

    //Definir prioridades
    rc5 = pthread_attr_init(&attr5);
    rc5 = pthread_attr_getschedparam(&attr5,&param5);
    param5.sched_priority = newprio5;
    pthread_attr_setinheritsched(&attr5, PTHREAD_EXPLICIT_SCHED);
    rc5 = pthread_attr_setschedpolicy(&attr5, SCHED_RR);
    rc5 = pthread_attr_setschedparam(&attr5,&param5);

    pthread_create(&tid1, &attr, hello1, NULL);
    pthread_create(&tid2, &attr2, hello2, NULL);
    pthread_create(&tid3, &attr3, hello3, NULL);
    pthread_create(&tid4, &attr4, hello4, NULL);
    pthread_create(&tid5, &attr5, hello5, NULL);

    printf("%i %i %i %i %i \n",rc,rc2,rc3,rc4,rc5);
    
    //Wait for both threads to finish:
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);

    

    return 0;
}