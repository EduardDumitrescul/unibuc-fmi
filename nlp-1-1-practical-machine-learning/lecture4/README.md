# Decision Trees and Random Forests

## 1. Instructor Information
* **Lecturer:** Radu Ionescu
* **Institution:** Faculty of Mathematics and Computer Science, University of Bucharest

---

## 2. Decision Trees

### Definition
* A tree-like model that illustrates a series of events leading to certain decisions.
* **Structure:**
    * **Nodes:** Represent a test on a specific attribute (e.g., "Is the applicant a student?").
    * **Branches:** Represent the outcome of the test (e.g., "Yes" or "No").
    * **Leaves:** Represent the final decision or class label.

### Application Example: Loan Approval
* **Goal:** Decide "Who to loan?" based on attributes.
* **Attributes:**
    * **Age:** (e.g., <=30, 31-40, >40)
    * **Income:** (High, Medium, Low)
    * **Student Status:** (Yes, No)
    * **Credit Record:** (Fair, Excellent)
* **Process:** The tree splits the population based on these attributes to reach a decision (Yes/No).

---

## 3. Ensemble Learning

### Overview
* **Definition:** Methods that combine multiple learning algorithms to obtain better predictive performance than could be obtained from any of the constituent learning algorithms alone.

### Common Methods
* **Bagging (Bootstrap Aggregating):**
    * Trains multiple models on random subsets of the training data (sampling with replacement).
    * Helps reduce variance and avoid overfitting.
* **Random Subspace Method:**
    * Trains multiple models on random subsets of the features.
* **Boosting:**
    * Trains models iteratively.
    * New models focus on the mistakes of previous models by increasing the weight of misclassified samples.
    * turns weak learners into strong learners.

---

## 4. Random Forests

### Concept
* An ensemble learning method that constructs a multitude of decision trees at training time.
* **Mechanism:**
    * It combines **Bagging** (sampling data) and the **Random Subspace Method** (sampling features).
    * Each tree is trained on a random subset of data and considers a random subset of features for splitting at each node.
* **Advantage:** They rectify the overfitting problem common to individual decision trees.

---

## 5. Python Implementation (Scikit-Learn)

### Decision Tree Classifier
* **Library:** `sklearn.tree.DecisionTreeClassifier`
* **Key Parameters:**
    * `criterion`: Measure of split quality (e.g., "gini", "entropy").
    * `max_depth`: Maximum depth of the tree.
    * `min_samples_leaf`: Minimum samples required at a leaf node.
    * `min_impurity_split`: Threshold for early stopping based on impurity.
* **Usage Notes:**
    * `clf.fit(X, y)` trains the model.
    * Scikit-learn implementation currently supports numerical attributes. Categorical attributes must be encoded (e.g., using `LabelEncoder` or `OneHotEncoder`).
    * `clf.feature_importances_` reveals the importance of each feature.
    * `clf.tree_` allows access to the underlying tree object.

### Random Forest Classifier
* **Library:** `sklearn.ensemble.RandomForestClassifier`
* **Key Parameter:**
    * `n_estimators`: The number of trees in the forest (e.g., `n_estimators = 20`).