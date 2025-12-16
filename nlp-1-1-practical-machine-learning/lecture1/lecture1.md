# Introduction to Machine Learning: Course Overview and Basic Concepts

## 1. Administrative Information

### Instructors
* **Lectures:** Radu Ionescu 
* **Labs:**
    * Adriana Costache
    * Silviu Gheorghe 
    * Mădălina Poșchină 
    * Vlad Hondru 

### Course Resources
* **Website:** `https://practical-ml-fmi.github.io/ML/`
* **Team Code:** 1jr5sik

### Grading System
The final grade is composed of three parts, and passing the minimum grade for each is required.

1.  **Project 1 (20%):**
    * Involves participating in a Kaggle competition launched during the semester.
    * **Grading:** Proportional to model accuracy ranking.
        * Top 1-20: up to 2 points
        * Top 21-50: up to 1.8 points
        * Top 51-80: up to 1.6 points
        * Top 81-100: up to 1.4 points
        * Top 101-120: up to 1.2 points
        * Others: up to 1 point

2.  **Project 2 (20%):**
    * Focuses on comparing two unsupervised approaches on a specific dataset.
    * **Constraints:** Dataset overlap among students is not allowed.

3.  **Oral Exam (60%):**
    * There is no paper exam.
    * Demonstrating knowledge of machine learning methods is mandatory to pass.

**Project Submission Guidelines:**
* Projects are individual.
* Methods and datasets must be chosen beforehand.
* Submission must include Python code (only `.py` files) and a PDF report.
* The report should contain a dataset description (for Project 2), method descriptions, results (figures/tables), comments, and a conclusion.
* If the oral exam is failed, projects must be redone.

### Bonus Points
* **Lectures:** Up to 1 bonus point added to the final grade. Points are awarded based on Kahoot rankings (Top 3 get up to 0.3 points).
* **Labs:** Up to 1 bonus point added to the final grade. The first student to solve an exercise gets 0.2 points (max 0.4 per lab).

### Collaboration and Plagiarism
* Each student must write their own code.
* Copying code from web sources is strictly prohibited and will be checked automatically and manually.
* Plagiarism is not tolerated.

---

## 2. Introduction to AI and Machine Learning

### Definitions
* **Artificial Intelligence (AI):** The goal is to build systems capable of reaching human intelligence levels.
    * **Turing Test:** A computer possesses human-level intelligence if a human interrogator cannot distinguish it from a human subject.
* **Machine Learning (ML):** A field of study giving computers the ability to learn from observations without explicit programming.
    * **Tom Mitchell's Definition:** A program learns from experience *E* regarding task *T* and performance *P* if performance at *T* improves with *E*.
    * **Key Concept:** ML involves recognizing complex patterns and making intelligent decisions based on data.

### Historical Context
* **1956:** AI was born at the Dartmouth Summer Research Project, proposed by John McCarthy, based on the conjecture that learning can be simulated by machines.
* **1960s-1980s:** The "AI Winter".
* **1990s:** Neural networks gained prominence due to backpropagation.
* **2000s:** Kernel methods dominated due to neural network training instability.
* **2010s:** Neural networks returned via Deep Learning.

**Factors for Modern Success:**
* Increased compute power.
* Availability of more data.
* Improved algorithms and models.

---

## 3. The Machine Learning Framework

### Core Components
Every machine learning algorithm consists of three components:
1.  **Representation:** The model class.
2.  **Evaluation:** The objective function.
3.  **Optimization:** The method to find the best model parameters.

### The Learning Task
* **Goal:** Learn a mapping function $f: X \rightarrow Y$ from input $X$ to output $Y$.
* **Process:**
    * **Input:** Data pairs $(x_1, y_1), ..., (x_N, y_N)$.
    * **Model:** A hypothesis $g: X \rightarrow Y$ that approximates the true target function.

---

## 4. Learning Paradigms

### A. Supervised Learning
The system learns from a set of labeled training samples.
* **Canonical Problems:** Classification and Regression.
* **Examples:**
    * **Handwritten Digit Recognition:** Classifying MNIST images into digits 0-9.
    * **Face Detection:** Classifying image regions as "face" or "not-face".
    * **Spam Detection:** Classifying emails using features like word frequencies.
    * **Stock Price Prediction:** Predicting future prices (Regression).
* **Models:** Naive Bayes, k-NN, Decision Trees, Random Forests, SVM, Neural Networks.

### B. Unsupervised Learning
The system learns from an unlabeled training set.
* **Canonical Problems:** Clustering and Dimensionality Reduction.
* **Examples:**
    * **Clustering:** Grouping images based on similarity.
    * **Feature Learning:** Using auto-encoders for tasks like abnormal event detection.
    * **Phylogenetic Trees:** Clustering species based on DNA.
* **Models:** K-means, DBScan, PCA, t-SNE, HMMs.

### C. Reinforcement Learning (RL)
The system learns intelligent behavior using a reinforcement signal (reward).
* **Key Characteristics:**
    * Rewards may be delayed (not immediate).
    * Data is sequential, and actions influence future data.
    * Often formalized as a Markov Decision Process (MDP) involving observations, actions, and rewards.
* **Examples:**
    * **AlphaGo:** Learning to play Go.
    * **Robotics:** Learning to ride a bike.
    * **Gaming:** Learning to play Pong.

### D. Other Paradigms
* **Semi-supervised Learning:** Uses partially annotated training data.
* **Active Learning:** Selects specific samples from an unlabeled pool for annotation to improve the model efficiently.
* **Transfer Learning:** Adapts a model from one task/domain to another.
    * Includes **Zero-shot learning**, where models recognize classes not seen during training.

---

## 5. Ethics in AI
* **Ethical Considerations:** The application of AI raises questions about what is ethical, illustrated by the "Trolley paradox".
* **Moral Machine:** A platform for exploring these dilemmas (`http://moralmachine.mit.edu`).

---

## 6. Bibliography
* Hastie, Tibshirani, Friedman, *The Elements of Statistical Learning*, Springer.
* Duda, Hart, Stork, *Pattern Classification*, Second Edition.
* Géron, *Hands-On Machine Learning with Scikit-Learn & TensorFlow*, O'Reilly.
* Ionescu, Popescu, *Knowledge Transfer between Computer Vision and Text Mining*, Springer.