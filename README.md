# Tankoop 

### Game Description

Tankoop is a simple arcade game that is created using the QT Application Framework.

The player controls a single tank in a 2D arena, where the tank can be level up by eliminating the surrounding blocks and enemy tanks by firing bullets from their tank.

The goal of the game is to survive as many waves as possible. The player gets stronger every time it destroys an enemy tank or a block. 
The player will then obtain a skill point to upgrade one of its attributes once the tank level up. 
When the player reached level 5, it can choose to become one of the following four types (Giant, Assassin, Sharpshooter, Engineer). 
The tank can further evolve once more when it reaches level 10. 
The player is given the choice of selecting 2 different sub-tanks based on the type of tank they chose. 
Each sub-tank has its unique skill and its skill activation and cooldown timer. 
The wave, on the other hand, will get harder as the game progresses. 
The first wave will start with three enemy and the total number of enemies will increase by 1 for the next wave. 
For every 5 waves, a boss enemy will be spawned, with increased stats and size. 


### How To Play

#### Basic Controls
The player can move the tank around the map by pressing **"WASD"** where **'W'** will move the tank up, **'S'** will move the tank down, **'A'** will move the tank to the left and
**'S'** will move the tank to the right. The screen will always be center on the tank. In addition, the tank is able to fire out a bullet by pressing **'SPACEBAR'**. The player 
can adjust the direction where the bullet is fire by changing the cursor position. After reaching level 10, the player can activate the skill of the subtank by 
pressing the **"Q"** button. 

#### Initial Stats for player 
Stats | Value 
--- | --- 
Max Health | 300
Health | 300
Health Regen | 1
Bullet Damage | 50
Movement Speed | 10
Reload Speed | 0.8
Bullet Speed | 0.6 
   
**Note that Bullet Speed is how fast the bullet travels and Reload Speed is the time interval between a new bullet is created.
   
##### Game Mechanics
The game ends when the player's health reaches 0.

A new wave is started whenever the player destroys all the enemy tanks in the current wave. As stated above, each wave gets harder as more enemies will be spawned with a boss
enemy being spawned for every 5 waves.

For every block destroyed by the player using a bullet, the player will gain the full experience point of the block. Otherwise, if the player hit one of the blocks when 
it is moving, the player will only gain 70% of the total exp of the block and get 7 health deducted from its max health. 
For every enemy destroyed by the player, the player will gain the full experience point of the enemy. The player doesn't take collision damage if it hits an enemy.

The player will level up for every additional 100 xp gain.

After reaching level 5, the player can select one of the following four type -- (Giant, Sharpshooter, Assassin, Engineer) for its tank. For the type selected by the player, 
all of the current tank's stats will be multiply by different multipliers based on the type they choose. For example, Giant will get more health regen and more health while 
sharpshooter will get more bullet damage but increased reload speed.

After reaching level 10, the player can further evolved the tank by selecting a sub-tank class for it. There are in total of 8 different sub-tank classes. Every skill has a cooldown
time of 6 seconds. During the active duration the tank's skill, the tank has additional features during the active duration. The brief description is listed below.

Sub-Tank | Previous Tank Type | Skill Description| Active Duration (seconds)
--- | --- | --- | --- 
Spinner | Giant | Constantly dealing damage to enemy when the tank collides with the enemy | 4
Pounder | Giant | Change into a special kind of mode where the 4 bullets are being fired in 4 different directions | 5
Sniper | Sharpshooter | Drastically increase the bullet's damage and the travelling speed| 3
Dual | Sharpshooter | Change into a special kind of mode where 3 bullets are being fired in the same direction | 4
Hunter | Assassin | Increase every stats of the tank | 5
Immune | Assassin | Remove collision damage with block and increase tank's movement speed and health regen | 3
Spawner | Engineer | A static turret is spawn which will target the nearest enemy or block, giving the tank exp when the block/enemy is destroyed  | 4
Trapper | Engineer | A wall is created on the map, where the enemy's bullet cannot pass throught the wall without destroying the wall first | N/A








