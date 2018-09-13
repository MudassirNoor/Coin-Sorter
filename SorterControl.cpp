//Name: Mudassir Noor
//Student ID: 301338172
//Purpose of Code: To sort coins in a coin sorting machine by matching the weight, diameter and image of the coins with known standards.
//Date of Creation: November 15, 2017

#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	//Declared variables and constants.
	char inputname[1024] = {'\0'};
	char outputname[1024] = {'\0'};
	char garbage[1000] = {'\0'};
	ifstream infile;
	ofstream outfile;

	int num_lines = 0;
	int lines = 0;

	double weight = 0;
	double diameter = 0;
	string usability = "";
	string compatibility = "";

	int tries = 0;

	int numNickel = 0;
	int numDime = 0;
	int numQuarter = 0;                                 //These set of variables were created for keepeing count of each set of coin in the loop.
	int numLoonie = 0;
	int numTwonie = 0;
	int numOtherCoin = 0;

	int nickelcounter = 0;
	int dimecounter = 0;
	int quartercounter = 0;                             //These set of variables are used for keeping count of each set of coins in the current
	int looniecounter = 0;                              //roll or container.
	int twoniecounter = 0;
	int totalOthercoincounter = 0;


	double bentcoinweight = 0;
	double totalBentcoin = 0;                            //These set of variables are used for keeping account of the changing weight, the total weight
	double bentcontainerweight = 0;                      // and the weight in the current container of bent and other coins.
	double othercoinweight = 0;
	double totalOthercoin = 0;
	double othercontainerweight = 0;

	int NickelsRollscounter = 0;
	int DimesRollscounter = 0;
	int QuartersRollscounter = 0;
	int LooniesRollscounter = 0;                          //These set of variables are used for keeping track of the rolls or container being used.
	int TwoniesRollscounter = 0;
	int OthersContainercounter = 0;
	int OthersCurrentContainer = 0;

	double weightinGrams = 0;                              //These variables are used for storing the converted weights from the input variables.
	double actualdiameter = 0;

	const long int Max_lines = 5000;                        
	const int Min_lines = 0;                                 
	const int Max_tries = 3;                                //These set of constants represents the limits of inputs or tries.
	const double MaxInteger = 255;
	const double MinInteger = 0;

	const double MaxWeight_Nickel = 4.3;
	const double MaxWeight_Dime = 2.2;
	const double MaxWeight_Quarter = 4.8;                    //These constants show the maximum weight of each set of coins.
	const double MaxWeight_Loonie = 7.5;
	const double MaxWeight_Twonie = 7.85;

	const double MinWeight_Nickel = 3.6;
	const double MinWeight_Dime = 1.3;
	const double MinWeight_Quarter = 4.0;                    //These constants show the minimum weight of each set of coins.
	const double MinWeight_Loonie = 6.5;
	const double MinWeight_Twonie = 6.75;

	const double MaxDiameter_Nickel = 21.8;
	const double MaxDiameter_Dime = 18.7; 
	const double MaxDiameter_Quarter = 24.6;                 //These constants show the maximum diameter of each set of coins.
	const double MaxDiameter_Loonie = 27.0;
	const double MaxDiameter_Twonie = 29.1;
	
	const double MinDiameter_Nickel = 20.2;
	const double MinDiameter_Dime = 17.3;
	const double MinDiameter_Quarter = 22.8;                 //These constants show the minimum diameter of each set of coins.
	const double MinDiameter_Loonie = 25.0;
	const double MinDiameter_Twonie = 26.9;
	
	const int MaxNickel_per_Roll = 40;
	const int MaxDime_per_Roll = 50;
	const int MaxQuarter_per_Roll = 40;                       //These constants represent the maximum number of coins allowed in each roll
	const int MaxLoonie_per_Roll = 25;                        //or container.
	const int MaxTwonie_per_Roll = 25;
	const double MaxBentContainerWeight = 100;
	const double MaxOtherContainerWeight = 200;
	
	const double MaxIncrease = 5.0;
	const double MaxDiameterallowed = 30.0;
	const double Lengthratio = MaxIncrease/MaxInteger;
	const double Diameter_ratio = MaxDiameterallowed/MaxInteger;

	const string Value1 = "bent";
	const string Value2 = "usable";
	const string Value3 = "BothMatch";                       //The constant string that are to be match with the string from the data file
	const string Value4 = "OneMatch";
	const string Value5 = "NoMatch";


	//Prompt user for the name of the input file. Maximum 3 tries.
	do{
		cout << "Type the name of the input file containing sensor readings: " << endl;
		cin >> inputname;
		infile.open(inputname);

		tries++;

		if(infile.fail())
		{
			cerr << "ERROR: File " << inputname << " could not be opened for input" << endl;
		}
		
		if(tries == Max_tries)
		{
			cerr << "ERROR: You exceeded the maximum number of tries allowed" << endl << "while entering the input file name";
			return 1;
		}
	}while (infile.fail());

	//Prompt user for the name of the output file. Maximum 3 tries.
	do
	{
		tries = 0;
		cout << "Type the name of the output file which will hold the simulation" << endl << "results:" << endl;
		cin >> outputname;
		outfile.open(outputname);

		tries++;

		if(outfile.fail())
		{
			cerr << "ERROR: File " << outputname << " cout not be openeed" << endl;
		}

		if(tries == Max_tries)
		{
			cerr << "ERROR: You exceeded the maximum number of tries allowed" << endl << "while entering the outpt file name" << endl;
			return 2;
		}
	}while (outfile.fail());

