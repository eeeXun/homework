from urllib.request import urlopen
import json

response = urlopen("https://opendata.cwb.gov.tw/fileapi/v1/opendataapi/F-C0032-026?Authorization=rdec-key-123-45678-011121314&format=JSON").read()
myjson = json.loads(response.decode("UTF-8")).get("cwbopendata")
myData = myjson.get("dataset")
print(myData.get("location").get("locationName"), "氣象預報")
print("發佈時間:", myjson.get("sent"))
pSet = myData.get("parameterSet").get("parameter")
tmp = 1
for p in pSet:
    print(tmp, p.get("parameterValue"))
    tmp += 1
