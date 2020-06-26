#Lesson - 03

mini project on path planning using A* search Algorithm.

It is based on 2D board for path planning. It has 6 states `Open, Obstacle, Closed, Path, Start, Finish`.

* `Open` - State of cell on board which is not explored by the Algorithm yet.
* `Obstacle` - State of cell on board which represent some non movable/replaceable object.
* `Closed` - State represent Algorithm has explored the path.
* `Path` - State represent Algorithm has chosen this cell for moving
* `Start` - Initial state of the Algorithm.
* `Finished` - Goal state of the Algorithm.

## Input to the Algorithm:
It require input in text format with 2D representation of board. Example as follows:

```
0,1,0,0,0,0,
0,1,0,0,0,0,
0,1,0,0,0,0,
0,1,0,0,0,0,
0,0,0,0,1,0,
```

## Output from the Algorithm:

```
S   /\   0   0   0   0
P   /\   0   0   0   0
P   /\   0   0   0   0
P   /\   0   P   P   P
P   P   P   P   /\   F
```

`S` - Start State,
`P` - Path chosen,
`/\`- Obstacle,
`F` - Finish,
`0` - Empty space