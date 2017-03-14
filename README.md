# VARUS
Program to draw optimal samples out of RNA-Seq Libraries for the purpose of gene-finding.

# INSTALLATION
```sh
git clone https://github.com/WillyBruhn/VARUS.git

# change to the source
cd VARUS/Implementation

# build VARUS
make
``` 

# Tutorial
Find an example of how to use the program under Tutorial/GettingStarted.

Downloading reads of Drosophila melanogaster from the NCBI:
Requirements:
        Check that you have fastq-dump installed [link to be inserted].
        Check that you have STAR installed [https://github.com/alexdobin/STAR].
        Check that you have a genome-file for Drosophila melanogaster.

Step 0:
        Create a new folder MyFirstTest.

Step 1: First you need to download the accession-ids of the runs.
        You do this with the RunListRetriever. Open the terminal in the folder 
        /VARUS/RunListRetriever. Run the RunListRetriever:
```sh
         ./RunListRetriever --outFileDir <absolute path>/MyFirstTest
``` 
        By default this downloads the accession-ids of the first 100 runs of 
        Drosophila melanogaster from the NCBI. For other species and other 
        runs check ```sh ./RunListRetriever -h. ```
        The resulting file "Runlist.txt", located in MyFirstTest, contains the accession-ids.

Step 2: Copy the file "VARUS/Tutorial/Drosophila/parametersCopy" into the folder MyFirstTest.
        Open parametersCopy and make changes to arguments marked with < >.

Step 3: Call VARUS:
```sh        
        ./VARUS --readParametersFromFile 1 --pathToParameters <absolute path>/MyFirstTest
        ``` 
        This chooses 10 times a run to download from and downloads 1000 000 reads each time.

Step 4: Call the visualization-tool:
```sh
         /VARUS/VisualizationTool/./visOverview.R <absolute path>/MyFirstTest/ AdvancedEstimator
          ```        
