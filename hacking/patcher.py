import sys
import os

print(sys.argv)

def nop_useless_code(file_addr, useless_size):
    if useless_size <= 0:
        return

    nope_str = b'\x90' * useless_size
    f = open(file_addr, "ab")
    f.write(nope_str)
    f.close()

def fix_password_check(file_addr, useful_size):
    good_asm = open('brute_asm', 'rb')
    f = open(file_addr, 'wb')
    byte = good_asm.read(useful_size)
    f.write(byte)

    good_asm.close()
    f.close()

def main():
    if len(sys.argv) < 2:
        print('You should write file name')
        exit()
    file_addr = sys.argv[1]

    if not os.path.isfile(file_addr):
        print("File with such name does not exist")
        exit()
    
    file_size = os.path.getsize(file_addr)
    print("file size", file_size)
    useful_size = os.path.getsize('brute_asm')

    fix_password_check(file_addr, useful_size)  
    nop_useless_code(file_addr, file_size - useful_size)

if __name__ == "__main__":
    main()
