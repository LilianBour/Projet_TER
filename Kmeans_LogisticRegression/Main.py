import string
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn import metrics
from sklearn.cluster import KMeans
from sklearn.ensemble import AdaBoostClassifier
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, recall_score, confusion_matrix
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler

pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)

"""
#Statistic
data=pd.read_excel('C:/Users/lilia/github/Projet_ter/data.xlsx',error_bad_lines=False)
print(data.head())
print(data.info())

#Class repartition
sns.set_style('darkgrid')
sns.countplot(x='Class', data=data, palette='RdBu_r')
plt.show()
#TODO data not equal

#Number of pattern histo
sns.distplot(data['Counter'].dropna(), kde=False, bins=650, color='Blue')
plt.show()

#Convert Pattern to list of int in new col Pattern2 + add a new int col for each of the 27 values
newcol =[[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[],[]]
pat2 = []
names =['p1','p2','p3','p4','p5','p6','p7','p8','p9','p10','p11','p12','p13','p14','p15','p16','p17','p18','p19','p20','p21','p22','p23','p24','p25','p26','p27',]
for j,row in data.iterrows():
    b = list(data.iloc[j, 4].split(','))
    b.pop(-1)
    for i in range(len(b)):
        b[i] = int(b[i])
        newcol[i].append(int(b[i]))
    pat2.append(b)
data['Pattern2']=pd.Series(pat2)
for i in range(len(names)) :
    data[names[i]]=pd.Series(newcol[i])
print(data.head())
print(data.info())

#Correlation matrix
print(data.count())





#Logistic Regression
#Testsplit
df2=data.drop(['Pattern','Pattern2'],axis=1)
print(df2.iloc[:,7:].head())
X_train, X_test, y_train, y_test = train_test_split(df2.iloc[:,7:], data['Class'], test_size=0.30, random_state=42)
#fit the model
logmod = LogisticRegression()
logmod.fit(X_train, y_train)
#predictions
Pred=logmod.predict(X_test)
print(classification_report(y_test,Pred))



#Kmeans
x=df2.iloc[:,7:]
#KMEANS

#finding the best k
   cost=[]
for i in range(1,1001):
    print((i/1001)*100,"%\n")
    km = KMeans(n_clusters = i, n_jobs = 4, random_state=21)
    km.fit(x)
    #calculates squared error for the clustered points
    cost.append(km.inertia_)
print("Done")
# plot the cost against K values
plt.plot(range(1, 1001), cost, color ='b', linewidth ='4')
plt.xticks(np.arange(1,1001+1, 50.0))
plt.xlabel("Value of K")
plt.ylabel("Sqaured Error (=Cost)")
plt.show()


#Best K is approximately 50 (See Kmeans graph)
k=50
y=data.iloc[:,5]
print("Optimal k :",k)
km = KMeans(n_clusters=k, n_jobs=4, random_state=21)
km.fit(x)
centers = km.cluster_centers_
#Print all cluster centers
for i in centers:
    print(i)
"""

############### data_slopes ##########################
print("Data Slopes : \n")
#Statistic
data=pd.read_excel('C:/Users/lilia/github/Projet_ter/data_slopes.xlsx',error_bad_lines=False)
print(data.head())
print(data.info())

#Class repartition
sns.set_style('darkgrid')
sns.countplot(x='classe', data=data, palette='RdBu_r')
plt.show()
#TODO data not equal


#Logistic Regression
print("LOGISTIC REGRESSION \n")
#Testsplit
X_train, X_test, y_train, y_test = train_test_split(data, data['classe'], test_size=0.50, random_state=10)
#fit the model
logmod = LogisticRegression()
logmod.fit(X_train, y_train)
#predictions
Pred=logmod.predict(X_test)
print(classification_report(y_test,Pred))
print("Confusion matrix:\n",confusion_matrix(y_test, Pred))


#Adaptive Boosting
print("ADAPTIVE BOOSTING")
dt1 = DecisionTreeClassifier(criterion="gini",splitter="best")
AdaBoost=AdaBoostClassifier(base_estimator=dt1,n_estimators=400,learning_rate=1)
boost_model=AdaBoost.fit(X_train,y_train)
y_pred1 = boost_model.predict(X_test)
print(classification_report(y_test,y_pred1))
print("Confusion matrix:\n",confusion_matrix(y_test, y_pred1))


