## Inventory System
An inventory system of laboratory equipments using File Handling in C as the storage.

•	with 3 types of users. 
  o	(admin) (manages the account and the equipment) (Add, Remove, Edit of the Users and Equipment)
  o	Staff (approves borrowing and return of items as per request of the User)
  o	Ordinary User (Borrows and return the item ---> applies through the system)

### Process
  Administrator
  •	There already exist a pre-defined administrator 
  •	Administrator can login and change password
  •	Administrator will manage all accounts
  •	Administrator will manage the equipment
  
  Ordinary Users(OU):
  1.	User will register as Ordinary User
  2.	The OU can login only when the administrator approves the registration or the accounts is enabled.
  3.	OU can browse on all the available equipment
  4.	OU can borrow equipment
  5.	OU can return equipment
  
  Staff
  1.	Staff can login if account was already created and enabled
  2.	Staff can view all request for borrowing
  3.	Staff can view all request for return
  4.	Staff can approve and disapprove request for borrowing
  5.	Staff can approve return of equipment
  6.	Staff can deny return of equipment if damaged()
