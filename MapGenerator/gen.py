#!/usr/bin/env python

import sys
import random

def check_args(map_duration, spawn_percentage):
    if (spawn_percentage < 0 or spawn_percentage > 100):
        return False;
    if (map_duration < 60):
        return False;
    return True;

def gen_map(map_name, map_duration, spawn_percentage):
    i = 0.0;
    print(map_name);
    while i < map_duration:
        spawn = random.randint(0, 100);
        mobType = random.randint(1, 3);
        if mobType == 2:
            mobType = 1;
        if spawn < spawn_percentage:
            s = str(round(float(repr(i)), 3)) + ';0;' + str(mobType) \
            + ';1300;' + str(random.randint(20, 700))
            print(s);
        i += 0.1;

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print ("Usage: ./gen map_name map_duration spawn_percentage")
        print ("Example usage:")
        print ("$ ./gen map 300 75")
        sys.exit(0)
    else:
        if (not check_args(int(sys.argv[2]), int(sys.argv[3]))):
            print ("Map duration must be at least 60 seconds")
            print ("Spawn percentage must be between 0 and 100")
            sys.exit(1);
        gen_map(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]));
        sys.exit(0);
