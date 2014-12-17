"""
An early draft of creating and visualizing walls for the LBCC Slambot system.
"""
import pygame, sys, random, math
from pygame.locals import *


class Map:
    """ Base class for all maps. """

    def __init__(self, precision=5):
        """ Constructor for Map class. """
        # Defaults to precision to resolution of 5 cm.
        self.precision = precision
        # Floating point values holds bot position on map
        self.posX, self.posY = 0, 0
        # Dictionary of key:value pairs holds {(x,y):confidence} of walls
        self.walls = {}
        self.botPos = [self.posX, self.posY]

    def find_wall(self, dist, angle):
        """ Add a wall using distance and angle (in radians) of the turret. """
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
    white = (255, 255, 255)
    black = (0, 0, 0)
    screen.fill(black)

    localMap = Map()
    localMap.set_bot(250, 250)  # Position bot in center of the room.
    # Draw an empty room surrounded by walls.
    # Syntax is: screen, color, (x, y, width, height), thickness
    pygame.draw.rect(screen, white, (50, 50, 400, 400), 0)
    pygame.draw.circle(screen, black, localMap.botPos, 4, 0)

    # Add randomized walls using distance & angle.
    for angle in [math.radians(a) for a in range(0, 200, 5)]:
        if (angle%(3*math.pi/4))/(math.pi/4) < 1:
            d = abs(200/math.cos(angle))
            print d, angle, 'cos'
            localMap.find_wall(d, angle)
        else:
            d = abs(200/math.sin(angle))
            print d, angle, 'sin'
            localMap.find_wall(d, angle)

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