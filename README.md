# Programa de Hilos Sincronizados

Programa en C que crea 4 hilos, cada uno realizando una operación matemática diferente.

## Hilos

| Hilo | Operación | Descripción |
|------|-----------|-------------|
| 1 | Acumulado | Suma de 1 hasta n |
| 2 | Factorial | Productoria n! |
| 3 | Potencias | 2^0, 2^1, ... 2^n |
| 4 | Fibonacci | Primeros n números |

## Compilar

```bash
gcc -o hilos_sync hilos_sync.c -lpthread
```

## Ejecutar

```bash
./hilos_sync
```

## Ver árbol de procesos

Para ver el árbol con el proceso padre y sus 4 hilos:

```bash
pstree -p <PID>
```

El PID se muestra al inicio del programa.

## Ejemplo de salida

```
============================================
   PROGRAMA DE HILOS SINCRONIZADOS
============================================
PID del proceso principal: 12345

Para ver el árbol de procesos ejecute:
  pstree -p 12345
============================================

Ingrese un número (n): 4

[Hilo 1 - Acumulado] Calculando suma de 1 hasta 4:
  Paso 1: suma = 1
  Paso 2: suma = 3
  Paso 3: suma = 6
  Paso 4: suma = 10
  Resultado final: 10

[Hilo 2 - Factorial] Calculando 4!:
  Paso 1: factorial = 1
  Paso 2: factorial = 2
  Paso 3: factorial = 6
  Paso 4: factorial = 24
  Resultado final: 24

[Hilo 3 - Potencias de 2] Calculando 2^0 hasta 2^4:
  2^0 = 1
  2^1 = 2
  2^2 = 4
  2^3 = 8
  2^4 = 16

[Hilo 4 - Fibonacci] Primeros 4 números de Fibonacci:
  F(0) = 0
  F(1) = 1
  F(2) = 1
  F(3) = 2

============================================
Todos los hilos han terminado.
============================================
```

## Sincronización

- **pthread_mutex_t**: Evita que los hilos mezclen su salida en consola
- **pthread_join**: El hilo principal espera a que terminen los 4 hilos