//Check the fist line that contains the line number to see if it exists and is of the correct type.
	if(!(infile >> num_lines))
	{
		if(infile.eof())
		{
			cerr << "ERROR: input data file is empty";
			infile.close();
			outfile.close();
			return 3;
		}
		else
		{
			cerr << "ERROR: First piece of data in the file is not an integer";
			infile.close();
			outfile.close();
			return 4;
		}
	}



	else
	{
		//Checks that the number of lines is within the limit.
			if(num_lines <= Min_lines || num_lines >= Max_lines)
			{
				cerr << "ERROR: The number of sensor readings is out of range";
				infile.close();
				outfile.close();
				return 5;
			}
	}


//Data input starts.
	for(lines = 0; lines < num_lines; lines++)
	{
		//Check for the weight, diameter, structure and image of the coins from the sensor readings. Check to see if each line has the correct input of data and ignore redundant information.
			if(!(infile >> weight))
			{
				if(!infile.eof())  //Checks to see the type of data.
				{
					cerr << "ERROR: Weight sensor value read on line " << lines + 1 << " is not an integer" << endl << "Simulation terminated early: Please correct your data file" << endl;
					break;
				}
				else if(infile.eof())
				{
					cerr << "ERROR: No more data" << endl << "Simulation completed early before line " << lines + 1 << " of input" << endl;;
					break;
				}
			}
			if(weight < MinInteger || weight > MaxInteger)
			{
				cerr << "ERROR: Sensor eading out of range, ignoring line " << lines + 1 << " int the" << endl << "input file" << endl;
				infile.getline(garbage, 1000); //After checking the range of the weight sensor, if false, would ignore rest of the data in that line.
				continue;
			}

			infile.get();               //Reads the next character after taking the input and ignores it. The next character would be a space.
			if(infile.peek() == '\n')   //Looks into the next caracter after the space to see if the enter key had been pressed to start a new line.
			{
				//If true, it would print the error message below and move to the next line.
				cerr << "ERROR: Weight sensor measurement only" << endl << "Ignoring line " << lines + 1 << " of the input file" << endl;
				continue;
			}
			
			if(!(infile >> diameter))
			{
				if(!infile.eof())
				{
					cerr << "ERROR: Diameter sensor reading on line " << lines + 1 << " is not an integer" << endl << "Simulation terminated early: Please correct your data file" << endl;
					break;
				}
				else if(infile.eof())
				{
					cerr << "ERROR: No more data" << endl << "Simulation completed early before line " << lines + 1 << " of input" << endl;
					break;
				}
			}
			if(diameter < MinInteger || diameter > MaxInteger)
			{
				cerr << "ERROR: Sensor eading out of range, ignoring line " << lines + 1 << " int the" << endl << "input file" << endl;
				infile.getline(garbage, 1000);
				continue;
			}

			infile.get();
			if(infile.peek() == '\n')
			{
					cerr << "ERROR: Weight and diameter sensor measurements only" << endl << "Ignoring line " << lines + 1 << " of the input file" << endl;
					continue;
			}

			infile >> usability;
			if(usability != Value1 && usability != Value2) //Checks to see if the string is what it is expected to be.
			{
					cerr << "ERROR: Result of test to determine if coin is bent at line " << lines + 1 << endl << "is invalid" << endl << "Ignoring this line of data" << endl;
					infile.getline(garbage, 1000);
					continue;
			}

			infile.get();
			if(infile.peek() == '\n')
			{
				cerr << "ERROR: Weight and diameter sensor measurements and bent string only" << endl << "Ignoring line " << lines + 1 << " of the input file" << endl;
				continue;
			}

			infile >> compatibility;
			if(compatibility != Value3 && compatibility != Value4 && compatibility != Value5)
			{
					cerr << "ERROR: image processing result at line " << lines + 1 << " is invalid" << endl << "Ignoring this line of data" << endl;
					infile.getline(garbage, 1000);
					continue;
			}
			
			infile.getline(garbage, 1000);     //After reading the required 4 datas, this funtion will read and store the rest of the unnecessary                                                       characters and store them in garbage asthey ae not needed and will not be used. It stops at newline.
			
			weightinGrams = 2*weight*Lengthratio;  //Converts the measurement into weight.

			//Checks to see if the first string is 'bent' or 'usable'.
			if (usability == Value1)
			{
				//If bent, the weight will be stored in bentcoinweight. This will be added and furter incremented in total weight.
				bentcoinweight = weightinGrams;
				totalBentcoin += bentcoinweight;
				bentcontainerweight += bentcoinweight; //This helps to keep track of the weight in the container.

				outfile << "The Coin Sorter has sent this coin to the bent coin container" << endl;

				cout << "The Coin Sorter has sent this coin to the bent coin container" << endl;

				if(bentcontainerweight > MaxBentContainerWeight) 
				{
					//If the maxmimum weight in the container has been reached, the container is replaced, (the counter for the containe is reset to 0.
					bentcontainerweight = 0;
					bentcontainerweight += bentcoinweight;

					//The following texts are printed in both the screen and the output file.
					outfile << "This coin does not fit in the bent coin container" << endl;
					outfile << "The bent coin container has been replaced" << endl;
					outfile << "The coin in the new bent coin container weighs " << fixed << setprecision(2) << bentcontainerweight << " grams" << endl;

					cout << "This coin does not fit in the bent coin container" << endl;
					cout << "The bent coin container has been replaced" << endl;
					cout << "The coin in the new bent coin container weighs " << fixed << setprecision(2) << bentcontainerweight << " grams" << endl;
					continue;
				}
				else
				{
					outfile << "The coins in the bent coin container now weigh " <<  fixed << setprecision(2) << bentcontainerweight << " grams" << endl;
						
					cout << "The coins in the bent coin container now weigh " <<  fixed << setprecision(2) << bentcontainerweight << " grams" << endl;
					continue;
				}
				
			}
			if( usability == Value2)  //If the coin is usable, it moves on to check the diameter and image.
			{
				actualdiameter = (diameter*Diameter_ratio) + 10; //Calculation of diameter.

			 //Each if and else if statements in the following lines, compare the weight, diameter and image of standard Canadian coins. If the conditions match, the instruction in the respective if statements are carried out.
			//If the conditions do not match, they are treated as other coins and the set of instructions in the else statement is followed.
			//Every if/else if statments for each type of coins follows th same instruction with exception to the 'other coin' for which a more rigorous calculation is required to be carried out.

				if(actualdiameter <= MaxDiameter_Nickel && actualdiameter >= MinDiameter_Nickel && weightinGrams >= MinWeight_Nickel && weightinGrams <= MaxWeight_Nickel && compatibility == Value3)
				{
						nickelcounter++; //Keeps counts of nickels in th container.
						outfile << "The Coin Sorter has sent one coin to the nickels wrapper" << endl;

						if(nickelcounter > MaxNickel_per_Roll) //Checks to see if the maximum for the roll is reached.
						{
							NickelsRollscounter++;              //If the maximum is reached, it increments and so keeps track of the rolls.
							nickelcounter = 0;                  //If the maximum is reached, the nickel counter is set to zero.
							outfile << "The nickel wrapper is now full" << endl;
							outfile << "The nickel wrapper has now been replaced" << endl;
							cout << "The nickel wrapper is now full" << endl;
							cout << "The nickel wrapper has now been replaced" << endl;
							continue;
						}
						else //If the maximum for the contaier os not reached, the following set is  carried out.
						{
							outfile << "There are now " << nickelcounter << " coins in the nickels wrapper" << endl;
							cout << "There are now " << nickelcounter << " coins in the nickels wrapper" << endl;
							continue;
						}
				}

				else if(actualdiameter <= MaxDiameter_Dime && actualdiameter >= MinDiameter_Dime && weightinGrams >= MinWeight_Dime && weightinGrams <= MaxWeight_Dime && compatibility == Value3)
				{
						dimecounter++;
						outfile << "The Coin Sorter has sent one coin to the dimes wrapper" << endl;

						if(dimecounter > MaxDime_per_Roll)
						{
							DimesRollscounter++;
							dimecounter = 0;
							outfile << "The dime wrapper is now full" << endl;
							outfile << "The dime wrapper has now been replaced" << endl;
							cout << "The dime wrapper is now full" << endl;
							cout << "The dime wrapper has now been replaced" << endl;
							continue;
						}
						else
						{
							outfile << "There are now " << dimecounter << " coins in the dimes wrapper" << endl;
							cout << "There are now " << dimecounter << " coins in the dimes wrapper" << endl;
							continue;
						}
				}

				else if(actualdiameter <= MaxDiameter_Quarter && actualdiameter >= MinDiameter_Quarter && weightinGrams >= MinWeight_Quarter && weightinGrams <= MaxWeight_Quarter && compatibility == Value3)
				{
						quartercounter++;
						outfile << "The Coin Sorter has sent one coin to the quarters wrapper" << endl;

						if(quartercounter > MaxQuarter_per_Roll)
						{
							QuartersRollscounter++;
							quartercounter = 0;
							outfile << "The quarter wrapper is now full" << endl;
							outfile << "The quarter wrapper has now been replaced" << endl;
							cout << "The quarter wrapper is now full" << endl;
							cout << "The quarter wrapper has now been replaced" << endl;
							continue;
						}
						else
						{
							outfile << "There are now " << quartercounter << " coins in the quarters wrapper" << endl;
							cout << "There are now " << quartercounter << " coins in the quarters wrapper" << endl;
							continue;
						}
				}

				else if(actualdiameter <= MaxDiameter_Loonie && actualdiameter >= MinDiameter_Loonie && weightinGrams >= MinWeight_Loonie && weightinGrams <= MaxWeight_Loonie && compatibility == Value3)
				{
						looniecounter++;
						outfile << "The Coin Sorter has sent one coin to the loonies wrapper" << endl;

						if(looniecounter > MaxLoonie_per_Roll)
						{
							LooniesRollscounter++;
							looniecounter = 0;
							outfile << "The loonie wrapper is now full" << endl;
							outfile << "The loonie wrapper has now been replaced" << endl;
							cout << "The loonie wrapper is now full" << endl;
							cout << "The loonie wrapper has now been replaced" << endl;
							continue;
						}
						else
						{
							outfile << "There are now " << looniecounter << " coins in the loonies wrapper" << endl;
							cout << "There are now " << looniecounter << " coins in the loonies wrapper" << endl;
							continue;
						}
				}

				else if(actualdiameter <= MaxDiameter_Twonie && actualdiameter >= MinDiameter_Twonie && weightinGrams >= MinWeight_Twonie && weightinGrams <= MaxWeight_Twonie && compatibility == Value3)
				{
						twoniecounter++;
						outfile << "The Coin Sorter has sent one coin to the twonies wrapper" << endl;

						if(twoniecounter > MaxTwonie_per_Roll)
						{
							TwoniesRollscounter++;
							twoniecounter = 0;
							outfile << "The twonie wrapper is now full" << endl;
							outfile << "The twonie wrapper has now been replaced" << endl;
							cout << "The twonie wrapper is now full" << endl;
							cout << "The twonie wrapper has now been replaced" << endl;
							continue;
						}
						else
						{
							outfile << "There are now " << twoniecounter << " coins in the twonies wrapper" << endl;
							cout << "There are now " << twoniecounter << " coins in the twonies wrapper" << endl;
							continue;
						}
				}
					
			else
					{
						numOtherCoin++;                         //Keeps track of coins in the current contaner.
						totalOthercoincounter++;                //Total numbe of coins in the other coin category.
						othercoinweight = weightinGrams;        //Weight of the coins.
						totalOthercoin += othercoinweight;      //Ttal weight of all the coins.
						
						outfile << "The Coin Sorter has sent this coin to the other coin container" << endl;
						cout << "The Coin Sorter has sent this coin to the other coin container" << endl;
						
						othercontainerweight += othercoinweight; //Weight of the current container.

						if(othercontainerweight > MaxOtherContainerWeight) 
						{
							//If maximum weight is reached, the current coin counter is reset to 0. The current container is reset to 0. Then is incremented and is added to totl number of containers.
							numOtherCoin = 0;
							OthersCurrentContainer = 0;
							OthersCurrentContainer++;
							OthersContainercounter += OthersCurrentContainer;
							othercontainerweight = 0;
							othercontainerweight += othercoinweight;
							
							outfile << "This coin does not fit in the other coin container" << endl;
							outfile << "The other coin container has been replaced" << endl;
							outfile << "The coin in the new other coin container weighs " << fixed << setprecision(2) << othercontainerweight << " grams" << endl;
							cout << "This coin does not fit in the other coin container" << endl;
							cout << "The other coin container has been replaced" << endl;
							cout << "The coin in the new other coin container weighs " << fixed << setprecision(2) << othercontainerweight << " grams" << endl;
							continue;
						}
						else
						{
							outfile << " The coins in the other coin container now weigh " << fixed << setprecision(2) << othercontainerweight << " grams" << endl;
							
							cout << "The coins in the other coin container now weigh " << fixed << setprecision(2) << othercontainerweight << " grams" << endl;
							continue;
						}
					}
				
		}
	}

	//The following texts provide a summary of the coin sorter from the input data.


		cout << endl << endl << endl;
		outfile << endl << endl << endl;

		cout << "SUMMARY" << endl;
		cout << "The Coin Sorter made " << NickelsRollscounter<< " rolls of nickels." << endl;
		cout << "    There are " << nickelcounter << " nickels in the partially full roll." << endl;
		cout << "The Coin Sorter made " << DimesRollscounter << " rolls of dimes." << endl;
		cout << "    There are " << dimecounter << " dimes in the partially full roll." << endl;
		cout << "The Coin Sorter made " << QuartersRollscounter << " rolls of quarters." << endl;
		cout << "There are " << quartercounter << " quarters in the partially full roll." << endl;
		cout << "The Coin Sorter made " << LooniesRollscounter << " rolls of loonies." << endl;
		cout << "    There are " << looniecounter << " loonies in the partially full roll." << endl;
		cout << "The Coin Sorter made " << TwoniesRollscounter << " rolls of toonies." << endl;
		cout << "    There are " << twoniecounter << " toonies in the partially full roll." << endl;
		cout << "The Coin Sorter processed " << totalOthercoincounter << " other coins." << endl;
		cout << "    The other coins completely filled " <<  OthersContainercounter << " containers. " << endl;
		cout << "    There were " << numOtherCoin << " other coins in the partially full container" << endl;
		cout << "    The total weight of the other coins was "<< fixed << setprecision(3) <<  totalOthercoin << " grams" << endl;
		cout << "The Coin Sorter processed " << fixed << setprecision(4) << totalBentcoin << " g of bent coins" << endl;

		outfile << "SUMMARY" << endl;
		outfile << "The Coin Sorter made " << NickelsRollscounter<< " rolls of nickels." << endl;
		outfile << "    There are " << nickelcounter << " nickels in the partially full roll." << endl;
		outfile << "The Coin Sorter made " << DimesRollscounter << " rolls of dimes." << endl;
		outfile << "    There are " << dimecounter << " dimes in the partially full roll." << endl;
		outfile << "The Coin Sorter made " << QuartersRollscounter << " rolls of quarters." << endl;
		outfile << "There are " << quartercounter << " quarters in the partially full roll." << endl;
		outfile << "The Coin Sorter made " << LooniesRollscounter << " rolls of loonies." << endl;
		outfile << "    There are " << looniecounter << " loonies in the partially full roll." << endl;
		outfile << "The Coin Sorter made " << TwoniesRollscounter << " rolls of toonies." << endl;
		outfile << "    There are " << twoniecounter << " toonies in the partially full roll." << endl;
		outfile << "The Coin Sorter processed " << totalOthercoincounter << " other coins." << endl;
		outfile << "    The other coins completely filled " <<  OthersContainercounter << " containers. " << endl;
		outfile << "    There were " << numOtherCoin << " other coins in the partially full container" << endl;
		outfile << "    The total weight of the other coins was "<< fixed << setprecision(3) <<  totalOthercoin << " grams" << endl;
		outfile << "The Coin Sorter processed " << fixed << setprecision(4) << totalBentcoin << " g of bent coins" << endl;

		outfile.close();
		infile.close();
	
	return 0;
}