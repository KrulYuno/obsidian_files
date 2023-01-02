"""
    Source: https://github.com/KrulYuno/obsidian_files/tree/master/Codes/mp3_the_general's_daugther_-_err_-_tree
"""

import sys
from FileDescriptor import FileDescriptor
from GeneralTreeNode import (DirectoryNode, FileNode)


def main():

    root    = DirectoryNode('/') 
    cmd     = FileDescriptor(root)
    dirs    = ['bin', 'dev', 'home', 'opt', 'root', 'sbin', 'sys', 'usr',
               'boot', 'etc', 'mnt', 'proc', 'run', 'srv', 'tmp', 'var']
    for name in dirs:
        cmd.mkdir(name)

    for _ in cmd.pwd.children:
        print(_.name)

def print_help():
    print(f"{'Commands':<10}   Info")
    print(f"{'--------':<10}   ----")
    print(f"  {'gui':<10} Run as GUI.")
    print()

if __name__ == "__main__":
    """
        Will check if we run the code as GUI or CLI.
    """
    if len(sys.argv) > 1:
        match sys.argv[1]:
            case "-h" | "--help":
                print_help()
            case "--gui":
                print("gui mode")
            case "--":
                print("Missing argument after '--'.")
                sys.exit(2)

            case _:
                print(f"Invalid argument '{sys.argv[1]}'. ")
                sys.exit(1)
    else:
        main()
