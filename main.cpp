#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "ArrayList.cpp"

using namespace std;

class Chromosome{
	public:
		ArrayList<bool> genoms;
		void gen (int len){
			for (int i=0;i<len;i++){
				double decision = (double)rand() / (double)RAND_MAX;
				if (decision > 0.5){
					genoms.push(true);
				}
				
				else{
					genoms.push(false);
				}
			}
		}
		
		void print(){
			for (int i=0;i<genoms.getSize();i++){
				if (genoms.get(i)){
					cout<<"1";
				}
				
				else{
					cout<<"0";
				}
			}
			
			cout<<endl;
		}	
};

class Block{
	
	public:
		ArrayList<int> weight;
		ArrayList<int> benefit;
		int inputSize;
		int KnapSackMaxSize;
};

class GA{
	Block b;
	public:
		GA(Block b){
			this->b = b;
		}
		
		Chromosome mutate(Chromosome ch){
			Chromosome mutatedCh;
			for (int i=0;i<ch.genoms.getSize();i++){
				//cout<<b.weight.get(i)<<" "<<b.KnapSackMaxSize<<" "<<b.weight.getSize()<<" "<<ch.genoms.getSize()<<endl;	
							
				if (b.weight.get(i) <= b.KnapSackMaxSize){
					double decision = (double)rand() / (double)RAND_MAX;
					
					if (decision < 0.1){
						if (ch.genoms.get(i)){
							mutatedCh.genoms.push(false);
						}
						
						else{
							mutatedCh.genoms.push(true);
						}
					}
					
					else{
						mutatedCh.genoms.push(ch.genoms.get(i));
					}
				}
				
				else{
					mutatedCh.genoms.push(false);
				}
			}
			
			return mutatedCh;
		}
		
		ArrayList<Chromosome> crossover(Chromosome ch1 , Chromosome ch2){
			int decision = rand()%ch1.genoms.getSize()-1;
			
			if (decision < 0){
				decision = decision * -1;
			}
			
			Chromosome newCh1,newCh2;
			
			//cout<<decision<<endl;
						
			for (int i=0;i<decision;i++){
				newCh1.genoms.push(ch1.genoms.get(i));
				newCh2.genoms.push(ch2.genoms.get(i));
			}
			
			for (int i=decision;i<ch1.genoms.getSize();i++){
				newCh1.genoms.push(ch2.genoms.get(i));
				newCh2.genoms.push(ch1.genoms.get(i));
			}
			
			//cout<<ch1.genoms.getSize()<<" "<<newCh1.genoms.getSize()<<" "<<ch2.genoms.getSize()<<" "<<newCh2.genoms.getSize()<<endl;
			
			ArrayList<Chromosome> l;
			l.push(newCh1);
			l.push(newCh2);
			
			return l;
		}
		
		int getMaxFitness(ArrayList<Chromosome> pop){
			int max = -1;
			Chromosome maxCh = pop.get(0);
			for (int i=0;i<pop.getSize();i++){
				int res = calcFitness(pop.get(i),0);
				if (res > max){
					maxCh = pop.get(i);
					max = res;
				}
			}
			
			calcFitness(maxCh,1);
			
			return max;
		}
		
		int calcFitness(Chromosome c,int printable){
			int maxWeight = 0;
			int maxBenefit = 0;
			
			for (int i=0;i<c.genoms.getSize();i++){
				if (c.genoms.get(i)){
					maxWeight += b.weight.get(i);
					maxBenefit += b.benefit.get(i);
				}
			}
			
			if (maxWeight > b.KnapSackMaxSize){
				return -1;
			}
			
			else{
				if (printable == 1){
					for (int i=0;i<c.genoms.getSize();i++){
						if (c.genoms.get(i)){
							cout<<b.weight.get(i)<<" "<<b.benefit.get(i)<<endl;
						}
					}
				}
				return maxBenefit;
			}
		}
		
