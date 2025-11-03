#include <sys/times.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
    struct tms tms_start, tms_end;
    clock_t start_ticks, end_ticks;
    long ticks_per_second;
    long i;
    double dummy = 0.0;
    
    // Obtener la frecuencia de ticks del sistema
    if ((ticks_per_second = sysconf(_SC_CLK_TCK)) == -1) {
        perror("sysconf error");
        exit(EXIT_FAILURE);
    }
    
    // 1. Registrar el tiempo de inicio (en ticks)
    if ((start_ticks = times(&tms_start)) == (clock_t)-1) {
        perror("times error start");
        exit(EXIT_FAILURE);
    }
    
    // 2. Tarea a medir (cálculo intensivo)
    for (i = 0; i < 50000000; i++) {
        dummy = dummy + 1.0;
    }
    
    // 3. Registrar el tiempo de fin (en ticks)
    if ((end_ticks = times(&tms_end)) == (clock_t)-1) {
        perror("times error end");
        exit(EXIT_FAILURE);
    }

    // --- CÁLCULOS EN SEGUNDOS ---
    
    // Tiempo de Usuario (User time)
    double user_time_s = (double)(tms_end.tms_utime - tms_start.tms_utime) / ticks_per_second;
    
    // Tiempo de Sistema/Kernel (System time)
    double system_time_s = (double)(tms_end.tms_stime - tms_start.tms_stime) / ticks_per_second;
    
    // Tiempo Real (Wall-clock time)
    double real_time_s = (double)(end_ticks - start_ticks) / ticks_per_second;

    // --- SALIDA PARA GNUPLOT ---
    // Imprime los tres valores separados por espacio.
    // Orden: Usuario, Sistema, Real
    fprintf(stdout, "%.4f %.4f %.4f\n", user_time_s, system_time_s, real_time_s);

    return 0;
}