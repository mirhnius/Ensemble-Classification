# Ensemble-Classification
Ensemble Classification is a way of generating various base classifiers from which a new classifier is derived which performs better than any constituent classifier. These base classifiers may differ in the algorithm used, hyper parameters, representation or the training set.

This project explores a top-down design of the implementation of Ensemble Classificationw which is one of the common methods in machine learning. As one of the most widely used branches of artificial intelligence, machine learning sets and explores methods and algorithms based on which computers and systems are able to learn and predict.

In Machine Learning, models whose attemps to predict a type or a feature, are described using a number of numerical and measurable features in the form of feature vectors. There are many algorithms for classification that can assign a score to each calss using a linear function. This scoring is done by multiplying the feature vector by the weight vector and adding by Bias (a weight vector with a weight equal to one) for each of the features. The predicted class is has the highest score among the other classes. 

This function is described below:

![image](https://user-images.githubusercontent.com/40741680/125419653-f15f16ac-b011-45ed-ab31-4d40eec70354.png)


The goal of ensemble methods is to combine the predictions of several base estimators built with a given learning algorithm in order to improve generalizability/robustness over a single estimator.
<p align="center">
  
<img src="https://github.com/niushamir/Ensemble-Classification/blob/main/Ensemble-Classification%20diagram.png" width="550" height="300">
 </p>

* ### Implementation procedure
1. Linear classifiers extract the corresponding weight vectors from a file.
2. The class for each sample in the validation data set file is then determined by all linear classifiers. This step is performed by calculating the internal multiplication of the weight vectors of each feature with the feature vector of the sample.
3. After completing the linear category operation on the validation data set, the class for each sample is predicted by calculating the maximum repetition of a class for the sample (**Voting**).
4. After the prediction operation is completed, the accuracy of the Ensemble Classification is measured. This is done by comparing forecast information with validation data labels.
