/*Rwalpindi stadium code*/

#include<iostream>
#include<time.h>
#include<cstdlib>
using namespace std;
int main()
{
	int a;
	int b;
	int c,d,e;
	int adult, cnic;
	int child;
	int seats;
	int random;
	float price, priceC, priceA;
cout<<"1. 27 Feb 2020  Islamabad United v Quetta Gladiators, Pindi Cricket Stadium (7pm-10.15pm)"<<endl;
cout<<"2. 28 Feb 2020  Peshawar Zalmi v Lahore Qalandars, Pindi Cricket Stadium (8pm-11.15pm)"<<endl;
cout<<"3. 29 Feb 2020  Islamabad United v Peshawar Zalmi, Pindi Cricket Stadium (7pm-10.15pm)"<<endl;
cout<<"4. 1 Mar 2020   Islamabad United v Karachi Kings, Pindi Cricket Stadium (7pm-10.15pm)"<<endl;
cout<<"5. 2 Mar 2020   Peshawar Zalmi v Karachi Kings, Pindi Cricket Stadium (7pm-10.15pm)"<<endl;
cout<<"6. 5 Mar 2020   Peshawar Zalmi v Quetta Gladiators, Pindi Cricket Stadium (7pm-10.15pm)"<<endl;
cout<<"7. 7 Mar 2020   Peshawar Zalmi v Islamabad United, Pindi Cricket Stadium (2pm-5.15pm)"<<endl;
cout<<"8. 8 Mar 2020   Multan Sultans v Islamabad United, Pindi Cricket Stadium (2pm-5.15pm)"<<endl;
cin>>a;

if(a==1 ){
	cout<<"1. Imran Khan enclosure: Max 1000 seats."<<endl;
    cout<<"2. Javed Miandad enclosure: Max 1000 seats."<<endl;
    cout<<"3. Javed Akhter enclosure: Max 1000 seats."<<endl;
    cout<<"4. Azhar Mehmood enclosure: Max 1000 seats."<<endl;
    cout<<"5. Sohail Tanveer enclosure: Max 3000 seats."<<endl;
    cout<<"6. Shoaib Akhtar enclosure: Max 3000 seats."<<endl;
    cout<<"7. Imran Buksh enclosure: Max 2500 seats."<<endl;
    cout<<"8. Yasir Arafat enclosure: Max 2500 seats."<<endl;
    cout<<"------------------------------------------------"<<endl;
    cin>>b;
    if(b==1 || b==2 || b==3 || b==4)
{   srand(time(0));
    random = rand() % 1000;
    srand(time(0));}
    if(b==5 || b==6)
{   srand(time(0));
    random = rand() % 3000;
    srand(time(0));}
    if(b==7 || b==8)
{   srand(time(0));
    random = rand() % 2500;
    srand(time(0));}
	switch(1)
	{

	    /*Master 1*/


	case 1:
    cout<<"27 February 2020 | Islamabad United v Quetta Gladiators (7 pm-10.15 pm)"<<endl;
    cout<<" 1. VIP =Rs. 3000         "<<endl;
    cout<<" 2. Premium =Rs. 1500     "<<endl;
	cout<<" 3. First-class =Rs. 1000 "<<endl;
	cout<<" 4. General =Rs. 500      "<<endl;
	cout<<" Number of seats available are "<<random<<endl;
    cout<<" Which ticket? ";
	cin>>c;

	switch(c)
	{
	    //VIP

	    case 1:
	    price=3000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

	      //premium

    case 2:
	  {price=1500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;}

		      //first class

    case 3:
	    price=1000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //General

    case 4:
	    price=500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;}

	}
	}








	if(a==2 ){
	cout<<"1. Imran Khan enclosure: Max 1000 seats."<<endl;
    cout<<"2. Javed Miandad enclosure: Max 1000 seats."<<endl;
    cout<<"3. Javed Akhter enclosure: Max 1000 seats."<<endl;
    cout<<"4. Azhar Mehmood enclosure: Max 1000 seats."<<endl;
    cout<<"5. Sohail Tanveer enclosure: Max 3000 seats."<<endl;
    cout<<"6. Shoaib Akhtar enclosure: Max 3000 seats."<<endl;
    cout<<"7. Imran Buksh enclosure: Max 2500 seats."<<endl;
    cout<<"8. Yasir Arafat enclosure: Max 2500 seats."<<endl;
    cout<<"------------------------------------------------"<<endl;
    cin>>b;
    if(b==1 || b==2 || b==3 || b==4)
{   srand(time(0));
    random = rand() % 1000;
    srand(time(0));}
    if(b==5 || b==6)
{   srand(time(0));
    random = rand() % 3000;
    srand(time(0));}
    if(b==7 || b==8)
{   srand(time(0));
    random = rand() % 2500;
    srand(time(0));}
	switch(1)
	{

	    /*Master 1*/


	case 1:
    cout<<"28 February 2020 | Peshawar Zalmi v Lahore Qalandars (7 pm-10.15 pm)"<<endl;
    cout<<" 1. VIP =Rs. 3000         "<<endl;
    cout<<" 2. Premium =Rs. 1500     "<<endl;
	cout<<" 3. First-class =Rs. 1000 "<<endl;
	cout<<" 4. General =Rs. 500      "<<endl;
	cout<<" Number of seats available are "<<random<<endl;
    cout<<" Which ticket? ";
	cin>>c;

	switch(c)
	{
	    //VIP

	    case 1:
	    price=3000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

	      //premium

    case 2:
	    price=1500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //first class

    case 3:
	    price=1000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //General

    case 4:
	    price=500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;}

	}
	}





	if(a==3 ){
	cout<<"1. Imran Khan enclosure: Max 1000 seats."<<endl;
    cout<<"2. Javed Miandad enclosure: Max 1000 seats."<<endl;
    cout<<"3. Javed Akhter enclosure: Max 1000 seats."<<endl;
    cout<<"4. Azhar Mehmood enclosure: Max 1000 seats."<<endl;
    cout<<"5. Sohail Tanveer enclosure: Max 3000 seats."<<endl;
    cout<<"6. Shoaib Akhtar enclosure: Max 3000 seats."<<endl;
    cout<<"7. Imran Buksh enclosure: Max 2500 seats."<<endl;
    cout<<"8. Yasir Arafat enclosure: Max 2500 seats."<<endl;
    cout<<"------------------------------------------------"<<endl;
    cin>>b;
    if(b==1 || b==2 || b==3 || b==4)
{   srand(time(0));
    random = rand() % 1000;
    srand(time(0));}
    if(b==5 || b==6)
{   srand(time(0));
    random = rand() % 3000;
    srand(time(0));}
    if(b==7 || b==8)
{   srand(time(0));
    random = rand() % 2500;
    srand(time(0));}
	switch(1)
	{

	    /*Master 1*/


	case 1:
    cout<<"29 February 2020 | Islamabad United v Peshawar Zalmi (7 pm-10.15 pm)"<<endl;
    cout<<" 1. VIP =Rs. 3000         "<<endl;
    cout<<" 2. Premium =Rs. 1500     "<<endl;
	cout<<" 3. First-class =Rs. 1000 "<<endl;
	cout<<" 4. General =Rs. 500      "<<endl;
	cout<<" Number of seats available are "<<random<<endl;
    cout<<" Which ticket? ";
	cin>>c;

	switch(c)
	{
	    //VIP

	    case 1:
	    price=3000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

	      //premium

    case 2:
	    price=1500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //first class

    case 3:
	    price=1000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //General

    case 4:
	    price=500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;}

	}
	}




	if(a==4 ){
	cout<<"1. Imran Khan enclosure: Max 1000 seats."<<endl;
    cout<<"2. Javed Miandad enclosure: Max 1000 seats."<<endl;
    cout<<"3. Javed Akhter enclosure: Max 1000 seats."<<endl;
    cout<<"4. Azhar Mehmood enclosure: Max 1000 seats."<<endl;
    cout<<"5. Sohail Tanveer enclosure: Max 3000 seats."<<endl;
    cout<<"6. Shoaib Akhtar enclosure: Max 3000 seats."<<endl;
    cout<<"7. Imran Buksh enclosure: Max 2500 seats."<<endl;
    cout<<"8. Yasir Arafat enclosure: Max 2500 seats."<<endl;
    cout<<"------------------------------------------------"<<endl;
    cin>>b;
    if(b==1 || b==2 || b==3 || b==4)
{   srand(time(0));
    random = rand() % 1000;
    srand(time(0));}
    if(b==5 || b==6)
{   srand(time(0));
    random = rand() % 3000;
    srand(time(0));}
    if(b==7 || b==8)
{   srand(time(0));
    random = rand() % 2500;
    srand(time(0));}
	switch(1)
	{

	    /*Master 1*/


	case 1:
    cout<<"1 March 2020 | Islamabad United v Karachi Kings (7 pm-10.15 pm)"<<endl;
    cout<<" 1. VIP =Rs. 2000         "<<endl;
    cout<<" 2. Premium =Rs. 1000     "<<endl;
	cout<<" 3. First-class =Rs. 500 "<<endl;
	cout<<" 4. General =Rs. 250      "<<endl;
	cout<<" Number of seats available are "<<random<<endl;
    cout<<" Which ticket? ";
	cin>>c;

	switch(c)
	{
	    //VIP

	    case 1:
	    price=2000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

	      //premium

    case 2:
	    price=1000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //first class

    case 3:
	    price=500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //General

    case 4:
	    price=250;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;}

	}
	}




	if(a==5 ){
	cout<<"1. Imran Khan enclosure: Max 1000 seats."<<endl;
    cout<<"2. Javed Miandad enclosure: Max 1000 seats."<<endl;
    cout<<"3. Javed Akhter enclosure: Max 1000 seats."<<endl;
    cout<<"4. Azhar Mehmood enclosure: Max 1000 seats."<<endl;
    cout<<"5. Sohail Tanveer enclosure: Max 3000 seats."<<endl;
    cout<<"6. Shoaib Akhtar enclosure: Max 3000 seats."<<endl;
    cout<<"7. Imran Buksh enclosure: Max 2500 seats."<<endl;
    cout<<"8. Yasir Arafat enclosure: Max 2500 seats."<<endl;
    cout<<"------------------------------------------------"<<endl;
    cin>>b;
    if(b==1 || b==2 || b==3 || b==4)
{   srand(time(0));
    random = rand() % 1000;
    srand(time(0));}
    if(b==5 || b==6)
{   srand(time(0));
    random = rand() % 3000;
    srand(time(0));}
    if(b==7 || b==8)
{   srand(time(0));
    random = rand() % 2500;
    srand(time(0));}
	switch(1)
	{

	    /*Master 1*/


	case 1:
    cout<<"2 March 2020 | Peshawar Zalmi v Karachi Kings (7 pm-10.15 pm)"<<endl;
    cout<<" 1. VIP =Rs. 1500         "<<endl;
    cout<<" 2. Premium =Rs. 1000     "<<endl;
	cout<<" 3. First-class =Rs. 500 "<<endl;
	cout<<" 4. General =Rs. 250      "<<endl;
	cout<<" Number of seats available are "<<random<<endl;
    cout<<" Which ticket? ";
	cin>>c;

	switch(c)
	{
	    //VIP

	    case 1:
	    price=1500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

	      //premium

    case 2:
	    price=1000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //first class

    case 3:
	    price=500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //General

    case 4:
	    price=250;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;}

	}
	}





	if(a==6 ){
	cout<<"1. Imran Khan enclosure: Max 1000 seats."<<endl;
    cout<<"2. Javed Miandad enclosure: Max 1000 seats."<<endl;
    cout<<"3. Javed Akhter enclosure: Max 1000 seats."<<endl;
    cout<<"4. Azhar Mehmood enclosure: Max 1000 seats."<<endl;
    cout<<"5. Sohail Tanveer enclosure: Max 3000 seats."<<endl;
    cout<<"6. Shoaib Akhtar enclosure: Max 3000 seats."<<endl;
    cout<<"7. Imran Buksh enclosure: Max 2500 seats."<<endl;
    cout<<"8. Yasir Arafat enclosure: Max 2500 seats."<<endl;
    cout<<"------------------------------------------------"<<endl;
    cin>>b;
    if(b==1 || b==2 || b==3 || b==4)
{   srand(time(0));
    random = rand() % 1000;
    srand(time(0));}
    if(b==5 || b==6)
{   srand(time(0));
    random = rand() % 3000;
    srand(time(0));}
    if(b==7 || b==8)
{   srand(time(0));
    random = rand() % 2500;
    srand(time(0));}
	switch(1)
	{

	    /*Master 1*/


	case 1:
    cout<<"5 March 2020 | Peshawar Zalmi v Quetta Gladiators (7 pm-10.15 pm)"<<endl;
    cout<<" 1. VIP =Rs. 1500         "<<endl;
    cout<<" 2. Premium =Rs. 1000     "<<endl;
	cout<<" 3. First-class =Rs. 500 "<<endl;
	cout<<" 4. General =Rs. 250      "<<endl;
	cout<<" Number of seats available are "<<random<<endl;
    cout<<" Which ticket? ";
	cin>>c;

	switch(c)
	{
	    //VIP

	    case 1:
	    price=1500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

	      //premium

    case 2:
	    price=1000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //first class

    case 3:
	    price=500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //General

    case 4:
	    price=250;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;}

	}
	}





	if(a==7 ){
	cout<<"1. Imran Khan enclosure: Max 1000 seats."<<endl;
    cout<<"2. Javed Miandad enclosure: Max 1000 seats."<<endl;
    cout<<"3. Javed Akhter enclosure: Max 1000 seats."<<endl;
    cout<<"4. Azhar Mehmood enclosure: Max 1000 seats."<<endl;
    cout<<"5. Sohail Tanveer enclosure: Max 3000 seats."<<endl;
    cout<<"6. Shoaib Akhtar enclosure: Max 3000 seats."<<endl;
    cout<<"7. Imran Buksh enclosure: Max 2500 seats."<<endl;
    cout<<"8. Yasir Arafat enclosure: Max 2500 seats."<<endl;
    cout<<"------------------------------------------------"<<endl;
    cin>>b;
    if(b==1 || b==2 || b==3 || b==4)
{   srand(time(0));
    random = rand() % 1000;
    srand(time(0));}
    if(b==5 || b==6)
{   srand(time(0));
    random = rand() % 3000;
    srand(time(0));}
    if(b==7 || b==8)
{   srand(time(0));
    random = rand() % 2500;
    srand(time(0));}
	switch(1)
	{

	    /*Master 1*/


	case 1:
    cout<<" 7 March 2020 | Peshawar Zalmi v Islamabad United (2 pm-5.15 pm)"<<endl;
    cout<<" 1. VIP =Rs. 2000         "<<endl;
    cout<<" 2. Premium =Rs. 1000     "<<endl;
	cout<<" 3. First-class =Rs. 500 "<<endl;
	cout<<" 4. General =Rs. 250      "<<endl;
	cout<<" Number of seats available are "<<random<<endl;
    cout<<" Which ticket? ";
	cin>>c;

	switch(c)
	{
	    //VIP

	    case 1:
	    price=2000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

	      //premium

    case 2:
	    price=1000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //first class

    case 3:
	    price=500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //General

    case 4:
	    price=250;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;}

	}
	}




	if(a==8 ){
	cout<<"1. Imran Khan enclosure: Max 1000 seats."<<endl;
    cout<<"2. Javed Miandad enclosure: Max 1000 seats."<<endl;
    cout<<"3. Javed Akhter enclosure: Max 1000 seats."<<endl;
    cout<<"4. Azhar Mehmood enclosure: Max 1000 seats."<<endl;
    cout<<"5. Sohail Tanveer enclosure: Max 3000 seats."<<endl;
    cout<<"6. Shoaib Akhtar enclosure: Max 3000 seats."<<endl;
    cout<<"7. Imran Buksh enclosure: Max 2500 seats."<<endl;
    cout<<"8. Yasir Arafat enclosure: Max 2500 seats."<<endl;
    cout<<"------------------------------------------------"<<endl;
    cin>>b;
    if(b==1 || b==2 || b==3 || b==4)
{   srand(time(0));
    random = rand() % 1000;
    srand(time(0));}
    if(b==5 || b==6)
{   srand(time(0));
    random = rand() % 3000;
    srand(time(0));}
    if(b==7 || b==8)
{   srand(time(0));
    random = rand() % 2500;
    srand(time(0));}
	switch(1)
	{

	    /*Master 1*/


	case 1:
    cout<<"8 March 2020 | Multan Sultans v Islamabad United (2 pm-5.15 pm)"<<endl;
    cout<<" 1. VIP =Rs. 1500         "<<endl;
    cout<<" 2. Premium =Rs. 1000     "<<endl;
	cout<<" 3. First-class =Rs. 500 "<<endl;
	cout<<" 4. General =Rs. 250      "<<endl;
	cout<<" Number of seats available are "<<random<<endl;
    cout<<" Which ticket? ";
	cin>>c;

	switch(c)
	{
	    //VIP

	    case 1:
	    price=1500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

	      //premium

    case 2:
	    price=1000;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //first class

    case 3:
	    price=500;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;

		      //General

    case 4:
	    price=250;
      cout<<"1:Family options"<<endl;
      cout<<"2:Adult options"<<endl;
	  cin>>d;
    switch(d)
	    {
		case 1:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter child  : ";cin>>child;

		cout<<"Enter CNIC : ";cin>>cnic;
		if(adult>4) priceA=(0.9*price)*adult;
		if(child>5) priceC=(0.8*price)*adult;
		else priceA=price*(adult+child);break;
        case 2:
	    cout<<"Enter adults : ";cin>>adult;
		cout<<"Enter CNIC   : ";cin>>cnic;
        priceA=(price)*adult;
        break;
	}break;}

	}
	}



      cout<<"The final price for your match seats are : "<<(priceA+priceC)<<endl;
}
