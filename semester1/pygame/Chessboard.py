import pygame,sys,time

pygame.init()

screen=pygame.display.set_mode((640,640))
pygame.display.set_caption('CHessboard')

white=(242,234,218)
green=(92,122,41)

for i in range(8):
    for j in range(4):
        if i%2==0:
            pygame.draw.rect(screen,white,(0+160*j,0+80*i,80,80),0)
        else:
            pygame.draw.rect(screen,white,(80+160*j,0+80*i,80,80),0)
for i in range(8):
    for j in range(4):
        if i%2==0:
            pygame.draw.rect(screen,green,(80+160*j,0+80*i,80,80),0)
        else:
            pygame.draw.rect(screen,green,(0+160*j,0+80*i,80,80),0)

pygame.display.update()
time.sleep(5)