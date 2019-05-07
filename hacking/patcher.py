import sys
import os

print(sys.argv)

if len(sys.argv) < 2:
    print('You should write file name')
    exit()

if not os.path.isfile(sys.argv[1]):
    print("File with such name does not exist")
    exit()
