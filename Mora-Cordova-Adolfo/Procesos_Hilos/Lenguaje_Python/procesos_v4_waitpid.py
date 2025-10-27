import os
import sys
import time


def hijo():
    print(f"Soy el proceso hijo con PID {os.getpid()}")
    time.sleep(2)
    os._exit(0)


def padre(pid_hijo):
    print(f"Soy el proceso padre con PID {os.getpid()}")
    pid, status = os.waitpid(pid_hijo, 0)
def main():

    try:
        pid = os.fork()
    except OSError as e:
        print(f"Error al crear el proceso: {e}")
        sys.exit(1)
    match pid:
        
        case -1:
            print("Error al crear el proceso")
            sys.exit(1)
        case 0:
            hijo()
            os._exit(0)
        case _:
             padre(pid)

if __name__ == "__main__":
    main()