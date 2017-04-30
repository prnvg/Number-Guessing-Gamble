/* NUMBER GUESSING GAME */
#include<fstream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
/*
This program plays a simple game.The computer picks a random number
from 0 to 100, and the user tries to guess the number.
*/
const int totalchances=7;
void main()
{
  long int credit;        //the user's credit
  long int credit1;       //for reading from existing file
  int number;             //the computer's random number
  int guess;              //the user's guess
  int chances=0,earned=0;
  long int bet; 	  //the user's bet
  int newgame;            //for starting a new game
  char ch,x;
  clrscr();
  cout<<"Welcome to the Number Guessing game.";
  cout<<"\nI will pick a random number from 0 to 100.";
  cout<<"\nYou must try to guess the number.";
  cout<<"\nYou have maximum of 7 chances.";
  cout<<"\nYou have to bet a certain amount from your available credits. Minimum bet is 50";
  cout<<"\nYou will earn credits for correctly guessing the number according to your bet and the number of chances left.";
  cout<<"\nIf you fail to guess the correct number, you will lose the bet amount.";
  cout<<"\nPress any key to continue ";
  cin>>x;
  ifstream fin("credit.txt");
  fin>>credit1;
  if(fin)
  {
    clrscr();
    credit=credit1;
    cout<<"Wecome Back !!";
    delay(1000);
  }
  else
  {
    clrscr();
    credit=100;
    cout<<"You are playing for the first time. All the best!!";
    delay(1000);
  }
  do
  {
    clrscr();
    b:clrscr();
    cout<<"Your credits: "<<credit;
    if(credit>=50)
    {
      cout<<"\nEnter your bet: ";
      cin>>bet;
      a:if(bet<50||bet>credit)
      {
	while(bet<50)
	{
	  cout<<"Bet should be at least 50 credits.";
	  cout<<" Enter your bet: ";
	  cin>>bet;
	  goto a;
	}
	while(bet>credit)
	{
	  cout<<"You dont have sufficient credits to bet "<<bet;
	  cout<<". Enter your bet: ";
	  cin>>bet;
	  goto a;
	}
      }
      chances=earned=0;
      randomize();
      number=(int)(rand()%100);
      do
      {
	cout<<"\nWhat is your guess? (0 to 100) ";
	cin>>guess;
	if((guess<0)||(guess>100))
	{
	  cout<<"You have to guess number between 0 and 100 !!";
	}
	else if(guess < number)
	{
	  cout<<guess<<" is low. Try a higher number.";
	}
	else if(guess > number)
	{
	  cout<<guess<<" is high. Try a lower number.";
	}
	else		//if correct number is guessed
	{
	  cout<<guess<<" is correct. Congratulations!";
	  earned=bet*(totalchances-chances);   //earning calculated for number of chances left
	  credit+=earned;
	  cout<<" Your earning is "<<earned<<endl;
	  break;
	}
	chances++;
	if(guess!=number)
	cout<<"\nNow you have "<<totalchances-chances<<" chances left."<<endl;
	if(chances==totalchances)
	{
	  cout<<"Sorry. You are out of chances. Better luck next time !!";
	  cout<<"\nThe actual number was "<<number<<endl;
	  credit-=bet;
	  break;
	}
      }
      while (guess!=number);
      cout<<"Thank you for playing !";
      cout<<"\nYou have "<<credit<<" crdits left.";
      cout<<"\nWant to play it again? (y/n)...";
      cin>>ch;
    }
    else
    {
      cout<<"\nSorry. You don't have sufficient credits !!";
      cout<<"\nPress 1 to start a new game with 100 credits ";
      cin>>newgame;
      if(newgame==1)
      {
	credit=100;
	goto b;
      }
      else
      break;
    }
  }
  while(ch=='y'||ch=='Y');
  ofstream fout("credit.txt");
  fout<<credit;
  getch();
}