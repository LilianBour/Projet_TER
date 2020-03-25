import string
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.cluster import KMeans
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)


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
"""cost=[]
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
"""

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
