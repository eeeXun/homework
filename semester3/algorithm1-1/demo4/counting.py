import csv
def readfile():
    with open('/home/xun/Downloads/access_large.log','r') as f:
        rows=csv.reader(f,delimiter=' ')
        status_count={}
        log_read=[]
        for row in rows:
            log_read.append(row)
            if row[6] in status_count:
                status_count[row[6]]+=1
            else:
                status_count[row[6]]=1
        return status_count,log_read

def bubbleSort_status(sorted_status):
    for i in range(len(sorted_status)-1,-1,-1):
        for j in range(i):
            if sorted_status[j]>sorted_status[j+1]:
                sorted_status[j],sorted_status[j+1]=sorted_status[j+1],sorted_status[j]

def sorting_status(status_count):
    sorted_status=[]
    sorted_count=[]
    sorted_status_count={}
    for i in status_count:
        sorted_status.append(i)
    bubbleSort_status(sorted_status)
    for i in sorted_status:
        sorted_count.append(status_count[i])
        # sorted_status_count[i]=status_count[i]
    for i in range(1,len(sorted_status)):
        sorted_count[i]+=sorted_count[i-1]
    for i in range(len(sorted_status)):
        sorted_status_count[sorted_status[i]]=sorted_count[i]

    return sorted_status_count

def counting_sort(log_read,sorted_status_count):
    sorted_log=[]
    for i in range(len(log_read)):
        sorted_log.append([])
    for i in range(len(log_read)-1,-1,-1):
        tmp_status=log_read[i][6]
        tmp_log=log_read[i]
        sorted_log[sorted_status_count[tmp_status]-1]=tmp_log
        sorted_status_count[tmp_status]-=1
    return sorted_log

def writeLog(sorted_log):
    with open('status.log','w') as f:
        writer=csv.writer(f,delimiter=' ')
        for i in sorted_log:
            writer.writerow(i)

def main():
    status_count,log_read=readfile()
    sorted_status_count=sorting_status(status_count)
    sorted_log=counting_sort(log_read,sorted_status_count)

    writeLog(sorted_log)

if __name__=='__main__':
    main()
