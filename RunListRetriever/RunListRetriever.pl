#!/usr/bin/perl 
use strict;
use warnings;
use Getopt::Long;
# Program to retrieve a list of available Runs and number of reads per run for a given Species
# Willy Bruhn 2.3.2016

#1. URL aus Speciesname basteln
#SPECIESNAME-GENUS=Drosophila
#SPECIESNAME-SPECIES=melanogaster
#URL =  "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=sra&term=" + Drosophila + "+" + melanogaster + "%5borgn%5d+AND+biomol_rna%5bProp%5d&usehistory=y"

#wget -O list.xml $URL

# dann aus list.xml die WebENV herausparsen
#WEBENV=NCID_1_68563684_165.112.9.37_9001_1456932823_1456949776_0MetA0_S_MegaStore_F_1

#wget -O out0-3.html "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esummary.fcgi?db=sra&WebEnv=" + WEBENV + "&query_key=1&retmax=10000&retstart=0"


#/home/willy/Uni/5.Semester/Bachelorarbeit/pearlAccesionManager/./RunListRetriever.pl --retstart 0 --retmax 5 --outFileDir /home/willy/Uni/5.Semester/Bachelorarbeit/Manager/test11/


my $usage = "Usage:\n";
$usage .= "  --genus: \tdefault: Drosophila\n\n";
$usage .= "  --species: \tdefault: melanogaster\n\n";
$usage .= "  --retmax: \tdefault: 100, number of runs to be downloaded\n\n";
$usage .= "  --retstart: \tdefault: 1, download from retstart to retstart + retmax-1\n\n";
$usage .= "  --outFileDir: default: \"\", the directory where all files will be stored\n\n";
$usage .= "  --all: \tdefault: 'false', retrieve all available runs\n\n";
$usage .= "  --paired: \tdefault: 'false', retrieve only paired-seq runs\n\n";

my $species_name_GENUS = "Drosophila";
my $species_name_SPECIES = "melanogaster";
my $retmax = 100;		# number of runs to be downloaded
my $retstart = 1;		# first run; download from $retstart to $retstart + $retmax-1
my $all = 0;
my $outFileDir = "";
my $help = 0;
my $onlyPaired = 0;

my $outfiles = 0; # if true, output the files with the list in addition to the stats
GetOptions('genus=s'=>\$species_name_GENUS,
		   'species=s'=>\$species_name_SPECIES,
		   'retmax=i'=>\$retmax,
		   'retstart=i'=>\$retstart,
		   'all!'=>\$all,
		   'outFileDir=s'=>\$outFileDir,
		   'paired!'=>\$onlyPaired,
		   'help!'=>\$help)
or die($usage);

my $n = scalar @ARGV;
if ($help) {
    print $usage;
    exit;
}


# RETRIEVE ID
#_______________________________________


my $URL = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=sra&term=
$species_name_GENUS+$species_name_SPECIES%5borgn%5d+AND+biomol_rna%5bProp%5d&usehistory=y";

my $IDFile = "IDFile.xml";
system "wget -O $outFileDir$IDFile \"$URL\"";
print "wget -O $outFileDir$IDFile \"$URL\"";


my $WEBENV;
open(FILE, "<", "$outFileDir$IDFile") or die("Could not open file $outFileDir$IDFile");
while (<FILE>)
{
	print "$_";
	if($_ =~ /\<WebEnv\>(.*)\<\/WebEnv\>/)
	{
		$WEBENV = $1;
	}
}
close (FILE);

print "$WEBENV\n";

# RETRIEVE LIST OF RUNS
#__________________________________________


sub getRuns
{
    # Get passed arguments
    my ($WEBENV, $retmax, $retstart) = @_;

	my $URL2 = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esummary.fcgi?db=sra&WebEnv=$WEBENV&query_key=1&retmax=$retmax&retstart=$retstart";

	my $listFile = "list$retstart-$retmax.html";

	system "wget -O $outFileDir$listFile \"$URL2\"";

	my $Run_acc;
	my $total_spots;
	my $total_bases;
	my $paired = 0;

	my @array = ();
	open(FILE, "<", "$outFileDir$listFile") or die("Could not open file $outFileDir$listFile");
	while (<FILE>)
	{
		# build run
		if($_ =~ /Run acc="(.*?)" total_spots="(\d*?)" total_bases="(\d*?)"/)
		{
			$Run_acc = $1;
			$total_spots = $2;
			$total_bases = $3;

			if("" eq $total_spots)
			{
				$total_spots = "N/A";
			}
			if("" eq $total_bases)
			{
				$total_bases = "N/A";
			}
			
			if(($onlyPaired == 1 && $paired == 1) || $onlyPaired == 0)
			{
				print "$Run_acc\t$total_spots\t$total_bases\n";
	
				my @runParameters = ();
				push (@runParameters, $Run_acc, $total_spots, $total_bases, $paired);
				push (@array, [@runParameters]);
			}

			if(1 == $paired)
			{
				$paired = 0;
			}
		}

		# check if it's a run with paired reads
		if($_ =~ /(PAIRED NOMINAL_LENGTH)/)
		{
			$paired = 1;
		}
	}
	close (FILE);
	@array;
}

sub saveListToFile
{
    # Get passed arguments
    my ($start, $arr) = @_;

    # Get the array from the reference
    my @array = @{$arr};
    my $end = scalar @array + $start - 1;

#	open(OUTPUTFILE, ">", "$outFileDir Runlist$start-$end.txt");
	my $fileName = "Runlist.txt";
	open(OUTPUTFILE, ">", "$outFileDir$fileName");
	print OUTPUTFILE  "\@Run_acc\ttotal_spots\ttotal_bases\tbool:paired\t#tabulator separated\n";
	for(my $i = 0;  $i < scalar @array ; $i++)
	{
		for(my $j = 0;  $j < scalar @{$array[$i]} ; $j++)
		{
			print OUTPUTFILE "$array[$i][$j]\t";
		}
		print OUTPUTFILE "\n";
	}
	close(OUTPUTFILE);
}

sub createRunScoreFile
{
    # Get passed arguments
    my ($arr) = @_;

    # Get the array from the reference
    my @array = @{$arr};

#	open(OUTPUTFILE, ">", "$outFileDir Runlist$start-$end.txt");
	my $fileName = "RunScores.txt";
	open(OUTPUTFILE, ">", "$outFileDir$fileName");
	for(my $i = 0;  $i < scalar @array ; $i++)
	{
		# runname	score	length
		print OUTPUTFILE "$array[$i][0]\t1000000\t0\n";
	}
	close(OUTPUTFILE);
}

my @array = ();

if(1 == $all)
{
	my $loop_count = 0;
	$retstart = 0;
	$retmax = 10000;
	do
	{
		$loop_count++;
		push (@array, getRuns($WEBENV, $retmax, $retstart));

		$retstart += 10000;

	}while(scalar @array ==  $loop_count * $retmax);
	
	# saving the results in a file
	saveListToFile(0, \@array);
	
}
else
{
	push(@array, getRuns($WEBENV, $retmax, $retstart));
	saveListToFile($retstart, \@array);
}

#createRunScoreFile(\@array);

