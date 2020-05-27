import pandas as pd
import math
import matplotlib.pyplot as plt
pd.set_option('display.max_rows', 500)
pd.set_option('display.max_columns', 500)
pd.set_option('display.width', 1000)

#Import cluster centers
cluster=pd.read_excel('kmeans_clusters_100.xlsx')
k=len(cluster.columns)
clusters_k= [[] for i in range(k)]
clusters_names=[]
for i in range(len(cluster.columns)):
    clusters_names.append(int(cluster.columns[i].replace('C','')))
for j in range(k):
    clusters_k[j] = cluster[cluster.columns[j]].values

#Hist_comparison
numbers_1=['220','221']
numbers_2_0=['1195','1196','1197','1198','1199','1200','1201','1202','1203','1204','1228']
numbers_2_1=['1353','1354','1355','1359','1360','1361','1363','1365','1366','1367','1368','1370','1371','1373','1375','1376','1377','1378','1379','1380','1381','1382','1383','1384','1385']


f = open('classification_parcels_normalized_data.csv','w')

for i in clusters_names:
    f.write(str(i))
    f.write(";")
f.write("classe")
f.write("\n")

#Loop through all parcels
for number_1 in numbers_1:
    if number_1 == "220":
        for number_2_0 in numbers_2_0:
            # Get patterns
            patterns_attribution = [0 for i in range(k)]
            data = pd.read_excel(
                "C:/Users/lilia/github/Projet_ter/Kmeans_LogisticRegression/hist_comparison_data/Parcels_" + number_1 + "_quantized_" + number_2_0 + ".0.xlsx",
                error_bad_lines=False)
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
            sum_ = sum(patterns_attribution,patterns_attribution[0])
            for i in range(len(patterns_attribution)):
                patterns_attribution[i] = (patterns_attribution[i] / sum_)

            #Write on csv
            for i in patterns_attribution:
                f.write(str(i))
                f.write(";")
            f.write("0")
            f.write("\n")


            #Plot barplot for attribution in clusters and save it
            fig1, ax1 = plt.subplots()
            #ax1.hist(patterns_attribution,clusters_names[0:40], color='g', edgecolor='k',density=True)
            ax1.bar(clusters_names, patterns_attribution, color='g', edgecolor='k')
            ax1.set_ylim([0, 1.1])
            plt.title(number_1+'_'+number_2_0)
            fig1.savefig('C:/Users/lilia/github/Projet_ter/Kmeans_LogisticRegression/hist_comparison_fig/'+number_1+'_'+number_2_0)
            plt.close(fig1)

    if number_1=="221":
        for number_2_1 in numbers_2_1:
            # Get patterns
            patterns_attribution = [0 for i in range(k)]
            data = pd.read_excel(
                "C:/Users/lilia/github/Projet_ter/Kmeans_LogisticRegression/hist_comparison_data/Parcels_" + number_1 + "_quantized_" + number_2_1 + ".0.xlsx",
                error_bad_lines=False)
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
            sum_ = sum(patterns_attribution,patterns_attribution[0])
            for i in range(len(patterns_attribution)):
                patterns_attribution[i] = (patterns_attribution[i] / sum_)

            #Write on csv
            for i in patterns_attribution:
                f.write(str(i))
                f.write(";")
            f.write("1")
            f.write("\n")

            #Plot barplot for attribution in clusters and save it
            fig1, ax1 = plt.subplots()
            ax1.bar(clusters_names, patterns_attribution, color='g', edgecolor='k')
            ax1.set_ylim([0, 1.1])
            plt.title(number_1 + '_' + number_2_1)
            fig1.savefig('C:/Users/lilia/github/Projet_ter/Kmeans_LogisticRegression/hist_comparison_fig/' + number_1 + '_' + number_2_1)
            plt.close(fig1)

f.close()


