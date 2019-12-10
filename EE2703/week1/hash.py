with open("test.txt","r") as f: #open file in readmode providing correct path
    contents = f.read()
words = contents.lower().split() #spilt words in file with considering case sensitive
d = {}                    #make an empty dict to add words as key and frequency of word as value
for word in words:
    if word in d:          # if word is in dict increase frequency by 1
        d[word] +=1
    else:
        d[word] = 1           #else append word to dict
#for k in sorted(d,key=d.get,reverse=True)[:10]: #prints first ten highest frequency words
#    print k,d[k]
for k in sorted(d,key=d.get,reverse=True): #prints all words and their frequency
    print k,d[k]
