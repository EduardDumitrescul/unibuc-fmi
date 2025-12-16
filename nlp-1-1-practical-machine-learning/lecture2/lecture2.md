# Basic Concepts, Naïve Bayes, and Performance Metrics

## 1. Instructor Information
* **Lecturer:** Radu Ionescu, Prof. PhD. (`raducu.ionescu@gmail.com`)
* **Institution:** Faculty of Mathematics and Computer Science, University of Bucharest

---

## 2. Learning Paradigms

### Standard Paradigms
* **Supervised learning:** Learning from labeled data.
* **Unsupervised learning:** Learning from unlabeled data.
* **Semi-supervised learning:** Combining labeled and unlabeled data.
* **Reinforcement learning:** Learning through interaction and rewards.

### Non-Standard Paradigms
* **Active learning:** The model selects data to be labeled.
* **Transfer learning:** Applying knowledge from one task to another.
* **Transductive learning:** Reasoning from specific training cases to specific test cases.

### Canonical Problem Forms
* **Supervised:**
    * **Classification:** Predicting categorical labels.
    * **Regression:** Predicting continuous values.
* **Unsupervised:**
    * **Clustering:** Grouping similar data points.
    * **Dimensionality Reduction:** Reducing the number of features.

---

## 3. Supervised Learning Framework

### The Paradigm
* **Goal:** Find a function $\hat{f}$ in a hypothesis class $\mathcal{F}$ such that for training data $\{(x_{i},y_{i})\}$, the approximation $y_{i} \approx \hat{f}(x_{i})$ holds.
* **Prediction:** Use the learned function to predict $y = \hat{f}(x)$ for new data $x$.

### Basic Steps
1.  **Data Collection:** Start with data containing known outcomes (labeled by a teacher/oracle).
2.  **Representation:** Decide how to feature-engineer the data.
3.  **Modeling:** Select a hypothesis class $H=\{g:X\rightarrow Y\}$.
    * *Note:* Learning is difficult without establishing a hypothesis class (e.g., classifying "gelato" into Banana or Furbish languages requires knowing the vocabulary of those classes).
4.  **Learning/Estimation:** Find the best hypothesis within the chosen class.
5.  **Model Selection:** Test different models and select the best one; stop if results are satisfactory.

### Training vs. Testing
* The goal is not low loss on training data, but good performance on unseen **test data**.
* **Training Data:** Used to learn the mapping function.
* **Test Data:** Used to verify if learning has occurred.

---

## 4. Error Analysis

### Error Definitions
* **Generalization Error:** The expected error over the joint probability distribution of inputs and outputs.
* **Empirical Error:** The average error calculated on the available dataset.
* **Important:** Estimating empirical error on the training set instead of the test set is considered "cheating".

### Error Decomposition
The total error can be decomposed into several components:
1.  **Approximation/Modeling Error:** Arises from the model class being unable to fully represent reality.
2.  **Estimation Error:** Arises from trying to learn with a finite amount of data.
3.  **Optimization Error:** Arises from failing to optimize the model to completion.
4.  **Bayes Error:** The irreducible error inherent in the reality of the data.

### Bias-Variance Trade-off

* **Bias (Underfitting):** Systematic error due to the model's inability to learn true relationships (e.g., model is too simple). Corrected by increasing model complexity.
* **Variance (Overfitting):** Random error due to sensitivity to small fluctuations/noise in training data. Corrected by adding more data or decreasing model complexity.


* **Underfitting:** High training error and high test error.
* **Overfitting:** Low training error but high test error.
* **Optimum:** The complexity level where test error is minimized.

---

## 5. Statistical Estimation & Model Validation

### Viewpoint
* Data is assumed to be **IID** (Independent Identically Distributed) sampled from a distribution $P(X,Y)$.
* **Model Capacity:** Measures the size of the hypothesis class.
* **Generalization Capacity:** The ability to achieve low error on new data.
* **Learning Theory:** Guarantees that with enough data and a hypothesis class that is not too complex, generalization is probable.

### Data Splitting Strategies
1.  **Train/Validation/Test Split:**
    * Used when plenty of data is available (e.g., 50% Train, 25% Validation, 25% Test).
    * **Validation Set:** Used to tune hyperparameters. Using the test set for tuning leads to overfitting in hyperparameter space.

