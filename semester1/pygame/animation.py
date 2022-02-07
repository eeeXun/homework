import pygame,sys,time
from pygame.locals import*

pygame.init()

screen=pygame.display.set_mode((400,400))
pygame.display.set_caption('animation')
red=(255,0,0)
green=(0,255,0)
blue=(0,0,255)
white=(255,255,255)
black=(0,0,0)

b1={'rect':pygame.Rect(300,80,50,100),'color':red,'dir':[10,2]}
b2={'rect':pygame.Rect(200,200,20,20),'color':green,'dir':[-5,6]}
b3={'rect':pygame.Rect(100,150,60,60),'color':blue,'dir':[7,-15]}
box=[b1,b2,b3]

while True:
    for event in pygame.event.get():
        if event.type==QUIT:
            pygame.quit()
            sys.exit()
    screen.fill(white)
    for b in box:
        b['rect'].left+=b['dir'][0]
        b['rect'].top+=b['dir'][1]
        if b['rect'].top<0:
            b['dir'][1]=-b['dir'][1]
        if b['rect'].right>400:
            b['dir'][0]=-b['dir'][0]
        if b['rect'].bottom>400:
            b['dir'][1]=-b['dir'][1]
        if b['rect'].left<0:
            b['dir'][0]=-b['dir'][0]
        pygame.draw.rect(screen,b['color'],b['rect'])
    
    pygame.display.update()
    time.sleep(0.04)