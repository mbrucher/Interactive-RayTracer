#!/bin/bash

valgrind --tool=callgrind --simulate-cache=yes --dump-instr=yes --collect-jumps=yes python measure_image.py
