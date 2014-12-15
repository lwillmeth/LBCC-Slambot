"""
An early draft of creating and visualizing walls for the LBCC Slambot system.
"""
import pygame, sys, random, os
from pygame.locals import *


class Map:
    """ Base class for all maps. """
    walls = {}

    def __init__(self, precision=5):
        """ Defaults to precision to resolution of 5 cm. """
        self.precision = precision

    def make_wall(self, x, y):
        """ Adds, or increments a map point. """
        # Increment wall position, or start a new wall segment
        if (x, y) in Map.walls:
            Map.walls[(x, y)] += 1
        else:
            Map.walls[(x, y)] = 1


if __name__ == "__main__":
    pygame.init()
    screen = pygame.display.set_mode((500, 500))
    screen.fill((255, 255, 255))  # white background

    localMap = Map()
    botPos = [0, 0]

    # Add some randomized walls to the model
    for i in range(100):
        localMap.make_wall(random.randrange(0, 600), random.randrange(0, 600))

    for spot in walls:
        color = 255-walls[spot]*55  # Walls get darker as they are seen more often
        # Syntax is: screen, color, (x, y, width, height), thickness
        pygame.draw.rect(screen, (color, color, color),
                         [a+b for a, b in zip(botPos, spot)]+[5, 5], 0)

    pygame.display.update()
    #Pygame seems to freak out on exit, I'm not yet sure why.
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                print "Quitting."
                pygame.quit()
                sys.exit()