# lem-in

This is project about graph theory.

## Description

This program finds the optimal path for ants from the start room to the end.

* Program will receive the data describing the ant farm from the standard outputin the following format:
```
number_of_ants
the_rooms
the_links
```
* Ant farm is defined by the following links:
```
##start
1 23 3
2 16 7
#comment
3 16 3
4 16 5
5 9 3
6 1 5
7 4 8
##end
0 9 5
0-4
0-6
1-3
4-3
5-2
3-5
#another comment
4-2
2-1
7-6
7-2
7-4
6-5
#another comment
```
* Which corresponds to the following representation:

```
              ______________
            /                \
    ______[5]----[3]----[1]   |
  /              |     /      |
[6]-----[0]----[4]   /        |
 \    _________/ | /          |
   \ /          [2]__________/
    [7]_________/
```

* Results displays on the standard output in the following format:

```
number_of_ants
the_rooms
the_links
Lx-y Lz-w Lr-o ...
```
x, z, r represents the ant’s numbers (going from 1 to number_of_ants) and y, w, o represents the room’s names.

## Getting Started

Clone repository with command ```git clone --recurse-submodules https://github.com/ergottli/lem-in.git```

Than enter command ```make``` in the root of repository.

Was compiled on MacOS Catalina 10.15.3

## Usage

```
./lem-in < ant_farm_map.txt
```

## Example

```
 ./lem-in < map.txt
 ##start
 0 1 0
 ##end
 1 5 0
 2 9 0
 3 13 0
 0-2
 2-3
 3-1
 
 L1-2
 L1-3 L2-2
 L1-1 L2-3 L3-2
 L2-1 L3-3
 L3-1
 ```
