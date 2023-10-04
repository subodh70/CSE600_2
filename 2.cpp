#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>   
#include <stdlib.h>
using namespace std;
int stu=-1,fac=-1,s=1999,f=5999,user_stu[100],user_fac[100],cnt[110],b_id[110],ind_store[100],issue_var=0,issue_var_m=0;
string author[110], isbn[110], title[110],pub[83],b_issued[100],m_issued[100];
//Ques 2 global Data structures & variables :
string lib1_title[3]={"Fundamentals of Electrical Engineering" , "Fundamentals of Mechanical Engineering" ,"Fundamentals of Civil Engineering"}, // assume library 1 is library of IIT-Delhi
lib1_isbn[3]={"7777777777","8888888888","9999999999"},
lib1_auth[3]={"Ram Kumar" , "Sham Jha" , "Alka Gupta"},
lib2_title[3]={"Cardiology","Neurology","Oncology"},        // aaume library 2 is of AIIMS Delhi
lib2_isbn[3]={"2222222222","3333333333","1111111111"},
lib2_auth[3]={"Namita Johri","Dr. Sadhana","Girish Chandr"},
rec1[100],rec2[100];
int lib_str[3] , other_rec1=0,other_rec2=0;


/*******************************************Reading******************************************/

class library
{
public:
    string b_title, m_title; // each item assigned identifier
};

/*************************************************************Reading Starts******************************************************************/

class books : public library
{
public:
    int  j = 0; 
    void loadBooks(const string &filename)
    {
        ifstream file(filename);

        if (!file.is_open())
        {
            cout << "Error: Could not open file " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Read and discard the header line

        int line_number = 1;
        while (getline(file, line))
        {
            int n = line.size(), id, book_count, col_count = 0;
            string temp, Isbn, authors;
            for (int i = 0; i < n;)
            {

                if (line[i] == '"')
                {
                    i++;
                    while (line[i] != '"')
                    {
                        temp.push_back(line[i]);
                        i++;
                    }
                    if (col_count == 7)
                    {
                        authors = temp;
                    }
                    else if (col_count == 9)
                    {
                        b_title = temp;
                    }
                    i++;
                }
                if (line[i] == ',')
                {
                    if (col_count == 0)
                    {
                        id = stoi(temp);
                    }
                    else if (col_count == 4)
                    {
                        book_count = stoi(temp);
                    }
                    else if (col_count == 5)
                    {
                        long double y = stod(temp);
                        long long int x = y;
                        Isbn = to_string(x);
                    }
                    else if (col_count == 7)
                    {
                        authors = temp;
                    }
                    else if (col_count == 9)
                    {
                        b_title = temp;
                    }
                    temp = "";
                    col_count++;
                    i++;
                }
                else
                {
                    temp.push_back(line[i]);
                    i++;
                }
            }
            
            b_id[j] = id;
            author[j] = authors ;
            isbn[j] = Isbn;
            title[j] = b_title;
            cnt[j] = book_count;
            j++;
            line_number++;
        }
        file.close();
        

    }

};

class magazine : public library
{
    public :
    void readmagazines()
{
    ifstream f("Magzines.csv");
    if(!f.is_open())
       return ;
    
    string line;
    getline(f,line);
    int x=0;
    while(getline(f,line))
    {
       
        stringstream ss(line);
        getline(ss,m_title,'"');
        getline(ss,m_title,'"');
        pub[x] = m_title;
        x++;
    }
    f.close();
    
}
};

/*************************************************************Reading Over*******************************************************************/

/////////////used during issue , to check whether user is registered or not////////////////////////

int check(int id)       
{
    int f=0;
    for(int i=0;i<100;i++)
  {
    if(user_stu[i]==id||user_fac[i]==id)
       f++;
  }
  
 return f; 
}

//////////////////////////to get issue time////////////////////////////////////

void time() 
{
    time_t now = time(0); //current date/time wrt to system 
    char* dt = ctime(&now); // convert it into string  
    cout<< "\nDate & time of issue is: "<<dt;
}

/////////////////////// user registration 1(iv)/////////////////////////////////////

void reg(char c) 
{
  int h=0;
  if(c=='s'||c=='S')
  {
   cout<<"Registered as student with id : "<<s+1;
   stu+=1;
   user_stu[stu]=s+1;
   s+=1;
   cout<<"\nStudents' IDs registered till date : ";
   for(;h<20;h++)
   {
        if(user_stu[h]==0)
    break;
    cout<<user_stu[h]<<"\t";
    }
  } 
  if(c=='f'||c=='F')
   {
    cout<<"Registered as faculty with id : "<<f+1;
    fac+=1; 
    user_fac[fac]=f+1;
    f+=1;
    cout<<"\nFaculties' IDs registered till date : ";
    for(;h<20;h++)
    {
        if(user_fac[h]==0)
    break;
    cout<<user_fac[h]<<"\t";
    }
   }
}

////////////////////////////Other Library////////////////////////

void other_title(string x)
{
    int y=1,p;
    char u;
    for (int i = 0; i < 3; i++) 
    {
        if (lib1_title[i].find(x) != std::string::npos)
         {
            lib_str[y] = i; 
            cout<<"\n"<<y<<". "<<lib1_title[i]<<"\nAuthor : "<<lib1_auth[i]<<"\nISBN : "<<lib1_isbn[i]<<"\nLocation : IIT-Delhi";
            y++;
        }
    }
    
    if(y>1)
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nBook : "<<lib1_title[lib_str[p]]<<" issued ";
                 time();
                  rec1[other_rec1]=lib1_title[lib_str[p]];
                  other_rec1++;
                  cout<<"\nRecord of Borrowing from IIT-Delhi : ";
                  for(i=0;i<20;i++)
                  {
                    cout<<"\n"<<rec1[i]<<"\t";
                  }
            }
        }
    }
    else if(y==1)
    {
    cout<<"\nNot present in IIT_Delhi , checking in AIIMS Delhi......";
    for (int i = 0; i < 3; i++) 
    {
        if (lib2_title[i].find(x) != std::string::npos)
         {
            lib_str[y] = i; 
            cout<<"\n"<<y<<". "<<lib2_title[i]<<"\nAuthor : "<<lib2_auth[i]<<"\nISBN : "<<lib2_isbn[i]<<"\nLocation : AIIMS Delhi ";
            y++;
        }
    }
         if(y>1)
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nBook : "<<lib2_title[lib_str[p]]<<" issued ";
                 time();
                  rec1[other_rec1]=lib2_title[lib_str[p]];
                  other_rec2++;
                  cout<<"\nRecord of Borrowing from AIIMS Delhi : ";
                  for(i=0;i<20;i++)
                  {
                    cout<<"\n"<<rec2[i]<<"\t";
                  }
            }
        }
    }
    }
    
    else
    cout<<"\nNot found";

}

