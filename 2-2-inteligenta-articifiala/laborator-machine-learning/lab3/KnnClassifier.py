import numpy as np


class KnnClassifier:
    def __init__(self, train_images, train_labels):
        self.train_images = train_images
        self.train_labels = train_labels

    def getDistance(self, metric):
        if metric == 'l1':
            return lambda x, y: np.sum(abs(x - y))
        if metric == 'l2':
            return lambda x, y: np.sqrt(np.sum(np.power(x - y, 2)))

    def computeDistance(self, metric, x, y):
        return self.getDistance(metric)(x, y)

    def classify_image(self, test_image, num_neighbors=3, metric='l2'):
        #     print(np.shape(test_image))
        #     print(np.shape(self.train_images))
        dist = np.apply_along_axis(lambda x: self.computeDistance(metric, test_image, x), 1, self.train_images)
        dist_with_labels = np.array(list(zip(dist, self.train_labels)))
        dist_with_labels = sorted(dist_with_labels, key=lambda x: x[0])

        dist_with_labels = dist_with_labels[:num_neighbors]
        unique, counts = np.unique(dist_with_labels[:], return_counts=True)
        return unique[np.argmax(counts)]

    def classify_images(self, test_images, num_neighbors=3, metric='l2'):
        return np.apply_along_axis(lambda image: self.classify_image(image, num_neighbors, metric), arr=test_images, axis=1)


    def accuracy_score(self, test_images, test_labels, num_neighbors=3, metric='l2'):
        algo_labels = self.classify_images(test_images, num_neighbors, metric)

        correct = np.sum(algo_labels == test_labels)
        total = np.size(test_labels)

        return (correct / total)
