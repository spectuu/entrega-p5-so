#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Mutex para sincronización de salida
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Variable global para el número a procesar
int numero;

// Hilo 1: Acumulado (suma de 1 hasta n)
void *acumulado(void *arg) {
    int suma = 0;

    pthread_mutex_lock(&mutex);
    printf("\n[Hilo 1 - Acumulado] Calculando suma de 1 hasta %d:\n", numero);
    for (int i = 1; i <= numero; i++) {
        suma += i;
        printf("  Paso %d: suma = %d\n", i, suma);
    }
    printf("  Resultado final: %d\n", suma);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Hilo 2: Productoria/Factorial
void *factorial(void *arg) {
    long long fact = 1;

    pthread_mutex_lock(&mutex);
    printf("\n[Hilo 2 - Factorial] Calculando %d!:\n", numero);
    for (int i = 1; i <= numero; i++) {
        fact *= i;
        printf("  Paso %d: factorial = %lld\n", i, fact);
    }
    printf("  Resultado final: %lld\n", fact);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Hilo 3: Potencias de 2
void *potencias_dos(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("\n[Hilo 3 - Potencias de 2] Calculando 2^0 hasta 2^%d:\n", numero);
    for (int i = 0; i <= numero; i++) {
        int potencia = 1 << i;  // 2^i usando shift
        printf("  2^%d = %d\n", i, potencia);
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

// Hilo 4: Fibonacci
void *fibonacci(void *arg) {
    pthread_mutex_lock(&mutex);
    printf("\n[Hilo 4 - Fibonacci] Primeros %d números de Fibonacci:\n", numero);

    long long a = 0, b = 1, temp;
    for (int i = 0; i < numero; i++) {
        printf("  F(%d) = %lld\n", i, a);
        temp = a + b;
        a = b;
        b = temp;
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t hilo1, hilo2, hilo3, hilo4;
    pid_t pid = getpid();

    printf("============================================\n");
    printf("   PROGRAMA DE HILOS SINCRONIZADOS\n");
    printf("============================================\n");
    printf("PID del proceso principal: %d\n", pid);
    printf("\nPara ver el árbol de procesos ejecute:\n");
    printf("  pstree -p %d\n", pid);
    printf("============================================\n");

    // Solicitar número al usuario
    printf("\nIngrese un número (n): ");
    scanf("%d", &numero);

    if (numero < 1) {
        printf("Error: El número debe ser mayor o igual a 1\n");
        return 1;
    }

    printf("\nCreando los 4 hilos...\n");

    // Crear los 4 hilos
    if (pthread_create(&hilo1, NULL, acumulado, NULL) != 0) {
        perror("Error creando hilo 1");
        return 1;
    }

    if (pthread_create(&hilo2, NULL, factorial, NULL) != 0) {
        perror("Error creando hilo 2");
        return 1;
    }

    if (pthread_create(&hilo3, NULL, potencias_dos, NULL) != 0) {
        perror("Error creando hilo 3");
        return 1;
    }

    if (pthread_create(&hilo4, NULL, fibonacci, NULL) != 0) {
        perror("Error creando hilo 4");
        return 1;
    }

    // Esperar a que todos los hilos terminen (sincronización)
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);
    pthread_join(hilo3, NULL);
    pthread_join(hilo4, NULL);

    // Destruir el mutex
    pthread_mutex_destroy(&mutex);

    printf("\n============================================\n");
    printf("Todos los hilos han terminado.\n");
    printf("============================================\n");

    return 0;
}
