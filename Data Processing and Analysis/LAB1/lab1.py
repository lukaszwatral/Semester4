import numpy as np

#zadanie 1

a = np.random.randint(100, size=(10, 5))
slad = np.trace(a)
print(a)
print("Suma głownej przekątnej:", slad)
print(np.diag(a))

#zadanie 2

a = np.random.normal(size=(5, 1))
b = np.random.normal(size=(1, 5))

print(a @ b) #mnożenie macierzowe
print(a*b) #mnożenie po indeksach

#zadanie 3

a = np.random.randint(1, 101, size=25)
b = np.random.randint(1, 101, size=25)
a = a.reshape(5, 5)
b = b.reshape(5,5)

print(a+b)

#zadanie 4

a = np.random.randint(0, 100, size=(4, 5))
b = np.random.randint(0, 100, size=(5, 4))

print(a+b.T) #transponowanie macierzy b

#zadanie 5

a = np.random.randint(0, 100, size=(4, 5))
b = np.random.randint(0, 100, size=(5, 4))

print(a[:, 2]*b.T[:, 3])

#zadanie 6

a = np.random.normal(size=(3, 3))
b = np.random.uniform(size=(3, 3))

print("Macierz a: średnia =", np.average(a), "odchylenie standardowe =", np.std(a), "wariancja =", np.var(a))
print("Macierz b: średnia =", np.average(b), "odchylenie standardowe =", np.std(b), "wariancja =", np.var(b))

#zadanie 7

a = np.arange(9).reshape(3,3)
b = np.arange(9, 18).reshape(3,3)

print(a*b) #mnożenie po indeksach
print(np.dot(a, b)) #mnożenie macierzowe

#zadanie 8

a = np.arange(50).reshape(5, 10)

print(a)
print(np.lib.stride_tricks.as_strided(a, shape=(3, 5) ,strides=a.strides))

#zadanie 9

a = np.arange(9).reshape(3, 3)
b = np.arange(9, 18).reshape(3, 3)

print(np.vstack((a, b))) #macierz pod macierzą
print(np.hstack((a, b))) #macierz obok macierzy

#zadanie 10

from numpy.lib.stride_tricks import as_strided
a = np.arange(24).reshape(4, 6)

print(np.max(np.lib.stride_tricks.as_strided(a, shape=(2, 3), strides=(a.strides))))
print(np.max(np.lib.stride_tricks.as_strided(a[0][3:6], shape=(2, 3), strides=(a.strides))))
print(np.max(np.lib.stride_tricks.as_strided(a[2], shape=(2, 3), strides=(a.strides))))
print(np.max(np.lib.stride_tricks.as_strided(a[2][3:6], shape=(2, 3), strides=(a.strides))))