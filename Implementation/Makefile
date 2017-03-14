COMP =	g++ -std=c++11 -c -O3
LINK =	g++ -std=c++11


# this will compile the program and the tests and run the tests
all: VARUS VARUSTest
	./VARUSTest

debug: COMP += -DDEBUG -g
debug: VARUS

profile: COMP += -pg
profile: main.o main.o ParameterHandler.o Controller.o ChromosomeInitializer.o Alligner.o Downloader.o Run.o Operators.o RNAread.o myRandomEngine.o Estimator.o SimpleEstimator.o Simulator.o AdvancedEstimator.o DirichletMixture.o DirichletDistribution.o Functions.o ClusterEstimator.o ClusterComponent.o
	$(LINK) -pg main.o ParameterHandler.o Controller.o ChromosomeInitializer.o Alligner.o Downloader.o Run.o Operators.o RNAread.o myRandomEngine.o Estimator.o SimpleEstimator.o Simulator.o AdvancedEstimator.o DirichletMixture.o DirichletDistribution.o Functions.o ClusterEstimator.o ClusterComponent.o -o VARUSgprof
	

test: VARUSTest

VARUSTest: main_Test.o ParameterHandler.o Operators.o Run.o ChromosomeInitializer.o Downloader.o Alligner.o RNAread.o Controller.o myRandomEngine.o Estimator.o SimpleEstimator.o Simulator.o AdvancedEstimator.o Functions.o DirichletMixture.o DirichletDistribution.o ClusterEstimator.o ClusterComponent.o
	$(LINK) ParameterHandler.o Operators.o main_Test.o Run.o ChromosomeInitializer.o Downloader.o Alligner.o RNAread.o Controller.o myRandomEngine.o Estimator.o SimpleEstimator.o Simulator.o AdvancedEstimator.o Functions.o DirichletMixture.o DirichletDistribution.o ClusterEstimator.o ClusterComponent.o -o VARUSTest

clean:
	rm -f *.o VARUS

VARUS: main.o ParameterHandler.o Controller.o ChromosomeInitializer.o Alligner.o Downloader.o Run.o Operators.o RNAread.o myRandomEngine.o Estimator.o SimpleEstimator.o Simulator.o AdvancedEstimator.o DirichletMixture.o DirichletDistribution.o Functions.o ClusterEstimator.o ClusterComponent.o
	$(LINK) main.o ParameterHandler.o Controller.o ChromosomeInitializer.o Alligner.o Downloader.o Run.o Operators.o RNAread.o myRandomEngine.o Estimator.o SimpleEstimator.o Simulator.o AdvancedEstimator.o DirichletMixture.o DirichletDistribution.o Functions.o ClusterEstimator.o ClusterComponent.o -o VARUS
	
main.o: main.cpp debug.h TypeConventions.h ParameterHandler.h Warning.h Alligner.h Downloader.h Run.h Controller.h ChromosomeInitializer.h RNAread.h myRandomEngine.h Estimator.h SimpleEstimator.h Simulator.h AdvancedEstimator.h DirichletMixture.h DirichletDistribution.h Functions.h 
	$(COMP) main.cpp
	
main_Test.o: main_Test.cpp debug.h TypeConventions.h Operators.h ParameterHandler.h Warning.h ChromosomeInitializer.h myRandomEngine.h Estimator.h SimpleEstimator.h Simulator.h AdvancedEstimator.h Functions.h DirichletMixture.h DirichletDistribution.h ClusterEstimator.h ClusterComponent.h
	$(COMP) main_Test.cpp
	
ParameterHandler.o: ParameterHandler.cpp TypeConventions.h Operators.h ParameterHandler.h Warning.h
	$(COMP) ParameterHandler.cpp
	
Operators.o: Operators.cpp Operators.h TypeConventions.h
	$(COMP) Operators.cpp
	
Run.o: Run.cpp Run.h
	$(COMP) Run.cpp
	
ChromosomeInitializer.o: ChromosomeInitializer.cpp ChromosomeInitializer.h myRandomEngine.h
	$(COMP) ChromosomeInitializer.cpp
	
Downloader.o: Downloader.cpp Downloader.h Run.h ParameterHandler.h
	$(COMP) Downloader.cpp
	
Alligner.o: Alligner.cpp Alligner.h Run.h ParameterHandler.h RNAread.h
	$(COMP) Alligner.cpp
	
RNAread.o: RNAread.cpp RNAread.h
	$(COMP) RNAread.cpp

myRandomEngine.o: myRandomEngine.cpp ParameterHandler.h
	$(COMP) myRandomEngine.cpp

Controller.o: Controller.cpp Controller.h ParameterHandler.h Alligner.h Downloader.h Run.h TypeConventions.h Operators.h ChromosomeInitializer.h myRandomEngine.h Estimator.h SimpleEstimator.h Simulator.h AdvancedEstimator.h DirichletMixture.h
	$(COMP) Controller.cpp
	
Estimator.o: Estimator.cpp Run.h ParameterHandler.h
	$(COMP) Estimator.cpp
	
SimpleEstimator.o: SimpleEstimator.cpp Estimator.h
	$(COMP) SimpleEstimator.cpp

Simulator.o: Simulator.cpp Operators.h Run.h myRandomEngine.h
	$(COMP) Simulator.cpp
	
AdvancedEstimator.o: AdvancedEstimator.cpp Estimator.h
	$(COMP) AdvancedEstimator.cpp
	
Functions.o: Functions.cpp Functions.h
	$(COMP) Functions.cpp
	
DirichletDistribution.o: DirichletDistribution.cpp Functions.h
	$(COMP) DirichletDistribution.cpp
	
DirichletMixture.o: DirichletMixture.cpp Estimator.h myRandomEngine.h Functions.h DirichletDistribution.h
	$(COMP) DirichletMixture.cpp
	
ClusterComponent.o: ClusterComponent.cpp 
	$(COMP) ClusterComponent.cpp
	
ClusterEstimator.o: ClusterEstimator.cpp Estimator.h myRandomEngine.h Operators.h
	$(COMP) ClusterEstimator.cpp	
