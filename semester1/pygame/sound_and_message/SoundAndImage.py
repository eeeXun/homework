import pygame,sys,time
from pygame.locals import *

pygame.init()

screen=pygame.display.set_mode((850,480))
pygame.display.set_caption('Sound And Image')


t=pygame.image.load('toilet.png')
bgi=pygame.transform.scale(t,(850,480))
p=pygame.image.load('poo.png')
transpoo1=pygame.transform.scale(p,(100,100))
p2=pygame.transform.scale(p,(50,50))
transpoo2=pygame.transform.flip(p2,False,True)
t2=pygame.transform.flip(p2,True,False)
screen.blit(bgi,(0,0))
screen.blit(transpoo1,(375,270))
screen.blit(transpoo2,(400,180))
screen.blit(p2,(200,250))
screen.blit(t2,(570,240))

pygame.mixer.music.load('NewYearCountdown.mp3')
pygame.mixer.music.play(-1)
musicPlay=True




pygame.display.update()

while True:
    for event in pygame.event.get():
        if event.type==QUIT:
            pygame.quit()
            sys.exit()
        if event.type==KEYUP:
            if event.key==K_ESCAPE:
                pygame.quit()
                sys.exit()
            if event.key==K_m:
                if musicPlay:
                    pygame.mixer.music.stop()
                    musicPlay=False
                else:
                    pygame.mixer.music.play(-1)
                    musicPlay=True
                    