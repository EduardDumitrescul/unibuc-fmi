import numpy as np
from matplotlib import pyplot as plt

from lab3.KnnClassifier import KnnClassifier

train_images = np.loadtxt('data/train_images.txt')  # incarcam imaginile
train_labels = np.loadtxt('data/train_labels.txt', 'int', converters=float)


test_images = np.loadtxt('data/test_images.txt')  # incarcam imaginile
test_labels = np.loadtxt('data/test_labels.txt', 'int', converters=float)




knn = KnnClassifier(train_images, train_labels)

neighbors = [1, 3, 5, 7, 9]
scoresL2 = [knn.accuracy_score(test_images, test_labels, x, "l2") for x in neighbors]
scoresL1 = [knn.accuracy_score(test_images, test_labels, x, "l1") for x in neighbors]

print(scoresL2)

plt.title("Acuratetea pentru distantele L1 si L2")
plt.xlabel("accuracy")
plt.ylabel("number of neighbors")
plt.plot(neighbors, scoresL2, label="L2")
plt.plot(neighbors, scoresL1, label="L1")
plt.legend()
plt.show()