#include <stdio.h>
#include <pthread.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include <sched.h>


int rc,rc2,rc3,rc4,rc5;
int newprio = 21;
int newprio2 = 22;
int newprio3 = 23;
int newprio4 = 24;
int newprio5 = 25;
pthread_attr_t attr,attr2,attr3,attr4,attr5;
struct sched_param param,param2,param3,param4,param5;
int sum = 0;

void *hello1(void *param) {
    sleep(3);
    printf("Hello from thread 1 \n");
    return NULL;
}
void *hello2(void *param) {
    sleep(3);
    printf("Hello from thread 2 \n");
    return NULL;
}
void *hello3(void *param) {
    sleep(3);
    printf("Hello from thread 3 \n");
    return NULL;
}
void *hello4(void *param) {
    sleep(3);
    printf("Hello from thread 4 \n");
    return NULL;
}
void *hello5(void *param) {
    sleep(3);
    printf("Hello from thread 5 \n");
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
    param.sched_priority = newprio;
    rc = pthread_attr_setschedpolicy(&attr, SCHED_RR);
    rc = pthread_attr_setschedparam(&attr,&param);

    //Definir prioridades
    rc2 = pthread_attr_init(&attr2);
    rc2 = pthread_attr_getschedparam(&attr2,&param2);
    param2.sched_priority = newprio2;
    rc2 = pthread_attr_setschedpolicy(&attr2, SCHED_RR);
    rc2 = pthread_attr_setschedparam(&attr2,&param2);

    //Definir prioridades
    rc3 = pthread_attr_init(&attr3);
    rc3 = pthread_attr_getschedparam(&attr3,&param3);
    param3.sched_priority = newprio3;
    rc3 = pthread_attr_setschedpolicy(&attr3, SCHED_RR);
    rc3 = pthread_attr_setschedparam(&attr3,&param3);

    //Definir prioridades
    rc4 = pthread_attr_init(&attr4);
    rc4 = pthread_attr_getschedparam(&attr4,&param4);
    param4.sched_priority = newprio4;
    rc4 = pthread_attr_setschedpolicy(&attr4, SCHED_RR);
    rc4 = pthread_attr_setschedparam(&attr4,&param4);

    //Definir prioridades
    rc5 = pthread_attr_init(&attr5);
    rc5 = pthread_attr_getschedparam(&attr5,&param5);
    param5.sched_priority = newprio5;
    rc5 = pthread_attr_setschedpolicy(&attr5, SCHED_RR);
    rc5 = pthread_attr_setschedparam(&attr5,&param5);

    pthread_create(&tid1, &attr, hello1, NULL);
    pthread_create(&tid2, &attr2, hello2, NULL);
    pthread_create(&tid3, &attr3, hello3, NULL);
    pthread_create(&tid4, &attr4, hello4, NULL);
    pthread_create(&tid5, &attr5, hello5, NULL);

    
    //Wait for both threads to finish:
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);

    printf("%i %i %i %i %i \n",rc,rc2,rc3,rc4,rc5);

    return 0;
}