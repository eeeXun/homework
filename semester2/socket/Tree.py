import os,glob
Dir=[]
def scan_dir(path):
    if os.path.isdir(path):
        Dir.append(path)
        for filename in glob.glob(path+'/*'):
            scan_dir(filename)
    return Dir

def PrintTree(d):
    topDir=os.path.dirname(d[0])
    for i in d:
        if i==d[0]:
            print(os.path.basename(i))
            continue
        layer=0
        dirtory=os.path.dirname(i)
        basename=os.path.basename(i)
        while dirtory != topDir:
            layer+=1
            dirtory=os.path.dirname(dirtory)
        for i in range(layer-1):
            print('|   ',end='')
        print('|')
        for i in range(layer-1):
            print('|   ',end='')
        print('+---%s'%(basename))
        
PrintTree(scan_dir('D:\\Users\\Desktop'))
