import os
import time

def proceso(pid):
    print("\t"* pid, end="")
    print(f"<PID={os.getpid()}, i={i}>")
    i+=1
    time.sleep(1)

def main(N):
    for i in range(1, N+1):
        pid = os.fork()
        match pid:
            case -1:
                print("Error al crear el proceso")
                os._exit(1)
            case 0:
                proceso(i)
                os._exit(0)
            case _:
                pass
if __name__ == "__main__":
    N = 3
    main(N)
