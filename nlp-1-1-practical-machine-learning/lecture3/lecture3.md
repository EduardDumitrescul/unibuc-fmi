# k-Nearest Neighbors, Local Learning, and the Curse of Dimensionality

## 1. Instructor Information
* **Lecturer:** Radu Ionescu, Prof. PhD.
* **Institution:** Faculty of Mathematics and Computer Science, University of Bucharest

---

## 2. Supervised Learning Tasks

### Classification
* **Goal:** Estimate a function $g(x)$ from a set of $N$ training examples $(x_i, y_i)$ where $y_i$ represents a class label (e.g., $\{-1, 1\}$).

### Regression
* **Goal:** Estimate a function $g(x)$ from training examples where the output $t$ is continuous.
* **Loss Function:** Typically Mean Squared Error (MSE).
* **Generalization Error:** The expected error over the joint probability distribution.
* **Empirical Error:** The average error calculated on the training set.

---

## 3. k-Nearest Neighbors (k-NN)

### The Algorithm
k-NN is a memory-based classifier that relies on the assumption that training and test data are sampled from the same distribution.
1.  For a test sample $x$, find the $k$ nearest neighbors in the training set.
2.  **Classification:** Label $x$ using a plurality vote among the $k$ neighbors.
3.  **Regression:** The output is the mean of the labels (values) of the $k$ neighbors: $f(x) = \frac{1}{K}\sum_{i=1}^{K}y_{i}$.

### Tie-Breaking Strategies
When there is a tie in voting:
1.  Choose a random label from the tied ones.
2.  Apply 1-NN (reduce $k$ to 1).
3.  Use distances to the test sample as weights for the votes.

### The Effect of k
* **$k=1$:** Produces a Voronoi diagram partition. Decision borders are non-linear and pass through areas equidistant between points. Can lead to overfitting (error on training data is 0, but may be high on test data).
* **Increasing $k$:** The decision boundary becomes smoother. This acts as a regularization method, potentially increasing generalization capacity, but if $k$ is too large, it can lead to underfitting.

### Advantages
* Simple model.
* Directly applicable to multi-class problems.
* Non-linear decision boundaries.
* Quality improves with more training data.
* Only one parameter ($k$) to tune.

### Disadvantages
* Requires defining a meaningful distance metric.
* High computational cost (must store and search the entire training set during inference).
* Suffers significantly from the "Curse of Dimensionality".

### Optimizations
To avoid the high cost of searching the whole dataset, spatial partitioning methods can be used:
* **k-d Trees:** Binary tree structure that splits data by alternating dimensions and finding medians.
* **Locality Sensitive Hashing.**

---

## 4. Distance Metrics

The choice of distance function is critical for k-NN.

### Standard Distances
* **Euclidean (L2):** $d_{L_2}(x,y) = \sqrt{\sum (x_i - y_i)^2}$.
* **Manhattan (L1):** $d_{L_1}(x,y) = \sum |x_i - y_i|$.
* **Minkowski (Lp):** Generalization where $d_{L_p}(x,y) = \sqrt[p]{\sum |x_i - y_i|^p}$.
    * *Note:* If $p < 1$, the triangle inequality is violated, so it is no longer a valid distance metric.

### Discrete/String Distances
* **Hamming Distance:** Counts the number of positions at which corresponding symbols are different. Useful for categorical features or DNA.
* **Edit (Levenshtein) Distance:** The number of changes (insert, delete, replace) required to transform one string into another. Useful for text or DNA.

### Dynamic Time Warping (DTW)
Used for comparing temporal sequences (e.g., gesture recognition trajectories) that may vary in speed. It finds the optimal alignment between two sequences $M$ and $Q$.

**Alignment Rules:**
1.  **Boundaries:** The alignment must start at $(S_1, t_1)$ and end at $(S_m, t_n)$.
2.  **Monotonicity:** The alignment cannot go backwards in time ($s_{i+1} \ge s_i$ and $t_{i+1} \ge t_i$).
3.  **Continuity:** The alignment cannot skip elements ($s_{i+1} - s_i \le 1$ and $t_{i+1} - t_i \le 1$).

**Algorithm:**
Solved using Dynamic Programming. The cost of a cell $(i, j)$ depends on the cost of the current match plus the minimum cost of the previous allowable steps:
$$C[i,j] = cost(M_i, Q_j) + \min(C[i-1, j], C[i, j-1], C[i-1, j-1])$$

---

## 5. k-NN Variants

### Edited Nearest Neighbors
* **Goal:** Produce smoother borders by removing outliers.
* **Method:** Eliminate training samples that have a different label from their $k$ nearest neighbors.

### Condensed Nearest Neighbors
* **Goal:** Reduce dataset size by keeping only samples that affect the decision boundary.
* **Method:**
    1.  Select a random set $P$ (at least one per class).
    2.  Add a training sample to $P$ only if the current k-NN based on $P$ classifies it incorrectly.

---

## 6. Local Learning

Instead of a global model, Local Learning trains a specific model for each specific query.
1.  Select training samples located in the vicinity of the test sample.
2.  Train a classifier (e.g., SVM, Neural Net) only on these selected examples.
3.  Apply this local classifier to predict the label of the test sample.

*Example:* Using VGG features for images, clustering them, and then performing local learning within the neighborhood of a test image.

---

## 7. The Curse of Dimensionality

### The Concept
As the dimensionality of the feature space increases (e.g., going from 1D to 200x200 pixel images which is 40,000 dimensions), the volume of the space increases exponentially.

### Implications
* **Sparsity:** To "fill" a space with data points to maintain the same density, you need exponentially more data as dimensions increase.
* **Distance Concentration:** In high-dimensional Euclidean spaces, the distance between points grows, and the ratio between the nearest and farthest points approaches 1. The concept of "nearest neighbor" becomes less meaningful because all points become roughly equidistant.
* **Hughes Phenomenon:** For a fixed sample size, classifier performance initially increases as features are added (more information), but eventually peaks and then degrades as the dimensionality continues to grow (due to sparsity and difficulty in estimating parameters).