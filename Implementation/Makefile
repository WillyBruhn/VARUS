COMP =	g++ -std=c++11 -c -O3
#COMP =	g++ -std=c++11 -c -DDEBUG -g
LINK =	g++ -std=c++11

BUILD = ./bin/
#BUILD = ./deb/

SRC = ./src/
HEADERS = ./headers/

Test = ./Tests/catch/
TestSrc = ./Tests/catch/src/

TestSources = ./Tests/Tests/unitTests/src/

all: VARUS

debug: COMP += -DDEBUG -g
debug: VARUS

profile: COMP += -pg
profile: $(BUILD)main.o $(BUILD)ParameterHandler.o $(BUILD)Controller.o $(BUILD)ChromosomeInitializer.o $(BUILD)Alligner.o $(BUILD)Downloader.o $(BUILD)Run.o $(BUILD)Operators.o $(BUILD)RNAread.o $(BUILD)myRandomEngine.o $(BUILD)Estimator.o $(BUILD)SimpleEstimator.o $(BUILD)Simulator.o $(BUILD)AdvancedEstimator.o $(BUILD)DirichletMixture.o $(BUILD)DirichletDistribution.o $(BUILD)Functions.o $(BUILD)ClusterEstimator.o $(BUILD)ClusterComponent.o $(BUILD)systemFunctions.o
	$(LINK) -pg $(BUILD)main.o $(BUILD)ParameterHandler.o $(BUILD)Controller.o $(BUILD)ChromosomeInitializer.o $(BUILD)Alligner.o $(BUILD)Downloader.o $(BUILD)Run.o $(BUILD)Operators.o $(BUILD)RNAread.o $(BUILD)myRandomEngine.o $(BUILD)Estimator.o $(BUILD)SimpleEstimator.o $(BUILD)Simulator.o $(BUILD)AdvancedEstimator.o $(BUILD)DirichletMixture.o $(BUILD)DirichletDistribution.o $(BUILD)Functions.o $(BUILD)ClusterEstimator.o $(BUILD)ClusterComponent.o $(BUILD)systemFunctions.o -o VARUSgprof

# this will compile the program and the tests and run the tests
#test: VARUS VARUSTest
#	./VARUSTest

test:CatchTest
	$(Test)./CatchTest

VARUSTest: $(BUILD)main_Test.o $(BUILD)ParameterHandler.o $(BUILD)Operators.o $(BUILD)Run.o $(BUILD)ChromosomeInitializer.o $(BUILD)Downloader.o $(BUILD)Alligner.o $(BUILD)RNAread.o $(BUILD)Controller.o $(BUILD)myRandomEngine.o $(BUILD)Estimator.o $(BUILD)SimpleEstimator.o $(BUILD)Simulator.o $(BUILD)AdvancedEstimator.o $(BUILD)Functions.o $(BUILD)DirichletMixture.o $(BUILD)DirichletDistribution.o $(BUILD)ClusterEstimator.o $(BUILD)ClusterComponent.o
	$(LINK) $(BUILD)main_Test.o $(BUILD)ParameterHandler.o $(BUILD)Operators.o $(BUILD)Run.o $(BUILD)ChromosomeInitializer.o $(BUILD)Downloader.o $(BUILD)Alligner.o $(BUILD)RNAread.o $(BUILD)Controller.o $(BUILD)myRandomEngine.o $(BUILD)Estimator.o $(BUILD)SimpleEstimator.o $(BUILD)Simulator.o $(BUILD)AdvancedEstimator.o $(BUILD)Functions.o $(BUILD)DirichletMixture.o $(BUILD)DirichletDistribution.o $(BUILD)ClusterEstimator.o $(BUILD)ClusterComponent.o -o VARUSTest


CatchTest: $(Test)catch.o $(BUILD)systemFunctions.o $(BUILD)ParameterHandler.o $(BUILD)Alligner.o $(BUILD)Run.o $(BUILD)RNAread.o
	$(LINK) $(Test)catch.o $(BUILD)systemFunctions.o $(BUILD)ParameterHandler.o $(BUILD)Alligner.o $(BUILD)Run.o $(BUILD)RNAread.o -o $(Test)CatchTest

