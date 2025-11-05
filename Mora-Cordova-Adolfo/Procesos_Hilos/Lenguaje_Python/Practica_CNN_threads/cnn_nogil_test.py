import threading
import time
import os
from concurrent.futures import ThreadPoolExecutor

# --- Configuración de la Simulación ---
# Número de imágenes en nuestro "lote" de datos
NUM_IMAGENES = 32 
# Simulación de trabajo de CPU por imagen (operaciones)
# Aumenta esto si tienes un CPU muy rápido
TRABAJO_POR_IMAGEN = 40_000_000 

def procesar_imagen(nombre_imagen: str) -> str:
    """
    Simula una tarea pesada de CPU: cargar, decodificar y aumentar
    una imagen antes de enviarla a la CNN.
    """
    # Usamos native_id para ver el ID real del hilo del OS
    thread_id = threading.get_native_id()
    print(f"[Hilo {thread_id}] 🏃 Iniciando: {nombre_imagen}")
    
    # --- Simulación de trabajo intensivo de CPU ---
    # En Python "nogil", esta sección se ejecutará en paralelo
    # real en múltiples núcleos de CPU.
    # En Python "con GIL", los hilos se turnarán en un solo núcleo.
    cuenta = 0
    for i in range(TRABAJO_POR_IMAGEN):
        cuenta += (i % 1000) - (i % 500) # Operación matemática arbitraria
    # --- Fin del trabajo de CPU ---
    
    print(f"[Hilo {thread_id}] ✅ Terminado: {nombre_imagen}")
    return f"datos_procesados_de_{nombre_imagen}"

# --- Función Principal ---
def main():
    
    # Generamos una lista de nombres de archivo de imagen ficticios
    lote_imagenes = [f"imagen_{i}.jpg" for i in range(NUM_IMAGENES)]
    
    # Usamos la cantidad de CPUs disponibles como número de workers
    num_workers = os.cpu_count() or 4 # Default a 4 si os.cpu_count() falla
    
    print(f"--- Simulación de DataLoader para CNN ---")
    print(f"Versión de Python: 3.13 ('nogil' esperado)")
    print(f"Procesando {NUM_IMAGENES} imágenes con {num_workers} hilos (workers).")
    print(f"Trabajo simulado por imagen: {TRABAJO_POR_IMAGEN} operaciones.")
    print("---------------------------------------------")

    start_time = time.time()
    
    resultados = []
    
    # Usamos ThreadPoolExecutor para gestionar los hilos de forma eficiente.
    # Él se encarga de iniciar, gestionar y cerrar los hilos.
    with ThreadPoolExecutor(max_workers=num_workers) as executor:
        
        # 'executor.map()' aplica la función 'procesar_imagen'
        # a cada elemento de 'lote_imagenes' usando el pool de hilos.
        # Es la forma moderna y eficiente de manejar esto.
        resultados = list(executor.map(procesar_imagen, lote_imagenes))
        
    end_time = time.time()
    
    print("---------------------------------------------")
    print("--- ¡Procesamiento del Lote Completado! ---")
    print(f"Resultados obtenidos: {len(resultados)}")
    print(f"Tiempo total: {end_time - start_time:.4f} segundos.")
    print("---------------------------------------------")

    # --- Interpretación de Resultados ---
    # Calculamos el tiempo que tomaría secuencialmente (aprox.)
    start_secuencial = time.time()
    procesar_imagen("imagen_prueba_secuencial")
    tiempo_una_imagen = time.time() - start_secuencial
    
    tiempo_secuencial_total = tiempo_una_imagen * NUM_IMAGENES
    
    print("\n--- Análisis de Rendimiento (Teórico) ---")
    print(f"Tiempo de 1 imagen (secuencial): {tiempo_una_imagen:.4f} seg")
    print(f"Tiempo total (paralelo):       {end_time - start_time:.4f} seg")
    print(f"Tiempo total (secuencial est.): {tiempo_secuencial_total:.4f} seg")
    
    if (end_time - start_time) < (tiempo_secuencial_total / 2):
        print("\n🎉 ¡ÉXITO! El tiempo total es mucho menor que el secuencial.")
        print("Esto indica que el paralelismo real de CPU (nogil) está funcionando.")
    else:
        print("\n🐢 ADVERTENCIA: El tiempo total es similar al secuencial.")
        print("Esto sugiere que estás ejecutando con el GIL activado.")


if __name__ == "__main__":
    # Importante ejecutar el código dentro de esta guarda
    # si esto fuera a crecer (especialmente con multiprocessing)
    main()