void other_auth(string x)
{
    int y=1,p;
    char u;
    for (int i = 0; i < 3; i++) 
    {
        if (lib1_auth[i].find(x) != std::string::npos)
         {
            lib_str[y] = i; 
            cout<<"\n"<<y<<". "<<lib1_title[i]<<"\nAuthor : "<<lib1_auth[i]<<"\nISBN : "<<lib1_isbn[i]<<"\nLocation : IIT-Delhi";
            y++;
        }
    }
    
    if(y>1)
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nBook : "<<lib1_title[lib_str[p]]<<" issued ";
                 time();
                  rec1[other_rec1]=lib1_title[lib_str[p]];
                  other_rec1++;
                  cout<<"\nRecord of Borrowing from IIT-Delhi : ";
                  for(i=0;i<20;i++)
                  {
                    cout<<"\n"<<rec1[i]<<"\t";
                  }
            }
        }
    }
    else if(y==1)
    {
    cout<<"\nNot present in IIT_Delhi , checking in AIIMS Delhi......";
    for (int i = 0; i < 3; i++) 
    {
        if (lib2_auth[i].find(x) != std::string::npos)
         {
            lib_str[y] = i; 
            cout<<"\n"<<y<<". "<<lib2_title[i]<<"\nAuthor : "<<lib2_auth[i]<<"\nISBN : "<<lib2_isbn[i]<<"\nLocation : AIIMS Delhi ";
            y++;
        }
         }     if(y>1)
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nBook : "<<lib2_title[lib_str[p]]<<" issued ";
                 time();
                  rec1[other_rec1]=lib2_title[lib_str[p]];
                  other_rec2++;
                  cout<<"\nRecord of Borrowing from AIIMS Delhi : ";
                  for(i=0;i<20;i++)
                  {
                    cout<<"\n"<<rec2[i]<<"\t";
                  }
            }
        }
    }
    }
    
    else
    cout<<"\nNot found";

}

