# Zappy: A tribute to *Zaphod Beeblebrox* ⚡

> *“No clash royale here…”*

## Project Description

The goal of this project is to create a network game where several teams confront each other on a tile map containing resources.  
The winning team is the first one where at least 6 players reach the maximum elevation. (more on that later).

This project has to be carried out in groups of **4-6 people**. The project is **split** in **three parts**, each being a separate executable:

- **zappy_server**
- **zappy_gui**
- **zappy_ai**

The world (called ***Trantor***) is a M x N 2D rectangular set of flat tiles on which players or resources can be inside of. If a player goes off the map, it will end up on the opposite side.

The goal of zappy is to be the player who reaches the maximum elevation level (8) before all others.

To do this, the AIs will need to gather resources that spawn at the beginning and throughout the simulation and consume them in a ritual that upgrades their statistics and abilities to interact with the world. Those resources are stones, considered food for the AIs that allow them to survive for more cycles (or time units).

### List of existing stones

- linemate
- deraumere
- sibur
- mendiane
- phiras
- thystame

The server spawns resources upon starting and every 20 time units.

**The game follows this set of rules:**

- on Trantor you must find at least one of each resource and food on the floor.
- resources should be evenly spread across the map.
- the resource quantity can be found with the following formula: `map_width * map_height * density`

List of resource densities:

| item name | density |
|---|---:|
| food | 0.5 |
| linemate | 0.3 |
| deraumere | 0.15 |
| sibur | 0.1 |
| mendiane | 0.1 |
| phiras | 0.08 |
| thystame | 0.05 |

Note that this is the maximum amount of a given resource in the world. If it is 50 for food, then there should be 50 units of food on the map at each respawn.

## The NPCs

- One unit of food allows them to live for 126 time units.
- They are pacifists. They are neither violent nor aggressive.
- There can be more than one on the same tile.
- They ask the server what is around them to see; the higher their level, the further they are able to see.
- One unit of food allows them to live for 126 time units.

### Their vision

With each elevation, the vision increases by one unit in front, and one on each side of the new line.  
At the first level, the unit is defined as 1.  
In order for a player to recognize their team, the client sends the look command. The server will respond with the character string, as follows.

text
look\n
[player, object-on-tile1, ..., object-on-tileP,...]\n
```

If more than one object is located on a tile, they will all be indicated and separated by a space.  
Example for a level-1 player having two objects in tile 1:

text
look
[player, player deraumere,,]
```

### Broadcasting

The NPCs can send a message to all others through the broadcast command. It sends a message to the server, which will send the message to all clients.

**All broadcasts are anonymous.**

The other NPCs can only perceive the direction the sound is coming from and its subsequent message.

> The direction is indicated by the number of the tile affected by the sound, before arriving in the player's tile.  
> This numbering is done through attributing 1 to the tile that is located in front of the player, then through deducting the tiles that trigonomically encircle the player.  
> In the event that the broadcast is emitted from the same player receptor tile, they will receive the message coming from the 0 tile.
>
> **As the world is spherical, several trajectories are possible for the sound between the emitter and the player.**  
> **The shortest path will always be chosen.**

## The elevation ritual

This ritual, which enhances physical and mental capacities, must be done according to a particular rite. They must gather the following on the same unit of terrain:

- At least a certain number of each stones
- At least a certain number of players with the same level

The elevation begins as soon as a player initiates the incantation.

It is not necessary for the players to be on the same team; they only need to be of the same level.  
Every player in a group doing an incantation attains the higher level.  
The elevation requirement comes down to this:

| Elevation | players required | linemate | deraumere | sibur | mendiane | phiras | thystame |
|---|---:|---:|---:|---:|---:|---:|---:|
| 1 -> 2 | 1 | 1 | 0 | 0 | 0 | 0 | 0 |
| 2 -> 3 | 2 | 1 | 1 | 1 | 0 | 0 | 0 |
| 3 -> 4 | 2 | 2 | 0 | 1 | 0 | 2 | 0 |
| 4 -> 5 | 4 | 1 | 1 | 2 | 0 | 1 | 0 |
| 5 -> 6 | 4 | 1 | 2 | 1 | 3 | 0 | 0 |
| 6 -> 7 | 6 | 1 | 2 | 3 | 0 | 1 | 0 |
| 7 -> 8 | 6 | 2 | 2 | 2 | 2 | 2 | 1 |

The verification of the prerequisites for the incantation is done at the beginning and at the end of the action. If the conditions aren’t met, the ritual fails.

Each player participating in an elevation is frozen during the ritual. They can't do any other action in the meantime.

**Once the ritual succeeds, the stones are consumed and disappear.**

## Technical details

## Programs

We have to create three binaries:

- A server, written in C, C++ or Rust, that generates the inhabitants' world.

text
$> ./zappy_server --help
USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq
option description
-p port port number
-x width width of the world
-y height height of the world
-n name1 name2 ... name of the team
-c clientsNb number of initial clients per team
-f freq reciprocal of time unit for execution of actions
```

- A graphical client, written in C++, that can be used to watch what happens in the world.

text
$> USAGE: ./zappy_gui -p port -h machine
option description
-p port port number
-h machine hostname of the server
```

- A client, with no language constraint, that drives an inhabitant through orders sent to the server.

text
$> ./zappy_ai --help
USAGE: ./zappy_ai -p port -n name -h machine
option description
-p port port number
-n name name of the team
-h machine name of the machine; localhost by default
The server is executed as one single process and one single thread.
```

This project demands mastery of the topics we have encountered in our second year at [Epitech](http://epitech.eu).

This “game” strangely resembles [*Spore*](https://en.wikipedia.org/wiki/Spore_(2008_video_game)), with less gameplay mechanics of course.
