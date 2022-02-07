import csv

def readfile():
    with open('/home/xun/Downloads/500_constituents_financial.csv','r') as f:
        first_row=True
        head=[]
        csv_read=[]
        rows=csv.reader(f)
        for row in rows:
            if first_row:
                head=row
                first_row=False
                continue
            else:
                csv_read.append(row)
        return head,csv_read

def shellsort(csv_read):
    size_csv=len(csv_read)
    gap=1
    while gap<size_csv:
        gap=gap*3+1
    while gap>1:
        gap//=3
        key=int
        key_list=[]
        j=int
        for i in range(gap,size_csv):
            key=eval(csv_read[i][10])
            key_list=csv_read[i]
            j=i-gap
            while j>=0 and key<eval(csv_read[j][10]):
                csv_read[j+gap]=csv_read[j]
                j-=gap
            csv_read[j+gap]=key_list

def writefile(head,csv_read):
    with open('new.csv','w') as f:
        writer=csv.writer(f)
        writer.writerow(head)
        for i in csv_read:
            writer.writerow(i)

def main():
    head,csv_read=readfile()
    shellsort(csv_read)
    writefile(head,csv_read)

if __name__=='__main__':
    main()
