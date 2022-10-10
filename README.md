# Base Operative System
Este programa permite la ejecución de tareas básicas por consola. Permitiendo listar los procesos activos, eliminación mediante PID, obtención de la fecha y hora actual del SO.
Adicionalmente tiene una vista de ayuda para los comandos, permite la suma de dos enteros y muestra los días que tiene un mes pasado por parametro.

# ¿Cómo ejecutar el programa?
En la carpeta /exe de este repositorio puede encontrar el ejecutable correspondiente, sin embargo si desea realizar nuevas modificaciones,
debe compilar el código como se hace usualmente con C++ usando el comando:
```
g++ baseos.cpp -o exe/baseos
```
# Ejemplos de uso
El programa usa una estructura de comandos similar a Linux, por lo que los comandos se utilizaran de la forma:

```
baseos --function [params...]
```
## 1. Función Ayuda
![Imagen de ejecución de la función ayuda](/images/help.png)

### 2. Función Tiempo
![Imagen de ejecución de la función tiempo](/images/time.png)

### 3. Función Lista de Procesos
![Imagen de ejecución de lista de procesos](/images/processlist.png)

### 4. Función Eliminación de Proceso
![Imagen de ejecución de eliminación de proceso](/images/deleteprocess.png)

### 5. Función Suma
![Imagen de ejecución de suma](/images/addition.png)

### 6. Función Días de un Mes
![Imagen de ejecución de dias de un mes](/images/monthdays.png)
