import csv

def readfile():
    d1=[]
    d2=[]
    d3=[]
    d4=[]
    d5=[]
    with open('./status.log','r') as f:
        rows=csv.reader(f,delimiter=' ')
        for row in rows:
            if 100<=int(row[6])<=199:
                d1.append(row)
            elif 200<=int(row[6])<=299:
                d2.append(row)
            elif 300<=int(row[6])<=399:
                d3.append(row)
            elif 400<=int(row[6])<=499:
                d4.append(row)
            else:
                d5.append(row)
    return d1,d2,d3,d4,d5

def write_html(d1,d2,d3,d4,d5):
    d1_msg=''
    d2_msg=''
    d3_msg=''
    d4_msg=''
    d5_msg=''
    for i in d1:
        d1_msg+='<tr style="background-color:#5bc0de"><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td></tr>\n'.format(i[0],i[1],i[2],i[3],i[4],i[5],i[6],i[7],i[8],i[9])
    for i in d2:
        d2_msg+='<tr style="background-color:#5cb85c"><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td></tr>\n'.format(i[0],i[1],i[2],i[3],i[4],i[5],i[6],i[7],i[8],i[9])
    for i in d3:
        d3_msg+='<tr style="background-color:#0275d8"><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td></tr>\n'.format(i[0],i[1],i[2],i[3],i[4],i[5],i[6],i[7],i[8],i[9])
    for i in d4:
        d4_msg+='<tr style="background-color:#f0ad4e"><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td></tr>\n'.format(i[0],i[1],i[2],i[3],i[4],i[5],i[6],i[7],i[8],i[9])
    for i in d5:
        d5_msg+='<tr style="background-color:#d9534f"><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td><td>{}</td></tr>\n'.format(i[0],i[1],i[2],i[3],i[4],i[5],i[6],i[7],i[8],i[9])
    html='''
<table border=1>
{}
{}
{}
{}
{}
</table>'''.format(d1_msg,d2_msg,d3_msg,d4_msg,d5_msg)
    with open('new.html','w') as f:
        f.write(html)

def main():
    d1,d2,d3,d4,d5=readfile()
    write_html(d1,d2,d3,d4,d5)

if __name__=='__main__':
    main()