void other_isbn(string x)
{
    int y=1,p;
    char u;
    for (int i = 0; i < 3; i++) 
    {
        if (lib1_isbn[i].find(x) != std::string::npos)
         {
            lib_str[y] = i; 
            cout<<"\n"<<y<<". "<<lib1_title[i]<<"\nAuthor : "<<lib1_auth[i]<<"\nISBN : "<<lib1_isbn[i]<<"\nLocation : IIT-Delhi";
            y++;
        }
    }
    
    if(y>1)
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nBook : "<<lib1_title[lib_str[p]]<<" issued ";
                 time();
                  rec1[other_rec1]=lib1_title[lib_str[p]];
                  other_rec1++;
                  cout<<"\nRecord of Borrowing from IIT-Delhi : ";
                  for(i=0;i<20;i++)
                  {
                    cout<<"\n"<<rec1[i]<<"\t";
                  }
            }
        }
    }
    else if(y==1)
    {
    cout<<"\nNot present in IIT_Delhi , checking in AIIMS Delhi......";
    for (int i = 0; i < 3; i++) 
    {
        if (lib2_isbn[i].find(x) != std::string::npos)
         {
            lib_str[y] = i; 
            cout<<"\n"<<y<<". "<<lib2_title[i]<<"\nAuthor : "<<lib2_auth[i]<<"\nISBN : "<<lib2_isbn[i]<<"\nLocation : AIIMS Delhi ";
            y++;
        }
       }
          if(y>1)
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nBook : "<<lib2_title[lib_str[p]]<<" issued ";
                 time();
                  rec1[other_rec1]=lib2_title[lib_str[p]];
                  other_rec2++;
                  cout<<"\nRecord of Borrowing from AIIMS Delhi : ";
                  for(i=0;i<20;i++)
                  {
                    cout<<"\n"<<rec2[i]<<"\t";
                  }
            }
        }
    }
    }
    
    else
    cout<<"\nNot found";

}



/*************************************************************Searching Starts*******************************************************************/

void by_author(string x)
{
    int y=1,p;
    char u;
    for (int i = 0; i < 110; i++) 
    {
        if (author[i].find(x) != std::string::npos)
         {
            
            ind_store[y] = i; 
            cout<<"\n"<<y<<". "<<title[i]<<"\nAuthor : "<<author[i]<<"\nBook Id = "<<b_id[i]<<"\nISBN : "<<isbn[i]<<"\nLocation : ";
            // Location of books
            if(i<25)
            cout<<"Shelf 1\n" ;   
            if(i>=25&&i<=49)
            cout<<"Shelf 2\n" ;  
            if(i>=50&&i<=74)
            cout<<"Shelf 3\n" ;   
            if(i>=75)
            cout<<"Shelf 4\n" ; 
            y++;
        }
    }
    if(y==1)
    {
    cout<<"\nNot present,Do you want to search in other libraries (Y/N) : ";
    cin>>u;
    if(u=='Y'||u=='y')
    other_auth(x);
    }
    else
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            char c1;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nBook : "<<title[ind_store[p]]<<" issued ";
                 cout<<"\nEarlier count : "<<cnt[ind_store[p]];
                 cout<<"\n Current Count = "<<--cnt[ind_store[p]];
                 b_issued[issue_var]=title[ind_store[p]]; //record of issue
                issue_var+=1;
                time();
                cout<<"\nBooks issued till date : ";  //issue record print
                for(k=0;k<20;k++)
                cout<<b_issued[k]<<"\t";

            }
        }
    }
}    