2.  **Cross-Validation:**
    
    * Used when data is limited.
    * Split data into $k$ folds; train on $k-1$, test on the remaining fold. Repeat $k$ times and average the results.
    * **Leave-one-out:** A special case where $k$ equals the number of samples.

### Improving Generalization
* **Early Stopping:** Halt training when validation error begins to rise.
* **Regularization:** Add a penalty term (e.g., $\lambda R(f)$) to the loss function to constrain model complexity.

---

## 6. Probabilities and Bayes Rule

### Basics
* **Probability $P(A)$:** Can be viewed statistically (limiting frequency) or Bayesian (belief).
* **Axioms:** $0 \le P(A) \le 1$, $P(\emptyset)=0$, $P(\forall)=1$, and $P(A \text{ or } B) = P(A) + P(B) - P(A \text{ and } B)$.
* **Conditional Probability:** $P(A|B)$ is the fraction of worlds where $A$ is true given $B$ is true.

### Bayes Rule
$$P(B|A) = \frac{P(A|B)P(B)}{P(A)}$$
* **Prior:** Belief before seeing data.
* **Likelihood:** How well a hypothesis explains the data.
* **Posterior:** Belief after seeing data.

### The Monty Hall Problem
* **Scenario:** 3 doors (1 prize, 2 goats). You pick door 1. Host opens door 3 (goat). Should you switch?
* **Analysis:**
    * Prior probability of prize behind any door is $1/3$.
    * If you stick, you win only if the prize was originally behind door 1 ($1/3$ chance).
    * Using Bayes rule, given the host opened door 3, the probability the prize is behind door 2 becomes $2/3$.
    * **Conclusion:** You should switch.

### Bayes Classifier
* **Theorem:** The Bayes classifier, $h^*(x) = \text{argmax}_y P(Y=y|X=x)$, is optimal and achieves the lowest possible error (Bayes error).
* **Challenge:** Estimating the full joint probability is difficult due to the curse of dimensionality (complex models have high variance with limited data).

---

## 7. Naïve Bayes Classifier

### The Assumption
* Features are assumed to be **conditionally independent** given the class $Y$.
$$P(X_1...X_n|Y) = \prod_{i} P(X_i|Y)$$
* This drastically reduces the number of parameters to estimate (from $2^n$ to $2n$ for binary features).

### The Classifier
* **Decision Rule:**
$$h_{NB}(x) = \operatorname*{argmax}_{y} P(y) \prod_{i} P(x_i|y)$$
* **Implementation:** Often implemented using the sum of logs to avoid underflow.
* **Parameter Estimation:** Parameters (Class-Prior and Likelihoods) are estimated using **Maximum Likelihood Estimation (MLE)** based on counts in the training data.
* **Performance:** Often works well in practice even when the independence assumption is violated.

---

## 8. Performance Evaluation Metrics

### Classification Metrics
* **Confusion Matrix:**
    
    A table showing True Positives (TP), False Positives (FP), True Negatives (TN), and False Negatives (FN).
* **Accuracy:** Correct predictions / Total predictions.
* **Error Rate:** Wrong predictions / Total predictions.
* **Precision:** $TP / (TP + FP)$.
* **Recall (TPR):** $TP / (TP + FN)$.
* **False Positive Rate (FPR):** $FP / (FP + TN)$.
* **F-Score:** Harmonic mean of precision and recall ($F_1$ score uses $\beta=1$).
* **Precision-Recall Curve:** Plots Precision vs Recall; area under curve (AP) indicates performance.
* **ROC Curve:** Plots TPR vs FPR; Area Under Curve (AUC) indicates performance.

### Detection Metrics
* **Intersection over Union (IoU):** Also known as Jaccard index. A detection is considered correct if $IoU > 0.5$.

### Regression Metrics
* **Mean Squared Error (MSE):** Average of squared differences between predicted and actual values.
* **Mean Absolute Error (MAE):** Average of absolute differences.
* **Kendall Tau:** Ordinal measure checking if the system predicts the correct *order* of difficulty/values compared to ground truth (based on concordant vs discordant pairs).