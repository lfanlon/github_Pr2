#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
int getValidatedInt(int minVal, int maxVal);// reused to validate menu choice and score count
double getValidatedScore (double minVal, double maxVal);
void inputScores(double scores[], int& count); 
void displayScores(double scores[], int count);
void displayMenu();
void computeStats(double scores[], int count, double &total, double &average,
double &minVal, double &maxVal);
void selectionSort(double scores[],int count);
void swap(double &a, double &b);
int linearSearch(const double scores[],int count, double target);
void writeReportToFile(string fileName, string studentName, int count, double scores[],
                       double total, double average,double minVal, double maxVal );

int main()
{   
    cout<< fixed<< setprecision(2);// to format the output 
    
    int choice;
    int count=0;
    double scores[50];
    double total=0;
    double average=0;
    double minVal=0;
    double maxVal=0;
    
    string fileName, studentName;
    
    cout<<"Welcome to the Student Scores Array Manager! \n\n" 
        <<"Enter your name: ";
        getline(cin, studentName);
        cout<<"Enter output File name (e.g., report.txt): ";
        getline(cin, fileName);
    inputScores(scores,count);
do
{
    displayMenu();
    cout<<"Enter your choice (1-5): ";
    choice =  getValidatedInt(1,5);//here I reused this function to validate choice input.
    if (choice==1)
    {
        displayScores(scores, count);
        cout<<endl;
    }
    else if (choice==2)                                                                                          
    {
        computeStats(scores,count,total, average, minVal,maxVal);
        cout<<"Statistics: \n";
        cout<<"Count: " <<count <<"\nTotal: "<<total
            <<"\nAverage: "<<average <<"\nMin: " <<minVal <<"\nMax: "<<maxVal << endl;
    }                                                                
    else if (choice==3)
    {
        double target;
        int position;
        cout<<"Enter the value to search(0-100): ";
        target=getValidatedScore(0,100);
        position=linearSearch(scores,count,target);
        if(position==-1)
        {
            cout<<"Value "<<target<<" was not found.\n";
        }
        else
        {
            cout<<"Value "<< target<<" was found at index " << position<<" \n\n";
        }
    }
    else if(choice==4)
    {
        selectionSort(scores, count);
        cout<<"Scores have been sorted in ascending order.\n\n";
    }
    else if (choice==5)
    {
        //recompute before writting to the report , so the report always has update values.
        computeStats(scores, count, total, average,minVal, maxVal);
        writeReportToFile(fileName, studentName, count, scores,
                       total, average, minVal, maxVal );
        cout<<"Exiting program. The report File has been generated. Goodbye!!";
        
    }
    
} 
 while(choice!=5);
    
    
    return 0;
    

}
int getValidatedInt(int minVal, int maxVal)
{
    int value;
    cin>> value;
    
     while (value<minVal || value>maxVal)
     {
         cout<<"Invalid value. Please enter a number between "
         << minVal << " and " << maxVal<<": ";
         cin >> value;
     }
     return value;
}

double getValidatedScore(double minVal, double maxVal)
{
    
    double value;
    cin>> value;
    while (value<minVal || value> maxVal)
    {
        cout <<"Invalid score. Please enter a score between "
        << minVal<<" and "<< maxVal<<" :";
        cin>> value;
    }
    return value;    
        
}  

void inputScores(double scores[], int& count)
{
  cout <<"How many scores do you want to enter (1-50): ";
  count= getValidatedInt(1,50);
  
  for(int i=0; i< count; i++)
  {
     cout<<"Enter score # " << i+1<<": ";
     scores[i]= getValidatedScore(0,100);
  }
}
void displayScores(double scores[], int count)
{
   cout<<"\n Score: \n";
   for (int i=0; i< count; i++)
     {
         cout << scores[i] << endl;
     }
      
}
void displayMenu()
{
    cout <<"------------------- Main Menu -----------------------\n\n"
         <<"1. Display scores\n"<<"2. Show statistics\n"
         <<"3. Search for a score\n"<<"4. Sort scores(ascending)\n"
         <<"5. Exit\n";
    
}

void computeStats(double scores[], int count, double &total, double &average,
double &minVal, double &maxVal)
{
    total=0;
    minVal= scores[0];
    maxVal= scores[0];
    for(int i=0; i<count; i++)
    {
        total += scores[i];
        if (scores[i]<minVal)
        {
            minVal = scores[i];
        }
        if (scores[i]> maxVal)
        {
            maxVal=scores [i];
        }
        
    }
    
    average=total/count;
    
}

void selectionSort(double scores[], int count) 
{ 
   int minIndex;
   double minValue;
 
   for (int start= 0; start < (count - 1); start++) 
   { 
      minIndex = start;
      minValue=scores[start];
       
      for (int index = start + 1; index < count; index++) 
      { 
         if (scores[index] < minValue) 
         { 
            minValue=scores[index];
            minIndex = index; 
         } 
      } 
      swap(scores[minIndex], scores[start]); 
   } 
} 

void swap(double &a, double &b) 
{ 
   double temp = a; 
   a = b; 
   b = temp; 
} 

int linearSearch (const double scores[], int count, double target) 
{ 
   int index = 0;      
   int position = -1;    
   bool found = false;   
    
   while (index < count && !found) 
   { 
       if (scores[index] == target)      
       { 
          found = true;              
          position = index;         
       } 
       index++;                      
   } 
   return position;                  
} 

void writeReportToFile(string fileName, string studentName, int count, double scores[],
                       double total, double average,double minVal, double maxVal )
{
    
    ofstream outFile(fileName);
    outFile<< fixed << setprecision(2);
    
    outFile<<"Student Scores Array Manager Report \n\n"
           <<"Student Name: " << studentName <<"\nCount: " <<count <<"\nTotal: "<<total
            <<"\nAverage: "<<average <<"\nMin: " << minVal <<"\nMax: "<<maxVal << "\nScores: ";
            for(int i=0; i<count; i++)
            {
                outFile<< scores[i] <<" ";
            }
            outFile.close();
}