void by_ISBN(string x)
{
int y=1,p;
char u;
    for (int i = 0; i < 110 ; ++i)
     {
        if (isbn[i].find(x) != std::string::npos) 
        {
            ind_store[y] = i; 
            cout<<"\n"<<y<<". "<<title[i]<<"\nAuthor : "<<author[i]<<"\nBook Id = "<<b_id[i]<<"\nISBN : "<<isbn[i]<<"\nLocation : ";
            // Location of books
            if(i<25)
            cout<<"Shelf 1\n" ;   
            if(i>=25&&i<=49)
            cout<<"Shelf 2\n" ;  
            if(i>=50&&i<=74)
            cout<<"Shelf 3\n" ;   
            if(i>=75)
            cout<<"Shelf 4\n" ; 
            y++;
        }
    }
  if(y==1)
    {
    cout<<"\nNot present,Do you want to search in other libraries (Y/N) : ";
    cin>>u;
    if(u=='Y'||u=='y')
    other_isbn(x);
    }
    else
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            char c1;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nBook : "<<title[ind_store[p]]<<" issued ";
                 cout<<"\nEarlier count : "<<cnt[ind_store[p]];
                 cout<<"\n Current Count = "<<--cnt[ind_store[p]];
                 b_issued[issue_var]=title[ind_store[p]]; //record of issue
                issue_var+=1;
                time();
                cout<<"\nBooks issued till date : ";  //issue record print
                for(k=0;k<20;k++)
                cout<<b_issued[k]<<"\t";

            }
        }
    }
}    
void by_title(string x)
{
int y=1,p;
char u;
    for (int i = 0; i < 110 ; ++i) 
    {
        if (title[i].find(x) != std::string::npos) 
        {
            ind_store[y] = i; 
            cout<<"\n"<<y<<". "<<title[i]<<"\nAuthor : "<<author[i]<<"\nBook Id = "<<b_id[i]<<"\nISBN : "<<isbn[i]<<"\nLocation : ";
            // Location of books
            if(i<25)
            cout<<"Shelf 1\n" ;   
            if(i>=25&&i<=49)
            cout<<"Shelf 2\n" ;  
            if(i>=50&&i<=74)
            cout<<"Shelf 3\n" ;   
            if(i>=75)
            cout<<"Shelf 4\n" ; 
            y++;
            
        }
    }
    if(y==1)
    {
    cout<<"\nNot present,Do you want to search in other libraries (Y/N) : ";
    cin>>u;
    if(u=='Y'||u=='y')
    other_title(x);
    }
    else
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            char c1;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nBook : "<<title[ind_store[p]]<<" issued ";
                 cout<<"\nEarlier count : "<<cnt[ind_store[p]];
                 cout<<"\n Current Count = "<<--cnt[ind_store[p]];
                 b_issued[issue_var]=title[ind_store[p]]; //record of issue
                issue_var+=1;
                time();
                cout<<"\nBooks issued till date : ";  //issue record print
                for(k=0;k<20;k++)
                cout<<b_issued[k]<<"\t";

            }
        }
    }
}     

void by_mtitle(string x)
{
    int y = 1,p;
    char u;
    for (int i = 0; i < 83; ++i)
    {
        if (pub[i].find(x) != std::string::npos)
        {
            ind_store[y] = i;
            cout << "\n" << y << ". " << pub[i] << "\nLocation : ";
            // Location of magazines
            if (i < 20)
                cout << "Shelf 5";
            else if (i >= 20 && i <= 39)
                cout << "Shelf 6";
            else if (i >= 40 && i <= 59)
                cout << "Shelf 7";
            else if (i >= 60)
                cout << "Shelf 8";
            y++;
        }
    }
 if(y==1)
    {
    cout<<"\nNot present,Do you want to search in other libraries (Y/N) : ";
    cin>>u;
    if(u=='Y'||u=='y')
    other_title(x);
    }
    else
    {
        cout<<"\nDo you want to issue from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
            int i,k;
            char c1;
            cout<<"\nYour id =  ";
            cin>>i;
            k = check(i);
            if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
            else
            {
                 if(i<6000)
                     cout<<"\nYou are student , items will be issued for 1 month";
                 else if(i>=6000)
                      cout<<"\nYou are faculty , items will be issued for 6 months";
          
          
                 cout<<"\nWhich magzine you want to issue , enter it's S.No. from above : ";
                 cin>>p;
                 cout<<"\nMagazine : "<<pub[ind_store[p]]<<" issued ";
                 m_issued[issue_var_m]=title[ind_store[p]]; //record of issue
                 issue_var_m+=1;
                 time();
                 cout<<"\nMagazines issued till date : "; //issue record print
                for(k=0;k<20;k++)
                cout<<m_issued[k]<<"\t";
            }
        }
    }
}               


/*************************************************************Searching Over*********************************************************************/

/*************************************************************Issuing Starts*********************************************************************/


