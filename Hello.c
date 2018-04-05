#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <sched.h>


int rc,rc2,rc3,rc4,rc5,policy;
long newprio = 5;
long newprio2 = 4;
long newprio3 = 3;
long newprio4 = 2;
long newprio5 = 1;
pthread_attr_t attr,attr2,attr3,attr4,attr5;
struct sched_param param,param2,param3,param4,param5;
int sum = 0;

void *hello1(void *param) {
    while(1){
    printf("Hello from thread 1 \n");
    sleep(1);
    }
    return NULL;

}
void *hello2(void *param) {
    while(1){
    printf("Hello from thread 2 \n");
    sleep(1);
    }
    return NULL;
}
void *hello3(void *param) {
    while(1){
    printf("Hello from thread 3 \n");
    sleep(1);
    }
    return NULL;
}
void *hello4(void *param) {
    while(1){
    printf("Hello from thread 4 \n");
    sleep(1);
    }
    return NULL;
}
void *hello5(void *param) {
    while(1){
    printf("Hello from thread 5 \n");
    sleep(1);
    }
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
    
    //param.sched_priority = newprio;
    
    rc = pthread_attr_setschedpolicy(&attr, SCHED_RR);
    rc = pthread_attr_setschedparam(&attr,&param);
    pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
    rc = pthread_attr_getschedparam(&attr,&param);
    rc = pthread_attr_setscope(&attr,PTHREAD_SCOPE_PROCESS);
    printf("Prioridad modificada: %i \n",param.sched_priority);
    
    if(pthread_attr_getschedpolicy(&attr, &policy) != 0)
        fprintf(stderr, "Unable to get policy.\n");
    else{
        if(policy == SCHED_OTHER)
            printf("SCHED_OTHER\n");
        else if(policy == SCHED_RR)
            printf("SCHED_RR\n");
        else if(policy == SCHED_FIFO)
            printf("SCHED_FIFO\n");
    }
    
    int scop;
    if(pthread_attr_getscope(&attr,&scop) != 0)
        fprintf(stderr, "Unable to get Scope.\n");
    else{
        if(scop == PTHREAD_SCOPE_SYSTEM){
            printf("PTHREAD_SCOPE_SYSTEM\n");
        }
        else if(scop == PTHREAD_SCOPE_PROCESS){
            printf("PTHREAD_SCOPE_PROCESS\n");
        }
    }
    
    pthread_create(&tid1, &attr, hello1, NULL);
    printf("%i \n",rc);
    
    //Wait for threads to finish:
    pthread_join(tid1, NULL);
    

    return 0;
}