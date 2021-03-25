/*create.sql
  dgrim*/


DROP SCHEMA Lab1 CASCADE;
CREATE SCHEMA Lab1;


CREATE TABLE Shoppers(
	shopperID INTEGER,
	shopperName VARCHAR(40),
	address VARCHAR(60),
	joinDate DATE,
	status CHAR(1),

	PRIMARY KEY(shopperID)
);

CREATE TABLE Products(
	productID INTEGER,
	productName VARCHAR(40), 
	manufacturer VARCHAR(40), 
	regularPrice NUMERIC(5,2),

	PRIMARY KEY(productID)
);

CREATE TABLE Markets(
	marketID INTEGER, 
	address VARCHAR(60), 
	managerID INTEGER, 
	numCheckstands INTEGER,

	PRIMARY KEY(marketID)
);

CREATE TABLE Employees(
	empID INTEGER, 
	empName VARCHAR(40), 
	marketID INTEGER, 
	hireDate DATE, 
	level CHAR(1), 
	stillEmployed BOOLEAN,

	FOREIGN KEY(marketID) REFERENCES Markets(marketID),
	PRIMARY KEY(empID)
);

CREATE TABLE ShoppingTrips(
	shopperID INTEGER, 
	tripTimestamp TIMESTAMP, 
	marketID INTEGER, 
	checkStand INTEGER, 
	checkerID INTEGER,
    payType CHAR(1), 
    paymentValid BOOLEAN,

    FOREIGN KEY(shopperID) REFERENCES Shoppers(shopperID),
    FOREIGN KEY(marketID) REFERENCES Markets(marketID),
    FOREIGN KEY(checkerID) REFERENCES Employees(empID),
    PRIMARY KEY(shopperID, tripTimestamp)
);

CREATE TABLE Purchases(
	shopperID INTEGER, 
	tripTimestamp TIMESTAMP, 
	productID INTEGER, 
	quantity INTEGER, 
	paidPrice NUMERIC(5,2),
	
	FOREIGN KEY(shopperID, tripTimestamp) REFERENCES ShoppingTrips(shopperID, tripTimestamp),
	FOREIGN KEY(productID) REFERENCES Products(productID),
	PRIMARY KEY(shopperID, tripTimestamp, productID)
);