#CatchTest: $(Test)catch.o $(BUILD)ParameterHandler.o $(BUILD)ChromosomeInitializer.o $(BUILD)Alligner.o $(BUILD)Downloader.o $(BUILD)Run.o $(BUILD)Operators.o $(BUILD)RNAread.o $(BUILD)myRandomEngine.o $(BUILD)Estimator.o $(BUILD)SimpleEstimator.o $(BUILD)Simulator.o $(BUILD)AdvancedEstimator.o $(BUILD)DirichletMixture.o $(BUILD)DirichletDistribution.o $(BUILD)Functions.o $(BUILD)ClusterEstimator.o $(BUILD)ClusterComponent.o
#	$(LINK) $(Test)catch.o $(BUILD)ParameterHandler.o $(BUILD)ChromosomeInitializer.o $(BUILD)Alligner.o $(BUILD)Downloader.o $(BUILD)Run.o $(BUILD)Operators.o $(BUILD)RNAread.o $(BUILD)myRandomEngine.o $(BUILD)Estimator.o $(BUILD)SimpleEstimator.o $(BUILD)Simulator.o $(BUILD)AdvancedEstimator.o $(BUILD)DirichletMixture.o $(BUILD)DirichletDistribution.o $(BUILD)Functions.o $(BUILD)ClusterEstimator.o $(BUILD)ClusterComponent.o -o $(Test)CatchTest


$(Test)catch.o: $(Test)catch.cpp $(Test)catch.hpp $(TestSources)test_myRandomEngine.cpp $(TestSources)test_RunListRetriever.cpp $(TestSources)test_systemFunctions.cpp $(TestSrc)commandline.cpp $(TestSources)test_Aligner.cpp
		$(COMP) $(Test)catch.cpp -o $(Test)catch.o;

#$(Test)catch.o: $(Test)catch.cpp $(Test)catch.hpp headers/debug.h headers/TypeConventions.h headers/ParameterHandler.h headers/Warning.h headers/Alligner.h headers/Downloader.h headers/Run.h headers/#ChromosomeInitializer.h headers/RNAread.h headers/myRandomEngine.h headers/Estimator.h headers/SimpleEstimator.h headers/Simulator.h headers/AdvancedEstimator.h headers/DirichletMixture.h headers/#DirichletDistribution.h headers/Functions.h
#	$(COMP) $(Test)catch.cpp -o $(Test)catch.o;

clean:
	rm -f $(BUILD)*.o VARUS VARUSTest VARUSgprof $(Test)CatchTest rm -f $(Test)*.o

#------------------------------------------------------------------------------------------------------------------------------------------------------------------

VARUS: $(BUILD)main.o $(BUILD)ParameterHandler.o $(BUILD)Controller.o $(BUILD)ChromosomeInitializer.o $(BUILD)Alligner.o $(BUILD)Downloader.o $(BUILD)Run.o $(BUILD)Operators.o $(BUILD)RNAread.o $(BUILD)myRandomEngine.o $(BUILD)Estimator.o $(BUILD)SimpleEstimator.o $(BUILD)Simulator.o $(BUILD)AdvancedEstimator.o $(BUILD)DirichletMixture.o $(BUILD)DirichletDistribution.o $(BUILD)Functions.o $(BUILD)ClusterEstimator.o $(BUILD)ClusterComponent.o $(BUILD)systemFunctions.o
	$(LINK) $(BUILD)main.o $(BUILD)ParameterHandler.o $(BUILD)Controller.o $(BUILD)ChromosomeInitializer.o $(BUILD)Alligner.o $(BUILD)Downloader.o $(BUILD)Run.o $(BUILD)Operators.o $(BUILD)RNAread.o $(BUILD)myRandomEngine.o $(BUILD)Estimator.o $(BUILD)SimpleEstimator.o $(BUILD)Simulator.o $(BUILD)AdvancedEstimator.o $(BUILD)DirichletMixture.o $(BUILD)DirichletDistribution.o $(BUILD)Functions.o $(BUILD)ClusterEstimator.o $(BUILD)ClusterComponent.o $(BUILD)systemFunctions.o -o VARUS
	
$(BUILD)main.o: $(SRC)main.cpp headers/debug.h headers/TypeConventions.h headers/ParameterHandler.h headers/Warning.h headers/Alligner.h headers/Downloader.h headers/Run.h headers/Controller.h headers/ChromosomeInitializer.h headers/RNAread.h headers/myRandomEngine.h headers/Estimator.h headers/SimpleEstimator.h headers/Simulator.h headers/AdvancedEstimator.h headers/DirichletMixture.h headers/DirichletDistribution.h headers/Functions.h 
	$(COMP) $(SRC)main.cpp -o $(BUILD)main.o;
	
$(BUILD)main_Test.o: $(SRC)main_Test.cpp headers/debug.h headers/TypeConventions.h headers/Operators.h headers/ParameterHandler.h headers/Warning.h headers/ChromosomeInitializer.h headers/myRandomEngine.h headers/Estimator.h headers/SimpleEstimator.h headers/Simulator.h headers/AdvancedEstimator.h headers/Functions.h headers/DirichletMixture.h headers/DirichletDistribution.h headers/ClusterEstimator.h headers/ClusterComponent.h
	$(COMP) $(SRC)main_Test.cpp -o $(BUILD)main_Test.o;
	
