
/*--Each manager (managerID) in the Markets table must appear in the Employees table as an empID.
	(Explanation of what that means appear in the above paragraph.) If an Employees tuple is deleted and
	there is a Markets that refers to that employee, then the deletion should be rejected. Also, if the
	Primary Key of an Employees tuple is updated, and there is a market whose manager corresponds to
	that person, then the update should also be rejected.*/
-------------------------------------------------------------------------
ALTER TABLE Markets
	ADD CONSTRAINT marketsFK FOREIGN KEY(managerID)
	REFERENCES Employees(empID);

-------------------------------------------------------------------------


/*Each market (marketID) that’s in the Employees table must appear in the Markets table as a marketID.
If a tuple in the Markets table is deleted, then all Employees in which that market (marketID) appears
should also be deleted. If the Primary Key (marketID) of a Markets tuple is updated, then all
Employees tuples who have that marketID should also be updated, getting the same new value for their
marketID.*/
-------------------------------------------------------------------------
ALTER TABLE Employees
	ADD CONSTRAINT employeesFK FOREIGN KEY(marketID)
	REFERENCES Markets(marketID)
	ON DELETE CASCADE
	ON UPDATE CASCADE;
-------------------------------------------------------------------------



/*Each market (marketID) that’s in the ShoppingTrips table must either be NULL or appear in the
Markets table as a marketID. If a tuple in the Markets table is deleted, then the marketID for all tuples
in the ShoppingTrips table which match that marketID should be set to NULL. If the Primary Key
(marketID) of a Markets tuple is updated, then all ShoppingTrips tuples that have the corresponding
marketID should also be updated, getting the same new value for their marketID.*/
-------------------------------------------------------------------------
ALTER TABLE ShoppingTrips
	ADD CONSTRAINT shoppingtripsFK FOREIGN KEY (marketID)
	REFERENCES Markets(marketID)
	ON DELETE SET NULL
	ON UPDATE CASCADE;
-------------------------------------------------------------------------