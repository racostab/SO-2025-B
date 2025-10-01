"""
Programa en python para crear una copia de un proceso y observar el PID del proceso padre e hijo.
Ejecución: python3 Procesos_hijos.py o python Procesos_hijos.py dependiendo la variable del sistema
Salida: Proceso padre: #ID proceso
        Proceso hijo: #ID proceso
"""


import os
import time
import sys


def hijo():
    my_pid = os.getpid()
    print(f"Proceso hijo {my_pid}")

def proceso():
    proceso =  os.fork()
    
    match proceso:
        case -1:
            print("Error al crear el proceso")
        case 0:
            hijo()
        case _:
            my_pid = os.getpid()
            print(f"Proceso padre: {my_pid}")
    
proceso()
