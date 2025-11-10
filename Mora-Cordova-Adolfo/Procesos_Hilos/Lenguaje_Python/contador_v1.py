import threading
import time
import random
import os
import fcntl  

archivo = "contador.txt"


def init_file():
  
    if not os.path.exists(archivo):
        with open(archivo, "w") as f:
            f.write("0\n")


def leer_contador(pid):

    while True:
        
        with open(archivo, "r+") as f:
            
            fcntl.flock(f, fcntl.LOCK_EX)

            contenido = f.read().strip() or "0"
            valor = int(contenido)
            print(f"[T{pid}] R={valor}")

            valor += 1

            f.seek(0)
            f.truncate()
            f.write(f"{valor}\n")
            f.flush()
            print(f"[T{pid}] W={valor}")

            fcntl.flock(f, fcntl.LOCK_UN)

        time.sleep(random.random() / 5)


if __name__ == "__main__":
    
    init_file()

    t1 = threading.Thread(target=leer_contador, args=(1,))
    t2 = threading.Thread(target=leer_contador, args=(2,))

    t1.start()
    t2.start()

    t1.join()
    t2.join()

