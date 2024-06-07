import numpy as np
from sklearn.naive_bayes import MultinomialNB
import matplotlib.pyplot as plt


def value_to_bins(matrix, bins):
    matrix = np.digitize(matrix, bins) - 1
    return matrix


def test_model(train_images, train_labels, test_images, test_labels, num_bins):
    bins = np.linspace(start=0, stop=256, num=num_bins+1)
    # print(bins)

    train_images = value_to_bins(train_images, bins)
    test_images = value_to_bins(test_images, bins)

    # plt.imshow(np.reshape(train_images[0], (28, 28)).astype(np.uint8), cmap='gray')
    # plt.show()

    naive_bayes_model = MultinomialNB()
    naive_bayes_model.fit(train_images, train_labels)
    score = naive_bayes_model.score(test_images, test_labels)
    return score

def show_bad_exmaples(train_images, train_label, test_images, test_labels, num_bins, num_examples):
    bins = np.linspace(start=0, stop=256, num=num_bins + 1)

    train_images = value_to_bins(train_images, bins)
    test_images = value_to_bins(test_images, bins)

    naive_bayes_model = MultinomialNB()
    naive_bayes_model.fit(train_images, train_labels)
    res_labels = naive_bayes_model.predict(test_images)

    for (img, res, exp) in zip(test_images, res_labels, test_labels):
        if res != exp:
            plt.imshow(np.reshape(img, (28, 28)).astype(np.uint8), cmap='gray')
            plt.show()
            print(f"result: {res} - expected: {exp}")
            num_examples -= 1
        if num_examples <= 0:
            break

    miss = dict()
    total = dict()
    for i in range(10):
        for j in range(10):
            miss[(i, j)] = 0
            total[(i, j)] = 0

    number_examples = np.array([0 for i in range(10)])
    number_misclassified = np.array([0 for i in range(10)])
    for (img, res, exp) in zip(test_images, res_labels, test_labels):
        number_examples[exp] += 1
        if res != exp:
            miss[(exp, res)] += 1
            number_misclassified[exp] += 1

    miss_ratio = number_misclassified / number_examples
    print(f"{np.argmax(miss_ratio)} - {np.max(miss_ratio)}")

    max = 0.0
    pair = (0, 0)

    for i in range(10):
        for j in range(i+1, 10):
            p = miss[(i, j)] + miss[(j, i)]
            if max < p:
                max = p
                pair = (i, j)

    print(f"{max} - {pair}")


def confusion_matrix(label_exp, label_res):
    c = np.zeros((10, 10))
    for(exp, res) in zip(label_exp, label_res):
        c[exp][res] += 1
    return c



train_images = np.loadtxt('data/train_images.txt')  # incarcam imaginile
train_labels = np.loadtxt('data/train_labels.txt', 'int', converters=float)



test_images = np.loadtxt('data/test_images.txt')  # incarcam imaginile
test_labels = np.loadtxt('data/test_labels.txt', 'int', converters=float)

for num_bins in [3, 5, 7, 9, 11]:
    print(f"{num_bins}: {test_model(train_images, train_labels, test_images, test_labels, num_bins)}")


### EX 5

show_bad_exmaples(train_images, train_labels, test_images, test_labels, 7, 10)


