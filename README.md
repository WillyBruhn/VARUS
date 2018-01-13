# VARUS: Drawing diverse samples from RNA-Seq libraries
**VARUS** automates the selection and download of RNA-Seq runs available at the SRA, with regard to a **sufficiently** high coverage. This is done in a stepwise procedure. An iteration includes:

- selecting a run to download, that is expected to complement previously downloaded reads the most
- download the run with **fastq-dump**
- align the reads with **STAR**
- evaluate the alignment

The key here is that runs are only downloaded partially in each iteration. With these read-samples, estimations of the runs value for further downloads from this run are made. This allows **VARUS** to distinguish good runs from bad runs within the first few downloads, and download more extensively from runs that are likely to contain more reads from yet underrepresented transcripts.

# INSTALLATION
## LINUX
```sh
git clone https://github.com/WillyBruhn/VARUS.git

# change to the source
cd VARUS/Implementation

# build VARUS
make
``` 

# Getting Started
## Downloading reads of Drosophila melanogaster from the NCBI:
Find a working setup under /GettingStarted/Drosophila. You can use this for your applications by modifying **parametersCopy** 
and species.txt and substituting ***drosophila.fasta*** with the needed genome-file. 
Invoke the following command to start downloading runs.
```sh
./runVARUS.pl
```
The final output should be a file called **VARUS.bam**.

### Requirements:
Check that you have fastq-dump installed [https://ncbi.github.io/sra-tools/fastq-dump.html].  
Check that you have STAR installed [https://github.com/alexdobin/STAR].  
Check that you have a genome-file for Drosophila melanogaster.  


The result might look like this:
![alternate text](/Tutorial/ComparisonNEW.png)
