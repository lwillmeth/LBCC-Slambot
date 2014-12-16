"""
An early draft of creating and visualizing walls for the LBCC Slambot system.
"""
import pygame, sys, random, math
from pygame.locals import *


class Map:
    """ Base class for all maps. """

    def __init__(self, precision=5):
        """ Constructor for Map class """
        # Defaults to precision to resolution of 5 cm.
        self.precision = precision
        # Floating point values holds bot position on map
        self.posX, self.posY = 0.0, 0.0
        # Dictionary of key:value pairs holds {(x,y):confidence} of walls
        self.walls = {}

    def find_wall(self, dist, angle):
        """ Adds a wall using distance and angle of the turret. """
        self.make_wall(dist*math.sin(angle), dist*math.cos(angle))

    def make_wall(self, x, y):
        """ Adds, or increments a map point. """
        # Bot position is a float but we want to store wall positions as
        # integers to save space, so we round and truncate combined position.
        x = int(round(self.posX+x))
        y = int(round(self.posY+y))
        # Increment existing wall position, or start a new wall segment
        if (x, y) in self.walls:
            self.walls[(x, y)] += 1
        else:
            self.walls[(x, y)] = 1

    def move_bot(self, x, y):
        """ Move the bot relative to it's current position on the map. """
        self.posX += x
        self.posY += y

    def set_bot(self, x, y):
        """ Move the bot to a specific position on the map. """
        self.posX = x
        self.posY = y

if __name__ == "__main__":
    pygame.display.init()
    # For some reason, using pygame.init() alone causes program to hang.
    # Could not find a better solution than initializing display by itself.
    screen = pygame.display.set_mode((500, 500))
    screen.fill((255, 255, 255))  # white background

    localMap = Map()
    botPos = [0, 0]

    # Add some randomized walls to the model
    for i in range(100):
        if i % 2 == 0:
            localMap.make_wall(random.choice([100, 400]), random.randrange(100, 400))
        else:
            localMap.make_wall(random.randrange(100, 400), random.choice([100, 400]))

    # Draw walls on a pygame map.
    for spot in localMap.walls:
        # Walls get darker as they are seen more often
        color = min(abs(255-localMap.walls[spot]*55), 255)
        # Syntax is: screen, color, (x, y, width, height), thickness
        pygame.draw.rect(screen, (color, color, color),
                         spot+(localMap.precision, localMap.precision), 0)
        # Original design used a local botPos
        # [a+b for a, b in zip(botPos, spot)]+[5, 5]

    # Redraw map using newly placed walls.
    pygame.display.update()

    # Pygame has stupid problems quitting
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                print "Quitting."
                pygame.quit()
                sys.exit()