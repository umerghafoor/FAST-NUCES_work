# Rawalpindi-Stadium

Write a C++ program for a company that is planning to sell e-tickets for PSL-5 matches being
held in Rawalpindi Cricket Stadium (RCS). 

The map of the seating enclosures is shown below.
Each of the enclosures has the following maximum capacity:
● Imran Khan enclosure: Max 1000 seats.
● Javed Miandad enclosure: Max 1000 seats.
● Javed Akhter enclosure: Max 1000 seats.
● Azhar Mehmood enclosure: Max 1000 seats.
● Sohail Tanveer enclosure: Max 3000 seats.
● Shoaib Akhtar enclosure: Max 3000 seats.
● Imran Buksh enclosure: Max 2500 seats.
● Yasir Arafat enclosure: Max 2500 seats.
Here is the list of all ticket prices for night matches in Rawalpindi Cricket Stadium.
● 27 February 2020 | Islamabad United v Quetta Gladiators (7 pm-10.15 pm)
(VIP – Rs. 3000, Premium – Rs. 1500, First-class – Rs. 1000, General – Rs. 500)
Programming Fundamentals – Assignment 2 (Fall 2022)
● 28 February 2020 | Peshawar Zalmi v Lahore Qalandars (7 pm-10.15 pm)
(VIP – Rs. 3000, Premium – Rs. 1500, First-class – Rs. 1000, General – Rs. 500)
● 29 February 2020 | Islamabad United v Peshawar Zalmi (7 pm-10.15 pm)
(VIP – Rs. 3000, Premium – Rs. 1500, First-class – Rs. 1000, General – Rs. 500)
● 1 March 2020 | Islamabad United v Karachi Kings (7 pm-10.15 pm)
(VIP – Rs. 2000, Premium – Rs. 1000, First-class – Rs. 500, General – Rs. 250)
● 2 March 2020 | Peshawar Zalmi v Karachi Kings (7 pm-10.15 pm)
(VIP – Rs. 1500, Premium – Rs. 1000, First-class – Rs. 500, General – Rs. 250)
● 5 March 2020 | Peshawar Zalmi v Quetta Gladiators (7 pm-10.15 pm)
(VIP – Rs. 1500, Premium – Rs. 1000, First-class – Rs. 500, General – Rs. 250)
Here is the list of all ticket prices for day matches in Rawalpindi Cricket Stadium.
● 7 March 2020 | Peshawar Zalmi v Islamabad United (2 pm-5.15 pm)
(VIP – Rs. 2000, Premium – Rs. 1000, First-class – Rs. 500, General – Rs. 250)
● 8 March 2020 | Multan Sultans v Islamabad United (2 pm-5.15 pm)
(VIP – Rs. 1500, Premium – Rs. 1000, First-class – Rs. 500, General – Rs. 250)
The program should start by displaying a menu listing the schedule of matches in the
stadium.
1. 27 Feb 2020 – Islamabad United v Quetta Gladiators, Pindi Cricket Stadium
(7pm-10.15pm)
2. 28 Feb 2020 – Peshawar Zalmi v Lahore Qalandars, Pindi Cricket Stadium
(8pm-11.15pm)
3. 29 Feb 2020 – Islamabad United v Peshawar Zalmi, Pindi Cricket Stadium
(7pm-10.15pm)
4. 1 Mar 2020 – Islamabad United v Karachi Kings, Pindi Cricket Stadium
(7pm-10.15pm)
5. 2 Mar 2020 – Peshawar Zalmi v Karachi Kings, Pindi Cricket Stadium
(7pm-10.15pm)
6. 5 Mar 2020 – Peshawar Zalmi v Quetta Gladiators, Pindi Cricket Stadium
(7pm-10.15pm)
7. 7 Mar 2020 – Peshawar Zalmi v Islamabad United, Pindi Cricket Stadium
(2pm-5.15pm)
8. 8 Mar 2020 – Multan Sultans v Islamabad United, Pindi Cricket Stadium
(2pm-5.15pm)
Enter your choice (1 - 8)
When a user selects one of the above options, a sub-menu is shown listing names of all the
enclosures, their class, ticket price and number of seats available . The available seats are
randomly generated for each enclosure within its range of maximum capacity. When the
user selects one of the enclosures in the sub-menu, the programs prompts the user if he/she
Programming Fundamentals – Assignment 2 (Fall 2022)
wishes to buy tickets for a family. In case, the family option is selected - the user is prompted
to enter the required number of adult and children tickets, his/her CNIC number (maximum
4 adults, and 5 children). If the family option is not selected, the user is prompted to enter
the required number of adult tickets, his/her CNIC number (maximum 8 adults). To attract
more spectators, the company is giving discounts for groups and children. If the user selects
family option or enters adult tickets greater than four, 10% rebate is given on all adult
tickets. A child ticket is given 20% rebate. The program finally displays the total amount due.
You have to write this program using switch statements primarily. Hint: For one and two-way
selections (e.g. input validations), you are allowed (and encouraged) to use if statements.
