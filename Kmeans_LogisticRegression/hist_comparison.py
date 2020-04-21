import string
import pandas as pd
import random
import math
import numpy as np
import matplotlib.pyplot as plt
import statistics
import csv
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)


cluster=pd.read_excel('kmeans_clusters.xlsx')
k=len(cluster.columns)
clusters_k= [[] for i in range(k)]
clusters_names=cluster.columns
for j in range(k):
    clusters_k[j] = cluster[cluster.columns[j]].values

for i in range(len(clusters_k)):
    print("Cluster ",i,end=' : ')
    for j in clusters_k[i] :
        print(j,end=' ')
    print("\n")

#Hist
#Extract list of img from csv
#Loop through all parcels
patterns_attribution=  [0 for i in range(k)]
data=pd.read_excel('C:/Users/lilia/github/Projet_ter/test_kemans1.xlsx',error_bad_lines=False)
#Converting patterns to list of list
pat = data["pattern"].values
patterns=[[],[]]
for i in pat :
    list_splited = i.split(",")
    new_list = []
    for j in range(len(list_splited)-1):
        new_list.append(int(list_splited[j]))
    patterns.append((new_list))
del patterns[0]
del patterns[0]



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

for i in patterns_attribution:
    print(i)
plt.bar(clusters_names,patterns_attribution,color='g',edgecolor='k')
plt.show()