void b_issue()
{
   char c,u;
   int p,k;
   cout<<"\nIssue by author (press A) / ISBN (press I) / Title (press T) : ";
   cin>>c;
   if(c=='A')
    {
        string x;
        cout << "\nEnter the author to search for: ";
        cin >> x;
        int y=1;
       for (int i = 0; i < 110 ; ++i) 
        {
           if (author[i].find(x) != std::string::npos) 
           {
            ind_store[y] = i; 
            cout<<"\n"<<y<<". "<<title[i]<<"\nAuthor : "<<author[i]<<"\nBook Id = "<<b_id[i]<<"\nISBN : "<<isbn[i]<<"\nLocation : ";
            // Location of books
            if(i<25)
            cout<<"Shelf 1\n" ;   
            if(i>=25&&i<=49)
            cout<<"Shelf 2\n" ;  
            if(i>=50&&i<=74)
            cout<<"Shelf 3\n" ;   
            if(i>=75)
            cout<<"Shelf 4\n" ; 
            y++;
            
          }
        }
      if(y==1)
    {
    cout<<"\nNot present,Do you want to search in other libraries (Y/N) : ";
    cin>>u;
    if(u=='Y'||u=='y')
    other_auth(x);
    }
      else
      {
        cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
        cin>>p;
        cout<<"\nBook : "<<title[ind_store[p]]<<" issued ";
        cout<<"\nEarlier count : "<<cnt[ind_store[p]];
        cout<<"\n Current Count = "<<--cnt[ind_store[p]];
        b_issued[issue_var]=title[ind_store[p]]; //record of issue
        issue_var+=1;
        time();
        cout<<"\nBooks issued till date : ";  //issue record print
                for(k=0;k<20;k++)
                cout<<b_issued[k]<<"\t";

      }

    }

   else if(c=='I')
    {
        string x;
        cout << "\nEnter the ISBN to search for: ";
        cin >> x;
        int y=1;
        for (int i = 0; i < 110 ; ++i) 
      {
        if (isbn[i].find(x) != std::string::npos) 
        {
            ind_store[y] = i; 
            cout<<"\n"<<y<<". "<<title[i]<<"\nAuthor : "<<author[i]<<"\nBook Id = "<<b_id[i]<<"\nISBN : "<<isbn[i]<<"\nLocation : ";
            // Location of books
            if(i<25)
            cout<<"Shelf 1\n" ;   
            if(i>=25&&i<=49)
            cout<<"Shelf 2\n" ;  
            if(i>=50&&i<=74)
            cout<<"Shelf 3\n" ;   
            if(i>=75)
            cout<<"Shelf 4\n" ; 
            y++;
            
        }
      }
    if(y==1)
    {
    cout<<"\nNot present,Do you want to search in other libraries (Y/N) : ";
    cin>>u;
    if(u=='Y'||u=='y')
    other_isbn(x);
    }
     else
      {
            cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
        cin>>p;
        cout<<"\nBook : "<<title[ind_store[p]]<<" issued ";
        cout<<"\nEarlier count : "<<cnt[ind_store[p]];
        cout<<"\n Current Count = "<<--cnt[ind_store[p]];
        b_issued[issue_var]=title[ind_store[p]]; //record of issue
        issue_var+=1;
        time();
        cout<<"\nBooks issued till date : ";  //issue record print
                for(k=0;k<20;k++)
                cout<<b_issued[k]<<"\t";

        
      }

    }
         
  else if(c=='T')
    {
        string x;
        cout << "\nEnter the title to search for: ";
        cin >> x;
        int y=1;
        for (int i = 0; i < 110 ; ++i) 
      {
        if (title[i].find(x) != std::string::npos) 
        {
            ind_store[y] = i; 
            cout<<"\n"<<y<<". "<<title[i]<<"\nAuthor : "<<author[i]<<"\nBook Id = "<<b_id[i]<<"\nISBN : "<<isbn[i]<<"\nLocation : ";
            // Location of books
            if(i<25)
            cout<<"Shelf 1\n" ;   
            if(i>=25&&i<=49)
            cout<<"Shelf 2\n" ;  
            if(i>=50&&i<=74)
            cout<<"Shelf 3\n" ;   
            if(i>=75)
            cout<<"Shelf 4\n" ; 
            y++;
                       
        }
      }
   if(y==1)
    {
    cout<<"\nNot present,Do you want to search in other libraries (Y/N) : ";
    cin>>u;
    if(u=='Y'||u=='y')
    other_title(x);
    }
    else
      {
        cout<<"\nWhich book you want to issue , enter it's S.No. from above : ";
        cin>>p;
        cout<<"\nBook : "<<title[ind_store[p]]<<" issued ";
        cout<<"\nEarlier count : "<<cnt[ind_store[p]];
        cout<<"\n Current Count = "<<--cnt[ind_store[p]];
        b_issued[issue_var]=title[ind_store[p]]; //record of issue
        issue_var+=1;
        time();
        cout<<"\nBooks issued till date : ";  //issue record print
                for(k=0;k<20;k++)
                cout<<b_issued[k]<<"\t";
      }
    } 

 else
        cout<<"\nWrong Choice";
        
}
void m_issue()
{
     int y = 1,p,k;
     string x;
     char u;
        cout << "\nEnter the publication to search for: ";
        cin >> x;
    for (int i = 0; i < 83; ++i)
    {
        if (pub[i].find(x) != std::string::npos)
        {
            ind_store[y] = i;
            cout << "\n" << y << ". " << pub[i] << "\nLocation : ";
            // Location of magazines
            if (i < 20)
                cout << "Shelf 5";
            else if (i >= 20 && i <= 39)
                cout << "Shelf 6";
            else if (i >= 40 && i <= 59)
                cout << "Shelf 7";
            else if (i >= 60)
                cout << "Shelf 8";
            y++;
        }
    }
 if(y==1)
    {
    cout<<"\nNot present,Do you want to search in other libraries (Y/N) : ";
    cin>>u;
    if(u=='Y'||u=='y')
    other_title(x);
    }
    else
    {
        cout<<"\nWhich magzine you want to issue , enter it's S.No. from above : ";
        cin>>p;
        cout<<"\nBook : "<<pub[ind_store[p]]<<" issued ";
        m_issued[issue_var_m]=title[ind_store[p]]; //record of issue
        issue_var_m+=1;
        time();
        cout<<"\nBooks issued till date : ";  //issue record print
                for(k=0;k<20;k++)
                cout<<m_issued[k]<<"\t";
        
       
    }
}

