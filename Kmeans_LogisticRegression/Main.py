import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report, recall_score, confusion_matrix
from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler
from imblearn.over_sampling import SMOTE
from imblearn.under_sampling import NearMiss
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)

#Function to evaluate classification model
def print_report(y_test,y_pred):
    print("Classification report : ")
    print(classification_report(y_test, y_pred))
    print("Confusion matrix : ")
    print(confusion_matrix(y_test, y_pred))

#Data Slopes analysis
print("Data Slopes : \n")
#Descriptive Statistics
data=pd.read_excel('C:/Users/lilia/github/Projet_ter/data_slopes.xlsx',error_bad_lines=False)
print(data.head())
print(data.info())
plt.scatter(data["p1"],data["p2"],c=data["classe"])
plt.show()

#Modify data to test with differents features
data=data.drop(['p1','p2'],axis=1)

#Class repartition
sns.set_style('darkgrid')
sns.countplot(x='classe', data=data, palette='RdBu_r')
plt.show()

#Smote data creation
X = data.loc[:, data.columns != 'classe']
y = data['classe']
sm = SMOTE(sampling_strategy='auto', random_state=42)
X_smote, y_smote = sm.fit_resample(X, y)

sns.set_style('darkgrid')
sns.countplot(x=y_smote, data=X_smote, palette='RdBu_r')
plt.show()

#Nearmiss data creation
nm1 = NearMiss(version=1)
X_nm, y_nm = nm1.fit_resample(X, y)

sns.set_style('darkgrid')
sns.countplot(x=y_nm, data=X_nm, palette='RdBu_r')
plt.show()



#Logistic Regression
print("LOGISTIC REGRESSION \n")
#Normal model
X_train, X_test, y_train, y_test = train_test_split(data.loc[:, data.columns != 'classe'], data['classe'], test_size=0.30, random_state=10)
logmod = LogisticRegression()
logmod.fit(X_train, y_train)
Pred=logmod.predict(X_test)
print("Logistic Regression - Normal Model : ")
print_report(y_test,Pred)
#SMOTE model
X_train, X_test, y_train, y_test = train_test_split(X_smote, y_smote, test_size=0.30, random_state=10)
logmod = LogisticRegression()
logmod.fit(X_train, y_train)
smote_prediction=logmod.predict(X_test)
print("Logistic Regression - Smote Model : ")
print_report(y_test,smote_prediction)
#Nearmiss model
X_train, X_test, y_train, y_test = train_test_split(X_nm, y_nm, test_size=0.30, random_state=10)
logmod = LogisticRegression()
logmod.fit(X_train, y_train)
nm_prediction=logmod.predict(X_test)
print("Logistic Regression - Nearmiss Model : ")
print_report(y_test,nm_prediction)


#Normal SVM
print("SVM")
X_train, X_test, y_train, y_test = train_test_split(data.loc[:, data.columns != 'classe'], data['classe'], test_size=0.30, random_state=10)
sc = StandardScaler()
X_train=sc.fit_transform(X_train)
X_test=sc.transform((X_test))
svm = SVC(kernel='linear')
svm.fit(X_train, y_train)
Pred_svm = svm.predict(X_test)
print("SVM - Normal Model : ")
print_report(y_test,Pred_svm)
#SMOTE SVM
X_train, X_test, y_train, y_test = train_test_split(X_smote, y_smote, test_size=0.30, random_state=10)
sc = StandardScaler()
X_train=sc.fit_transform(X_train)
X_test=sc.transform((X_test))
svm = SVC(kernel='linear')
svm.fit(X_train, y_train)
smote_prediction_svm=svm.predict(X_test)
print("SVM - Smote Model : ")
print_report(y_test,smote_prediction_svm)
#Nearmiss SVM
X_train, X_test, y_train, y_test = train_test_split(X_nm, y_nm, test_size=0.30, random_state=10)
sc = StandardScaler()
X_train=sc.fit_transform(X_train)
X_test=sc.transform((X_test))
svm = SVC(kernel='linear')
svm.fit(X_train, y_train)
nm_prediction_svm=svm.predict(X_test)
print("SVM - Smote Model : ")
print_report(y_test,nm_prediction_svm)