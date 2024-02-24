#!/usr/bin/env python
import os
import subprocess


def getLib(name):
    return os.popen("pkg-config --cflags --libs " + name).read().replace("\n", "")


errors = []


def getFlag(flag_name, default_value):
    # Assuming the flags are passed as command-line arguments
    import sys

    for arg in sys.argv:
        if arg.startswith(flag_name + "="):
            # Return the value after the equals sign
            return arg[len(flag_name) + 1 :]
    # If the flag is not found, return the default value
    return default_value


def run(*args):
    print(*args)
    subprocess.run(args)


functions = {
    "__builtins__": {
        "getLib": getLib,
        "print": print,
        "run": run,
        "exit": exit,
        "getFlag": getFlag,
    }
}

with open("build.zx") as f:
    exec(f.read(), functions)