/*************************************************************Issuing Over*********************************************************************/

/*************************************************************Buying Starts*********************************************************************/

void buy_title(string x)
{
int y=1,p,b,a;
char u;
    for (int i = 0; i < 110 ; ++i) 
    {
        if (title[i].find(x) != std::string::npos) 
        {
            ind_store[y] = i; 
            cout<<"\n"<<y<<". "<<title[i]<<"\nAuthor : "<<author[i]<<"\nBook Id = "<<b_id[i]<<"\nISBN : "<<isbn[i];
            y++;
         }
    }
    if(y==1)
    cout<<"\nNot present";
    else
    {
        cout<<"\nDo you want to buy from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
        cout<<"\nWhich book you want to buy , enter it's S.No. from above : ";
        cin>>p;
        cout<<"#Copies you want to order = ";
        cin>>b;
        cout<<"\n"<<b<<" copies of "<<title[ind_store[p]]<<" ordered ";
        cout<<"\nEarlier count : "<<cnt[ind_store[p]];
        a = b + cnt[ind_store[p]];
        cout<<"\n Current Count = "<<a;
        }
    }
}      

void buy_author(string x)
{
int y=1,p,b,a;
char u;
    for (int i = 0; i < 110 ; ++i) 
    {
        if (author[i].find(x) != std::string::npos) 
        {
            ind_store[y] = i; 
            cout<<"\n"<<y<<". "<<title[i]<<"\nAuthor : "<<author[i]<<"\nBook Id = "<<b_id[i]<<"\nISBN : "<<isbn[i];
            y++;
         }
    }
    if(y==1)
    cout<<"\nNot present";
    else
    {
        cout<<"\nDo you want to buy from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
        cout<<"\nWhich book you want to buy , enter it's S.No. from above : ";
        cin>>p;
        cout<<"#Copies you want to order = ";
        cin>>b;
        cout<<"\n"<<b<<" copies of "<<title[ind_store[p]]<<" ordered ";
        cout<<"\nEarlier count : "<<cnt[ind_store[p]];
        a = b + cnt[ind_store[p]];
        cout<<"\n Current Count = "<<a;
        }
    }
} 