$(BUILD)ParameterHandler.o: $(SRC)ParameterHandler.cpp headers/TypeConventions.h headers/Operators.h headers/ParameterHandler.h headers/Warning.h
	$(COMP) $(SRC)ParameterHandler.cpp -o $(BUILD)ParameterHandler.o;
	
$(BUILD)Operators.o: $(SRC)Operators.cpp headers/Operators.h headers/TypeConventions.h
	$(COMP) $(SRC)Operators.cpp -o $(BUILD)Operators.o;
	
$(BUILD)Run.o: $(SRC)Run.cpp headers/Run.h
	$(COMP) $(SRC)Run.cpp -o $(BUILD)Run.o;
	
$(BUILD)ChromosomeInitializer.o: $(SRC)ChromosomeInitializer.cpp headers/ChromosomeInitializer.h headers/myRandomEngine.h
	$(COMP) $(SRC)ChromosomeInitializer.cpp -o $(BUILD)ChromosomeInitializer.o;
	
$(BUILD)Downloader.o: $(SRC)Downloader.cpp headers/Downloader.h headers/Run.h headers/ParameterHandler.h
	$(COMP) $(SRC)Downloader.cpp -o $(BUILD)Downloader.o;
	
$(BUILD)systemFunctions.o: $(SRC)systemFunctions.cpp
	$(COMP) $(SRC)systemFunctions.cpp -o $(BUILD)systemFunctions.o
	
$(BUILD)Alligner.o: $(SRC)Alligner.cpp headers/Alligner.h headers/Run.h headers/ParameterHandler.h headers/RNAread.h headers/systemFunctions.h
	$(COMP) $(SRC)Alligner.cpp -o $(BUILD)Alligner.o;
	
$(BUILD)RNAread.o: $(SRC)RNAread.cpp headers/RNAread.h
	$(COMP) $(SRC)RNAread.cpp -o $(BUILD)RNAread.o;

$(BUILD)myRandomEngine.o: $(SRC)myRandomEngine.cpp headers/ParameterHandler.h
	$(COMP) $(SRC)myRandomEngine.cpp -o $(BUILD)myRandomEngine.o;

$(BUILD)Controller.o: $(SRC)Controller.cpp headers/Controller.h headers/ParameterHandler.h headers/Alligner.h headers/Downloader.h headers/Run.h headers/TypeConventions.h headers/Operators.h headers/ChromosomeInitializer.h headers/myRandomEngine.h headers/Estimator.h headers/SimpleEstimator.h headers/Simulator.h headers/AdvancedEstimator.h headers/DirichletMixture.h
	$(COMP) $(SRC)Controller.cpp -o $(BUILD)Controller.o;
	
$(BUILD)Estimator.o: $(SRC)Estimator.cpp headers/Run.h headers/ParameterHandler.h
	$(COMP) $(SRC)Estimator.cpp -o $(BUILD)Estimator.o;
	
$(BUILD)SimpleEstimator.o: $(SRC)SimpleEstimator.cpp headers/Estimator.h
	$(COMP) $(SRC)SimpleEstimator.cpp -o $(BUILD)SimpleEstimator.o;

$(BUILD)Simulator.o: $(SRC)Simulator.cpp headers/Operators.h headers/Run.h headers/myRandomEngine.h
	$(COMP) $(SRC)Simulator.cpp -o $(BUILD)Simulator.o;
	
$(BUILD)AdvancedEstimator.o: $(SRC)AdvancedEstimator.cpp headers/Estimator.h
	$(COMP) $(SRC)AdvancedEstimator.cpp -o $(BUILD)AdvancedEstimator.o;
	
$(BUILD)Functions.o: $(SRC)Functions.cpp headers/Functions.h
	$(COMP) $(SRC)Functions.cpp -o $(BUILD)Functions.o;
	
$(BUILD)DirichletDistribution.o: $(SRC)DirichletDistribution.cpp headers/Functions.h
	$(COMP) $(SRC)DirichletDistribution.cpp -o $(BUILD)DirichletDistribution.o;
	
$(BUILD)DirichletMixture.o: $(SRC)DirichletMixture.cpp headers/Estimator.h headers/myRandomEngine.h headers/Functions.h headers/DirichletDistribution.h
	$(COMP) $(SRC)DirichletMixture.cpp -o $(BUILD)DirichletMixture.o;
	
$(BUILD)ClusterComponent.o: $(SRC)ClusterComponent.cpp 
	$(COMP) $(SRC)ClusterComponent.cpp -o $(BUILD)ClusterComponent.o;
	
$(BUILD)ClusterEstimator.o: $(SRC)ClusterEstimator.cpp headers/Estimator.h headers/myRandomEngine.h headers/Operators.h
	$(COMP) $(SRC)ClusterEstimator.cpp -o $(BUILD)ClusterEstimator.o;	
