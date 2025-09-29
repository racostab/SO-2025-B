import os
import sys 

def hijo():
    print(f"Soy el proceso hijo con PID {os.getpid()}")

def padre(pid_hijo):
    print(f"Soy el proceso padre con PID {os.getpid()} y mi hijo tiene PID {pid_hijo}")

def main():
    try:
        pid = os.fork()
    except OSError as e:
        pid = -1
    
    match pid:
        case -1:
            print("Error al crear el proceso")
            sys.exit(1)
        case 0:
            hijo()
            sys.exit(0)
        case _:
            padre(pid)

if __name__ == "__main__":
    main()