void buy_isbn(string x)
{
int y=1,p,b,a;
char u;
    for (int i = 0; i < 110 ; ++i) 
    {
        if (isbn[i].find(x) != std::string::npos) 
        {
            ind_store[y] = i; 
            cout<<"\n"<<y<<". "<<title[i]<<"\nAuthor : "<<author[i]<<"\nBook Id = "<<b_id[i]<<"\nISBN : "<<isbn[i];
            y++;
         }
    }
    if(y==1)
    cout<<"\nNot present";
    else
    {
        cout<<"\nDo you want to buy from above (Y/N) : ";
        cin>>u;
        if(u=='Y'||u=='y')
        {
        cout<<"\nWhich book you want to buy , enter it's S.No. from above : ";
        cin>>p;
        cout<<"#Copies you want to order = ";
        cin>>b;
        cout<<"\n"<<b<<" copies of "<<title[ind_store[p]]<<" ordered ";
        cout<<"\nEarlier count : "<<cnt[ind_store[p]];
        a = b + cnt[ind_store[p]];
        cout<<"\n Current Count = "<<a;
        }
    }
} 

/*************************************************************Buying Over*********************************************************************/

int main()
{
    cout<<"\n~~~~~~~~~~~~~~~~~~~ Question 2 : IIIT-D Libarary & Other Libraries ~~~~~~~~~~~~~~~~~~~";
    books b;
    magazine m;
    b.loadBooks("books.csv");
    m.readmagazines(); // 1(i) reading
    int n;
    char ch = 'y',r;
 while(ch=='y'||ch=='Y')
  {
    cout<<"\n1.Search\n2.Issue\n3.Register\n4.Purchase\n5.Exit\nIf you aren't registred , first register\nYour Choice : ";
    cin>>n;
    switch(n)
    {
        case 1:     //search 1(iii)
        char c,t;
        cout<<"\nMagazine (press M) or Book (press B) : ";
        cin>>t;
        if(t=='B')
        {
        cout<<"\nSearch by author (press A) / ISBN (press I) / Title (press T) : ";
        cin>>c;
         if(c=='A')
        {
        string substring;
        cout << "\nEnter the author to search for: ";
        cin >> substring;
        by_author(substring);
        }

        else if(c=='I')
        {
        string substring;
        cout << "\nEnter the ISBN to search for: ";
        cin >> substring;
        by_ISBN(substring);
        }
         
        else if(c=='T')
        {
        string substring;
        cout << "\nEnter the title to search for: ";
        cin >> substring;
        by_title(substring);
        } 
        else
        cout<<"\nWrong Choice";
        }

        else if(t=='M')
        {
        string substring;
        cout << "\nEnter the publication to search for: ";
        cin >> substring;
        by_mtitle(substring);
        }

        else
        cout<<"\nWrong Choice";

        break;


        case 2:     //issue 1(ii)
        int i,k;
        char c1;
        cout<<"\nEnter id : ";
        cin>>i;
        k = check(i);
        if(k==0)
              cout<<"\nNot registered,fisrt register then issue";
        else
         {
          if(i<6000)
          cout<<"\nYou are student , items will be issued for 1 month";
          else if(i>=6000)
          cout<<"\nYou are faculty , items will be issued for 6 months";
          cout<<"\nWhat you want - Book(B) or Magazine(M) : ";
          cin>>c1;
          if(c1=='B')
          b_issue();
          else if(c1=='M')
          m_issue();
          else
          cout<<"\nWrong choice";
         }
        break;

        case 3:     //register 1(iv)
         cout<<"\nS -> Student , F -> Faculty : "; 
         cin>>r;
         reg(r);
         break;

        case 4:     //buy 1(v)
        char C;
        cout<<"\nSearch by author (press A) / ISBN (press I) / Title (press T) : ";
        cin>>C;
         if(C=='A')
        {
        string substring;
        cout << "\nEnter the author to search for: ";
        cin >> substring;
        buy_author(substring);
        }

        else if(C=='I')
        {
        string substring;
        cout << "\nEnter the ISBN to search for: ";
        cin >> substring;
        buy_isbn(substring);
        }
         
        else if(C=='T')
        {
        string substring;
        cout << "\nEnter the title to search for: ";
        cin >> substring;
        buy_title(substring);
        } 
        else
        cout<<"\nWrong Choice";
        
        break;
          
        case 5:
        exit(0);

        default:
        cout<<"\nWrong choice";
    }
    cout<<"\n\nDo you want more(Y/N): ";
    cin>>ch;
  }
    return 0;
}
