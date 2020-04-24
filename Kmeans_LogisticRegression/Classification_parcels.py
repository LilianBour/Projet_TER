import pandas as pd
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import train_test_split
from sklearn.metrics import classification_report, recall_score, confusion_matrix
import math
from imblearn.under_sampling import NearMiss
from sklearn.neighbors import KNeighborsClassifier
import matplotlib.pyplot as plt
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)

#Function to evaluate classification model
def print_report(y_test,y_pred):
    print("Classification report : ")
    print(classification_report(y_test, y_pred))
    print("Confusion matrix : ")
    print(confusion_matrix(y_test, y_pred))

#Import normalized data
train_data=pd.read_excel('classification_parcels_normalized_data.xlsx')
print(train_data.head())
print(train_data.info())

#Import Test and Classify test
numbers_1=['220','221']
numbers_2_0=['1316','1320','1333','1338','1339','1340','1533','1535','1537','1538','1539']
numbers_2_1=['1387','1388','1389','1390','1391','1392','1393','1394','1395','1404','1409','1416','1417','1433','1439','1442','1443','1444','1481','1482','1487','1489','1491','1494','1525']
#Import Cluster centers
cluster=pd.read_excel('kmeans_clusters.xlsx')
k=len(cluster.columns)
clusters_k= [[] for i in range(k)]
clusters_names=[]
for i in range(len(cluster.columns)):
    clusters_names.append(int(cluster.columns[i].replace('C','')))
for j in range(k):
    clusters_k[j] = cluster[cluster.columns[j]].values
#Set matrix for y_data
test_data=[[], []]
#Loop through all parcels
for number_1 in numbers_1:
    if number_1 == "220":
        for number_2_0 in numbers_2_0:
            # Get patterns
            patterns_attribution = [0 for i in range(k)]
            data = pd.read_excel("C:/Users/lilia/github/Projet_ter/Kmeans_LogisticRegression/classification_data/Parcels_" + number_1 + "_quantized_" + number_2_0 + ".0.xlsx",error_bad_lines=False)
            # Converting patterns to list of list
            pat = data["pattern"].values
            patterns = [[], []]
            for i in pat:
                list_splited = i.split(",")
                new_list = []
                for j in range(len(list_splited) - 1):
                    new_list.append(int(list_splited[j]))
                patterns.append((new_list))
            del patterns[0]
            del patterns[0]
            #Test image's patterns
            for pat in range(len(patterns)):
                distance_clusters = []
                for cluster in clusters_k:
                    ED = 0
                    # Euclidean distance
                    for l in range(len(patterns[pat])):
                        ED = ED + (cluster[l] - patterns[pat][l]) ** 2
                    ED = math.sqrt(ED)
                    # Stock value in distance_clusters
                    distance_clusters.append((ED))
                # Get position of min in distance_clusters
                # Append pat in clusters_component at position of min
                patterns_attribution[distance_clusters.index(min(distance_clusters))]=patterns_attribution[distance_clusters.index(min(distance_clusters))]+1
            # Normalize data
            mini = min(patterns_attribution)
            maxi = max(patterns_attribution)
            for i in range(len(patterns_attribution)):
                patterns_attribution[i] = (patterns_attribution[i] - mini) / (maxi - mini)

            test_data_local=[]
            for i in patterns_attribution:
                test_data_local.append(i)
            test_data_local.append(0)
            test_data.append(test_data_local)

    if number_1=="221":
        for number_2_1 in numbers_2_1:
            # Get patterns
            patterns_attribution = [0 for i in range(k)]
            data = pd.read_excel("C:/Users/lilia/github/Projet_ter/Kmeans_LogisticRegression/classification_data/Parcels_" + number_1 + "_quantized_" + number_2_1 + ".0.xlsx",error_bad_lines=False)
            # Converting patterns to list of list
            pat = data["pattern"].values
            patterns = [[], []]
            for i in pat:
                list_splited = i.split(",")
                new_list = []
                for j in range(len(list_splited) - 1):
                    new_list.append(int(list_splited[j]))
                patterns.append((new_list))
            del patterns[0]
            del patterns[0]
            #Test image's patterns
            for pat in range(len(patterns)):
                distance_clusters = []
                for cluster in clusters_k:
                    ED = 0
                    # Euclidean distance
                    for l in range(len(patterns[pat])):
                        ED = ED + (cluster[l] - patterns[pat][l]) ** 2
                    ED = math.sqrt(ED)
                    # Stock value in distance_clusters
                    distance_clusters.append((ED))
                # Get position of min in distance_clusters
                # Append pat in clusters_component at position of min
                patterns_attribution[distance_clusters.index(min(distance_clusters))] = patterns_attribution[distance_clusters.index(min(distance_clusters))] + 1
            # Normalize data
            mini = min(patterns_attribution)
            maxi = max(patterns_attribution)
            for i in range(len(patterns_attribution)):
                patterns_attribution[i] = (patterns_attribution[i] - mini) / (maxi - mini)

            test_data_local = []
            for i in patterns_attribution:
                test_data_local.append(i)
            test_data_local.append(1)
            test_data.append(test_data_local)

del test_data[0]
del test_data[0]
clusters_names.append('classe')
test_df = pd.DataFrame(test_data, columns=clusters_names)
#Set X_train_X_test,y_train,y_test
X_train=train_data.loc[:, train_data.columns != 'classe']
y_train=train_data.loc[:, train_data.columns == 'classe']
X_test=test_df.loc[:, test_df.columns != 'classe']
y_test=test_df['classe']

#Bad Result without balanced data
#[[ 0 11]
#[ 1 24]]

#Balancing data
nm1 = NearMiss(version=1)
X_train, y_train = nm1.fit_resample(X_train, y_train)
#Result with nearmiss
#[[ 9  2]
# [13 12]]
#Try to balance data before doing Hist, if results are still bad, try to balance data before Kmeans


#Logistic Regression
print("LOGISTIC REGRESSION \n")
logmod = LogisticRegression()
logmod.fit(X_train, y_train)
L_pred=logmod.predict(X_test)
print("Logistic Regression : ")
print_report(y_test,L_pred)
#Plot Logistic Reg

#K_neighbors (k=sqrt(n))
knn = KNeighborsClassifier(n_neighbors = int(math.sqrt(len(X_test+X_train))))
knn.fit(X_train,y_train.values.ravel())
K_pred=logmod.predict(X_test)
print("K_neighbors : ")
print_report(y_test,K_pred)
#Plot K neihbors

