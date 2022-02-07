import csv

def writerow(color,msg,row):
    msg+='''<tr style="background:{}"><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td>
        <td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td>
        <td>{}</td>\n'''.format(color,row[0],row[1],row[2],row[3],row[4],row[5],row[6],
                            row[7],row[8],row[9],row[10],row[11],row[12],row[13])
    return msg

def readfile():
    head=''
    d1=''
    d2=''
    d3=''
    d4=''
    with open('new.csv','r') as f:
        rows=csv.reader(f)
        first_row=True
        for row in rows:
            if first_row:
                head=writerow('white',head,row)
                first_row=False
                continue
            else:
                EBITDA=eval(row[10])
                if EBITDA<0:
                    d1=writerow('#d9534f',d1,row)
                elif EBITDA==0:
                    d2=writerow('#f0ad4e',d2,row)
                elif 0<EBITDA<1000000000:
                    d3=writerow('#5cb85c',d3,row)
                else:
                    d4=writerow('#0275d8',d4,row)
    return head,d1,d2,d3,d4

def tohtml(head,d1,d2,d3,d4):
    html='''
<table border=1>
{}{}{}{}{}
</table>'''.format(head,d1,d2,d3,d4)
    with open('index.html','w') as f:
        f.write(html)


def main():
    head,d1,d2,d3,d4=readfile()
    tohtml(head,d1,d2,d3,d4)

if __name__=='__main__':
    main()