		ArrayList<Chromosome> process(ArrayList<Chromosome> population){
			double CO = 0.7;
			ArrayList<Chromosome> newPop;
			for (int i=0;i<population.getSize();i=i+2){
				double decision = (double)rand() / (double)RAND_MAX;
				
				if (decision >= CO){
					ArrayList<Chromosome> temp = crossover(population.get(i),population.get(i+1));
					for (int j=0;j<2;j++){
						newPop.push(temp.get(j));
					}
				}
				
				else{
					newPop.push(population.get(i));
					newPop.push(population.get(i+1));
				}
			}
			
			for (int i=0;i<newPop.getSize();i++){
				Chromosome temp = mutate(newPop.get(i));
				newPop.set(i,temp);
			}
			
			int popMover = 0;
			int newPopMover = 0;
			ArrayList<Chromosome> fittestPop;
			//cout<<population.getSize()<<" "<<newPop.getSize()<<endl;
			while (popMover<population.getSize() && newPopMover<newPop.getSize() && fittestPop.getSize() < population.getSize()){
				if (calcFitness(population.get(popMover),0) > calcFitness(newPop.get(newPopMover),0)){
					fittestPop.push(population.get(popMover));
					popMover++;
				}
				
				else{
					fittestPop.push(newPop.get(newPopMover));
					newPopMover++;
				}
			}
			
			if (popMover<population.getSize()-1){
				while(fittestPop.getSize() < population.getSize()){
					fittestPop.push(population.get(popMover));
					popMover++;
				}
			}
			
			else if (newPopMover<newPop.getSize()-1){
				while(fittestPop.getSize() < population.getSize()){
					fittestPop.push(newPop.get(newPopMover));
					newPopMover++;
				}
			}
			
			return fittestPop;
		}
};

class Blocker{
	int testCasesNumber;
	ArrayList<string> list;
	
	public:
		ArrayList<Block> blockList;
		Blocker(ArrayList<string> list){
			this->list = list;
			
			stringstream stream1;
			stream1.str(list.get(0));
			stream1 >> this->testCasesNumber;
		}
		
		void divide(){
			int start = 1;
			for (int i=0;i<testCasesNumber;i++){
				Block block;
				
				stringstream stream1;
				stream1.str(list.get(start));
   				stream1 >> block.inputSize;
   				stream1.clear();
   				stream1.str(list.get(start + 1));
   				stream1 >> block.KnapSackMaxSize;
   				
				int moves = block.inputSize;
				
				for (int j=start+2;j<start+moves+2;j++){
					
					string temp = "";
					for (int k=0;k<list.get(j).length();k++){
						if (list.get(j)[k] == ' '){
							int var;
							stream1.clear();
			   				stream1.str(temp);
			   				stream1 >> var;
			   				
			   				block.weight.push(var);
			   				
			   				temp = "";
						}
						
						else if (k == list.get(j).length()-1){
							temp += list.get(j)[k];
							int var;
							stream1.clear();
			   				stream1.str(temp);
			   				stream1 >> var;
			   				
			   				block.benefit.push(var);
			   				
			   				temp = "";
						}
						
						else{
							temp += list.get(j)[k];
						}
					}
				}
				
				blockList.push(block);
				start = start + moves + 2;
			}
		}
};

class FileOperations{
	fstream stream;
	ArrayList<string> list;
	
	public:
		void open(string file){
			stream.open("input.txt",ios::in|ios::out);
		}
		
		void read(){
			string x;
			
			while(!stream.eof()){
				getline(stream,x);
				if (x.length() != 0){
					list.push(x);
				}
			}
		}
		
		ArrayList<string> getReading(){
			return list;
		}
};

int main(){
	srand((unsigned)time(NULL));
	FileOperations op;
	op.open("input.txt");
	op.read();
	
	ArrayList<string> list = op.getReading();
	Blocker blk(list);
	blk.divide();
	
	for (int i=0; i<blk.blockList.getSize(); i++){
		
		//Generate Population
		ArrayList<Chromosome> chromoList;
		for(int j=0;j<10;j++){
			Chromosome ch;
			ch.gen(blk.blockList.get(i).inputSize);
			chromoList.push(ch);
		}
		
		GA ga(blk.blockList.get(i));
		
		//Process Population
		for (int j=0;j<500;j++){
			chromoList = ga.process(chromoList);
		}
		
		
		//Calculate Max Fitness
		int res = ga.getMaxFitness(chromoList);
		
		//Output Max Fitness
		cout<<"Case "<<i+1<<" : "<<res<<endl;
		system("PAUSE");
	}
	
	system("PAUSE");
	return 0;
	//list.display();
}

