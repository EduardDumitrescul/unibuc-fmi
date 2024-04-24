import numpy as np
from skimage import io

# a
images = np.array([np.load(f"images/car_{i}.npy") for i in range(0, 9)])

# b

sum = np.sum(images)
print(f"B: {sum}")

# c
sum = np.sum(images, axis=(1, 2))
print(f"C: {sum}")

# d
max_index = np.argmax(sum)
print(f"D: {max_index}")

# e
mean_image = np.mean(images, axis=0)
io.imshow(mean_image.astype(np.uint8))
io.show()

# f

std = np.std(images, axis=(0))
print(f"F: {std}")

# g
images = np.divide(np.subtract(images, mean_image), std)
print(f"G: {images}")

# h
images = images[:, 200:300, 280:400]
print(np.shape(images))

# i
images = np.flip(images, axis=(1, 2))
for image in images:
    io.imshow(image.astype(np.uint8))
    io.show()
