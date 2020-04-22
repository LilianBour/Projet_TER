import pandas as pd
import random
import math
import matplotlib.pyplot as plt
import statistics
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)


data=pd.read_excel('C:/Users/lilia/github/Projet_ter/data_0_1.xlsx',error_bad_lines=False)

#Descriptive Statistics
print(data.head())
print(data.info())

#Converting patterns to list of list of int
pat = data["Pattern"].values
patterns=[[],[]]
for i in pat :
    list_splited = i.split(",")
    new_list = []
    for j in range(len(list_splited)-1):
        new_list.append(int(list_splited[j]))
    patterns.append((new_list))
del patterns[0]
del patterns[0]



#Kmeans
k = 100
patterns_cluster= [0 for i in range(len(patterns))]

#Initlize k clusters with random numbers
clusters_names=["C"+str(i+1) for i in range(k)]
old_clusters_k =  [[] for i in range(k)]
clusters_k = [[random.randrange(0,255) for i in range(27)]for j in range(k)]
clusters_component = [[] for i in range(k)]

#Algorithm
turn = 0
verif = False
while verif == False :
    print ("TRUN : ",turn)
    # Assign to nearest k
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
        clusters_component[distance_clusters.index(min(distance_clusters))].append(patterns[pat])
        patterns_cluster[pat]=distance_clusters.index(min(distance_clusters))

    # New cluster values are means of cluster's components
    for cluster_nb in range(len(clusters_k)):
        if (len(clusters_component[cluster_nb])!=0):
            new_clusters = [0 for x in range(27)]
            for i in range(len(patterns[0])):
                for j in range(len(clusters_component[cluster_nb])):
                    new_clusters[i] = new_clusters[i] + clusters_component[cluster_nb][j][i]
                new_clusters[i] = new_clusters[i] / len(clusters_component[cluster_nb])
            old_clusters_k[cluster_nb] = clusters_k[cluster_nb]
            clusters_k[cluster_nb] = new_clusters

    #Check if new values and old values are the same
    for i in range(len(old_clusters_k)):
        for j in range(len(old_clusters_k[i])):
            if (abs(old_clusters_k[i][j] - clusters_k[i][j]) < 0.001):
                verif = True
            else:
                verif = False
    turn = turn +1

#Save cluster centers
f = open('kmeans_clusters.csv','w')
for i in clusters_names:
    f.write(i)
    f.write(";")
f.write("\n")
for j in range(len(clusters_k[0])) :
    for i in range(len(clusters_k)):
        f.write(str(clusters_k[i][j]))
        f.write(";")
    f.write("\n")
f.close()

#Plot clusters witd SD and Mean
plt.scatter([statistics.stdev(row) for row in patterns], [(sum(row)/len(row)) for row in patterns], c=patterns_cluster, cmap='gist_rainbow', edgecolor='k', s=150)
plt.show()

