import matplotlib.pyplot as plt
import numpy as np
import pylab as py
from skimage import data
from skimage import filters
from skimage import exposure
from PIL import Image
import matplotlib.image

matplotlib.use('TkAgg') #aby obrazki wyświetlały się w nowym oknie

########################DYSKRETYZACJA########################

#zadanie 1, 2
def sinus(f, Fs):
    t = np.arange(0, 1, 1/Fs)
    s = np.sin(2*np.pi*f*t)
    return t, s

#zadanie 3
tab = [20, 21, 30, 45, 50, 100, 150, 200, 250, 1000]
for i in range(10):
    plt.subplot(2, 5, i+1)
    s = sinus(10, tab[i])
    plt.plot(s[0], s[1])
    plt.title(f"f=10Hz, Fs = {tab[i]}Hz")
plt.show()

#zadanie 4
#Twierdzenie o próbkowaniu Nyquista-Shannona

#zadanie 5
#aliasing

#zadanie 6
img = plt.imread("robal.png")
plt.imshow(img)
plt.axis((200, 300, 230, 300))
plt.show()

########################KWANTYZACJA########################


#zadanie 1
img = plt.imread("robal.png")
# plt.imshow(img)
# plt.show()

#zadanie 2
print(img.ndim)

#zadanie 3
print(img.shape) #3

#zadanie 4
img1 = (np.max(img, axis=2)+np.min(img, axis=2))/2
img2 = np.mean(img, axis=2)
img3 = 0.21*img[:,:,0]+0.72*img[:,:,1]+0.07*img[:,:,2]

plt.subplot(2, 2, 1)
plt.imshow(img)
plt.title("Oryginalne zdjęcie")
plt.subplot(2, 2, 2)
plt.imshow(img1, cmap='grey')
plt.title("Wyznaczenie jasności piksela")
plt.subplot(2, 2, 3)
plt.imshow(img2, cmap='grey')
plt.title("Uśrednienie wartości piksela")
plt.subplot(2, 2, 4)
plt.imshow(img3, cmap='grey')
plt.title("Wyznaczenie luminancji piksela")
plt.show()


#zadanie 5
counts1, bins1 = np.histogram(img1, bins=256)
counts2, bins2 = np.histogram(img2, bins=256)
counts3, bins3 = np.histogram(img3, bins=256)
plt.subplot(1, 3, 1)
plt.hist(bins1[:-1], bins1, weights=counts1)
plt.title("Histogram - wyznaczenie jasności piksela")
plt.subplot(1, 3, 2)
plt.hist(bins2[:-1], bins2, weights=counts2)
plt.title("Histogram - uśrednienie wartości piksela")
plt.subplot(1, 3, 3)
plt.hist(bins3[:-1], bins3, weights=counts3)
plt.title("Histogram - wyznaczenie luminancji piksela")
plt.show()

#zadanie 6
counts4, bins4 = np.histogram(img3, bins=16)
sr = (np.max(bins4)+np.min(bins4))/2
plt.hist(bins4[:-1], bins4, weights=counts4)
plt.plot()
plt.title('Histogram z redukcją kolorów, bins=16')
plt.vlines(x=sr, ymin=0, ymax=np.max(counts4), color='r', linestyles='dashed')
plt.show()
print(bins4)


########################BINARYZACJA########################
#zadanie 1,2
img = plt.imread('robal.png')
img5 = 0.21*img[:,:,0]+0.72*img[:,:,1]+0.07*img[:,:,2]
# plt.imshow(img5, cmap='grey')
# plt.show()
counts5, bins5 = np.histogram(img5,bins=256)
# plt.hist(bins5[:-1], bins5, weights=counts5)
# plt.show()

#zadanie 3, 4, 5
val = filters.threshold_otsu(img5)
hist, bins_center = exposure.histogram(img5)

plt.figure(figsize=(9,4))
plt.subplot(1, 3, 1)
plt.imshow(img5, cmap='grey', interpolation='nearest')
plt.subplot(1, 3, 2)
plt.imshow(img5 < val, cmap='grey', interpolation='nearest')
plt.subplot(1, 3, 3)
plt.plot(bins_center, hist, lw=2)
plt.axvline(val, color='r', linestyle='dashed')
plt.tight_layout()
plt.show()