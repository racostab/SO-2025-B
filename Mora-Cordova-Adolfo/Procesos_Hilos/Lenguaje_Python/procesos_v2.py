import os
import sys 
import time

def hijo(i):

    print(f"Soy el proceso hijo {i} con PID {os.getpid()}")

def padre(i, pid_hijo):
    print(f"Soy el proceso padre {i} con PID {os.getpid()} y mi hijo tiene PID {pid_hijo}")

def main():
    hijos = []
    for i in range(1,4):
        try:
             pid  = os.fork()
        except OSError as e:
             pid = -1
        match pid:
                case -1:
                    print("Error al crear el proceso")
                    sys.exit(1)
                case 0:
                    hijo(i)
                    sys.exit(0)
                case _:
                    hijos.append(pid)
                    padre(i, pid)
    for pid in hijos:
        try :
                os.waitpid(pid, 0)  
        except ChildProcessError:
                pass

if __name__ == "__main__":
        main()
             