#SVM
print("SVM")
sc = StandardScaler()
X_train=sc.fit_transform(X_train)
X_test=sc.transform((X_test))
svm = SVC(kernel='linear')
svm.fit(X_train, y_train)
y_pred2 = svm.predict(X_test)
print(classification_report(y_test,y_pred2))
print("Confusion matrix:\n",confusion_matrix(y_test, y_pred2))

#Kmeans
x=data.iloc[:,0:2]
y=data.iloc[:,3]
#KMEANS
print("KMEANS")
#finding the best k
cost=[]
for i in range(1,29):
    km = KMeans(n_clusters = i, n_jobs = 4, random_state=21)
    km.fit(x)
    #calculates squared error for the clustered points
    cost.append(km.inertia_)
# plot the cost against K values
plt.plot(range(1, 29), cost, color ='b', linewidth ='4')
plt.xticks(np.arange(1,29+1, 1.0))
plt.xlabel("Value of K")
plt.ylabel("Sqaured Error (=Cost)")
plt.show()


#Best K is approximately 50 (See Kmeans graph)
k=2
print("Optimal k :",k)
km = KMeans(n_clusters=k, n_jobs=4, random_state=21)
km.fit(x)
centers = km.cluster_centers_
#Print all cluster centers
for i in centers:
    print(i)

#Graph 1
new_labels = km.labels_
fig, axes = plt.subplots(1, 2, figsize=(16, 8))
axes[0].scatter(x.iloc[:, 0], data.iloc[:, 1], c=y, cmap='gist_rainbow', edgecolor='k', s=150)
axes[1].scatter(x.iloc[:, 0], data.iloc[:, 1], c=new_labels, cmap='jet', edgecolor='k', s=150)
axes[0].set_xlabel('Slope 1', fontsize=18)
axes[0].set_ylabel('Slope 2', fontsize=18)
axes[1].set_xlabel('Slope 1', fontsize=18)
axes[1].set_ylabel('Slope 2', fontsize=18)
axes[0].tick_params(direction='in', length=10, width=5, colors='k', labelsize=20)
axes[1].tick_params(direction='in', length=10, width=5, colors='k', labelsize=20)
axes[0].set_title('Actual', fontsize=18)
axes[1].set_title('Predicted', fontsize=18)
plt.show()

#Graph 2
new_labels = km.labels_
fig, axes = plt.subplots(1, 2, figsize=(16, 8))
axes[0].scatter(x.iloc[:, 0], data.iloc[:, 2], c=y, cmap='gist_rainbow', edgecolor='k', s=150)
axes[1].scatter(x.iloc[:, 0], data.iloc[:, 2], c=new_labels, cmap='jet', edgecolor='k', s=150)
axes[0].set_xlabel('Slope 1', fontsize=18)
axes[0].set_ylabel('Nb_pattern', fontsize=18)
axes[1].set_xlabel('Slope 1', fontsize=18)
axes[1].set_ylabel('Nb_pattern', fontsize=18)
axes[0].tick_params(direction='in', length=10, width=5, colors='k', labelsize=20)
axes[1].tick_params(direction='in', length=10, width=5, colors='k', labelsize=20)
axes[0].set_title('Actual', fontsize=18)
axes[1].set_title('Predicted', fontsize=18)
plt.show()

#Graph 3
new_labels = km.labels_
fig, axes = plt.subplots(1, 2, figsize=(16, 8))
axes[0].scatter(x.iloc[:, 1], data.iloc[:, 2], c=y, cmap='gist_rainbow', edgecolor='k', s=150)
axes[1].scatter(x.iloc[:, 1], data.iloc[:, 2], c=new_labels, cmap='jet', edgecolor='k', s=150)
axes[0].set_xlabel('Slope 2', fontsize=18)
axes[0].set_ylabel('Nb_pattern', fontsize=18)
axes[1].set_xlabel('Slope 2', fontsize=18)
axes[1].set_ylabel('Nb_pattern', fontsize=18)
axes[0].tick_params(direction='in', length=10, width=5, colors='k', labelsize=20)
axes[1].tick_params(direction='in', length=10, width=5, colors='k', labelsize=20)
axes[0].set_title('Actual', fontsize=18)
axes[1].set_title('Predicted', fontsize=18)
plt.show()