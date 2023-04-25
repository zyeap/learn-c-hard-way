#!/usr/bin/env bash

set -e
gcc -Wall -g heap-vs-stack-allocation.c -o heap-vs-stack

./heap-vs-stack db.dat c
./heap-vs-stack db.dat s 1 zak zak@123.com
./heap-vs-stack db.dat s 2 joe joe@123.com
./heap-vs-stack db.dat s 55 john john@321.com

echo "Get 55th record"
./heap-vs-stack db.dat g 55
echo "---"

echo "List all records"
./heap-vs-stack db.dat l
