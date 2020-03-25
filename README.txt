Folders description :
	- Data_220_quantized and Data_221_quantized
	  Contains, for each parcel, an excel file with graph with LogRank LogCounter Rank Counter Images as columns.
	  The graph LogRank/LogCounter contain a regression line, R², and linear equation.
	  A word document also contain the graph LogRank/LogCounter of each parcels for better visibility.
	- Image_Processing 
	  C++ code to exctract 3*3px on 3 dates and count them
	- Kmeans_LogisticRegression
	  Python script to apply Kmeans and a Logistic Regression
	  Contains a graph to find the best K and a graph for the counters of patterns  
	- Parcels
	Contains all images of the parcels (Intensive orchard and Traditional orchard)
	- data is a dataframe containing data of all parcels 
	- Regression_220_and_221 is a compilation of all regression line data of all parcels and some statistics

1) Copy the Parcels forlders inside Projet_ter/
2) Modify line 4 and 156 of Projet_ter\Image_Processing/Pattern.cpp to match your path
3) install xlrd in Projet_ter\Kmeans_LogisticRegression\venv\Scripts by opening the command prompt at this location 
and using : pip install xlrd 