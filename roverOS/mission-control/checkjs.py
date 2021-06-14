import pygame.joystick

pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)

while True:
    pygame.event.get()
    axis0 = joystick.get_axis(0)
    print(axis0)
