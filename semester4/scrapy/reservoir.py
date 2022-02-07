from urllib.request import urlopen
import json, os

key = os.getenv("EPA_KEY")
response = urlopen("https://data.epa.gov.tw/api/v1/stat_p_124?format=json&api_key={}".format(key)).read()
result = json.loads(response.decode("UTF-8")).get("records")

tmp = set()
for r in result:
    tmp.add(r.get("item2"))

for t in tmp:
    print(t)
