# Support Vector Machines, Kernel Methods, and Kernel Ridge Regression

## 1. Instructor Information
* **Lecturer:** Radu Ionescu, Prof. PhD.
* **Institution:** Faculty of Mathematics and Computer Science, University of Bucharest

---

## 2. Linear Support Vector Machines (SVM)

### The Classification Problem
* **Goal:** Separate two classes of data points with a decision boundary (hyperplane).
* **Separating Hyperplanes:** There are infinitely many hyperplanes that can separate linearly separable data.
* **The "Best" Hyperplane:** SVM chooses the hyperplane that maximizes the **margin** between the two classes.

### The Margin
* **Definition:** The margin is the distance from the decision boundary to the closest data points of either class.
* **Geometric Intuition:** A larger margin implies better generalization to unseen data.
* **Support Vectors:** The data points that lie closest to the decision boundary are called support vectors. They essentially "support" or define the margin. The model depends only on these points; moving other points (as long as they don't cross the margin) does not change the decision boundary.

### Mathematical Formulation (Primal)
Given a dataset of $N$ points $(x_i, y_i)$ where $y_i \in \{-1, 1\}$:
* **Hyperplane:** Defined by $w \cdot x + b = 0$.
* **Constraints:**
    * $w \cdot x_i + b \ge 1$ for $y_i = 1$
    * $w \cdot x_i + b \le -1$ for $y_i = -1$
    * Combined: $y_i(w \cdot x_i + b) \ge 1$
* **Margin Width:** The width of the margin is $\frac{2}{\|w\|}$.
* **Objective:** To maximize the margin $\frac{2}{\|w\|}$, we minimize $\|w\|$. Mathematically, it is convenient to minimize $\frac{1}{2}\|w\|^2$.

### Soft Margin SVM
Real-world data is rarely perfectly linearly separable. To handle noise and outliers, SVM introduces **slack variables** ($\xi_i$).
* **Relaxed Constraints:** $y_i(w \cdot x_i + b) \ge 1 - \xi_i$, where $\xi_i \ge 0$.
* **New Objective Function:**
  $$\min \frac{1}{2}\|w\|^2 + C \sum_{i=1}^N \xi_i$$
* **The $C$ Parameter:** Controls the trade-off between maximizing the margin and minimizing classification errors (hinge loss).
    * **High $C$:** Penalizes errors heavily (harder margin). Risk of overfitting.
    * **Low $C$:** Allows more errors (softer margin) for a wider margin. Smoother decision boundary.

---

## 3. The Dual Formulation

### Lagrange Multipliers
To solve the constrained optimization problem, we use Lagrange multipliers ($\alpha_i$). This transforms the problem into its **dual form**.

### The Dual Problem
* Maximize:
  $$\sum_{i=1}^N \alpha_i - \frac{1}{2} \sum_{i=1}^N \sum_{j=1}^N \alpha_i \alpha_j y_i y_j (x_i \cdot x_j)$$
* Subject to:
  * $0 \le \alpha_i \le C$
  * $\sum \alpha_i y_i = 0$

### Key Observation
The dual formulation depends on the data points only through their **dot products** $(x_i \cdot x_j)$. This is the crucial property that allows the use of **Kernel Methods**.

---

## 4. Kernel Methods

### Non-Linearity
Linear classifiers cannot solve non-linear problems (like the XOR problem).
* **Idea:** Map the input data from the original space (Input Space) into a higher-dimensional space (Feature Space) where the data becomes linearly separable.
* **Mapping Function:** $\Phi: \mathbb{R}^d \rightarrow \mathbb{R}^k$ (where $k > d$).

### The Kernel Trick
Computing the mapping $\Phi(x)$ explicitly can be computationally expensive or even impossible (infinite dimensions).
* **Definition:** A kernel function $k(x, y)$ computes the dot product in the high-dimensional feature space without explicitly mapping the points.
  $$k(x_i, x_j) = \Phi(x_i) \cdot \Phi(x_j)$$
* We replace the dot product $(x_i \cdot x_j)$ in the SVM dual formulation with the kernel function $k(x_i, x_j)$.

### Common Kernels
1.  **Linear Kernel:** $k(x, y) = x \cdot y$ (Standard linear SVM).
2.  **Polynomial Kernel:** $k(x, y) = (x \cdot y + 1)^d$. Maps data to a space of polynomial features of degree $d$.
3.  **Radial Basis Function (RBF) / Gaussian Kernel:**
    $$k(x, y) = \exp(-\gamma \|x - y\|^2)$$
    * This kernel maps data into an **infinite-dimensional** Hilbert space.
    * It measures similarity: close points have a kernel value near 1, distant points near 0.

### Mercer's Theorem
A function $k$ is a valid kernel if and only if the corresponding Gram matrix (the matrix of kernel values for all pairs of data points) is **positive semi-definite**.

---

## 5. Kernel Ridge Regression (KRR)

### Ridge Regression Recap
Ridge regression adds an $L_2$ regularization term to standard linear regression to prevent overfitting.
* **Primal Objective:** $\min \|y - wX\|^2 + \lambda \|w\|^2$
* **Primal Solution:** $w = (X^T X + \lambda I)^{-1} X^T y$

### Kernelization
Using the Representer Theorem, the weight vector $w$ can be expressed as a linear combination of the training samples: $w = \sum \alpha_i \Phi(x_i)$.
* **Dual Solution:**
  $$\alpha = (K + \lambda I)^{-1} y$$
  where $K$ is the kernel matrix ($K_{ij} = k(x_i, x_j)$).
* **Prediction:** For a new sample $x'$:
  $$f(x') = \sum_{i=1}^N \alpha_i k(x_i, x')$$

### KRR vs. Support Vector Regression (SVR)
* **Optimization:** KRR has a closed-form solution (matrix inversion), while SVR requires quadratic programming.
* **Scalability:** KRR involves inverting an $N \times N$ matrix ($O(N^3)$), which is slow for large datasets. SVR scales better ($O(N^2)$ to $O(N^3)$ depending on implementation).
* **Sparsity:** SVR solutions are sparse (depends only on support vectors). KRR solutions are dense (uses all training points).

---

## 6. Python Implementation (Scikit-Learn)

### Support Vector Classifier (SVC)
```python
from sklearn import svm

# Create classifier with linear kernel
clf = svm.SVC(kernel='linear', C=1.0)

# Create classifier with RBF kernel
# gamma is the kernel coefficient for 'rbf', 'poly' and 'sigmoid'
clf = svm.SVC(kernel='rbf', C=1.0, gamma='scale')

# Train the model
clf.fit(X_train, y_train)

# Predict
y_pred = clf.predict(X_test)

# Support vectors
print(clf.support_vectors_)