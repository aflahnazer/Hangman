#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<fstream.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<graphics.h>
#include<dos.h>

    const int maxlength=100;
    const int maxtries=5;
    const int maxrow=7;
    int score;
    char n[30];
    char title[20];
    int game_level;
    int guessed_letters[26];

    void main_menu();
    void heading(char[],int);
    void instructions();
    void instructions2();
    void highscores();
    int game(int);
    int fill(char,char[],char[]);
    void init(char[],char[]);
    void select_player();
    int select_game_level();
    void menu();
    void intro();
    void load_files();
    void music(int);
    void create_files();
    void file_missing();
    void settings();
    void sign_out();

 class player
    {
     int age;
     int score;
     public:
     char name[20];
     void insert_player();
     void existing_player();
     void modify_player();
     void update_score(int);
     void delete_player();
     void view_all_players();

  void get_data()
     {
      cout<<"\n\n\t\t   PLAYER DETAILS  ";
      cout<<"\n\n\t Enter the name of the player :   ";
      gets(name);
      cout<<"\n\t Enter the age                :   ";
      cin>>age;
     }

  void print_data()
     {
      cout<<"\n\n\t\t   PLAYER DETAILS  ";
      cout<<"\n\n\t\t Name     :    "<<name;
      cout<<"\n\t\t Age      :    "<<age;
      cout<<"\n\t\t Score    :    "<<score;
     }

  int get_age()
     {
      return age;
     }

  int get_score()
     {
      return score;
     }
 }P;

 void player::insert_player()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     player p1,play;
     char title[20]=" NEW PLAYER";
     heading(title,12);
     cout<<"\n\n";
     p1.get_data();
     p1.score=0;
     fstream infile("player.dat",ios::binary|ios::app);
     infile.write((char*)&p1,sizeof(p1));
     strcpy(n,p1.name);
     infile.close();
     cout<<"\n\n\t  Details Saved !!! \n\n";
     cout<<"\n\n  Press any key to continue";
     getch();
    }

 void player::existing_player()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     char nam[30];
     char found='n';
     char title[20]=" SEARCH PLAYER";
     heading(title,15);
     ifstream fi("player.dat",ios::in|ios::binary);
     cout<<"\n\n\t\tEnter the name of the Player  :   ";
     gets(nam);
     while(fi.read((char*)&P,sizeof(P)))
     {
      if(strcmpi(P.name,nam)==0)
      {
       strcpy(n,P.name);
       P.print_data();
       found='y';
       getch();
      }
     }
     if(found=='n')
     {
      cout<<"\n\n\t\tError!!!";
      cout<<"\n\n\t\tNo Such player Exists ";
      getch();
      fi.close();
      menu();
     }
    }

 void player::update_score(int s)
    {
     textbackground(WHITE);
     textcolor(BLUE);
     player p1;
     int pos;
     fstream fio("player.dat",ios::in|ios::out|ios::binary);
     fio.seekg(0);
     while(!fio.eof())
     {
      fio.read((char*)&p1,sizeof(p1));
      int pos=fio.tellg();
      if(strcmpi(p1.name,n)==0)
      {
       if(s>p1.score)
       {
	p1.score=s;
	cout<<"\n\n\t\tYour Score has been Updated ";
	cout<<"\n\n\t\tYour Current details   :";
	p1.print_data();
	getch();
	fio.seekg(pos-sizeof(p1));
	fio.write((char*)&p1,sizeof(p1));
       }
       else
       {
	cout<<"\n\n\t\tYour Current details   :";
	p1.print_data();
       }
      }
     }
     fio.close();
     sign_out();
     exit(0);
    }

 void player::modify_player()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     int ag;
     char ch,n[30],found='n';
     char nme[10];
     long pos;
     char title[20]=" MODIFY PLAYER";
     heading(title,15);
     player p1,p2;
     fstream fio("player.dat",ios::in|ios::out|ios::binary);
     cout<<"\n\tEnter the Name of the player to be modified  :   ";
     gets(n);
     while(!fio.eof())
     {
      pos=fio.tellg();
      fio.read((char*)&p1,sizeof(p1));
      if(strcmpi(p1.name,n)==0)
      {
       cout<<"\n\t\tExisting details of the player  :   ";
       cout<<"\n\t\tName     :   "<<p1.name;
       cout<<"\t\tAge      :   "<<p1.get_age();
       cout<<"\n\n\t\tEnter the new Name (Enter '.'to retain old one)  :   ";
       gets(nme);
       cout<<"\t\tEnter the new Age (Enter '0'to retain old one)   :   ";
       cin>>ag;
       age=p1.get_age();
       if(strcmpi(nme,".")!=0)
	strcpy(p1.name,nme);
       if(ag!=0)
	age=ag;
       fio.seekg(pos);
       fio.write((char*)&p1,sizeof(p1));
       found='y';
	break;
      }
     }
     if(found=='n')
     {
      cout<<"\n\t\tSorry Player not found";
      getch();
      return;
     }
     fio.seekg(0);
     fstream fi("player.dat",ios::in|ios::out|ios::binary);
     if(found=='y')
     {
      cout<<"\n\tThe updated data of the player  :   ";
      while(fi.read((char*)&p2,sizeof(p2)))
      {
       if(strcmpi(p2.name,nme)==0)
       {
	p2.print_data();
	getch();
       }
      }
      fi.close();
      fio.close();
     }
    }

 void player::delete_player()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     char ch;
     clrscr();
     char title[20]=" DELETE PLAYER ";
     heading(title,13);
     char deleted='y',confirm='n',found='n',nam[30];
     player p1;
     ifstream infile("player.dat",ios::binary|ios::in);
     ofstream outfile("temp.dat",ios::binary|ios::out);
     cout<<"\n\n\t\tEnter the name of the player to be deleted  :   ";
     gets(nam);
     while(infile.read((char*)&p1,sizeof(p1)))
     {
      if(strcmpi(p1.name,nam)==0)
      {
       p1.print_data();
       found='y';
       cout<<"\n\n\t\tAre you sure to want to delete this Player?  :   ";
       cin>>confirm;
       if(confirm=='n')
       {
	outfile.write((char*)&p1,sizeof(p1));
	deleted='n';
       }
      }
      else
      {
       outfile.write((char*)&p1,sizeof(p1));
      }
     }
     if(found=='n')
     {
      cout<<"\n\n\t\tError!!!";
      cout<<"\n\t\tSorry Record not found ";
      getch();
      return;
     }
     infile.close();
     outfile.close();
     remove("player.dat");
     rename("temp.dat","player.dat");
     if(deleted=='y')
     {
      cout<<"\n\n\t\t Player Deletion Succesfull ";
      getch();
     }
    }

 void player::view_all_players()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     char title[20]="VIEW ALL PLAYERS";
     heading(title,16);
     player p1,P;
     char ch;
     ifstream fin;
     fin.open("player.dat",ios::in|ios::binary);
     cout<<"\n\n\tNAME\t\t\tAGE\t\t\tSCORE";
     cout<<"\n\t----\t\t\t---\t\t\t-----\n";
     while(fin.read((char*)&P,sizeof(P)))
     {
      cout<<"\n\t"<<P.name;
      cout<<"\t\t\t"<<P.get_age();
      cout<<"\t\t\t"<<P.get_score();
     }
     fin.close();
     getch();
    }

 void main()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     intro();
     char found_not_first_time='y',found_player='y';
     ifstream infile("player.dat",ios::binary|ios::in);
     if(!infile)
      found_player='n';
     infile.close();
     ifstream ifile("!first_time.dat",ios::binary|ios::in);
     if(!ifile)
      found_not_first_time='n';
     ifile.close();
     if(found_player=='n'&&found_not_first_time=='n')
      create_files();
     if(found_not_first_time=='y'&&found_player=='y')
      load_files();
     if(found_player=='n'&&found_not_first_time=='y')
      file_missing();
     main_menu();
    }

 void intro()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\t\t";
       cprintf("****************************************************");
      }
     }
     cout<<"\n\n\t\t\t\t";
     textbackground(BLACK);
     {
      textcolor(GREEN);
      {
       cprintf("  WELCOME TO HANGMAN  ");
      }
     }
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n\t\t";
       cprintf("****************************************************");
      }
     }
     getch();
     cout<<"\n\n\t\t\t       _____                  "   ;
     cout<<"\n\t\t\t      |     |                 "   ;
     cout<<"\n\t\t\t      |   (`-')               "   ;
     cout<<"\n\t\t\t      |     |                 "   ;
     cout<<"\n\t\t\t      |    !|!                "   ;
     cout<<"\n\t\t\t      |     |                 "   ;
     cout<<"\n\t\t\t      |    ! !                "   ;
     cout<<"\n\t\t\t    __|__                     "   ;
     music(1);
     cout<<"\n\t\t\t\t\t\t\tDeveloped By  :";
     cout<<"\n\t\t\t\t\t\t\t\tAFLAH NAZER";
     cout<<"\n\t\t\t\t\t\t\t\t   AND";
     cout<<"\n\t\t\t\t\t\t\t\t  FIDAL";
     music(1);
     getch();
     music(1);
    }

 void create_files()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     char name[30];
     int age;
     int score;
     cout<<"\n\n\t\t\t\t\t     	__________";
     cout<<"\t\t\t\t\t\t    Creating Files     |";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     ofstream fout;
     fout.open("!first_time.dat",ios::app);
     if(!fout)
      cout<<"\n\n\t\tFile cannot be opened";
     fout.close();
     ofstream fout1;
     fout1.open("player.dat",ios::binary|ios::out);
     P.get_data();
     fout1.write((char*)&P,sizeof(P));
     fout1.close();
     cout<<"\n\t\t\tFile creation complete";
     cout<<"\nPress any key to continue";
     getch();
    }

 void load_files()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     cout<<"\n\n\t\t\t\t\t   __________";
     cout<<"\n\t\t\tLoading Files     |";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     cout<<"\n\n\t\t\t\tLoad complete";
     cout<<"\nPress any key to continue";
     getch();
    }

 void file_missing()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     char ch1;
     cout<<"\t\t   __________";
     cout<<"\n\t\t\tLoading Files     |";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     delay(600);cout<<"*";
     cout<<"\n\npress any key to continue";
     getch();
     clrscr();
     cout<<"\n\n\tThe file `Player.dat' is missing. Do you want to create it?";
     cout<<"\n\t{Caution: All your saved data will be lost}  :   ";
     cin>>ch1;
     if(ch1=='y')
     {
      ofstream fout;
      fout.open("player.dat",ios::binary|ios::out);
      P.get_data();
      fout.write((char*)&P,sizeof(P));
      fout.close();
      cout<<"\n\t\tFile creation complete";
      cout<<"\nPress any key to continue";
      getch();
     }
    }

 void music(int t)
   {
    int count=50;
    while(count--)
    {
     sound(10*random(10));
     delay(t);
     nosound();
     textattr(random(1)+'a'+BLINK);
    }
   }

 void main_menu()
    {
     main_menu:
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     int ch1;
     clrscr();
     char title[20]="  MAIN MENU  ";
     heading(title,13);
     cout<<"\n\n\t\t1. New Game";
     cout<<"\n\n\t\t2. Instructions";
     cout<<"\n\n\t\t3. Highscores";
     cout<<"\n\n\t\t4. Settings";
     cout<<"\n\n\t\t5. Exit";
     cout<<"\n\n\n\t\t  Please Choose One Option  :   ";
     cin>>ch1;
     switch(ch1)
     {
      case 1:
	     select_player();
	     int game_level=select_game_level();
	     int s=game(game_level);
	     P.update_score(s);
	     break;
      case 2:
	     instructions();
	     break;
      case 3:
	     highscores();
	     break;
      case 4:
	     settings();
	     break;
      case 5:
	     sign_out();
	     exit(0);
	     break;
     default:
	     cout<<"\n\n\t\tInvaild Entry!!!  Please Try again...";
	     cout<<"\nPress Any Key to Continue...";
	     getch();
	     goto main_menu;
    }
   }

 void heading(char title[],int n)
    {
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n";
       cprintf("================================");
      }
     }
     cout<<"\n\n";
     textbackground(YELLOW);
     {
      textcolor(GREEN);
      {
       cprintf("     " ) ;
       for(int i=0;i<=n;i++)
	cout<<title[i];
       cprintf("     ");
      }
     }
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n";
       cprintf("================================");
      }
     }
    }

 void instructions()
    {
     textbackground(WHITE);
     textcolor(BLACK);
     clrscr();
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\t\t";
       cprintf("****************************************************");
      }
     }
     cout<<"\n\n\t\t\t\t";
     textbackground(BLACK);
     {
      textcolor(GREEN);
      {
       cprintf("  WELCOME TO HANGMAN  ");
      }
     }
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n\t\t";
       cprintf("****************************************************");
      }
     }
     char title[20]=" GENERAL RULES ";
     heading(title,15);
     cout<<"\n 1.Each letter is represented by a star. ";
     cout<<"\n\n 2.Each time you guess a correct letter the star gets replaced by the letter. ";
     cout<<"\n\n 3.Each time you guess a wrong letter remaining guesses gets decremented by 1.";
     cout<<"\n\n 4.You can have a maximum of 5 wrong tries to guess the word.";
     cout<<"\n\n\n\nPress any key to continue...";
     getch();
     void insructions2();
     insructions2();
    }

 void insructions2()
    {
     textbackground(WHITE);
     textcolor(BLACK);
     clrscr();
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\t\t";
       cprintf("****************************************************");
      }
     }
     cout<<"\n\n\t\t\t\t";
     textbackground(BLACK);
     {
      textcolor(GREEN);
      {
       cprintf("  WELCOME TO HANGMAN  ");
      }
     }
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n\t\t";
       cprintf("****************************************************");
      }
     }
     char title[20]=" SCORE CRITERION ";
     heading(title,17);
     cout<<"\nEach time you guess a letter correctly  |";
     cout<<"  If you guess the word correctly";
     cout<<"\nyour score will be incremented by:      |";
     cout<<"  your score will be incremented by:";
     cout<<"\n\t\t\t\t\t|";
     cout<<"\n\tLEVEL\t\tSCORE           |";
     cout<<"  WRONG GUESSES\tSCORE";
     cout<<"\n\t\t\t\t\t|";
     cout<<"\n\tEASY\t\t 20             |";
     cout<<"\t0\t\t 200";
     cout<<"\n\tMEDIUM\t\t 40             |";
     cout<<"  \t1\t\t 180";
     cout<<"\n\tHARD\t\t 60             |";
     cout<<"  \t2\t\t 160";
     cout<<"\n\t\t\t\t\t|\t3\t\t 140";
     cout<<"\n\t\t\t\t\t|\t4\t\t 120";
     cout<<"\n\t\t\t\t\t|\t5\t\t 100";
     cout<<"\n\t\t****************************************************";
     cout<<"\n\t\t\t\t BEST WISHES";
     cout<<"\n\t\t\t  Press any key to continue...";
     getch();
     menu();
    }

 void highscores()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     char title[20]="  HIGHSCORE ";
     heading(title,13);
     player P3;
     int i,high_score,check=0;
     ifstream infile("player.dat",ios::in|ios::binary);
     infile.seekg(0);
     while(infile.read((char*)&P3,sizeof(P3)))
     {
      high_score=P3.get_score();
      check++;
     }
     ifstream file("player.dat",ios::in|ios::binary);
     while(file.read((char*)&P3,sizeof(P3)))
     {
      if(P3.get_score()>high_score)
       high_score=P3.get_score();
     }
     file.close();
     ifstream nfile("player.dat",ios::in|ios::binary);
     while(nfile.read((char*)&P3,sizeof(P3)))
     {
      if(high_score==P3.get_score())
      {
       P3.print_data();
       getch();
      }
     }
     nfile.close();
     menu();
    }

 int game(int game_level)
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     int s=0,count=0;
     char unknown[maxlength];
     char letter;
     int numofwrongguesses=0;
     char word[maxlength];
     if(game_level==1)
     {
      char words[][maxlength]=
      {
       "India","Pakistan","Japan","Nepal","Myanmar","Srilanka","Bangladesh"
       ,"China"
      };
      randomize();
      int n=random(8);
      strcpy(word,words[n]);
      init(word,unknown);
     }
     else if(game_level==2)
     {
      char words[][maxlength]=
      {
       "America","Southafrica","Mexico","Peru","Canada","Denmark","Netherlands"
       ,"Australia"
      };
      randomize();
      int n=random(8);
      strcpy(word,words[n]);
      init(word,unknown);
     }
     else if(game_level==3)
     {
      char  words[][maxlength]=
      {
       "Greenland","Slovakia","Czechoslovakia","Maldives","Papuanewguinea",
       "Ghana","Luxembourg","Iceland"
      };
      randomize();
      int n=random(1);
      strcpy(word,words[n]);
      init(word,unknown);
     }
     else
     {
      cout<<"\n\n\t\tInvalid entry. Please Try Again";
      menu();
     }
     clrscr();
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n\t\t";
       cprintf("****************************************************");
      }
     }
     cout<<"\n\n\t\t\t\t\t";
     textbackground(BLACK);
     {
      textcolor(GREEN);
      {
       cprintf("  HANGMAN  ");
      }
     }
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n\t\t";
       cprintf("****************************************************");
      }
     }
     while(numofwrongguesses<maxtries)
     {
      guess:
      clrscr();
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n\t\t";
       cprintf("****************************************************");
      }
     }
     cout<<"\n\n\t\t\t\t";
     textbackground(BLACK);
     {
      textcolor(GREEN);
      {
       cprintf("  HANGMAN  ");
      }
     }
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n\t\t";
       cprintf("****************************************************");
      }
     }
      cout<<"\n\n\n\t\t\t\t"<<unknown;
      cout<<"\n\n\t\t Guess a letter  :   ";
      cin>>letter;
      letter=tolower(letter);
      for(int i=0;i<count;i++)
      {
       if(guessed_letters[i]==letter)
       {
	cout<<"\n\n\t\tThe letter "<<letter;
	cout<<" is already guessed";
	getch();
	goto guess;
       }
      }
      count++;
      guessed_letters[count+1]=letter;
      int n=fill(letter,word,unknown);
      if(n==0)
      {
       cout<<endl<<"\n\n\t\t\t\t Sorry!!! \n\t\t\t The letter "<<letter<<" is not there ";
       cout<<endl;
       numofwrongguesses++;
      }
      else
      {
       cout<<endl<<"\n\n\t\t\t You have found a letter ";cout<<endl;
       if(game_level==1)
	s+=20;
       else if(game_level==2)
	s+=40;
       else if(game_level==3)
	s+=60;
      }
      cout<<"\n\n\t\t\t You have "<<maxtries-numofwrongguesses;
      cout<<" guesses left"<<endl;
      cout<<"\n\n\t\t\t Score  :   "<<s;
      getch();
      if(strcmpi(word,unknown)==0)
      {
       clrscr();
       cout<<"\n\n\n\n\t\t*******************************************";
       cout<<"\n\n\t\t\t  CONGRATULATIONS !!!!";
       cout<<"\n\n\t\t*******************************************";
       cout<<"\n\n\n\t\t\t You have found the word .";
       if(numofwrongguesses==0)
	s+=200;
       else if(numofwrongguesses==1)
	s+=180;
       else if(numofwrongguesses==2)
	s+=160;
       else if(numofwrongguesses==3)
	s+=140;
       else if(numofwrongguesses==4)
	s+=120;
       else if(numofwrongguesses==5)
	s+=100;
       cout<<"\n\n\t\t\t Score  :   "<<s;
       getch();
       break;
      }
     }
     if(numofwrongguesses==maxtries)
     {
      clrscr();
      cout<<"\n\n\n\t\t*******************************************";
      cout<<"\n\n\t\t\t      GAME OVER !!!!";
      cout<<"\n\n\t\t*******************************************";
      cout<<"\n\n\t\t\t YOU HAVE BEEN HANGED!!! "<<endl;
      cout<<"\n\n\t\t\t       _____                  "   ;
      cout<<"\n\t\t\t      |     |                 "   ;
      cout<<"\n\t\t\t      |   (`-')               "   ;
      cout<<"\n\t\t\t      |     |                 "   ;
      cout<<"\n\t\t\t      |    !|!                "   ;
      cout<<"\n\t\t\t      |     |                 "   ;
      cout<<"\n\t\t\t      |    ! !                "   ;
      cout<<"\n\t\t\t    __|__                     "   ;
      cout<<"\n\n\t\t\t The word was  :   "<<word<<endl;
      cout<<"\n\n\t\t\t Score         :   "<<s;
      getch();
     }
     return s;
    }

 void select_player()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     select_player:
     int ch;
     char title[20]=" PLAYER SELECTION";
     heading(title,18);
     cout<<"\n\n\n\t\t1.Existing Player";
     cout<<"\n\n\t\t2.New Player";
     cout<<"\n\n\n\t\t  Please Choose One Option  :   ";
     cin>>ch;
     switch(ch)
     {
      case 1:
	     P.existing_player();
	     break;
      case 2:
	     P.insert_player();
	     break;
     default:
	     cout<<"\n\n\t\tInvalid entry. Please Try Again";
	     getch();
	     goto select_player;
     }
    }

 int select_game_level()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     difficulty:
     clrscr();
     char title[20]=" GAME LEVEL";
     heading(title,12);
     cout<<"\n\n\t1. Easy";
     cout<<"\n\n\t2. Medium";
     cout<<"\n\n\t3. Hard";
     cout<<"\n\n\n\t\t  Please Choose One Option  :   ";
     cin>>game_level;
     return game_level;
    }

 int fill(char guess,char secretword[],char guessword[])
    {
     int i;
     int matches=0;
     for(i=0;guessword[i]!='\0';i++)
     {
      if(guess==secretword[i]||toupper(guess)==secretword[i])
      {
       guessword[i]=guess;
       matches++;
      }
     }
     return matches;
    }

 void init(char word[],char unknown[])
    {
     int i;
     int length=strlen(word);
     for(i=0;i<length;i++)
     unknown[i]='*';
     unknown[i]='\0';
    }

 void menu()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     char title[20]="  SUB-MENU ";
     heading(title,12);
     int ch2;
     menu:
     cout<<"\n\n\t\t1. Return to main menu";
     cout<<"\n\n\t\t2. PLAY HANGMAN";
     cout<<"\n\n\t\t3. Exit";
     cout<<"\n\n\n\t\t Please Choose One Option  :   ";
     cin>>ch2;
     switch(ch2)
     {
      case 1:
	     main_menu();
	     break;
      case 2:
	     select_player();
	     int game_level=select_game_level();
	     int s=game(game_level);
	     P.update_score(s);
	     break;
      case 3:
	     sign_out();
	     exit(0);
	     break;
     default:
	     cout<<"\n\n\t\tInvaild Entry.Please Try Again";
	     getch();
	     goto menu;
     }
    }

 void settings()
    {
     settings:
     textbackground(WHITE);
     textcolor(BLUE);
     int ch;
     char ch1,ch2,ch3,ch4,ch5,ch6,ch7,ch8,ch9;
     player p1;
     clrscr();
     char title[20]="  SETTINGS ";
     heading(title,12);
     cout<<"\n\n\n\t\t1. View all Players";
     cout<<"\n\n\t\t2. Add Player";
     cout<<"\n\n\t\t3. Search player";
     cout<<"\n\n\t\t4. Edit Player details";
     cout<<"\n\n\t\t5. Delete a Player";
     cout<<"\n\n\n\t\t Please Choose One Option  :   ";
     cin>>ch;
     switch(ch)
     {
      case 1:
	     p1.view_all_players();
	     cout<<"\n\n\tDo you want to return back to SETTINGS?   :  ";
	     cin>>ch1;
	     if(ch1=='y'|ch1=='Y')
	      goto settings;
	     else
	      menu();
      case 2:
	     do
	     {
	      p1.insert_player();
	      cout<<"\n\n\tDo you want to add more Players?   :  ";
	      cin>>ch2;
	     }while(ch2=='y'|ch2=='Y');
	     cout<<"\n\tDo you want to return back to SETTINGS?   :  ";
	     cin>>ch3;
	     if(ch3=='y'|ch3=='Y')
	      goto settings;
	     else
	      menu();
      case 3:
	     do
	     {
	      p1.existing_player();
	      cout<<"\n\n\tDo you want to search for more Players?   :  ";
	      cin>>ch4;
	     }while(ch4=='y'|ch4=='Y');
	     cout<<"\n\tDo you want to return back to SETTINGS?   :  ";
	     cin>>ch5;
	     if(ch5=='y'|ch5=='Y')
	      goto settings;
	     else
	      menu();
      case 4:
	     do
	     {
	      p1.modify_player();
	      cout<<"\n\n\tDo you want to modify more Players?   :  ";
	      cin>>ch6;
	     }while(ch6=='y'|ch6=='Y');
	     cout<<"\n\tDo you want to return back to SETTINGS?   :  ";
	     cin>>ch7;
	     if(ch7=='y'|ch7=='Y')
	      goto settings;
	     else
	      menu();
      case 5:
	     do
	     {
	      p1.delete_player();
	      cout<<"\n\n\tDo you want to delete more Players?   :  ";
	      cin>>ch8;
	     }while(ch8=='y'|ch8=='Y');
	     cout<<"\n\tDo you want to return back to SETTINGS?   :  ";
	     cin>>ch9;
	     if(ch9=='y'|ch9=='Y')
	      goto settings;
	     else
	      menu();
     }
    }

 void sign_out()
    {
     textbackground(WHITE);
     textcolor(BLUE);
     clrscr();
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n\n\n\t\t";
       cprintf("****************************************************");
      }
     }
     cout<<"\n\n\t\t\t";
     textbackground(BLACK);
     {
      textcolor(GREEN);
      {
       cprintf("  THANK YOU FOR PLAYING HANGMAN  ");
      }
     }
     textbackground(WHITE);
     {
      textcolor(RED);
      {
       cout<<"\n\n\t\t";
       cprintf("****************************************************");
      }
     }
     getch();
     cout<<"\n\n\n\t\t\t\t***  HAVE A GREAT DAY  ***";
     getch();
     cout<<"\n\n\n\n\t\t\t\t\t\t\t\t-AFLAH NAZER";
     getch();
    }
