# Description 
Its a survival game where the enemy is trying to find the player. The player has to use that maps turane to avoid the enemy.
If the enemy catches the player the enemy will return to its spawnpoint. 

## How To Play
- Use WASD to move the player.
- The enemy is trying to find the player.
- Run away from the enemy to survive.

## How the AI Functions 
- It uses a StateMachine
- It starts out by wandering around the map.
- Once the player enters the large range it starts to PathFind to the player.
- It will go back to wandering if the player escapes it's large range.
- Once the player enters the smaller range it seeks the player.
- It will gp back pathFinding if th eplayer escapes it's small range.

## Bugs that you might find
- The enemy will get stuck on corners.
