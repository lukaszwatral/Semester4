import numpy as np
import scipy
import pandas as pd
import sklearn
#5, 6 - nie robić

#zadanie 1

x = [7,7,3,3,8,3,8,8,9,7,8,4,5,3,7,5,1,6,4,4,7,2,1,1,9,3,5,6,1,9,1,1,2,9,6,4,4,7,4,6,9,6,4,9,5,6,9,8,2,3]
def freq(x, prob=True):
    x = np.sort(x)
    xi = set(x) #usunięcie duplikatów
    ni = {}
    pi = {}
    for i in x:
        if i in ni:
            ni[i] += 1
        else:
            ni[i] = 1
    for i in xi:
        pi[i] = ni[i]/x.size
    if prob == True:
        return [xi, list(pi.values())]
    else:
        return [xi, list(ni.values())]

print("Zadanie 1:")
print(freq(x, True))
print(freq(x, False))

#zadanie 2

x = [10, 20, 30, 40, 50, 10, 20, 30, 35]
y = ['a', 'b', 'b', 'c', 'd', 'a', 'b', 'e', 'e']
def freq2(x, y, prob=True):
    df = pd.DataFrame({"x":x, "y":y})
    ni = df.value_counts()
    pi = ni.values/len(x)
    tmp = df.drop_duplicates()
    xi = tmp["x"].tolist()
    yi = tmp["y"].tolist()
    if prob == True:
        return [xi, yi, list(pi)]
    else:
        return [xi, yi, list(ni.values)]

print("Zadanie 2:")
print(freq2(x, y, True))
print(freq2(x, y, False))

#zadanie 3
x = [1, 5, 7, 5, 2]
y = ['a', 'a', 'a', 'b', 'b']

def entrophy(x):
    xi, pi = freq(x, True)
    n = len(pi)
    h = 0
    for i in range(n):
        h += pi[i]*np.log2(pi[i])
    return -h

def entrophy2(x, y):
    xi, yi, pi = freq2(x, y, True)
    n = len(pi)
    h = 0
    for i in range(n):
        h += pi[i]*np.log2(pi[i])
    return -h

def infogain(x, y): #informacja wzajemna/przyrost informacji
    h = entrophy2(x, y)
    i = entrophy(x) + entrophy(y) - h
    return i

print("Zadanie 3:")
print(entrophy(x))
print(infogain(x, y))

#zadanie 4
plik = pd.read_csv('zoo.csv')
x = plik['type']
plik = plik.drop(columns=['type', 'animal']) #usunięcie pierwszej i ostatniej kolumny
dane = []
for row in plik:
    y = plik[row]
    dane.append([row, entrophy(y), infogain(x, y)])

df = pd.DataFrame(dane, columns=['kolumna', 'entrophy', 'infogain'])
df = df.sort_values(by='infogain', ascending=False)

print("Zadanie 4:")
print(df)