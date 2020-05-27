Folders description :
	- Data_220_quantized and Data_221_quantized
	  Contains, for each parcel, an excel file with graph with LogRank LogCounter Rank Counter Images as columns.
	  The graph LogRank/LogCounter contain a regression line, R², and linear equation.
	  A word document also contain the graph LogRank/LogCounter of each parcels for better visibility.
	- Image_Processing 
	  C++ code to exctract 3*3px on 3 dates pattern and count them
	  And create data to analyse 2 slopes and nb_pattern
	- Kmeans_LogisticRegression
	  Python scripts to classify with SVM and Logistic regression (Main.py), apply Kmeans (Kmeans.py), to compare histograms (hist_comparison.py) and to classify orchards (Classification_parcels.py)
	- Parcels contains all images of the parcels (Intensive orchard and Traditional orchard)
	- data is a dataframe containing data of all parcels 
	- data_0_1 : pattern to use for Kmeans
	- data_histo_comparison : list of parcels to use for graph comparison
	- data_kmeans_test : list of parcels to use for classification  
	- data_slopes contains two slopes and the number of pattern for each parcel
	- Analysis is the results of data_slopes classification and bar plot classification
	- Analysis_Regression_220_and_221 is a compilation of all regression line data of all parcels and some statistics


Part 1 : Slopes analysis
1) Use the code in Image_Processing to extract slope 1, slope 2, and nb_pattern for each parcel
2) Open data_slopes.csv and save as .xlxs
3) Use the script in Kmeans_LogisticRegression classify parcel with Logistic Regression and SVM (with Balanced Data)
Results can be found in data_slopes_analysis

Part 2 : Kmeans and Classification
1) Generate data_0_1, data_histo_comparison and data_kmeans_test with the code in Image_Processing
2) Generate csv for parcels in data_histo_comparison and data_kmeans_test, convert them to xlxs format and move them into Projet_ter\Kmeans_LogisticRegression\classification_data and Projet_ter\Kmeans_LogisticRegression\hist_comparison_data
3) Use Kmeans algorithm in Kmeans_LogisticRegression
4) Open kmeans_clusters.csv inside Kmeans_LogisticRegression and save as .xlxs 
5) Use hist_comparison to generate graph in hist_comparison_fig inside Kmeans_LogisticRegression
6) Use Classification_parcels.py to classify and print results 


- Copy the Parcels forlders inside Projet_ter/
- Modify all path like this one : Projet_ter\Image_Processing/Pattern.cpp to match yours
- You may need to install xlrd in Projet_ter\Kmeans_LogisticRegression\venv\Scripts by opening the command prompt at this location  and using : pip install xlrd 